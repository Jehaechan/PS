#include <stdio.h>
#include <string.h>

char map1[302][302];
char map2[302][302];

struct xy {
	int x;
	int y;
};

xy delta[8] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

int main() {
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		int len;
		scanf("%d", &len);
		for (int i = 1;i <= len;i++)
			scanf(" %s", &map1[i][1]);
		memset(map2, 2, sizeof(char) * 302 * 302);		// °¡ÀåÀÚ¸®´Â ÆøÅºÀ¸·Î Ã¤¿î´Ù

		for (int i = 1;i <= len;i++) {
			for (int j = 1;j <= len;j++) {
				if (map1[i][j] == '*') {
					continue;		// 2´Â ÆøÅº ÀÚ¸®
				}
				else {
					map2[i][j] = 0;	// 0Àº ÁÖº¯¿¡ ÆøÅºÀÌ ¾ø´Â ÀÚ¸®
					for (int k = 0;k < 8;k++) {
						int dx = delta[k].x;
						int dy = delta[k].y;
						if (map1[i + dx][j + dy] == '*') {
							map2[i][j] = 1;		// 1Àº ÁÖº¯¿¡ ÆøÅºÀÌ ÀÖ´Â ÀÚ¸®
							break;
						}
					}
				}
			}
		}

		int cnt = 0;		// Å¬¸¯ °³¼ö

		/*
		for (int i = 1;i <= len;i++) {
			for (int j = 1;j <= len;j++)
				printf("%d ", map2[i][j]);
			puts("\n\n");
		}
		break;
		*/

		for (int i = 1; i <= len; i++) {
			for (int j = 1;j <= len;j++) {
				if (!map2[i][j]) {		// ÆøÅºÀÌ ¾ø´Â ÀÚ¸®¶ó¸é
					cnt++;
					xy queue[5000];
					int front = 0, rear = 0;
					queue[front].x = i;
					queue[front++].y = j;
					map2[i][j] = 3;
					while (front != rear) {
						int cur_x = queue[rear].x;
						int cur_y = queue[rear++].y;
						for (int k = 0;k < 8;k++) {
							int dx = delta[k].x;
							int dy = delta[k].y;
							int next_x = cur_x + dx;
							int next_y = cur_y + dy;
							if (!map2[next_x][next_y]) {
								queue[front].x = next_x;
								queue[front++].y = next_y;
							}
							map2[next_x][next_y] = 3;
						}
					}
				}
			}
		}

		
		for (int i = 1;i <= len;i++)
			for (int j = 1;j <= len;j++) 
				if (map2[i][j] == 1) 
					cnt++;

		printf("#%d %d\n", test_case, cnt);
	}
	return 0;
}