#include<stdio.h>
char board[20][20];
int gift[26];
int cnt;
int max;
int R, C;

void dfs(int i, int j) {
	if (i >= R || j >= C || i < 0 || j < 0 || gift[board[i][j] - 'A']) {
		if (cnt > max)
			max = cnt;
		return;
	}
	gift[board[i][j] - 'A'] = 1;
	cnt++;

	dfs(i, j + 1);
	dfs(i, j - 1);
	dfs(i + 1, j);
	dfs(i - 1, j);

	gift[board[i][j] - 'A'] = 0;
	cnt--;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d %d", &R, &C);

		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				scanf(" %c", &board[i][j]);

		cnt = 0;
		max = 0;

		for (int i = 0;i < 26;i++) {
			gift[i] = 0;
		}
		/*
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				printf("%c ", board[i][j]);
			}
			puts("");
		}
		*/
		dfs(0, 0);
		printf("#%d %d\n", test_case, max);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
} 