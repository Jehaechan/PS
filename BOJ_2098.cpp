#include <stdio.h>
#define INT_MAX 987654321

// dp[visited][cur]
int dp[65536][16];
int graph[16][16];
int N;

int TSP(int visited, int cur) {
	//printf("visited:%d, cur:%d\n", visited, cur);
	if (dp[visited][cur]) {
		return dp[visited][cur];
	}
	if (visited == (1 << N) - 1)
		return 0;
	else {
		int min = INT_MAX;
		for (int i = 0;i < N;i++) {
			if (graph[cur][i] == 0)
				continue;
			int next_bit = 1 << i;
			// printf("visited: %d, next_bit: %d\n", visited, next_bit);
			if (visited & next_bit)
				continue;
			next_bit |= visited;
			//printf("visited2: %d, cur_bit2: %d\n", visited, next_bit);
			dp[next_bit][i] = TSP(next_bit, i);
			//printf("dp[%d][%d]: %d, graph[%d][%d]: %d\n", next_bit,i,dp[next_bit][i],cur,i, graph[cur][i]);
			if (min > dp[next_bit][i] + graph[cur][i])
				min = dp[next_bit][i] + graph[cur][i];
		}
	return min;
	}
}

int main() {
	scanf("%d", &N);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &graph[i][j]);
		}
	}
	
	// 무조건 0으로 도착하도록 하기 위해!
	for (int i = 1;i < N;i++)
		dp[(1 << N) - 1][i] = INT_MAX;

	TSP(0, 0);

	int ans = INT_MAX;
	for (int i = 0;i < N;i++) {
		if (graph[0][i] == 0)
			continue;
		int temp = graph[0][i] + dp[1 << i][i];
		//printf("%d %d %d\n", temp, graph[0][i], dp[1 << i][i]);
		if (ans > temp)
			ans = temp;
	}
	printf("%d", ans);
}