#include "serial_functions.h"
/* other needed header files .... */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <time.h>

// void test_image_conversion()
// {
//   int m, n, c, iters;
//   float kappa;
//   image u, u_bar;
//   unsigned char *image_chars;
//   char *input_jpeg_filename = "../mona_lisa_noisy.jpg"
//       , *output_jpeg_filename = "../mona_lisa_denoised.jpg";
//   import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
//
//   allocate_image (&u, m, n);
//   convert_jpeg_to_image (image_chars, &u);
//
//   convert_image_to_jpeg (&u, image_chars);
//   export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
// }

// void test_diffusion()
// {
//     int m=4, n=4;
//     // srand(time(NULL));
//     srand(5);
//
//
//     // int counter;
//     float *data_storage = (float*)malloc(n*m*sizeof(float));
//     float **data = (float**) malloc(m*sizeof(float*));
//     for (int i=0; i<m; i++) { data[i] = &data_storage[i*n]; }
//     int area=m*n;
//     for (int i=0; i<m; i++)
//     {
//         for (int j=0; j<n; j++) 
//         {
//             data[i][j] = rand()%(area);
//         }
//     }
//     image u, u_bar;
//     u.image_data = data;
//     u.m = m; u.n = n;
//
//     u_bar.m = m;
//     u_bar.n = n;
//     float *data2_storage = (float*)malloc(n*m*sizeof(float));
//     float **data2 = (float**) malloc(m*sizeof(float*));
//     for (int i=0; i<m; i++) { data2[i] = &data2_storage[i*n]; }
//     
//     for (int i=0; i<m; i++)
//     {
//         for (int j=0; j<n; j++) 
//         {
//             data2[i][j] = INT_MAX;
//         }
//     }
//     u_bar.image_data = data2;
//     
//
//
//     printf("test image array:\n");
//     printf("[%f %f %f %f]\n", 
//             u.image_data[0][0], u.image_data[0][1], u.image_data[0][2], u.image_data[0][3]);
//     printf("[%f %f %f %f]\n", 
//             u.image_data[1][0], u.image_data[1][1], u.image_data[1][2], u.image_data[1][3]);
//     printf("[%f %f %f %f]\n", 
//             u.image_data[2][0], u.image_data[2][1], u.image_data[2][2], u.image_data[2][3]);
//     printf("[%f %f %f %f]\n", 
//             u.image_data[3][0], u.image_data[3][1], u.image_data[3][2], u.image_data[3][3]);
//
//     float kappa = 0; int iters = 1;
//     iso_diffusion_denoising (&u, &u_bar, kappa, iters);
//
//     printf("test image array diffusion:\n");
//     printf("[%f %f %f %f]\n", 
//             u_bar.image_data[0][0], u_bar.image_data[0][1], u_bar.image_data[0][2], u_bar.image_data[0][3]);
//     printf("[%f %f %f %f]\n", 
//             u_bar.image_data[1][0], u_bar.image_data[1][1], u_bar.image_data[1][2], u_bar.image_data[1][3]);
//     printf("[%f %f %f %f]\n", 
//             u_bar.image_data[2][0], u_bar.image_data[2][1], u_bar.image_data[2][2], u_bar.image_data[2][3]);
//     printf("[%f %f %f %f]\n", 
//             u_bar.image_data[3][0], u_bar.image_data[3][1], u_bar.image_data[3][2], u_bar.image_data[3][3]);
//     
// }

int main(int argc, char *argv[])
{

    // test_image_conversion();
    // return -14;
    // test_diffusion();
    // return -6;
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename */
    if (argc < 2)
    {
      printf("incorrect number of inputs. usage:\n");
      printf("kappa, iters, input-filename, output-filename\n");
      return 1;
    }
    kappa = atof(argv[1]); iters = atof(argv[2]); 
    input_jpeg_filename = argv[3]; output_jpeg_filename = argv[4];
    /* ... */
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

    allocate_image (&u, m, n);
    allocate_image (&u_bar, m, n);
    convert_jpeg_to_image (image_chars, &u);

    iso_diffusion_denoising (&u, &u_bar, kappa, iters);

    convert_image_to_jpeg (&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image (&u);
    deallocate_image (&u_bar);

    return 0;
}
