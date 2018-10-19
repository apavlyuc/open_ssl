/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 15:47:35 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/19 15:09:30 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <md5.h>
# include <sha256.h>

# ifndef SSL_PAIR
#  define SSL_PAIR

typedef struct	s_pair_algofunc_and_algoname
{
	char		*algo_name;
	void		(*algo_func)(int ac, char **av);
}				t_pair;
t_pair			make_pair(char *algo_name, void (*algo_func)(int, char**));
# endif

/*
**			parser.c
*/
t_list			*parse(t_list *data_base, int ac, char **av);
/*
**			utility.c
*/
t_list			*find_pair_with_algoname(t_list *list, char *algo_name);
char			*get_string(int fd, size_t *len);
void			ft_delete(void *content, size_t len);
#endif
