/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:09:49 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/16 17:01:20 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>

#define L(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

static void		init_hash(t_hash *hash, int type)
{
	if (type == 1)
	{
		hash->h0 = 0x67452301;
		hash->h1 = 0xefcdab89;
		hash->h2 = 0x98badcfe;
		hash->h3 = 0x10325476;
	}
	else if (type == 2)
	{
		hash->tmp_h0 = hash->h0;
		hash->tmp_h1 = hash->h1;
		hash->tmp_h2 = hash->h2;
		hash->tmp_h3 = hash->h3;
	}
	else if (type == 3)
	{
		hash->h0 += hash->tmp_h0;
		hash->h1 += hash->tmp_h1;
		hash->h2 += hash->tmp_h2;
		hash->h3 += hash->tmp_h3;
	}
}

static int		init_msg(uint8_t **dst, uint8_t *src, int size)
{
	int			len;
	uint32_t	bits;

	len = size * 8 + 1;
	while (len % 512 != 448)
		++len;
	len /= 8;
	*dst = (uint8_t *)malloc(len + 64);
	ft_bzero(*dst, len + 64);
	memcpy(*dst, src, size);
	(*dst)[size] = 128;
	bits = 8 * size;
	memcpy(*dst + len, &bits, 4);
	return (len);
}

static void		magic_velosiped(t_hash *hash, uint32_t *w, int i, uint32_t tmp)
{
	uint32_t	f;
	uint32_t	g;

	f = hash->tmp_h2 ^ (hash->tmp_h1 | (~hash->tmp_h3));
	g = (7 * i) % 16;
	if (i < 16)
	{
		f = (hash->tmp_h1 & hash->tmp_h2) | ((~hash->tmp_h1) & hash->tmp_h3);
		g = i;
	}
	else if (i < 32)
	{
		f = (hash->tmp_h3 & hash->tmp_h1) | ((~hash->tmp_h3) & hash->tmp_h2);
		g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		f = (hash->tmp_h1 ^ hash->tmp_h2 ^ hash->tmp_h3);
		g = (3 * i + 5) % 16;
	}
	tmp = hash->tmp_h3;
	hash->tmp_h3 = hash->tmp_h2;
	hash->tmp_h2 = hash->tmp_h1;
	hash->tmp_h1 = hash->tmp_h1 + L((hash->tmp_h0 + f + g_k[i] + w[g]), g_r[i]);
	hash->tmp_h0 = tmp;
}

static void		process_hash(t_hash *hash, uint8_t *msg, int len)
{
	uint32_t	*tmp;
	uint32_t	i;
	int			offset;

	offset = 0;
	tmp = 0;
	while (offset < len)
	{
		tmp = (uint32_t *)(msg + offset);
		init_hash(hash, 2);
		i = 0;
		while (i < 64)
			magic_velosiped(hash, tmp, i++, 0);
		init_hash(hash, 3);
		offset += 64;
	}
}

char			*get_result_md5(uint8_t *string, int len)
{
	t_hash		hash;
	uint8_t		*msg;
	int			len_after_init;

	msg = 0;
	init_hash(&hash, 1);
	len_after_init = init_msg(&msg, string, len);
	process_hash(&hash, msg, len_after_init);
	free(msg);
	return (create_hash_from_four_uint32(hash.h0, hash.h1, hash.h2, hash.h3));
}
