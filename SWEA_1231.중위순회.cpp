#include <stdio.h>
#include <string.h>

char BST[101];

void traversal(int idx) {
	int left = idx * 2;
	int right = idx * 2 + 1;
	if (BST[left])
		traversal(left);
	printf("%c", BST[idx]);
	if (BST[right])
		traversal(right);
}

int main(int argc, char** argv) {
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	for (test_case = 1; test_case <= T; ++test_case) {
		memset(BST, 0, sizeof(char) * 101);
		int N;
		scanf("%d", &N);
		for (int i = 0;i < N;i++) {
			int idx;
			char buffer[10];
			scanf("%d", &idx);
			scanf("%[^\n]s", buffer);
			BST[idx] = buffer[1];
		}
		traversal(1);
		printf("#%d ", test_case);
		puts("");
		/*
		for (int i = 1;i < 102;i++)
			if (BST[i] != 0)
				printf("%d %c\n", i, BST[i]);
		*/
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}