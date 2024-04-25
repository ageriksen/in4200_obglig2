#include "serial_functions.h"
#include <stdlib.h>

void deallocate_image(image *u)
{
    free(u->image_data);
    // free(u);
}
