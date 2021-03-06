/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:01:13 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/19 16:05:01 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>

static void	print_params_usage(int type, char *file_name)
{
	if (type == 1)
	{
		ft_putstr("ft_ssl: md5: option requires an argument -- s\n");
		ft_putstr("usage: md5 [-pqr] [-s string] [files ...]\n");
	}
	else if (type == 2)
	{
		ft_putstr("ft_ssl: md5: ");
		ft_putstr(file_name);
		ft_putstr(": No such file or directory\n");
	}
}

static void	run_for_stdin(t_flags_md5 *flags, char **av)
{
	char	*msg;
	char	*answer;
	size_t	len;

	msg = get_string(0, &len);
	(void)av;
	answer = get_result_md5((uint8_t *)msg, len);
	print_result_md5(flags, msg, answer, STDIN);
	free(answer);
	free(msg);
}

static void	run_for_strings(t_flags_md5 *flags, int ac, char **av)
{
	char	*answer;
	int		i;

	i = 0;
	while (++i < flags->files_index)
		if (ft_strequ(av[i], "-s"))
		{
			if (++i == ac)
			{
				print_params_usage(1, 0);
				return ;
			}
			answer = get_result_md5((uint8_t *)av[i], ft_strlen(av[i]));
			print_result_md5(flags, av[i], answer, STRINGS);
			free(answer);
		}
}

static void	run_for_files(t_flags_md5 *flags, int ac, char **av)
{
	char	*answer;
	char	*msg;
	int		i;
	int		fd;
	size_t	len;

	i = flags->files_index - 1;
	while (++i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
			print_params_usage(2, av[i]);
		else
		{
			msg = get_string(fd, &len);
			answer = get_result_md5((uint8_t *)msg, len);
			print_result_md5(flags, av[i], answer, FILES);
			free(msg);
			free(answer);
		}
	}
}

void		md5(int ac, char **av)
{
	t_flags_md5	flags;

	flags = parse_flags_md5(ac, av);
	if (flags.is_p || ac == (2 + flags.is_p + flags.is_q + flags.is_r))
		run_for_stdin(&flags, av);
	run_for_strings(&flags, ac, av);
	run_for_files(&flags, ac, av);
}
