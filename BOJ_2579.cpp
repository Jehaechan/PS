#include <stdio.h>
int one_step[302];
int two_step[302];

int main() {
	int input, N;
	scanf("%d", &N);
	for (int i = 2;i < N + 2;i++) {
		scanf("%d", &input);
		one_step[i] = two_step[i - 1] + input;
		two_step[i] = (one_step[i - 2] > two_step[i - 2] ? one_step[i - 2] : two_step[i - 2]) + input;
	}
	/*
	for (int i = 0;i < N+2;i++)
		printf("%d ", one_step[i]);
	puts("");
	for (int i = 0;i < N+2;i++)
		printf("%d ", two_step[i]);
	puts("");
	*/
	printf("%d", one_step[N + 1] > two_step[N + 1] ? one_step[N + 1] : two_step[N + 1]);
}