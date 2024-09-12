#include<stdio.h>
#include<stdlib.h>

/* main method */
int main(int args, char** argv){
	int N, i;
	printf("Please enter number of elements in array: ");
	scanf("%d", &N);

	float arr[N];

	for (i=0; i<N; i++){
	  printf("Please enter element %d of array: ", (i+1));
	  scanf("%f", &arr[i]);
	}

	printf("Given array is: ");
	printf("[");
	for (i=0; i < N-1; i++){
	  printf("%f, ", arr[i]);
	}
	printf("%f]\n", arr[N-1]);

	float temp;
	int currLoc;
	for (i=1; i < N; i++){
		currLoc = i;
		while (currLoc > 0 && arr[currLoc-1] > arr[currLoc]){
			temp = arr[currLoc];
			arr[currLoc] = arr[currLoc-1];
			arr[currLoc-1] = temp;
			currLoc--;
		}
	}

	printf("Sorted array is: ");
	printf("[");
	for (i=0; i < N-1; i++){
	  printf("%f, ", arr[i]);
	}
	printf("%f]\n", arr[N-1]);

	return 0;
}
