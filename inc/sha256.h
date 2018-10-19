/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:10:18 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/19 15:09:11 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <libft.h>

static u_int32_t	g_k1[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

# ifndef S_FLAGS_SHA256
#  define S_FLAGS_SHA256

#  define STDIN 1
#  define STRINGS 2
#  define FILES 3

typedef struct	s_flags_sha256
{
	int			files_index;
	char		is_p;
	char		is_q;
	char		is_r;
}				t_flags_sha256;
# endif

# ifndef T_MAGIC_SHA256
#  define T_MAGIC_SHA256

typedef struct	s_magic_sha256
{
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	uint32_t g;
	uint32_t h;
}				t_magic_sha256;
# endif

# ifndef T_HOLDER_SHA256
#  define T_HOLDER_SHA256

typedef struct	s_holder_sha256
{
	int			i;
	int			j;
	uint32_t	chunk[64];
	size_t		chunk_move;
	uint8_t		*tmp;
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	s11;
	uint32_t	ch;
	uint32_t	temp1;
	uint32_t	s00;
	uint32_t	maj;
	uint32_t	temp2;
}				t_holder_sha256;
# endif

/*
**			sha256.c
*/
void			sha256(int ac, char **av);
/*
**			logic.c
*/
char			*get_result_sha256(u_int8_t *msg, size_t len);
/*
**			parse.c
*/
t_flags_sha256	parse_flags_sha256(int ac, char **av);
/*
**			utility.c
*/
char			*create_hash_from_magic_sha256(t_magic_sha256 *magic);
void			do_some_magic_velociped(t_magic_sha256 *magic,\
t_holder_sha256 *holder, char variant);
/*
**			ft_ssl/src/utility.c
*/
char			*get_string(int fd, size_t *len);
/*
**			print.c
*/
void			print_result_sha256(t_flags_sha256 *flags, char *src,\
char *answer, int type);
#endif
