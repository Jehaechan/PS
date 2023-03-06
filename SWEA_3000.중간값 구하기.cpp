#include <stdio.h>

#define left (i << 1)
#define right (i << 1 | 1)
#define parent (i >> 1)
#define HEAPSIZE 200003

int max_heap[HEAPSIZE];
int min_heap[HEAPSIZE];
int max_size;
int min_size;

int compare(int par, int child, int mode) {		// whether the heap conditions are met or not
	if (par > child) {
		return mode ? 1 : 0;
	}
	return mode ? 0 : 1;
}

void push(int val, int mode) {	// mode - 0:min_heap / 1:max_heap
	int* heap = mode ? max_heap : min_heap;
	int* size = mode ? &max_size : &min_size;

	heap[++(*size)] = val;
	for (int i = *size; i != 1 && !compare(heap[parent], heap[i], mode);i = parent) {
		int temp = heap[parent];
		heap[parent] = heap[i];
		heap[i] = temp;
	}
}

void pop(int mode) {
	int* heap = mode ? max_heap : min_heap;
	int* size = mode ? &max_size : &min_size;

	heap[1] = heap[(*size)--];
	for (int i = 1;left <= *size;) {
		if (left == *size || compare(heap[left], heap[right], mode)) {
			if (!compare(heap[i], heap[left], mode)) {
				int temp = heap[left];
				heap[left] = heap[i];
				heap[i] = temp;
				i = left;
			}
			else {
				break;
			}
		}
		else {
			if (!compare(heap[i], heap[right], mode)) {
				int temp = heap[right];
				heap[right] = heap[i];
				heap[i] = temp;
				i = right;
			}
			else {
				break;
			}
		}
	}
}

void init() {
	max_size = 0;
	min_size = 0;
}

int A[5];

void sort() {
	for (int i = 0;i < 4;i++) {
		for (int j = i + 1;j < 5;j++) {
			if (A[i] > A[j]) {
				int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
}



int main() {
	//freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1;tc <= T;tc++) {
		init();
		push(1000000002, 0);
		push(-2, 1);
		A[1] = -1;
		A[3] = 1000000001;
		int N, ans = 0;
		scanf("%d %d", &N, &A[2]);
		for (int loop = 0;loop < N;loop++) {
			scanf("%d %d", &A[0], &A[4]);
			sort();
			if (A[1] < max_heap[1]) {
				int temp = A[1];
				A[1] = max_heap[1];
				pop(1);
				push(temp, 1);
			}
			if (A[3] > min_heap[1]) {
				int temp = A[3];
				A[3] = min_heap[1];
				pop(0);
				push(temp, 0);
			}
			ans += A[2];
			ans %= 20171109;
			push(A[0], 1);
			push(A[4], 0);
		}
		printf("#%d %d\n", tc, ans);
	}
}