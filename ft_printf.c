/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 13:00:00 by student           #+#    #+#             */
/*   Updated: 2026/10/26 13:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert(t_fmt *f, va_list ap)
{
	if (f->type == 'c' || f->type == 's' || f->type == '%')
		return (ft_text(f, ap));
	if (f->type == 'd' || f->type == 'i' || f->type == 'u'
		|| f->type == 'x' || f->type == 'X' || f->type == 'p')
		return (ft_number(f, ap));
	return (-1);
}

static int	ft_run(const char *s, va_list ap)
{
	t_fmt	f;
	int		total;
	int		n;

	total = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			ft_parse(&s, &f);
			n = ft_convert(&f, ap);
		}
		else
			n = ft_write(s++, 1);
		if (n < 0 || total > 2147483647 - n)
			return (-1);
		total += n;
	}
	return (total);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		result;

	if (!format)
		return (-1);
	va_start(ap, format);
	result = ft_run(format, ap);
	va_end(ap);
	return (result);
}
