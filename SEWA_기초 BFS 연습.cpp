#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void bfs_init(int N, int map[10][10]);
extern int bfs(int x1, int y1, int x2, int y2);

static int test_bfs() {
	int N;
	int map[10][10];
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	bfs_init(N, map);
	int M;
	int score = 100;
	scanf("%d", &M);
	for (int i = 0; i < M; ++i) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		int result = bfs(x1, y1, x2, y2);
		int dist;
		scanf("%d", &dist);
		if (result != dist) score = 0;
	}
	return score;
}

int main() {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);
	printf("#total score : %d\n", test_bfs());

	return 0;
}

////////////////////// User Code ///////////////////////

int arr[12][12];

void bfs_init(int map_size, int map[10][10]) {
	for (int i = 0;i < 12;i++)
		for (int j = 0;j < 12;j++)
			arr[i][j] = 1;
	for (int i = 0;i < map_size;i++)
		for (int j = 0;j < map_size;j++)
			arr[i + 1][j + 1] = map[i][j];
}

struct coordinate {
	int x;
	int y;
};

coordinate move[4] = { {-1,0},{1,0},{0,-1},{0,1} };
char visited[12][12];
int distance[12][12];

int bfs(int x1, int y1, int x2, int y2) {
	for (int i = 0;i < 12;i++)
		for (int j = 0;j < 12;j++)
			visited[i][j] = 0;

	int front = 0, rear = 0;

	coordinate queue[1000];
	queue[front].x = y1;
	queue[front++].y = x1;
	distance[y1][x1] = 0;
	while (front != rear) {
		coordinate cur = queue[rear++];
		int cur_x = cur.x;
		int cur_y = cur.y;
		int new_distance = distance[cur_x][cur_y] + 1;
		if (cur_x == y2 && cur_y == x2) {
			return new_distance - 1;
		}
		for (int i = 0;i < 4;i++) {
			int next_x = cur_x + move[i].x;
			int next_y = cur_y + move[i].y;
			if ((!arr[next_x][next_y]) && (!visited[next_x][next_y])) {
				visited[next_x][next_y] = 1;
				queue[front].x = next_x;
				queue[front++].y = next_y;
				distance[next_x][next_y] = new_distance;
			}
		}
	}
	return -1;
}

/*
최단 거리를 구해야 하므로 DFS보다 BFS가 유리한 것
*/