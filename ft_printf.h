/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 13:00:00 by student           #+#    #+#             */
/*   Updated: 2026/10/26 13:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_fmt
{
	int		left;
	int		zero;
	int		hash;
	int		plus;
	int		space;
	int		width;
	int		prec;
	char	type;
}	t_fmt;

typedef struct s_num
{
	char	buf[32];
	char	*prefix;
	int		len;
	int		plen;
	int		zeros;
	int		pad;
}	t_num;

int		ft_printf(const char *format, ...);
void	ft_parse(const char **s, t_fmt *f);
int		ft_repeat(char c, int n);
int		ft_write(const char *s, int n);
int		ft_text(t_fmt *f, va_list ap);
int		ft_number(t_fmt *f, va_list ap);
int		ft_emit(t_fmt *f, t_num *n);

#endif
