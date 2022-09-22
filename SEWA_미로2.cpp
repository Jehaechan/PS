#include<stdio.h>

int res;
char arr[100][101];

void func(int a, int b) {
	if (res)
		return;
	if (arr[a][b] == '1')
		return;
	if (arr[a][b] == '3') {
		res = 1;
		return;
	}
	arr[a][b] = '1';
	func(a + 1, b);
	func(a - 1, b);
	func(a, b + 1);
	func(a, b - 1);
}

int main() {
	int TC = 0;
	while (TC < 10) {
		scanf("%d", &TC);
		res = 0;
		int x, y;
		for (int i = 0;i < 100;i++)
			scanf(" %s", &arr[i]);

		int flag = 0;
		for (int i = 0;i < 100;i++) {
			if (flag)
				break;
			for (int j = 0;j < 100;j++) {
				if (arr[i][j] == '2') {
					func(i, j);
					flag = 1;
					break;
				}
			}
		}
		printf("#%d %d\n", TC, res);
	}
}