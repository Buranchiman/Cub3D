/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillichien <chillichien@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:28:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/09 18:27:25 by chillichien      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

int	mouse_move(int x, int y, t_data *d)
{
	static int	first = 1;
	int			cx;
	int			cy;
	int			dx;

	(void)y;
	cx = SCRN_W / 2;
	cy = SCRN_H / 2;
	if (first)
	{
		mlx_mouse_move(d->mlx_ptr, d->win_ptr, cx, cy);
		first = 0;
		return (0);
	}
	dx = x - cx;
	if (dx != 0)
	{
		d->mouse_dx += dx;
		mlx_mouse_move(d->mlx_ptr, d->win_ptr, cx, cy);
	}
	return (0);
}

int	on_keydown(int keycode, void *param)
{
	t_data	*d;

	d = param;
	if (keycode == KEY_LEFT)
		d->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		d->keys.right = 1;
	else if (keycode == KEY_W)
		d->keys.w = 1;
	else if (keycode == KEY_A)
		d->keys.a = 1;
	else if (keycode == KEY_S)
		d->keys.s = 1;
	else if (keycode == KEY_D)
		d->keys.d = 1;
	else if (keycode == KEY_E)
		d->keys.e = 1;
	return (0);
}

int	on_keyup(int keycode, void *param)
{
	t_data	*d;

	d = param;
	if (keycode == KEY_ESC)
		ft_clean_exit(get_data(), 0, "See you soon👋");
	if (keycode == KEY_LEFT)
		d->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		d->keys.right = 0;
	else if (keycode == KEY_W)
		d->keys.w = 0;
	else if (keycode == KEY_A)
		d->keys.a = 0;
	else if (keycode == KEY_S)
		d->keys.s = 0;
	else if (keycode == KEY_D)
		d->keys.d = 0;
	else if (keycode == KEY_E)
		d->keys.e = 0;
	return (0);
}
