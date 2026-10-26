/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:30:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/15 13:12:03 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	parse_fmt(char const *s, t_format *f)
{
	int	i;

	ft_bzero(f, sizeof(t_format));
	f->prec = -1;
	i = 0;
	while (s[i] && ft_strchr("-0# +", s[i]))
	{
		f->minus |= (s[i] == '-');
		f->zero |= (s[i] == '0');
		f->hash |= (s[i] == '#');
		f->space |= (s[i] == ' ');
		f->plus |= (s[i] == '+');
		i++;
	}
	while (ft_isdigit(s[i]))
		f->width = f->width * 10 + (s[i++] - '0');
	if (s[i] == '.')
	{
		i++;
		f->prec = 0;
		while (ft_isdigit(s[i]))
			f->prec = f->prec * 10 + (s[i++] - '0');
	}
	return (i);
}

int	ft_format(char const **format_addr, va_list *args)
{
	t_format	options;
	char		letter;

	*format_addr += parse_fmt(*format_addr, &options);
	letter = **format_addr;
	if (letter == 'c')
		return (ft_print_char(&options, va_arg(*args, int)));
	else if (letter == 's')
		return (ft_print_str(&options, va_arg(*args, char *)));
	else if (letter == 'p')
		return (ft_print_ptr(&options, va_arg(*args, void *)));
	else if (letter == 'd' || letter == 'i')
		return (ft_print_int(&options, va_arg(*args, int)));
	else if (letter == 'u' || letter == 'x' || letter == 'X')
		return (ft_print_uint(&options, va_arg(*args, unsigned int),
				letter));
	return (ft_parser(letter, args));
}

/*int	main(void)
{
int	edad;
int	total;

edad = 41;
ft_printf("--- %%c y %%s ---\n");
ft_printf("Me llamo [%20s] y mi inicial es la [%3c].\n", "Cristiano Ronaldo",
'C');
ft_printf("A la izquierda soy [%-20s] y mi inicial es la [%-3c].\n",
"Cristiano Ronaldo", 'C');
ft_printf("Mi nombre de pila es [%.9s] y con ancho 12 es [%12.9s].\n",
"Cristiano Ronaldo", "Cristiano Ronaldo");
ft_printf("Si me pasan una cadena NULL imprimo [%10s].\n", (char *)0);
ft_printf("--- %%d y %%i ---\n");
ft_printf("Tengo [%5d] años y llevo el dorsal [%-5i].\n", edad, 7);
ft_printf("Con ceros tengo [%05d] años y llevo el dorsal [%.3i].\n", edad, 7);
ft_printf("Nací hace [%+d] años, es decir, en el año [%+i].\n", -edad, 1985);
ft_printf("Con espacio tengo [% d] años y nací hace [% i].\n", edad, -edad);
ft_printf("El menor int es [%15d] y el mayor es [%-15i].\n", -2147483647 - 1,
2147483647);
ft_printf("Mi dorsal con ancho y precisión: [%8.3d], [%-8.3d] y [%+08.3i].\n",
7, 7, 7);
ft_printf("Un cero con precisión 0 no imprime nada: [%.0d].\n", 0);
ft_printf("--- %%u ---\n");
ft_printf("He marcado más de [%8u] goles, o [%-8u], o [%08u], o [%.6u].\n",
900, 900, 900, 900);
ft_printf("Un -1 visto como unsigned es [%15u].\n", -1);
ft_printf("--- %%x y %%X ---\n");
ft_printf("Mis 900 goles en hex son [%#x] y en HEX son [%#X].\n", 900, 900);
ft_printf("El 255 es [%#10x] en minúsculas y [%-#10X] en mayúsculas.\n", 255,
255);
ft_printf("Con ceros es [%08x], [%#010X] y [%.6x]; el cero es [%#x].\n", 255,
255, 255, 0);
ft_printf("--- %%p ---\n");
ft_printf("Mi edad vive en la dirección [%20p] o [%-20p].\n", &edad, &edad);
ft_printf("Un puntero NULL se imprime como [%10p].\n", (void *)0);
ft_printf("--- %%%% y valor de retorno ---\n");
ft_printf("Tengo una efectividad del [%5d%%] en los penaltis.\n", 100);
total = ft_printf("Soy [%-20s], tengo [%+5d] años y el dorsal [%03i].\n",
"Cristiano Ronaldo", edad, 7);
ft_printf("La frase anterior tenía [%5d] caracteres.\n", total);
return (0);
}*/
