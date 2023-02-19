#include <stdio.h>
#include <string.h>

int v[100];
int c[100];
int dp[1001];
int dp1[1001];

// dp(volume) = cost
int main() {
	int T;
	scanf("%d", &T);
	for (int tc = 1;tc <= T;tc++) {
		memset(dp, 0, sizeof(int) * 1001);
		memset(dp1, 0, sizeof(int) * 1001);
		int N, K;
		scanf("%d %d", &N, &K);

		for (int i = 0;i < N;i++) {
			scanf("%d %d", &v[i], &c[i]);
		}

		for (int i = 0;i < N;i++) {
			int volume = v[i];
			int cost = c[i];
			for (int j = 0;j < 1001;j++) {
				int new_volume = volume + j;
				if (new_volume > K)
					break;
				int new_cost = cost + dp[j];
				if (dp[new_volume] < new_cost)
					dp1[new_volume] = new_cost;
				else
					dp1[new_volume] = dp[new_volume];
			}
			memcpy(dp, dp1, sizeof(int) * 1001);
		}

		int ans = 0;
		for (int i = 1001; i >= 0;i--) {
			if (ans < dp[i])
				ans = dp[i];
		}
		printf("#%d %d\n", tc, ans);
	}
}