#include "main_aux.h"

void exit_gracefully(void *to_free, int num_to_free)
{
	for (int i = 0; i < num_to_free; ++i)
		free(to_free[i]);
	free(to_free);
}