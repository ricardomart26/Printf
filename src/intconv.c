/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intconv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:23:48 by rimartin          #+#    #+#             */
/*   Updated: 2021/04/13 19:23:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision_inteiro(sign_t *st)
{
	if (st->dot < st->size_c && st->dot != -1) //&& (!st->align)
		st->size_c = st->dot; // O size fica com 0
	else if (st->dot > st->size_c)
	{
		st->dot -= st->size_c;
		mult_char('0', &st->words, st->dot);
		st->size_c -= st->dot;
	}
}



void	width_int(sign_t *st)
{
	int size;
	size = st->size_c;
	if (st->temp_dot > size)
		size = st->temp_dot;
	if (st->dot == 0)
		size = 0;
	if (size < st->width)
	{
		st->width -= size;
		if (st->zero)
			mult_char('0', &st->words, st->width);
		else
			mult_char(' ', &st->words, st->width);
	}

}


void align_width(sign_t *st)
{
	if (st->dot == 0 && st->max_value != 1)
		st->size_c = 0;
	if (st->size_c < st->width)
	{
		st->width -= st->size_c;
		if (st->zero)
			mult_char('0', &st->words, st->width);
		else
			mult_char(' ', &st->words, st->width);
	}

}

void align_int(sign_t *st)
{
	if (st->dot > st->size_c)
	{
		precision_inteiro(st);
		//printf("teste");
		ft_putstr(st->conv, &st->words);
		width_int(st);
	}
	else if (st->width > st->size_c)
	{
		if (st->dot != 0 || st->max_value == 1)
			ft_putstr(st->conv, &st->words);
		align_width(st);
	}
	// else if (st->dot == 0)
	// {
	// 	align_width(st);
	// }
}

void specific_i(sign_t *st)
{
	if (st->dot == 0 && !st->width && !st->align && st->conv[0] != '0')
		ft_putstr(st->conv, &st->words);
	if (st->align)
		align_int(st);
	else
	{
		if (st->width > st->dot)
			width_int(st);
		if (st->dot != -1)
			precision_inteiro(st);
		if (st->dot != 0)
			ft_putstr(st->conv, &st->words);
	}

	free(st->conv);
	st->conv = NULL;
}





void	width_int_u(sign_t *st, int uintmax)
{
	int size;
	size = st->size_c;
	if (st->temp_dot > size)
		size = st->temp_dot;
	if (st->dot == 0 && uintmax != 1)
		size = 0;
	if (size < st->width)
	{
		st->width -= size;
		if (st->zero)
			mult_char('0', &st->words, st->width);
		else
			mult_char(' ', &st->words, st->width);
	}

}

static void align_width_u(sign_t *st)
{
	if (st->size_c < st->width)
	{
		st->width -= st->size_c;
		if (st->zero)
			mult_char('0', &st->words, st->width);
		else
			mult_char(' ', &st->words, st->width);
	}
}




static void align_int_u(sign_t *st, int uintmax)
{
	// if (mst->size_c = 0;
	if (st->dot > st->size_c)
	{
		precision_inteiro(st);
		//printf("teste");
		ft_putstr(st->conv, &st->words);
		width_int(st);
	}
	else if (st->width > st->size_c)
	{
		if (st->dot != 0 || uintmax == 1)
		{
			ft_putstr(st->conv, &st->words);
		}
		else
			st->size_c = 0;
		align_width_u(st);
	}
	else if (uintmax == 1)
		ft_putstr(st->conv, &st->words);

	// else if (st->dot == 0)
	// {
	// 	align_width(st);
	// }
}



int	check_max_u_int(int size_c)
{
	// char str[10];
	// int c;

	// str[0] = '4';
	// str[1] = '2';
	// str[2] = '9';
	// str[3] = '4';
	// str[4] = '9';
	// str[5] = '6';
	// str[6] = '7';
	// str[7] = '2';
	// str[8] = '9';
	// str[9] = '5';
	// c = 0;
	// while (str[c] != '\0' && conv[c] != '\0')
	// {
	// 	if (str[c] != conv[c])
	// 		break;
	// 	c++;
	// }

	if (size_c > 9)
		return (1);
	else
		return (0);

}

void specific_u(sign_t *st)
{
	int uintmax;

	uintmax = check_max_u_int(st->size_c);
	if (st->dot == 0 && !st->width && !st->align && st->conv[0] != '0')
		ft_putstr(st->conv, &st->words);
	if (st->align)
		align_int_u(st, uintmax);
	else
	{
		if (st->width > st->dot)
			width_int_u(st, uintmax);
		if (st->dot != -1)
			precision_inteiro(st);
		if (st->dot != 0 || uintmax == 1)
			ft_putstr(st->conv, &st->words);
	}

	free(st->conv);
	st->conv = NULL;
}

