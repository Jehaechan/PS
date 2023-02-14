#include <stdio.h>
int dp[1000000];
int backtracking[1000000];
int arr[1000000];
int stack[1000000];

int lower_bound(int len, int val) {
	if (len == 0)
		return 0;
	int left = 0;
	int right = len - 1;
	int mid;
	if (dp[right] < val)
		return len;
	while (left < right) {
		mid = (left + right) / 2;
		if (dp[mid] < val)
			left = mid + 1;
		else
			right = mid;
	}
	return right;
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0;i < N;i++)
		scanf("%d", &arr[i]);
	int max_len = 0;
	for (int i = 0;i < N;i++) {
		int cur = arr[i];
		int lb = lower_bound(max_len, cur);
		if (lb == max_len) {
			backtracking[i] = max_len;
			dp[max_len++] = arr[i];
		}
		else {
			backtracking[i] = lb;
			dp[lb] = arr[i];
		}
	}
	printf("%d\n", max_len);

	int stack_idx = 0;
	max_len--;


	for (int i = N - 1;i >= 0;i--) {
		if (backtracking[i] == max_len) {
			stack[stack_idx++] = arr[i];
			max_len--;
		}
		if (max_len == -1)
			break;
	}

	for (int i = stack_idx - 1;i >= 0;i--) {
		printf("%d ", stack[i]);
	}

}