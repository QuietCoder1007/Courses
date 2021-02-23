// CS360 Insertion Sort
// Spring 2021

// So we can use scanf in Visual Studio
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Utilities.h"

#define INFINITY 32769
#define NUM_AVG 10               // Number of sorting runs to average
#define MAX_ELEMENTS 65537      // Maximum number of elements in input array
#define HIGH_RANGE 32768        // Maximum value for large input range
#define LOW_RANGE 1024			// Maximum value for small input range
#define MAX_RUNS 13             // Maximum number of 2^i input sizes to run
#define NUM_SORTS 1            // Number of sorting algorithms

int insertion_sort(int A[]);
int count;

int main(void)
{
	int A[MAX_ELEMENTS],D[MAX_ELEMENTS];
	int n,i,j,k;
	double counter[NUM_SORTS][MAX_RUNS][2];

	srand(0);
	// Initialize counter array
	for (k=0; k<NUM_SORTS; k++)
	{
		for (j=0; j<MAX_RUNS; j++)
		{
			counter[k][j][0] = 0.0;
			counter[k][j][1] = 0.0;
		}
	}

	// Set number of elements in initial array and start counter
	n = 16;
	i = 0;

	// Loop for each input size
	while ((n <= MAX_ELEMENTS) && (i < MAX_RUNS))
	{
		// Loop with random input arrays of fixed size to average results
		for (j = 0; j < NUM_AVG; j++)
		{
			for (k = 0; k < NUM_SORTS; k++) {
				// Generate random array of size n for large range
				make_array(D, n, HIGH_RANGE);

				// Run sort
				copy_array(A, D);
				//print_array(A);
				count = 0;
				counter[k][i][0] += (insertion_sort(A) / ((double)NUM_AVG));
				if (!checkSorted(A)) {
				    printf("Sort incorrect!\n");
				    exit(0);
				}
				//print_array(A);

				// Generate random array of size n for small range
				make_array(D, n, LOW_RANGE);

				// Run sort
				copy_array(A, D);
				//print_array(A);
				count = 0;
				counter[k][i][1] += (insertion_sort(A) / ((double)NUM_AVG));
                if (!checkSorted(A)) {
                    printf("Sort incorrect!\n");
                    exit(0);
                }
				//print_array(A);
			}
		}

		// Double number of input elements for next run
		n *= 2;
		i++;
	}

	/* Print avg runtime results */
	FILE *fp = fopen("insertionOutput.csv","w");
	n = 16;
    printf("%-20s %-20s %-20s\n", "n", "Insertion-32768", "Insertion-1024");
    fprintf(fp,"%-20s, %-20s, %-20s\n", "n", "Insertion-32768", "Insertion-1024");
	printf("-------------------- -------------------- --------------------\n");
	for (j = 0; j < i; j++)
	{
		printf("%-20d,", n);
        fprintf(fp, "%-20d,", n);
		for (k = 0; k < NUM_SORTS; k++)
		{
			if (k == NUM_SORTS - 1) {
				// No comma for last piece
				printf("%-20d,%-20d", (int)counter[k][j][0], (int)counter[k][j][1]);
                fprintf(fp, "%-20d,%-20d", (int)counter[k][j][0], (int)counter[k][j][1]);
			}
			else {
				printf("%-20d,%-20d,", (int)counter[k][j][0], (int)counter[k][j][1]);
                fprintf(fp, "%-20d,%-20d,", (int)counter[k][j][0], (int)counter[k][j][1]);
			}
		}
		printf("\n");
        fprintf(fp,"\n");
		n *= 2;
	}
	fclose(fp);

//	int key;
//	printf("Enter a value to quit");
//	scanf("%d",&key);
	
	return 0;
}


/* Insertion sort routine */
int insertion_sort(int A[])
{
    int i, j, key;

    /* TODO: add INSERTION-SORT() code */
    for( j = 2; j <= length(A); j++ )
    {
        count++;
        key = A[j];
        i = j - 1;
        while( i > 0 && A[i] > key )
        {
            count++;
            A[i+1] = A[i];
            i = i - 1;
        }
        count++;
        A[i+1] = key;
    }
    count++;
    return count;
}

