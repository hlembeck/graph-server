#include "arr_algs.h"

segment max_subarray(long *arr, segment bounds){
	segment left, right, cross;
	long sum=LONG_MIN, temp=0;
	unsigned int mid;

	if(bounds.low == bounds.high){
		bounds.value = arr[bounds.low];
		return bounds;
	}
	mid = .5*(bounds.high+bounds.low);
	left.low = bounds.low;
	left.high = mid;
	right.low = mid+1;
	right.high = bounds.high;
	left = max_subarray(arr, left);
	right = max_subarray(arr, right);

	cross.low = mid;
	cross.high = mid;
	cross.value = 0;
	for(int i=mid;i>bounds.low-1;i--){
		temp += arr[i];
		if(temp > sum){
			sum = temp;
			cross.low = i;
		}
	}
	cross.value = sum;
	sum = LONG_MIN;
	temp = 0;
	for(int i=mid;i<bounds.high+1;i++){
		temp += arr[i];
		if(temp > sum){
			sum = temp;
			cross.high = i;
		}
	}
	cross.value += sum;

	if(left.value > right.value){
		if(cross.value > left.value)
			return cross;
		return left;
	}
	if(cross.value > right.value)
		return cross;
	return right;
}

segment max_subarray2(long *arr, int len){
	segment bounds = {0,0,arr[0]};
	segment terminal_max = bounds;
	for(int i=1;i<len;i++){
		if(terminal_max.value < 0){
			terminal_max.low = i;
			terminal_max.value = 0;
		}
		terminal_max.high = i;
		terminal_max.value += arr[i];

		if(terminal_max.value > bounds.value)
			bounds = terminal_max;
	}

	return bounds;
}

void max_heapify(long *arr, int len, int i){
	int max, temp;
	temp = (i<<1)+1;
	while(temp < len-1){
		if(arr[temp] > arr[i])
			max = temp;
		else
			max = i;
		temp += 1;
		if(arr[temp] > arr[max])
			max = temp;

		if(max != i){
			temp = arr[i];
			arr[i] = arr[max];
			arr[max] = temp;
			i = max;
			temp = (max<<1)+1;
		}
		else{
			break;
		}
	}
	return;
}

void max_heapify_recursive(long *arr, int len, int i){
	int max;
	int temp = (i<<1)+1;
	if(temp >= len-1)
		return;

	if(arr[temp] > arr[i])
		max = temp;
	else
		max = i;
	temp += 1;

	if(arr[temp] > arr[max])
		max = temp;
	if(max != i){
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
		max_heapify_recursive(arr,len,max);
	}
	return;
}

void max_heap(long *arr, int len){
	int i = (len>>1)-1;
	while(i>=0){
		max_heapify(arr, len, i--);
	}
	return;
}

void heapsort(long *arr, int len, int heapsize){
	int temp;
	max_heap(arr,len);
	for(int i=len-1;i>=0;i--){
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		max_heap(arr,i);
	}
	return;
}