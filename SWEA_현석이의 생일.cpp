#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	freopen("input.txt", "r", stdin);
	int test_case;
	int T;
	scanf("%d ", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int x, y, len = -1;
		int num[100001];
		while (1) {
			len++;
			char tmp;
			scanf("%c", &tmp);
			if (tmp == ' ') {
				break;
			}
			num[len] = tmp - '0';
		}
		scanf("%d %d ", &x, &y);

		/*
		for (int i = 0; i < len; i++) {
			printf("%d", num[i]);
		}
		printf(" %d %d\n", x, y);
		*/

		int idx = len;
		for (int i = 0;i < len; i++) {
			if (num[i] != x && num[i] != y) {
				idx = i;
				break;
			}
		}

		printf("#%d ", test_case);
		if (idx == len) {
			for (int i = 0;i < idx;i++) {
				printf("%d", num[i]);
			}
		}
		else {
			if (num[idx] < x) {
				int new_idx = idx;
				for (int i = idx - 1; i >= 0;i--) {
					if (num[i] == y) {
						new_idx = i;
						break;
					}
				}
				if (new_idx == idx) {
					if (len == 1) {
						printf("-1");
					}
					else {
						for (int i = 0;i < len - 1;i++) {
							printf("%d", y);
						}
					}
				}
				else {
					for (int i = 0; i < new_idx;i++) {
						printf("%d", num[i]);
					}
					printf("%d", x);
					for (int i = 0;i < len - new_idx - 1;i++) {
						printf("%d", y);
					}
				}
			}
			else if(num[idx] > y) {
				for (int i = 0;i < idx;i++) {
					printf("%d", num[i]);
				}
				for (int i = 0;i < len - idx;i++) {
					printf("%d", y);
				}
			}
			else {
				if (idx == 0 && x == 0) {
					if (len == 1) {
						printf("-1");
					}
					else {
						for (int i = 0; i < len - 1;i++) {
							printf("%d", y);
						}
					}
				}
				else {
					for (int i = 0;i < idx;i++) {
						printf("%d", num[i]);
					}
					printf("%d", x);
					for (int i = 0;i < len - idx - 1;i++) {
						printf("%d", y);
					}
				}
			}
		}
		printf("\n");
	}
	return 0;
}