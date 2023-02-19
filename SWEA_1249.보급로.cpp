#include <stdio.h>
#include <string.h>

typedef struct a {
	int x;
	int y;
	int lx;
	int ly;
}type;

int main() {
	int TC;
	scanf("%d", &TC);
	for (int tc = 0;tc <= TC;tc++) {
		int size;
		scanf("%d", &size);
		
		char arr[102][103];
		int D[102][102];
		memset(arr, -1, sizeof(char) * 102 * 103);
		memset(D, 0, sizeof(int) * 102 * 102);

		for (int i = 1;i <= size;i++)
			scanf(" %s", &arr[i][1]);

		int front = -1;
		int rear = -1;
		type queue[20000];
		
		front++;
		queue[front].x = 2;
		queue[front].y = 1;
		queue[front].lx = 1;
		queue[front].ly = 1;

		front++;
		queue[front].x = 1;
		queue[front].y = 2;
		queue[front].lx = 1;
		queue[front].ly = 1;

		while (front != rear) {
			rear++;
			type temp = queue[rear];
			int x = temp.x;
			int y = temp.y;
			int lx = temp.lx;
			int ly = temp.ly;
			int distance = D[lx][ly];

			if (arr[x - 1][y] > 0) {
				if (D[x - 1][y] == 0 || D[x - 1][y] > distance + (arr[x - 1][y] - '0')) {
					front++;
					queue[front].x = x - 1;
					queue[front].y = y;
					queue[front].lx = x;
					queue[front].ly = y;
				}
			}
		}
	}
}