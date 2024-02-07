/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_options.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:10:08 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 17:57:11 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_OPTIONS_H
# define RENDER_OPTIONS_H

/* SMALL DEFINES */

// Small value defining an ofset
# define EPSILON 1e-4
// Closest t-value where an object can appear
# define NEAR_CLIP 1
// Furthest t-value where an object can appear
# define FAR_CLIP 1500
// Width and height of window
# define WIDTH 720
# define HEIGHT 480

/* SHADING */

// Number of recursive calls for reflection (mirror-like surfaces)
# define MAX_REFLECTION 3

/* SHADOWS */

// Small ofset to correct shadow fuzz
# define SHADOW_BIAS 1e-4
// Defines if a plane creates a shadow or not as they are quite big
// Only used in directional lights (spherical and ambient are always
// subject to plane shadowing)
# define PLANE_SHADOW 0

#endif
