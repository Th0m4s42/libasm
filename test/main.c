#include <errno.h>
#include <fcntl.h>
#include <libasm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Couleurs
#define GREEN	"\033[0;32m"
#define RED		"\033[0;31m"
#define RESET	"\033[0m"

// Macro de test
#define TEST(name, c_result, asm_result)		\
	if ((c_result) == (asm_result))				\
		printf(GREEN "[OK] " RESET name "\n");	\
	else										\
		printf(RED "[KO] " RESET name 			\
			" | C: %zu | ASM: %zu\n", (size_t)c_result, (size_t)asm_result);

// Macro pour comparer des strings (résultat de strcpy/strdup)
#define TEST_STR(name, c_result, asm_result)						\
	if (strcmp((c_result), (asm_result)) == 0)						\
		printf(GREEN "[OK] " RESET name " -> \"%s\"\n", asm_result);\
	else															\
		printf(RED "[KO] " RESET name								\
			" | C: \"%s\" | ASM: \"%s\"\n", c_result, asm_result);


// Macro pour strcmp : compare les SIGNES, pas les valeurs exactes
#define TEST_CMP(name, c_result, asm_result)				\
	if (((c_result) < 0 && (asm_result) < 0) ||				\
		((c_result) > 0 && (asm_result) > 0) ||				\
		((c_result) == 0 && (asm_result) == 0))				\
		printf(GREEN "[OK] " RESET name						\
			" | C: %d | ASM: %d\n", c_result, asm_result);	\
	else													\
		printf(RED "[KO] " RESET name						\
			" | C: %d | ASM: %d\n", c_result, asm_result);

// Macro pour tester write/read : compare valeur de retour ET errno
#define TEST_IO(name, c_ret, c_err, asm_ret, asm_err)				\
	if ((c_ret) == (asm_ret) && (c_err) == (asm_err))				\
		printf(GREEN "[OK] " RESET name								\
			" | ret: %zd | errno: %d\n", (ssize_t)asm_ret, asm_err);\
	else															\
		printf(RED "[KO] " RESET name								\
			" | C: ret=%zd errno=%d | ASM: ret=%zd errno=%d\n",		\
			(ssize_t)c_ret, c_err, (ssize_t)asm_ret, asm_err);

int main(void)
{
	setbuf(stdout, NULL);
	printf("\n===== ft_strlen =====\n");

	// Cas normaux
	TEST("hello",		strlen("hello"),		ft_strlen("hello"));
	TEST("empty",		strlen(""),				ft_strlen(""));
	TEST("one char",	strlen("a"),			ft_strlen("a"));
	TEST("long string",	strlen("Hello World"),	ft_strlen("Hello World"));

	// Cas avec espaces / caractères spéciaux
	TEST("spaces",		strlen("   "),			ft_strlen("   "));
	TEST("newline",		strlen("a\nb"),			ft_strlen("a\nb"));

	printf("\n===== ft_strcpy =====\n");
	
	char dst_c[100];
	char dst_asm[100];
	
	// Cas normaux
	strcpy(dst_c, "hello");
	ft_strcpy(dst_asm, "hello");
	TEST_STR("hello", dst_c, dst_asm);
	
	strcpy(dst_c, "");
	ft_strcpy(dst_asm, "");
	TEST_STR("empty", dst_c, dst_asm);
	
	strcpy(dst_c, "Hello World 42!");
	ft_strcpy(dst_asm, "Hello World 42!");
	TEST_STR("long string", dst_c, dst_asm);
	
	strcpy(dst_c, "a");
	ft_strcpy(dst_asm, "a");
	TEST_STR("one char", dst_c, dst_asm);
	
	strcpy(dst_c, "with\nnewline\there");
	ft_strcpy(dst_asm, "with\nnewline\there");
	TEST_STR("special chars", dst_c, dst_asm);
	
	// Vérifier que strcpy retourne bien dst
	char buf[50];
	char *ret = ft_strcpy(buf, "return test");

	if (ret == buf)
		printf(GREEN "[OK] " RESET "return value == dst\n");
	else
		printf(RED "[KO] " RESET "return value != dst\n");

	printf("\n===== ft_strcmp =====\n");

	// Égalité
	TEST_CMP("equal strings",	strcmp("hello", "hello"),	ft_strcmp("hello", "hello"));
	TEST_CMP("both empty",		strcmp("", ""),				ft_strcmp("", ""));
	TEST_CMP("one char equal",	strcmp("a", "a"),			ft_strcmp("a", "a"));

	// s1 < s2
	TEST_CMP("abc vs abd",		strcmp("abc", "abd"),		ft_strcmp("abc", "abd"));
	TEST_CMP("a vs b",			strcmp("a", "b"),			ft_strcmp("a", "b"));
	TEST_CMP("empty vs hello",	strcmp("", "hello"),		ft_strcmp("", "hello"));

	// s1 > s2
	TEST_CMP("abd vs abc",		strcmp("abd", "abc"),		ft_strcmp("abd", "abc"));
	TEST_CMP("b vs a",			strcmp("b", "a"),			ft_strcmp("b", "a"));
	TEST_CMP("hello vs empty",	strcmp("hello", ""),		ft_strcmp("hello", ""));

	// Longueurs différentes (préfixe)
	TEST_CMP("hello vs hello!",	strcmp("hello", "hello!"),	ft_strcmp("hello", "hello!"));
	TEST_CMP("hello! vs hello",	strcmp("hello!", "hello"),	ft_strcmp("hello!", "hello"));

	// Caractères spéciaux / signed vs unsigned
	TEST_CMP("\\x7f vs \\x80",	strcmp("\x7f", "\x80"),		ft_strcmp("\x7f", "\x80"));
	TEST_CMP("ascii high",		strcmp("é", "e"),			ft_strcmp("é", "e"));

	printf("\n===== ft_write =====\n");
	
	ssize_t c_ret, asm_ret;
	int c_err, asm_err;

	// --- Cas normal : écrire sur stdout ---
	printf("[C  ] ");
	errno = 0;
	c_ret = write(1, "hello\n", 6);
	c_err = errno;

	printf("[ASM] ");
	errno = 0;
	asm_ret = ft_write(1, "hello\n", 6);
	asm_err = errno;
	TEST_IO("write stdout", c_ret, c_err, asm_ret, asm_err);

	// --- Écrire 0 octet ---
	errno = 0;
	c_ret = write(1, "", 0);
	c_err = errno;
	errno = 0;
	asm_ret = ft_write(1, "", 0);
	asm_err = errno;
	TEST_IO("write 0 bytes", c_ret, c_err, asm_ret, asm_err);

	// --- fd invalide (-1) → doit set errno = EBADF (9) ---
	errno = 0;
	c_ret = write(-1, "fail", 4);
	c_err = errno;
	errno = 0;
	asm_ret = ft_write(-1, "fail", 4);
	asm_err = errno;
	TEST_IO("write fd=-1 (EBADF)", c_ret, c_err, asm_ret, asm_err);

	// --- fd fermé ---
	errno = 0;
	c_ret = write(42, "fail", 4);
	c_err = errno;
	errno = 0;
	asm_ret = ft_write(42, "fail", 4);
	asm_err = errno;
	TEST_IO("write fd=42 (EBADF)", c_ret, c_err, asm_ret, asm_err);

	// --- buffer NULL avec fd valide → EFAULT ---
	errno = 0;
	c_ret = write(1, NULL, 10);
	c_err = errno;
	errno = 0;
	asm_ret = ft_write(1, NULL, 10);
	asm_err = errno;
	TEST_IO("write NULL buf (EFAULT)", c_ret, c_err, asm_ret, asm_err);

	printf("\n===== ft_read =====\n");

	char buf_c[100];
	char buf_asm[100];

	// --- Lire depuis un fichier valide ---
	// Crée un fichier de test
	int fd_w = open("/tmp/libasm_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd_w, "Hello libasm!", 13);
	close(fd_w);

	int fd_c = open("/tmp/libasm_test.txt", O_RDONLY);
	errno = 0;
	c_ret = read(fd_c, buf_c, 13);
	c_err = errno;
	buf_c[c_ret > 0 ? c_ret : 0] = '\0';
	close(fd_c);

	int fd_asm = open("/tmp/libasm_test.txt", O_RDONLY);
	errno = 0;
	asm_ret = ft_read(fd_asm, buf_asm, 13);
	asm_err = errno;
	buf_asm[asm_ret > 0 ? asm_ret : 0] = '\0';
	close(fd_asm);

	TEST_IO("read file", c_ret, c_err, asm_ret, asm_err);
	TEST_STR("read content", buf_c, buf_asm);

	// --- Lire 0 octet ---
	fd_c = open("/tmp/libasm_test.txt", O_RDONLY);
	errno = 0;
	c_ret = read(fd_c, buf_c, 0);
	c_err = errno;
	close(fd_c);

	fd_asm = open("/tmp/libasm_test.txt", O_RDONLY);
	errno = 0;
	asm_ret = ft_read(fd_asm, buf_asm, 0);
	asm_err = errno;
	close(fd_asm);
	TEST_IO("read 0 bytes", c_ret, c_err, asm_ret, asm_err);

	// --- fd invalide (-1) → EBADF ---
	errno = 0;
	c_ret = read(-1, buf_c, 10);
	c_err = errno;
	errno = 0;
	asm_ret = ft_read(-1, buf_asm, 10);
	asm_err = errno;
	TEST_IO("read fd=-1 (EBADF)", c_ret, c_err, asm_ret, asm_err);

	// --- fd non ouvert ---
	errno = 0;
	c_ret = read(42, buf_c, 10);
	c_err = errno;
	errno = 0;
	asm_ret = ft_read(42, buf_asm, 10);
	asm_err = errno;
	TEST_IO("read fd=42 (EBADF)", c_ret, c_err, asm_ret, asm_err);

	// --- buffer NULL → EFAULT ---
	fd_c = open("/tmp/libasm_test.txt", O_RDONLY);
	errno = 0;
	c_ret = read(fd_c, NULL, 10);
	c_err = errno;
	close(fd_c);

	fd_asm = open("/tmp/libasm_test.txt", O_RDONLY);
	errno = 0;
	asm_ret = ft_read(fd_asm, NULL, 10);
	asm_err = errno;
	close(fd_asm);
	TEST_IO("read NULL buf (EFAULT)", c_ret, c_err, asm_ret, asm_err);

	// Cleanup
	unlink("/tmp/libasm_test.txt");

// ========== ft_strdup ==========
	printf("\n===== ft_strdup =====\n");

	char *c_dup, *asm_dup;

	// --- Cas normal ---
	c_dup   = strdup("hello");
	asm_dup = ft_strdup("hello");
	TEST_STR("hello", c_dup, asm_dup);
	free(c_dup);
	free(asm_dup);

	// --- String vide ---
	c_dup   = strdup("");
	asm_dup = ft_strdup("");
	TEST_STR("empty", c_dup, asm_dup);
	free(c_dup);
	free(asm_dup);

	// --- Un seul caractère ---
	c_dup   = strdup("a");
	asm_dup = ft_strdup("a");
	TEST_STR("one char", c_dup, asm_dup);
	free(c_dup);
	free(asm_dup);

	// --- Longue string ---
	c_dup   = strdup("Hello World 42 libasm project!");
	asm_dup = ft_strdup("Hello World 42 libasm project!");
	TEST_STR("long string", c_dup, asm_dup);
	free(c_dup);
	free(asm_dup);

	// --- Caractères spéciaux ---
	c_dup   = strdup("with\nnewline\there");
	asm_dup = ft_strdup("with\nnewline\there");
	TEST_STR("special chars", c_dup, asm_dup);
	free(c_dup);
	free(asm_dup);

	// --- Pointeur différent de la source ---
	const char *src = "independent";
	asm_dup = ft_strdup(src);
	if (asm_dup != src && strcmp(asm_dup, src) == 0)
		printf(GREEN "[OK] " RESET "different pointer, same content\n");
	else
		printf(RED   "[KO] " RESET "pointer or content issue\n");
	free(asm_dup);

	// --- Indépendance mémoire (modif sans toucher l'original) ---
	const char *original = "modifiable";
	asm_dup = ft_strdup(original);
	asm_dup[0] = 'M';
	if (original[0] == 'm' && asm_dup[0] == 'M')
		printf(GREEN "[OK] " RESET "dup is writable & independent\n");
	else
		printf(RED   "[KO] " RESET "dup modification affected original\n");
	free(asm_dup);

	// --- Vérifier la longueur ---
	asm_dup = ft_strdup("length check");
	if (strlen(asm_dup) == 12)
		printf(GREEN "[OK] " RESET "correct length (12)\n");
	else
		printf(RED   "[KO] " RESET "wrong length: %zu\n", strlen(asm_dup));
	free(asm_dup);

	printf("\n");
	return (0);
}
