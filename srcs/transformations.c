/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:48:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/03 03:49:11 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	apply_transformation(t_lform select, t_transform transform)
{
	printf("%c %d %d %d\n", select.shape, transform.x, transform.y, transform.z);
}
