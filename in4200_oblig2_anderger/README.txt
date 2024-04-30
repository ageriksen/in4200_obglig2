# Compiling
The code can be compiled in this folder through either

    make serial
    make parallel
    make

the latter will compile both versions of the task as well as the "simple-jpeg" library.
there are similar commands for clean

    make serial_clean
    make parallel_clean
    make clean

the latter will clean both versions of the code. 

# Running
Running the code requires providing
    kappa iters input-filename output-filename
after the executable. For the parallel version this is mpirun.


# Thoughts
The parallel implementation has not been tested on more than 2 processors, and not
on the cluster, regrettable though that is. 
The gathering up of the disparate images is not well implemented and should be revisited 
given further work. 
I stumbled over the halo rows when gathering and managed a poor solution which leaves a visible
"seam" where the images are joined. 
