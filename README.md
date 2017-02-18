# Optimized Matrix Multiplication

Approx. 120x Speedup for 1000x1000 matrices:
--------------------------------------------

Requirements:
-------------

	OpenMP installed.

Compile Code:
-------------
	
	Makefile included.

Example Snippets:
-----------------

	START TIMER:
	
	struct timespec start, end;
	double microsecs = 0.0;


	SINGLE MULIPLICATION:
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	Multiplier::multiplyMatrixSeq/Parallel/ParallelOptimized(mat1, mat2, output_matrix);
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	microsecs = (double) ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000);


		
	ITERTATIVE MULTIPLICATION:

	void printData(bool printheader, int type, int size, int iterations)
	
	* printheader	: true- prints column name, false- doesn't print column name	
	* type		: 0 - sequential, 1- parallel, 2- parallel optimized
	* size		: matrix width/ height
	* iterations	: number of iterations


