#include "mlx_utils.h"
#include "string.h"


int main(int argc, char** argv)
{
	(void) argc; (void) argv;
	t_mlxu visual;
	memset(&visual, 0, sizeof (visual));
	mlxu_setup_new_display(&visual);
	mlxu_setup_new_win(&visual, "TESTING", (t_mlxu_2d){800,600,0});
	sleep(1);
	mlxu_terminate(&visual, "bye");
	return (0);
}
