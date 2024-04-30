#include "parallel_functions.h"
#include <mpi.h>
/* other needed header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

int main(int argc, char *argv[])
{
    int m, n, c, iters;
    int my_m, my_rank, num_procs;
    float kappa;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_file name */
    if (argc < 2)
    {
        printf("incorrect number of inputs. usage:\n");
        printf("kappa, iters, input-filename, output-filename\n");
        return 1;
    }
    kappa = atof(argv[1]); iters = atof(argv[2]); 
    input_jpeg_filename = argv[3]; output_jpeg_filename = argv[4];
    /* ... */

    if (my_rank==0) {
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    allocate_image (&whole_image, m, n);
    }

    MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&kappa, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    /* 1D horizontal decomposition of the m x n pixels evenly among the MPI processes */
    /* If there is a neighbor from below, allocate one more row; Same if there is neighbor from above */
    my_m = m/num_procs+2; // base size + 2 ghost rows
    if (my_rank<(m%num_procs)) {my_m++; } // add eventual remainder rows
    if (my_rank == 0) { my_m--; } // if top or bottom, only 1 ghost, so remove 1 row
    if (my_rank == num_procs-1) { my_m--; }
    // my_m = ...;

    allocate_image (&u, my_m, n);
    allocate_image (&u_bar, my_m, n);

    /* each process asks process 0 for a partitioned region */
    /* of image_chars and copy the values into u */
    int stride = m/num_procs;
    int remainder = m%num_procs;
    int my_start = my_rank*stride;
    int my_end = my_start + stride - 1;

    if (my_rank < remainder) {
        my_start += my_rank;
        my_end += my_rank + 1;
    }else {
        my_start += remainder;
        my_end += remainder;
    }
    my_end = min(my_end, m-1);

    // mpi_comm calls
    // my_image_chars = (unsigned char*)malloc((my_end - my_start + 1)*n*sizeof(unsigned char));
    my_image_chars = (unsigned char*)malloc(my_m*n*sizeof(unsigned char));
    MPI_Scatter(
            image_chars, stride*n, MPI_UNSIGNED_CHAR,
            my_image_chars, (my_end - my_start + 1)*n, MPI_UNSIGNED_CHAR,
            0, MPI_COMM_WORLD
            );
    /*  ...  */
    /*  ...  */

    convert_jpeg_to_image (my_image_chars, &u);
    iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);
    
    /* each process sends its resulting content of u_bar to process 0 */
    /* process 0 receives from each process incoming values and */
    /* copy them into the designated region of struct whole_image */
    MPI_Barrier(MPI_COMM_WORLD);
    image my_u;
    if (my_rank==0 || my_rank == num_procs-1) {
        allocate_image(&my_u, my_m-1, n);
    } else {
        allocate_image(&my_u, my_m-2, n);
    }
    if (my_rank == 0) {
        for (int i=0; i<my_u.m; i++) {
            for (int j=0; j<my_u.n;j++) {
                my_u.image_data[i][j] = u_bar.image_data[i][j];
            }
        }
    }else if (my_rank == num_procs-1) {
        for (int i=0; i<my_u.m; i++) {
            for (int j=0; j<my_u.n;j++) {
                my_u.image_data[i][j] = u_bar.image_data[i+1][j];
            }
        }
    }else {
        for (int i=0; i<my_u.m; i++) {
            for (int j=0; j<my_u.n;j++) {
                my_u.image_data[i][j] = u_bar.image_data[i+1][j];
            }
        }
    }
    int gather_count = (my_rank == 0 || my_rank == num_procs-1)?(my_m-1)*n:(my_m-2)*n;
    
    MPI_Gather(
            my_u.image_data[0], gather_count, MPI_FLOAT, 
            whole_image.image_data[0], gather_count, MPI_FLOAT, 0, 
            MPI_COMM_WORLD
            );
    /*  ...  */

    if (my_rank==0) {
    convert_image_to_jpeg(&whole_image, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
    deallocate_image (&whole_image);
    }

    deallocate_image (&u);
    deallocate_image (&u_bar);

    MPI_Finalize ();
    return 0;
}
