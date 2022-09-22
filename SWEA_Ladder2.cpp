#include<stdio.h>
#include<string.h>

int main() {
	int TC = 0;
	int arr[100][102];
	memset(arr, 0, sizeof(int) * 100 * 102);
	while (TC < 10) {
		scanf("%d", &TC);
		for (int i = 0;i < 100;i++)
			for (int j = 1;j < 101;j++)
				scanf("%d", &arr[i][j]);

		int min = 10001;
		int x = 0;
		for (int j = 1;j < 101;j++) {
			int i = 0;
			int jidx = j;
			int cnt = 0;
			if (arr[i][jidx] == 0)
				continue;

			while (i < 100) {
				if (arr[i][jidx - 1] == 1) {
					while (arr[i][jidx - 1] == 1) {
						jidx--;
						cnt++;
					}
				}
				else if (arr[i][jidx + 1] == 1) {
					while (arr[i][jidx + 1] == 1) {
						jidx++;
						cnt++;
					}
				}
				i++;
			}
			if (min > cnt) {
				min = cnt;
				x = j;
			}
		}
		printf("#%d %d\n", TC, x - 1);
	}
}