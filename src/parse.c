/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:24:31 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:06:58 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void		print_command_usage(char *str)
{
	ft_putstr("ft_ssl: Error: \'");
	ft_putstr(str);
	ft_putstr("\' is an invalid command.\n\n");
	ft_putstr("Standard commands:\n\n");
	ft_putstr("Message Digest command:\n");
	ft_putstr("md5\nsha256\n\n");
	ft_putstr("Cipher commands:\n");
}

t_list			*parse(t_list *data_base, int ac, char **av)
{
	t_list		*ret;

	if (ac == 1)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]");
		return (NULL);
	}
	ret = find_pair_with_algoname(data_base, av[1]);
	if (ret == NULL)
		print_command_usage(av[1]);
	return (ret);
}
