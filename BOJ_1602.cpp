#include <stdio.h>
#define MAX_N 500
#define MAX_M 10000
#define MAX_Q 40000
#define INT_MAX 387654321
int choose_dog[MAX_N][MAX_N];

int main() {
	int N, M, Q;
	scanf("%d %d %d", &N, &M, &Q);

	int dog[MAX_N];
	for (int i = 0;i < N;i++) {
		scanf("%d", &dog[i]);
	}

	int graph[MAX_N][MAX_N];
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (i == j) {
				graph[i][j] = 0;
			}
			else {
				graph[i][j] = INT_MAX;
			}
		}
	}

	for (int i = 0;i < M;i++) {
		int start, fin, cost;
		scanf("%d %d %d", &start, &fin, &cost);
		graph[start - 1][fin - 1] = cost;
		graph[fin - 1][start - 1] = cost;
	}

	/*
	printf("dog: ");
	for (int i = 0;i < N;i++)
		printf("%d ", dog[i]);
	puts("");
	printf("<graph>\n");
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (graph[i][j] != INT_MAX) {
				printf("%d %d %d\n", i, j, graph[i][j]);
			}
		}
	}
	*/
	int idx[MAX_N];
	for (int i = 0;i < N;i++)
		idx[i] = i;

	for (int i = 0;i < N - 1;i++) {
		for (int j = i;j < N;j++) {
			int i_val = idx[i];
			int j_val = idx[j];
			if (dog[i_val] > dog[j_val]) {
				idx[j] = i_val;
				idx[i] = j_val;
			}
		}
	}

	/*
	puts("\n");
	for (int i = 0;i < N;i++) {
		printf("%d ", dog[idx[i]]);
	}
	puts("\n");
	*/
	for (int i = 0;i < N;i++) {
		int i_dog = dog[i];
		for (int j = 0;j < N;j++) {
			int j_dog = dog[j];
			choose_dog[i][j] = i_dog > j_dog ? i_dog : j_dog;
		}
	}

	for (int i = 0;i < N;i++) {	// 경유할 점 추가
		int sorted_idx = idx[i];
		int dog_val = dog[idx[i]];
		for (int j = 0;j < N;j++) {	// Start
			if (graph[j][sorted_idx] == INT_MAX)
				continue;
			for (int k = 0;k < N;k++) {	// Fin
				if (graph[sorted_idx][k] == INT_MAX)
					continue;
				int cur_dog = choose_dog[j][k];
				int new_dog = dog_val > cur_dog ? dog_val : cur_dog;
				int cur_cost = graph[j][k] + cur_dog;
				int new_cost = graph[j][sorted_idx] + graph[sorted_idx][k] + new_dog;
				if (new_cost < cur_cost) {
					graph[j][k] = new_cost - new_dog;
					choose_dog[j][k] = new_dog;
				}
			}
		}
	}

	/*
	printf("\n\n<graph>\n");
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (graph[i][j] != INT_MAX) {
				printf("%d %d %d\n", i, j, graph[i][j] + choose_dog[i][j]);
			}
		}
	}*/
	for (int i = 0;i < Q;i++) {
		int S, T;
		scanf("%d %d", &S, &T);
		S--;
		T--;
		printf("%d\n", graph[S][T] == INT_MAX ? -1 : graph[S][T] + choose_dog[S][T]);
	}
}