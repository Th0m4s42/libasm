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

	printf("\n");
	return (0);
}
