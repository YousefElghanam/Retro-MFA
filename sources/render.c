#include "Retro_MFA.h"

static void prt_frameinfo(t_debug* dinfo, t_list_dl *img_node)
{
	if (!DEBUG)
		return ;
	dinfo->frame++;
	printf("frame #%i: node %p mlx_img %p\n",
		dinfo->frame, img_node, ((t_mlxu_img*) img_node->content)->ptr);
}

void rnd_frame(t_data *data)
{
	prt_frameinfo(&data->dinfo, data->visual.active.img_node);
	mlxu_flush_buffer(&data->visual);
	usleep(FRAME_SLEEPTIME);
}

int keyhooks(int key, void* param)
{
	t_data* data = param;
	t_list_dl* node;
	if (key == K_Q || key == K_ESC)
		mlx_loop_end(data->visual.mlx_ptr);
	else if (key == K_LEFT || key == K_UP)
	{
		node = data->visual.active.img_node;
		data->visual.active.img = node->prev->content;
		data->visual.active.img_node = node->prev;
		rnd_frame(data);
	}
	else if (key == K_RIGHT || key == K_DOWN)
	{
		node = data->visual.active.img_node;
		data->visual.active.img = node->next->content;
		data->visual.active.img_node = node->next;
		rnd_frame(data);
	}
	return (0);
}
