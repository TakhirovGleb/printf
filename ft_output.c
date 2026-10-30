/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 13:00:00 by student           #+#    #+#             */
/*   Updated: 2026/10/26 13:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write(const char *s, int n)
{
	int		done;
	ssize_t	result;

	done = 0;
	while (done < n)
	{
		result = write(1, s + done, n - done);
		if (result <= 0)
			return (-1);
		done += result;
	}
	return (done);
}

int	ft_repeat(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (ft_write(&c, 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_emit(t_fmt *f, t_num *n)
{
	if (!f->left && ft_repeat(' ', n->pad) < 0)
		return (-1);
	if (ft_write(n->prefix, n->plen) < 0
		|| ft_repeat('0', n->zeros) < 0
		|| ft_write(n->buf, n->len) < 0)
		return (-1);
	if (f->left && ft_repeat(' ', n->pad) < 0)
		return (-1);
	return (n->pad + n->plen + n->zeros + n->len);
}
