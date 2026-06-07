#include <libasm.h>

int	main()
{
	ft_atoi_base("42", "0123456789")           ;//== 42;
	ft_atoi_base("-42", "0123456789")          ;//== -42;
	ft_atoi_base("--42", "0123456789")         ;//== 42;
	ft_atoi_base("   ---+-42abc", "0123456789");//== -42;
	ft_atoi_base("ff", "0123456789abcdef")     ;//== 255;
	ft_atoi_base("FF", "0123456789abcdef")     ;//== 0;	//(case sensitive)
	ft_atoi_base("101", "01")                  ;//== 5;
	ft_atoi_base("", "0123456789")             ;//== 0;
	ft_atoi_base("abc", "0123456789")          ;//== 0;
	ft_atoi_base("42", "")                     ;//== 0;	//(base trop courte)
	ft_atoi_base("42", "0+1")                  ;//== 0;	//(base invalide)
	ft_atoi_base("42", "00")                   ;//== 0;	//(doublon)
}
