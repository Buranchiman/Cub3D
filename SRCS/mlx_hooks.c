/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:28:34 by wivallee          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:10 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/cube.h"

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
