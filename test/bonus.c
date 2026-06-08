#include <libasm.h>
#include <stdio.h>
#include <stdlib.h>

// Helper pour afficher le résultat du test
static void print_test(const char *str, const char *base, int expected, int got)
{
	printf("ft_atoi_base(\"%s\", \"%s\")\n", str, base);
	printf("  Expected : %d\n", expected);
	printf("  Got      : %d\n", got);
	printf("  Status   : %s\n\n", expected == got ? "✅ OK" : "❌ KO");
}

void test_atoi_base(void)
{
	printf("===========================================\n");
	printf("          TESTS FT_ATOI_BASE\n");
	printf("===========================================\n\n");

	// --- Base 10 ---
	printf("--- Base 10 ---\n\n");
	print_test("42", "0123456789", 42, ft_atoi_base("42", "0123456789"));
	print_test("0", "0123456789", 0, ft_atoi_base("0", "0123456789"));
	print_test("-42", "0123456789", -42, ft_atoi_base("-42", "0123456789"));
	print_test("+42", "0123456789", 42, ft_atoi_base("+42", "0123456789"));
	print_test("2147483647", "0123456789", 2147483647, ft_atoi_base("2147483647", "0123456789"));
	print_test("-2147483648", "0123456789", -2147483648, ft_atoi_base("-2147483648", "0123456789"));

	// --- Base 2 ---
	printf("--- Base 2 (binaire) ---\n\n");
	print_test("101010", "01", 42, ft_atoi_base("101010", "01"));
	print_test("0", "01", 0, ft_atoi_base("0", "01"));
	print_test("1111111", "01", 127, ft_atoi_base("1111111", "01"));
	print_test("-101010", "01", -42, ft_atoi_base("-101010", "01"));

	// --- Base 16 ---
	printf("--- Base 16 (hexadecimal) ---\n\n");
	print_test("2a", "0123456789abcdef", 42, ft_atoi_base("2a", "0123456789abcdef"));
	print_test("ff", "0123456789abcdef", 255, ft_atoi_base("ff", "0123456789abcdef"));
	print_test("0", "0123456789abcdef", 0, ft_atoi_base("0", "0123456789abcdef"));
	print_test("-2a", "0123456789abcdef", -42, ft_atoi_base("-2a", "0123456789abcdef"));
	print_test("7fffffff", "0123456789abcdef", 2147483647, ft_atoi_base("7fffffff", "0123456789abcdef"));

	// --- Base 8 ---
	printf("--- Base 8 (octal) ---\n\n");
	print_test("52", "01234567", 42, ft_atoi_base("52", "01234567"));
	print_test("0", "01234567", 0, ft_atoi_base("0", "01234567"));
	print_test("-52", "01234567", -42, ft_atoi_base("-52", "01234567"));

	// --- Bases invalides ---
	printf("--- Bases invalides (retour attendu: 0) ---\n\n");
	print_test("42", "0", 0, ft_atoi_base("42", "0"));          // base taille 1
	print_test("42", "", 0, ft_atoi_base("42", ""));             // base vide
	print_test("42", "0011", 0, ft_atoi_base("42", "0011"));     // doublon dans base
	print_test("42", "01+3", 0, ft_atoi_base("42", "01+3"));     // '+' dans base
	print_test("42", "01-3", 0, ft_atoi_base("42", "01-3"));     // '-' dans base

	// --- Espaces et whitespace avant le nombre ---
	printf("--- Espaces avant le nombre ---\n\n");
	print_test("   42", "0123456789", 42, ft_atoi_base("   42", "0123456789"));
	print_test("\t\n42", "0123456789", 42, ft_atoi_base("\t\n42", "0123456789"));
	print_test("   -42", "0123456789", -42, ft_atoi_base("   -42", "0123456789"));

	// --- Plusieurs signes ---
	printf("--- Plusieurs signes ---\n\n");
	print_test("--42", "0123456789", 42, ft_atoi_base("--42", "0123456789"));
	print_test("+-42", "0123456789", -42, ft_atoi_base("+-42", "0123456789"));

	// --- Caracteres invalides dans str ---
	printf("--- Caracteres invalides dans str ---\n\n");
	print_test("4x2", "0123456789", 4, ft_atoi_base("4x2", "0123456789"));
	print_test("xyz", "0123456789", 0, ft_atoi_base("xyz", "0123456789"));
}

int	main(void)
{
	test_atoi_base();
	return (0);
}
