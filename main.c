#include "includes/ft_printf.h"
#include "srcs/libft/libft.h"
#include <stdio.h>

int main()
{

	/* printf("\ntestx:\n"); */
	/* testx(); */
	/* printf("\ntestp:\n"); */
	/* testp(); */
	/* printf("\ntestd:\n"); */
	/* testd(); */
	/* printf("\ntestu:\n"); */
	/* testu(); */
	int res;

//	model
//	res = ft_printf(">%..s<\n", ...);
//	printf("return waarde: %d\n", res);
//	res = printf(">%32s<\n", "abc");
//	printf("return waarde: %d\n", res);

	res = ft_printf("%.x", 43521);
	printf("return waarde: %d\n", res);

	res = printf("%.x", 43521);
	printf("return waarde: %d\n", res);

	res = ft_printf("%.X", 43521);
	printf("return waarde: %d\n", res);

	res = printf("%.X", 43521);
	printf("return waarde: %d\n", res);
}
