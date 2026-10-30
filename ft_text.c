/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 13:00:00 by student           #+#    #+#             */
/*   Updated: 2026/10/26 13:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_string(t_fmt *f, char *s)
{
	int	len;
	int	pad;

	if (!s)
		s = "(null)";
	len = 0;
	while (s[len] && (f->prec < 0 || len < f->prec))
		len++;
	pad = f->width - len;
	if (pad < 0)
		pad = 0;
	if (!f->left && ft_repeat(' ', pad) < 0)
		return (-1);
	if (ft_write(s, len) < 0)
		return (-1);
	if (f->left && ft_repeat(' ', pad) < 0)
		return (-1);
	return (len + pad);
}

int	ft_text(t_fmt *f, va_list ap)
{
	char	c;
	int		pad;

	if (f->type == 's')
		return (ft_string(f, va_arg(ap, char *)));
	c = '%';
	if (f->type == 'c')
		c = (char)va_arg(ap, int);
	pad = f->width - 1;
	if (pad < 0)
		pad = 0;
	if (!f->left && ft_repeat(' ', pad) < 0)
		return (-1);
	if (ft_write(&c, 1) < 0)
		return (-1);
	if (f->left && ft_repeat(' ', pad) < 0)
		return (-1);
	return (pad + 1);
}
