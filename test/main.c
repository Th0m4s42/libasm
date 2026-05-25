#include <stdio.h>
#include <string.h>
#include <libasm.h>

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
#define TEST_STR(name, c_result, asm_result)                        \
	if (strcmp((c_result), (asm_result)) == 0)                      \
		printf(GREEN "[OK] " RESET name " -> \"%s\"\n", asm_result);\
	else                                                            \
		printf(RED "[KO] " RESET name                               \
			" | C: \"%s\" | ASM: \"%s\"\n", c_result, asm_result);

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
	
	printf("\n");

	return (0);
}
