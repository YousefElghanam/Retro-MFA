#include "Retro_MFA.h"

int cleanup(t_data *data, int res, char *msg)
{
	if (data->fd) {
		close (data->fd);
	}
	mlxu_terminate(&data->visual, msg);
	return (res);
}
