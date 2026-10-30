/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 13:00:00 by student           #+#    #+#             */
/*   Updated: 2026/10/26 13:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_flags(const char **s, t_fmt *f)
{
	while (**s == '-' || **s == '0' || **s == '#'
		|| **s == '+' || **s == ' ')
	{
		if (**s == '-')
			f->left = 1;
		if (**s == '0')
			f->zero = 1;
		if (**s == '#')
			f->hash = 1;
		if (**s == '+')
			f->plus = 1;
		if (**s == ' ')
			f->space = 1;
		(*s)++;
	}
}

static int	ft_digits(const char **s)
{
	int	n;

	n = 0;
	while (**s >= '0' && **s <= '9')
	{
		if (n > (2147483647 - (**s - '0')) / 10)
			n = 2147483647;
		else
			n = n * 10 + **s - '0';
		(*s)++;
	}
	return (n);
}

void	ft_parse(const char **s, t_fmt *f)
{
	f->left = 0;
	f->zero = 0;
	f->hash = 0;
	f->plus = 0;
	f->space = 0;
	f->prec = -1;
	ft_flags(s, f);
	f->width = ft_digits(s);
	if (**s == '.')
	{
		(*s)++;
		f->prec = ft_digits(s);
	}
	f->type = **s;
	if (**s)
		(*s)++;
}
