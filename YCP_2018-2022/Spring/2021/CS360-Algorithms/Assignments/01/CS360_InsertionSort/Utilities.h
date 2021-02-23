/* Utility function to create a random B[] array of length n */
void make_array(int D[], int n, int range)
{
	int i;
	D[0] = n;
	for (i = 1; i <= n; i++)
	{
		D[i] = rand() % range + 1;
	}
}

/* Utility function to copy B[] -> A[] */
void copy_array(int A[], int D[])
{
	int i;
	for (i = 0; i <= D[0]; i++)
	{
		A[i] = D[i];
	}
}

/* Utility function to get array length */
int length(int A[])
{
	return A[0];
}

/* Utility function to print sorted A[] array */
void print_array(int A[])
{
	int i;
	for (i = 1; i <= length(A); i++)
	{
		printf("%i ", A[i]);
	}
	printf("\n");
}

bool checkSorted(int A[]) {
    for (int i = 1; i < A[0]; i++) {
        if (A[i] > A[i+1]) {
            return false;
        }
    }
    return true;
}

