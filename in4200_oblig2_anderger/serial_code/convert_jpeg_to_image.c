#include "serial_functions.h"

void convert_jpeg_to_image(const unsigned char* image_chars, image *u)
{
    for (int i=0; i<(u->m); i++) {
        for (int j=0; j<(u->n); j++) 
        {
            u->image_data[i][j] = (float)image_chars[(u->n)*i + j];
        }
    }
}
