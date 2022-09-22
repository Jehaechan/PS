#include <iostream>
#include <queue>
using namespace std;

typedef struct coordinate {
	char x;
	char y;
} coord;

char addval[4][2] = { {0, 1},{1, 0},{0, -1},{-1, 0} };
int arr[100][100];
int visit[100][100];
int R, C;

void clear_visit() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			visit[i][j] = 0;
}

int res2;
int res1;

int bfs() {
	int sum = 0;
	res1 = 0;
	queue<coord> q;
	coord start;
	start.x = 0;
	start.y = 0;
	visit[0][0] = 1;
	q.push(start);
	sum++;
	while (!q.empty()) {
		coord temp = q.front();
		q.pop();
		visit[temp.x][temp.y] = 1;
		for (int k = 0; k < 4; k++) {
			coord pushval;
			pushval.x = temp.x + addval[k][0];
			pushval.y = temp.y + addval[k][1];
			if (pushval.x < 0 || pushval.y < 0 || pushval.x > R - 1 || pushval.y > C - 1)
				continue;
			if (visit[pushval.x][pushval.y])
				continue;
			// visit[pushval.x][pushval.y] = 1;
			if (!arr[pushval.x][pushval.y]) {
				q.push(pushval);
				sum++;
			}
			if (arr[pushval.x][pushval.y]) {
				res1++;
				arr[pushval.x][pushval.y] = 0;
			}
		}
	}
	return sum;
}

int main() {
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			scanf("%d", &arr[i][j]);
	int res = 0;
	while (bfs() != R * C) {
		clear_visit();
		res++;
		res2 = res1;
	}
	printf("%d\n%d", res, res2);
}