#include <libasm.h>
#include <stdio.h>
#include <string.h>

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
#define TEST_CMP(name, c_result, asm_result)							\
	if (((c_result) < 0 && (asm_result) < 0) ||							\
		((c_result) > 0 && (asm_result) > 0) ||							\
		((c_result) == 0 && (asm_result) == 0))							\
		printf(GREEN "[OK] " RESET name									\
			" | C: %d | ASM: %d\n", c_result, asm_result);				\
	else																\
		printf(RED "[KO] " RESET name									\
			" | C: %d | ASM: %d\n", c_result, asm_result);

int main(void)
{
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

	printf("\n");

	return (0);
}
