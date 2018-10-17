/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:38:35 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:55:21 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha256.h>

static int			get_files_index(int ac, char **av)
{
	int				i;

	i = 2;
	while (i < ac && (ft_strequ(av[i], "-p") ||
	ft_strequ(av[i], "-q") || ft_strequ(av[i], "-r")))
		++i;
	while (i < ac && ft_strequ(av[i], "-s"))
		i += 2;
	return (i >= ac ? ac : i);
}

t_flags_sha256		parse_flags_sha256(int ac, char **av)
{
	t_flags_sha256	ret;
	int				i;

	ret.is_p = 0;
	ret.is_q = 0;
	ret.is_r = 0;
	i = 0;
	while (++i < ac)
		if (ft_strequ(av[i], "-p"))
			ret.is_p = 1;
		else if (ft_strequ(av[i], "-q"))
			ret.is_q = 1;
		else if (ft_strequ(av[i], "-r"))
			ret.is_r = 1;
	ret.files_index = get_files_index(ac, av);
	return (ret);
}
