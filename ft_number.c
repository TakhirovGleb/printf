/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 13:00:00 by student           #+#    #+#             */
/*   Updated: 2026/10/26 13:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long	ft_value(t_fmt *f, va_list ap, t_num *n)
{
	long	v;

	n->prefix = "";
	if (f->type == 'p')
	{
		n->prefix = "0x";
		return ((unsigned long)(uintptr_t)va_arg(ap, void *));
	}
	if (f->type != 'd' && f->type != 'i')
		return (va_arg(ap, unsigned int));
	v = va_arg(ap, int);
	if (v < 0)
		n->prefix = "-";
	else if (f->plus)
		n->prefix = "+";
	else if (f->space)
		n->prefix = " ";
	if (v < 0)
		return ((unsigned long)(-v));
	return ((unsigned long)v);
}

static void	ft_encode(unsigned long v, t_fmt *f, t_num *n)
{
	char			*digits;
	unsigned int	base;
	int				i;
	char			c;

	digits = "0123456789abcdef";
	if (f->type == 'X')
		digits = "0123456789ABCDEF";
	base = 10;
	if (f->type == 'x' || f->type == 'X' || f->type == 'p')
		base = 16;
	n->len = 0;
	while (v || (!n->len && f->prec != 0))
	{
		n->buf[n->len++] = digits[v % base];
		v /= base;
	}
	i = -1;
	while (++i < n->len / 2)
	{
		c = n->buf[i];
		n->buf[i] = n->buf[n->len - i - 1];
		n->buf[n->len - i - 1] = c;
	}
}

static void	ft_padding(t_fmt *f, t_num *n)
{
	n->plen = 0;
	while (n->prefix[n->plen])
		n->plen++;
	n->zeros = f->prec - n->len;
	if (n->zeros < 0)
		n->zeros = 0;
	n->pad = f->width - n->len - n->plen - n->zeros;
	if (n->pad < 0)
		n->pad = 0;
	if (f->zero && !f->left && f->prec < 0)
	{
		n->zeros += n->pad;
		n->pad = 0;
	}
}

int	ft_number(t_fmt *f, va_list ap)
{
	t_num			n;
	unsigned long	v;

	v = ft_value(f, ap, &n);
	if (v && f->hash && f->type == 'x')
		n.prefix = "0x";
	if (v && f->hash && f->type == 'X')
		n.prefix = "0X";
	ft_encode(v, f, &n);
	ft_padding(f, &n);
	return (ft_emit(f, &n));
}
