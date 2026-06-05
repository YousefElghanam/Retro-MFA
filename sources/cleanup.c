#include "Retro_MFA.h"

int cleanup(t_data *data, int res, char *msg)
{
	mlxu_terminate(&data->visual, msg);
	return (res);
}
