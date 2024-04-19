#include "serial_functions.h"

void convert_image_to_jpeg(const image *u, unsigned char* image_chars)
{
    for (int i=0; i<(u->m); i++) {
        for (int j=0; j<(u->n); j++) 
        {
            image_chars[(u->n)*i + j] = (unsigned char) u->image_data[i][j] ;
        }
    }
}
