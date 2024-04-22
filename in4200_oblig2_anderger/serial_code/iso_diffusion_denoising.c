#include "serial_functions.h"
#include <stdio.h>

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters)
{
    for (int cols = 0; cols < (u->n); cols++) {
        u_bar->image_data[0][cols] = u->image_data[0][cols]; // Copy top row
        printf("u[m-1=%d][%d] = %f\n", (u->m)-1, cols, u->image_data[(u->m)-1][cols]);
        u_bar->image_data[(u->m) - 1][cols] = u->image_data[(u->m) - 1][cols]; // Copy bottom row
    }

    for (int rows = 0; rows < (u->m); rows++) {
        u_bar->image_data[rows][0] = u->image_data[rows][0]; // Copy leftmost column
        printf("u[%d][n-1=%d] = %f\n", rows, (u->n)-1, u->image_data[rows][(u->n)-1]);
        u_bar->image_data[rows][(u->n) - 1] = u->image_data[rows][(u->n) - 1]; // Copy rightmost column
    }
    // image *temp;
    //
    // for (int iteration=0; iteration<iters; iteration++) 
    // {
        // for (int i=1; i<(u->m)-1; i++) 
        // {
        //     for (int j=1; j<(u->n)-1; j++) 
        //     {
        //         printf("denoising loop i=%d, j=%d\n", i, j);
        //         printf("current image data: %f\n", u->image_data[i][j]);
        //         u_bar->image_data[i][j] = u->image_data[i][j] + kappa*(
        //                 (u->image_data[i-1][j]) + (u->image_data[i][j-1])
        //                     -4.*(u->image_data[i][j])
        //                 + (u->image_data[i][j+1]) + (u->image_data[i+1][j])
        //                 );
        //         printf("denoised image data: %f\n", u_bar->image_data[i][j]);
        //     }
        // }
    //     temp = u_bar;
    //     u_bar = u;
    //     u = temp;
    // }
}
