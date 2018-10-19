/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:07:02 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/19 16:23:48 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void	init_supported_algo(t_list **commands)
{
	t_pair	pair;

	pair = make_pair("md5", md5);
	*commands = ft_lstnew((void *)&pair, sizeof(pair));
	pair = make_pair("sha256", sha256);
	ft_lstadd(commands, ft_lstnew((void *)&pair, sizeof(pair)));
}

int			main(int ac, char **av)
{
	t_list	*supported_algo;
	t_list	*needed_algo;

	init_supported_algo(&supported_algo);
	needed_algo = parse(supported_algo, ac, av);
	if (needed_algo == NULL)
		return (1);
	((t_pair *)needed_algo->content)->algo_func(ac, av);
	ft_lstdel(&supported_algo, ft_delete);
	return (0);
}
