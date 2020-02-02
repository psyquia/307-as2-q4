#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h> 

#define RANDOM_QUICKSORT_VARIANT 1 	/// 1 if k random-quicksort variant 
									/// 0 if random-quicksort 

using namespace std;

int n_tests[] = {1000, 2000, 4000, 8000, 16000, 32000};


void swap(int * x, int * y){
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

int partition(int * arr, int left, int right){
	int pivot = arr[right];

	int i = left;

	for(int k = left; k < right; k++){
		if(arr[k] < pivot){
			swap(&arr[k], &arr[i++]);
		}
	}
	swap(&arr[i], &arr[right]);
	return i;
}

int randomizedPartition(int * arr, int left, int right){
	int i = rand() % (right-left+1) + left;

	/// SWAP
	swap(&arr[i], &arr[right]);

	return partition(arr, left, right);
}

void randomizedQuicksort(int * arr, int left, int right){
	if(left < right){
		int q = randomizedPartition(arr, left, right);
		randomizedQuicksort(arr, left, q-1);
		randomizedQuicksort(arr, q+1, right);
	}
}

void insertionSort(int * arr, int left, int right){
	int key, j;
	for(int i = left+1; i <= right; i++){
		key = arr[i];
		j = i - 1;
		while(j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			--j;
		}
		arr[j+1] = key;
	}
}

void krandQuicksort(int * arr, int left, int right, int k){
	if( (right - left + 1) < k){
		insertionSort(arr,  left, right);
		return;
	}
	int q = randomizedPartition(arr, left, right);
	krandQuicksort(arr, left, q-1, k);
	krandQuicksort(arr, q+1, right, k);
}

int main(){
	struct timespec start, end;

	srand(time(NULL));

#if RANDOM_QUICKSORT_VARIANT
	
	int ks[] = {50,60,70,80,90,100,110};

	for(int k : ks)
	{	
		cout << "with k = n/" << k << ": "<< endl;
#endif

		for(int arr_size : n_tests)
		{
			int unsorted[arr_size];
			for(int i = 0; i < arr_size; i++)
				unsorted[i] = rand() % 100;

			clock_gettime(CLOCK_MONOTONIC, &start);

			ios_base::sync_with_stdio(false);

#if RANDOM_QUICKSORT_VARIANT
			krandQuicksort(unsorted, 0, arr_size-1, (int)(arr_size/k));
#else
			randomizedQuicksort(unsorted, 0, arr_size-1);
#endif

			clock_gettime(CLOCK_MONOTONIC, &end);

			double time_taken;
			time_taken = (end.tv_sec - start.tv_sec) * 1e9;
			time_taken = (time_taken + (end.tv_nsec - start.tv_nsec) * 1e-9);

			//if (arr_size == 50) {for (int i : unsorted) {cout << i; cout << ", ";} cout << endl;}

			cout << "n = " << arr_size << "; ";
			cout << "Time taken is: " << fixed << time_taken << setprecision(5);
			cout << " sec" << endl;
		}

#if RANDOM_QUICKSORT_VARIANT
	}
#endif

	return 0;
}
