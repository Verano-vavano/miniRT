/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_options.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:10:08 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 20:10:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_OPTIONS_H
# define RENDER_OPTIONS_H

/* SHADOWS */

// Small ofset to correct shadow fuzz
# define SHADOW_BIAS 1e-4
// Defines if a plane creates a shadow or not as they are quite big
// Only used in directional lights (spherical and ambient are always
// subject to plane shadowing)
# define PLANE_SHADOW false

#endif
