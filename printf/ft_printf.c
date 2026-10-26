/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 12:26:09 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/19 12:59:36 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parser(char c, va_list *args)
{
	if (c == '\0')
		return (0);
	else if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (c == 'p')
		return (puntero(va_arg(*args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base(va_arg(*args, int), "0123456789"));
	else if (c == 'u')
		return (ft_putnbr_ubase(va_arg(*args, unsigned int), "0123456789"));
	else if (c == 'x')
		return (((ft_putnbr_ubase(va_arg(*args, unsigned int),
				"0123456789abcdef"))));
	else if (c == 'X')
		return (((ft_putnbr_ubase(va_arg(*args, unsigned int),
				"0123456789ABCDEF"))));
	else if (c == '%')
		return (ft_putchar('%'));	
	return (ft_putchar('%') + ft_putchar(c));
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format != '%')
			count += ft_putchar(*format);
		else
		{
			format++;
			count += ft_format(&format, &args);
			if (!*format)
				break ;
		}
		format++;
	}
	va_end(args);
	return (count);
}

/*int	main(void)
{
int	edad;
int	total;

edad = 41;
ft_printf("--- %%c y %%s ---\n");
ft_printf("Me llamo %s y mi inicial es la %c.\n", "Cristiano Ronaldo", 'C');
ft_printf("Mi grito de gol es %s y mi apodo es %s%c%c.\n", "SIUUU", "CR", '7',
'!');
ft_printf("El único mejor que yo es %s.\n", (char *)0);
ft_printf("--- %%d y %%i ---\n");
ft_printf("Tengo %d años y llevo el dorsal %i.\n", edad, 7);
ft_printf("Nací hace %d años, es decir, en el año %i.\n", -edad, 1985);
ft_printf("He estado en %d clubes.\n", 5);
ft_printf("El menor int es %d y el mayor es %i.\n", -2147483647 - 1,
2147483647);
ft_printf("--- %%u ---\n");
ft_printf("Voy a llegar a los %u goles en mi carrera.\n", 1000);
ft_printf("Un -1 visto como unsigned es %u.\n", -1);
ft_printf("--- %%x y %%X ---\n");
ft_printf("Mis 900+ goles en hex son %x y en HEX son %X.\n", 900, 900);
ft_printf("CR7 sin la R es %x en minúsculas y %X en mayúsculas.\n", 0xc7,
0xc7);
ft_printf("--- %%p ---\n");
ft_printf("Mi edad vive en la dirección %p.\n", &edad);
ft_printf("Un puntero NULL se imprime como %p.\n", (void *)0);
ft_printf("--- %%%% y valor de retorno ---\n");
ft_printf("Tengo una efectividad del 100%% en los penaltis.\n");
total = ft_printf("Soy %s, tengo %d años y el dorsal %i.\n",
"Cristiano Ronaldo", edad, 7);
ft_printf("La frase anterior tenía %d caracteres.\n", total);
return (0);
}*/
