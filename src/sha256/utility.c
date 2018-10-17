/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 20:13:29 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 19:49:52 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha256.h>

#define R_ROT(A, B) (((A) >> (B)) | ((A) << (32 - (B))))

char		*create_hash_from_magic_sha256(t_magic_sha256 *magic)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 65);
	ft_bzero(ret, sizeof(char) * 65);
	ft_sprintf(ret, "%8.8x", magic->h0);
	ft_sprintf(ret + 8, "%8.8x", magic->h1);
	ft_sprintf(ret + 16, "%8.8x", magic->h2);
	ft_sprintf(ret + 24, "%8.8x", magic->h3);
	ft_sprintf(ret + 32, "%8.8x", magic->h4);
	ft_sprintf(ret + 40, "%8.8x", magic->h5);
	ft_sprintf(ret + 48, "%8.8x", magic->h6);
	ft_sprintf(ret + 56, "%8.8x\n", magic->h7);
	return (ret);
}

void		do_some_magic_velociped(t_magic_sha256 *m, t_holder_sha256 *hd,
									char variant)
{
	if (variant == 0)
		while (hd->i < 64)
		{
			hd->s0 = R_ROT(hd->chunk[hd->i - 15], 7) ^
			R_ROT(hd->chunk[hd->i - 15], 18) ^ (hd->chunk[hd->i - 15] >> 3);
			hd->s1 = R_ROT(hd->chunk[hd->i - 2], 17) ^
			R_ROT(hd->chunk[hd->i - 2], 19) ^ (hd->chunk[hd->i - 2] >> 10);
			hd->chunk[hd->i] = hd->chunk[hd->i - 16] + hd->s0 +
			hd->chunk[hd->i - 7] + hd->s1;
			hd->i++;
		}
	else if (variant == 1)
	{
		hd->s11 = R_ROT(m->e, 6) ^ R_ROT(m->e, 11) ^ R_ROT(m->e, 25);
		hd->ch = (m->e & m->f) ^ ((~m->e) & m->g);
		hd->temp1 = m->h + hd->s11 + hd->ch + g_k1[hd->j] + hd->chunk[hd->j];
		hd->s00 = R_ROT(m->a, 2) ^ R_ROT(m->a, 13) ^ R_ROT(m->a, 22);
		hd->maj = (m->a & m->b) ^ (m->a & m->c) ^ (m->b & m->c);
		hd->temp2 = hd->s00 + hd->maj;
	}
}
