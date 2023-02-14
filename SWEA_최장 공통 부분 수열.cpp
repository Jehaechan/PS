#include <stdio.h>
#include <string.h>

int dp[1001][1001];

int main() {
	int T;
	scanf("%d", &T);
	for (int tc = 1;tc <= T;tc++) {
		memset(dp, 0, sizeof(int) * 1001 * 1001);
		char input1[1001];
		char input2[1001];
		scanf(" %s %s", input1, input2);
		int len1 = strlen(input1);
		int len2 = strlen(input2);

		for (int i = 0; i < len1;i++) {
			char cur = input1[i];
			for (int j = 1;j <= len2;j++) {
				if (cur == input2[j - 1]) {
					dp[i + 1][j] = dp[i][j - 1] + 1;
				}
				else {
					int last = dp[i][j];
					int new_val = dp[i + 1][j - 1];
					dp[i + 1][j] = last > new_val ? last : new_val;
				}
			}
		}
		int ans = 0;
		for (int i = 0;i <= len2;i++) {
			int cur = dp[len1][i];
			if (cur > ans)
				ans = cur;
		}
		printf("#%d %d\n", tc, ans);
	}
}