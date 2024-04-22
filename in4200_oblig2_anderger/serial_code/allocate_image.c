#include "serial_functions.h"
#include <stdlib.h>

void allocate_image(image *u, int m, int n)
{
    u->m = m;
    u->n = n;
    
    float *data_storage = (float*)malloc(n*m*sizeof(float));
    float **data = (float**) malloc(m*sizeof(float*));

    for (int i=0; i<m; i++) { data[i] = &data_storage[i*n]; }

    u->image_data = data;
}
