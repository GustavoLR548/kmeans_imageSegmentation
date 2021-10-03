

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>     
#include "kmeans_omp.c"
#include "bmpfuncs.h"
#include "bmpfuncs.c"      
#include "kmeans_ser.c"   
#define GIG               1000000000
#define ITERS 			 100
#define TOLERANCE 		 0.5
#define DIM 		     512
#define CLUSTERS 		 50

int main(void){

	float* readImage(const char *filename, int* widthOut, int* heightOut);
	void storeImage(float *imageOut, const char *filename, int rows, int cols, const char* refFilename);
        float* k_means_omp(float *imageIn, int clusters, int dimension, int iterations);
 	float* k_means_serial(float *imageIn, int clusters, int dimension, int iterations);
	float* k_means_serial_optimized(float *imageIn, int clusters, int dimension, int iterations);

        double start,end;

        int w = DIM;
        int* width = &w;
	int h = DIM;
        int* height = &h;

	const char *imageInFile =  "testImageGrey.bmp";
        const char *imageOutFile =  "testImage512OMP_out.bmp";
	const char* refFilename = "testImageGrey.bmp";

	float* imageIn = readImage(imageInFile, width, height);

	printf("iters = %d\n", ITERS);
	printf("clusters = %d\n", CLUSTERS);

	printf("CPU CODE RUNNING \n");
	start = omp_get_wtime();
        float *imageOut2 = k_means_serial(imageIn, CLUSTERS, DIM, ITERS);
        end = omp_get_wtime();
        printf("CPU TIME: %f seconds \n\n", end-start);


	printf("OMP CODE RUNNING \n");
	start = omp_get_wtime(); 
        float *imageOut = k_means_omp(imageIn, CLUSTERS, DIM, ITERS);
        end = omp_get_wtime();
        printf("OMP TIME: %f seconds \n\n", end-start);


        storeImage(imageOut,imageOutFile, w, h, refFilename);
}
