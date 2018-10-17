/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:51:32 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:48:27 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>

char		*create_hash_from_four_uint32(uint32_t a, uint32_t b,
											uint32_t c, uint32_t d)
{
	char	*ret;
	uint8_t	*p;

	ret = (char *)malloc(sizeof(char) * 33);
	ret[32] = 0;
	p = (uint8_t *)&a;
	ft_sprintf(ret, "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&b;
	ft_sprintf(&ret[8], "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&c;
	ft_sprintf(&ret[16], "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&d;
	ft_sprintf(&ret[24], "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	return (ret);
}
