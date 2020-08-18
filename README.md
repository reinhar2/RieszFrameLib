# CudaFrames

Implementation of the Cuda Algorithms of the Phd Thesis of Martin Reinhardt

## General Ideas:
 
 * using plain C++ to have easy comparable code between OpenMP, MPI, CUDA, and other stuff
 * 

## class structure:

main class:
 * main class for frames, images, data in general
 * one array for all data (z*height + y*width + x)
 * maximum 3D
 * member: would like to have dim3, but only available in CUDA
 * DataDim, struct: x, y, z, size_t
 * compatible with CUDA dim3?
 
