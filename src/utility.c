/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:18:33 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:06:54 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void		ft_delete(void *content, size_t len)
{
	(void)len;
	free(content);
}

t_list		*find_pair_with_algoname(t_list *list, char *algo_name)
{
	t_pair	*content;

	while (list)
	{
		content = (t_pair *)list->content;
		if (ft_strequ(content->algo_name, algo_name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_pair		make_pair(char *algo_name, void (*algo_func)(int, char**))
{
	t_pair	ret;

	ret.algo_name = algo_name;
	ret.algo_func = algo_func;
	return (ret);
}

char		*get_string(int fd)
{
	char	*ret;
	char	*tmp;
	char	buffer[100];
	int		nbytes;

	ret = (char *)malloc(sizeof(char));
	while ((nbytes = read(fd, buffer, 99)) > 0)
	{
		buffer[nbytes] = 0;
		tmp = ret;
		ret = ft_strjoin(ret, buffer);
		free(tmp);
	}
	return (ret);
}
