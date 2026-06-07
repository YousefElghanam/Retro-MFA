/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:26:13 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 03:36:07 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

// -----------------------------------------------------------------------------
// headers
// -----------------------------------------------------------------------------

# include <mlx.h>
// for libft replacements
# include <strings.h> // bzero
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "lists.h"

// -----------------------------------------------------------------------------
// environment macros
// -----------------------------------------------------------------------------

# define BYTE			8
# define ERR_MLX_INI	"mlx_init() failed"						// 17
# define ERR_MLX_PTR	"no mlx pointer"						// 14
# define ERR_MLX_WIN	"mlx_new_mlxu_win() failed"				// 25
# define ERR_MLX_IMG	"mlx_new_image() failed"				// 22
# define ERR_MLX_GDA	"mlx_get_data_addr() failed"			// 26
# define ERR_MEM_WIN	"allocation for new window failed"		// 32 legacy
# define ERR_MEM_IMG	"allocation for new image failed"		// 31
# define ERR_XPM_ARG	"invalid args for loading XPM"			// 28
# define ERR_MLX_XPM	"mlx_xpm_file_to_image() failed"		// 30

// -----------------------------------------------------------------------------
// color macros
// -----------------------------------------------------------------------------

# define BLACK		0x000000
# define WHITE		0xFFFFFF
# define GREEN		0x00FF00
# define RED		0xFF0000
# define BLUE		0x0000FF
# define YELLOW		0xFFFF00
# define CYAN		0x00FFFF
# define MAGENTA	0xFF00FF
# define DARK_GREY	0x444444

// -----------------------------------------------------------------------------
// X server KEYS
// -----------------------------------------------------------------------------

# define B_LEFT		1 // mouse left click
# define B_MIDDLE	2 // mouse middle click
# define B_RIGHT	3 // mouse right click
# define B_WHEEL_UP	4 // mouse wheel
# define B_WHEEL_DN	5 // mouse wheel
# define B_SIDE_DN	8 // mouse side buttons 42 campus
# define B_SIDE_UP	9 // mouse side buttons 42 campus
# define K_W		119
# define K_A		97
# define K_S		115
# define K_D		100
# define K_Q		113
# define K_E		101
# define K_SPACE	32
# define K_PLUS		43
# define K_MINUS	45
# define K_SHIFT_L	65505
# define K_SHIFT_R	65506
# define K_CTRL_L	65507
# define K_CTRL_R	65508
# define K_ALT		65513
# define K_ALTGR	65027
# define K_ENTER	65293
# define K_HOME		65360
# define K_END		65367
# define K_ESC		65307
# define K_LEFT		65361
# define K_UP		65362
# define K_RIGHT	65363
# define K_DOWN		65364
# define K_PGUP		65365
# define K_PGDOWN	65366
# define K_INS		65379
# define K_DEL		65535

// -----------------------------------------------------------------------------
// X server HOOKS (full list X11/X.h)
// -----------------------------------------------------------------------------

# define H_KEY_PRESS		2
# define H_KEY_RELEASE		3
# define H_MOUSE_PRESS		4
# define H_MOUSE_RELEASE	5
# define H_MOUSE_MOVE		6
# define H_MOUSE_ENTER		7
# define H_MOUSE_LEAVE		8
# define H_WIN_FOCUS		9
# define H_WIN_UNFOCUS		10
# define H_EXPOSE			12
# define H_CREATE			16
# define H_DESTROY			17
# define H_UNMAP_NOTIFY		18
# define H_MAP_NOTIFY		19
# define H_CONFIG_NOTIFY	22
# define H_CONFIG_REQUEST	23
# define H_RESIZE_REQUEST	25

/* event masks taken from X.h
#define NoEventMask			0L
#define KeyPressMask			(1L<<0)
#define KeyReleaseMask			(1L<<1)
#define ButtonPressMask			(1L<<2)
#define ButtonReleaseMask		(1L<<3)
#define EnterWindowMask			(1L<<4)
#define LeaveWindowMask			(1L<<5)
#define PointerMotionMask		(1L<<6)
#define PointerMotionHintMask		(1L<<7)
#define Button1MotionMask		(1L<<8)
#define Button2MotionMask		(1L<<9)
#define Button3MotionMask		(1L<<10)
#define Button4MotionMask		(1L<<11)
#define Button5MotionMask		(1L<<12)
#define ButtonMotionMask		(1L<<13)
#define KeymapStateMask			(1L<<14)
#define ExposureMask			(1L<<15)
#define VisibilityChangeMask		(1L<<16)
#define StructureNotifyMask		(1L<<17)
#define ResizeRedirectMask		(1L<<18)
#define SubstructureNotifyMask		(1L<<19)
#define SubstructureRedirectMask	(1L<<20)
#define FocusChangeMask			(1L<<21)
#define PropertyChangeMask		(1L<<22)
#define ColormapChangeMask		(1L<<23)
#define OwnerGrabButtonMask		(1L<<24)
*/

// -----------------------------------------------------------------------------
// datatypes
// -----------------------------------------------------------------------------

typedef struct s_mlxu_2d // LEGACY structure, make 2d coord?
{
	int		x;
	int		y;
	int		color;
}	t_mlxu_2d;

typedef struct s_mlxu_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_mlxu_color;

typedef struct s_mlxu_img
{
	void		*ptr;
	void		*mlx_ptr;
	void		*mem;
	int			bits_pixel;
	int			bytes_line;
	int			endian;
	t_mlxu_2d	offset;			// see mlxu_setup_buffer_offset
	t_mlxu_2d	size;			// mainly for textures of different sizes
}	t_mlxu_img;

typedef struct s_mlxu_win
{
	void		*ptr;
	void		*mlx_ptr;
	char		*title;
	t_mlxu_img	buffer_1;
	t_mlxu_img	buffer_2;
	t_mlxu_2d	size;
}	t_mlxu_win;

typedef struct s_mlxu_active
{
	t_mlxu_win	*win;
	t_mlxu_img	*img;
}	t_mlxu_active;

typedef struct s_mlxu
{
	void			*mlx_ptr;
	t_mlxu_2d		dsp_size;
	t_list			*windows;
	t_list_dl		*images;
	t_mlxu_active	active;
}	t_mlxu;

// -----------------------------------------------------------------------------
// setup mlx
// -----------------------------------------------------------------------------

// Creates a new X environment with MiniLibX.
int		mlxu_setup_new_display(t_mlxu *env);
// Creates a new window in the current X environment with a double image buffer.
// Multiple windows can be created. The lastes one is env->active.win.
int		mlxu_setup_new_win(t_mlxu *env, char *title, t_mlxu_2d size);
// Creates a new ready-to-use image buffer to be added to fully rendered images.
// Images are organizes as circulat double linked lists. Acive one is saved.
int mlxu_setup_new_buffer(t_mlxu *env);
// Create a ready-to-use buffer from an XPM file
int		mlxu_create_buffer_from_xpm(t_mlxu *env, t_mlxu_img *buffer,
			char *path);

// -----------------------------------------------------------------------------
// terminate mlx
// -----------------------------------------------------------------------------

// Can print an error MSG to STDERR and clears used X environment.
int		mlxu_terminate(t_mlxu *env, char *msg);

// -----------------------------------------------------------------------------
// image buffer
// -----------------------------------------------------------------------------

// Writes a pixel directly to the currently active window buffer.
void	mlxu_pixel_put_buffer(t_mlxu *env, int x, int y, int color);
// Retrieves a pixel color from a given buffer (window/image, texture ...)
int		mlxu_pixel_get_buffer(t_mlxu_img *buffer, int x, int y);
// Resets all pixels in a buffer to black color.
void	mlxu_clear_buffer(t_mlxu_img *buffer);
// Flushed the currently active buffer to the screen and alternates buffers.
void	mlxu_flush_buffer(t_mlxu *env);

#endif
