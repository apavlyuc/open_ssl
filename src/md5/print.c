/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:09:38 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:53:48 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>

static void	print_from_stdin(t_flags_md5 *flags, char *src, char *answer)
{
	if (flags->is_p)
		ft_putstr(src);
	ft_putstr(answer);
}

static void	print_from_params(t_flags_md5 *flags, char *src, char *answer)
{
	if (flags->is_q)
		ft_putstr(answer);
	else
	{
		if (flags->is_r)
		{
			ft_putstr(answer);
			ft_putstr(" \"");
			ft_putstr(src);
			ft_putstr("\"");
		}
		else
		{
			ft_putstr("MD5 (\"");
			ft_putstr(src);
			ft_putstr("\") = ");
			ft_putstr(answer);
		}
	}
}

static void	print_from_files(t_flags_md5 *flags, char *src, char *answer)
{
	if (flags->is_q)
		ft_putstr(answer);
	else
	{
		if (flags->is_r)
		{
			ft_putstr(answer);
			ft_putstr(" ");
			ft_putstr(src);
		}
		else
		{
			ft_putstr("MD5 (");
			ft_putstr(src);
			ft_putstr(") = ");
			ft_putstr(answer);
		}
	}
}

void		print_result_md5(t_flags_md5 *flags, char *src, char *answer,
							int type)
{
	if (type == STDIN)
		print_from_stdin(flags, src, answer);
	else if (type == STRINGS)
		print_from_params(flags, src, answer);
	else if (type == FILES)
		print_from_files(flags, src, answer);
	write(1, "\n", 1);
}
