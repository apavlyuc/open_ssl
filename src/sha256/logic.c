/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 20:10:21 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/17 18:21:10 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha256.h>

#define RIGHT_ROT(A, B) (((A) >> (B)) | ((A) << (32 - (B))))
#define T_MG t_magic_sha256
#define T_HD t_holder_sha256

static void		init_magic_sha256(t_magic_sha256 *magic, char variant)
{
	if (variant == 0)
	{
		magic->h0 = 0x6a09e667;
		magic->h1 = 0xbb67ae85;
		magic->h2 = 0x3c6ef372;
		magic->h3 = 0xa54ff53a;
		magic->h4 = 0x510e527f;
		magic->h5 = 0x9b05688c;
		magic->h6 = 0x1f83d9ab;
		magic->h7 = 0x5be0cd19;
	}
	else if (variant == 1)
	{
		magic->a = magic->h0;
		magic->b = magic->h1;
		magic->c = magic->h2;
		magic->d = magic->h3;
		magic->e = magic->h4;
		magic->f = magic->h5;
		magic->g = magic->h6;
		magic->h = magic->h7;
	}
}

static void		refresh_magic_sha256(T_MG *magic, uint32_t tmp1,
									uint32_t tmp2, char variant)
{
	if (variant == 0)
	{
		magic->h = magic->g;
		magic->g = magic->f;
		magic->f = magic->e;
		magic->e = magic->d + tmp1;
		magic->d = magic->c;
		magic->c = magic->b;
		magic->b = magic->a;
		magic->a = tmp1 + tmp2;
	}
	else if (variant == 1)
	{
		magic->h0 = magic->h0 + magic->a;
		magic->h1 = magic->h1 + magic->b;
		magic->h2 = magic->h2 + magic->c;
		magic->h3 = magic->h3 + magic->d;
		magic->h4 = magic->h4 + magic->e;
		magic->h5 = magic->h5 + magic->f;
		magic->h6 = magic->h6 + magic->g;
		magic->h7 = magic->h7 + magic->h;
	}
}

static void		ft_sha256(T_MG *magic, uint8_t *msg, size_t msg_len)
{
	T_HD		hd;

	hd.chunk_move = 0;
	while (hd.chunk_move < msg_len)
	{
		hd.tmp = msg + hd.chunk_move;
		hd.i = -1;
		hd.j = 0;
		while (++hd.i < 16)
		{
			hd.chunk[hd.i] = (hd.tmp[hd.j] << 24) | (hd.tmp[hd.j + 1] << 16)
			| (hd.tmp[hd.j + 2] << 8) | (hd.tmp[hd.j + 3]);
			hd.j += 4;
		}
		do_some_magic_velociped(magic, &hd, 0);
		init_magic_sha256(magic, 1);
		hd.j = -1;
		while (++hd.j < 64)
		{
			do_some_magic_velociped(magic, &hd, 1);
			refresh_magic_sha256(magic, hd.temp1, hd.temp2, 0);
		}
		refresh_magic_sha256(magic, 0, 0, 1);
		hd.chunk_move += 64;
	}
}

static size_t	init_msg(uint8_t **msg, uint8_t *data, size_t data_len)
{
	uint64_t	bits_in_data;
	uint64_t	bits_in_msg;
	uint64_t	ret;

	bits_in_data = data_len * 8;
	bits_in_msg = (data_len * 8) + 1;
	while (bits_in_msg % 512 != 448)
		bits_in_msg++;
	bits_in_msg += 64;
	ret = bits_in_msg / 8;
	*msg = (uint8_t*)ft_strnew(ret);
	ft_bzero(*msg, ret);
	memcpy(*msg, data, data_len);
	(*msg)[data_len] = (uint8_t)0x80;
	(*msg)[ret - 1] = (uint8_t)bits_in_data;
	(*msg)[ret - 2] = (uint8_t)(bits_in_data >> 8);
	(*msg)[ret - 3] = (uint8_t)(bits_in_data >> 16);
	(*msg)[ret - 4] = (uint8_t)(bits_in_data >> 24);
	(*msg)[ret - 5] = (uint8_t)(bits_in_data >> 32);
	(*msg)[ret - 6] = (uint8_t)(bits_in_data >> 40);
	(*msg)[ret - 7] = (uint8_t)(bits_in_data >> 48);
	(*msg)[ret - 8] = (uint8_t)(bits_in_data >> 56);
	return (ret);
}

char			*get_result_sha256(u_int8_t *string, size_t len)
{
	T_MG		magic;
	uint8_t		*msg;
	size_t		len_after_init;

	init_magic_sha256(&magic, 0);
	len_after_init = init_msg(&msg, string, len);
	ft_sha256(&magic, msg, len_after_init);
	free(msg);
	return (create_hash_from_magic_sha256(&magic));
}
