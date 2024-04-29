#ifndef __in3200_oblig2_parallel__
#define __in3200_oblig2_parallel__

#include "serial_functions.h"
#include <mpi.h>

void iso_diffusion_denoising_parallel (image *u, image *u_bar, float kappa, int iters);

#endif
