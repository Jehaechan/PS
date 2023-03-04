#include <stdio.h>

#define left i << 1
#define right i << 1 | 1
#define parent i >> i
#define HEAPSIZE 203

int max_heap[HEAPSIZE];
int min_heap[HEAPSIZE];
int max_size;
int min_size;
int A[7];

void init() {
	max_size = 0;
	min_size = 0;
}

void sort(int size) {
	for (int i = 0;i < size - 1;i++) {
		for (int j = i + 1;j < size;j++) {
			if (A[i] > A[j]) {
				int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1;tc <= T;tc++) {
		init();
		int N;
		scanf("%d %d", &N, &A[0]);
		for (int loop = 0;loop < N;loop++) {
			scanf("%d %d", &A[1], &A[2]);
			A[3] = min_heap[1];
			pop(1);
			A[4] = min_heap[1];
			pop(1);

			sort(3);	// 오름차순


		}
	}
}