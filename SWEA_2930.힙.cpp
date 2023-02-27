#include <stdio.h>
#define parent i >> 1
#define left i << 1
#define right i << 1 | 1

int heap[100001];
int size;

void push(int key) {
	heap[++size] = key;
	for (int i = size;i != 1 && heap[i] > heap[parent];i = parent) {
		int temp = heap[i];
		heap[i] = heap[parent];
		heap[parent] = temp;
	}
}

void pop() {
	if (size == 0) {
		printf(" -1");
		return;
	}
	printf(" %d", heap[1]);
	heap[1] = heap[size--];
	for (int i = 1;left <= size;) {
		if ((size == left) || (heap[left] > heap[right])) {
			if (heap[left] > heap[i]) {
				int temp = heap[i];
				heap[i] = heap[left];
				heap[left] = temp;
				i = left;
			}
			else {
				return;
			}
		}
		else {
			if(heap[right] > heap[i]) {
				int temp = heap[i];
				heap[i] = heap[right];
				heap[right] = temp;
				i = right;
			}
			else {
				return;
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	heap[0] = -1;
	for (int tc = 1;tc <= T;tc++) {
		size = 0;
		printf("#%d", tc);
		int N;
		scanf("%d", &N);
		for (int i = 0;i < N;i++) {
			int mode;
			scanf("%d", &mode);
			if (mode == 1) {
				int key;
				scanf("%d", &key);
				push(key);
			}
			else {
				pop();
			}
		}
		puts("");
	}
}