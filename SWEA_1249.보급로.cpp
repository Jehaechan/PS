#include <stdio.h>
#include <string.h>
#define left i << 1
#define right i << 1 | 1
#define parent i >> 1

int move[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };

typedef struct heapnode {
	int cost;
	int x;
	int y;
}node;

int compare(node a, node b) {   // a < b?
	if (a.cost == b.cost) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
	return a.cost < b.cost;
}

node min_heap[10001];
char visited[100][100];
int map[100][100];
int cost[100][100];
int size;

void init() {
	memset(visited, 0, sizeof(char) * 100 * 100);
	visited[0][0] = 1;
	size = 0;
	min_heap[++size].cost = map[0][0];
	min_heap[size].x = 0;
	min_heap[size].y = 0;
}

void push(node Node) {
	min_heap[++size] = Node;
	for (int i = size;i != 1 && compare(min_heap[i], min_heap[parent]);i = parent) {
		node temp = min_heap[i];
		min_heap[i] = min_heap[parent];
		min_heap[parent] = temp;
	}
}

void pop() {
	min_heap[1] = min_heap[size--];
	for (int i = 1;left < size;) {
		if (size == left || compare(min_heap[left], min_heap[right])) {
			if (compare(min_heap[left], min_heap[i])) {
				node temp = min_heap[i];
				min_heap[i] = min_heap[left];
				min_heap[left] = temp;
				i = left;
			}
			else {
				break;
			}
		}
		else {
			if (compare(min_heap[right], min_heap[i])) {
				node temp = min_heap[i];
				min_heap[i] = min_heap[right];
				min_heap[right] = temp;
				i = right;
			}
			else {
				break;
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int tc = 1;tc <= T;tc++) {
		int N;
		scanf("%d", &N);
		for (int i = 0;i < N;i++) {
			char temp[101];
			scanf(" %s", temp);
			for (int j = 0;j < N;j++) {
				map[i][j] = temp[j] - '0';
			}
		}

		init();

		while (size) {
			node cur = min_heap[1];
			pop();

			int cur_x = cur.x;
			int cur_y = cur.y;
			int cur_cost = cur.cost;

			for (int i = 0;i < 4;i++) {
				int next_x = cur_x + move[i][0];
				int next_y = cur_y + move[i][1];

				if (next_x < 0 || next_y < 0 || next_x >= N || next_y >= N || visited[next_x][next_y])
					continue;

				node Node;
				Node.x = next_x;
				Node.y = next_y;
				Node.cost = cur_cost + map[next_x][next_y];
				cost[next_x][next_y] = Node.cost;

				visited[next_x][next_y] = 1;
				push(Node);
			}
		}

		printf("#%d %d\n", tc, cost[N - 1][N - 1]);
	}
}