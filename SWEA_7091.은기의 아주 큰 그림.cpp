#include <stdio.h>
#include <string.h>
#define MOD 0x7FFFFFFFFFFFFF
#define PRIME_NUM_ROW 157
#define PRIME_NUM_COL 173

int pic[2000][2000];	// Àº±â
int map[2000][2000];	// ¼±»ý´Ô
int H, W, N, M;

long long hashmap[2000][2000];

void init() {
	hashmap[1999][1999] = PRIME_NUM_ROW * PRIME_NUM_ROW;
	for (int i = 1998;i >= 0;i--) {
		hashmap[1999][i] = hashmap[1999][i + 1] * PRIME_NUM_ROW;
		hashmap[1999][i] &= MOD;
	}

	for (int i = 1998;i >= 0;i--) {
		for (int j = 0;j < 2000;j++) {
			hashmap[i][j] = hashmap[i + 1][j] * PRIME_NUM_COL;
			hashmap[i][j] &= MOD;
		}
	}
}

long long hashval(int map[][2000]) {
	long long ret = 0;
	for (int i = 0;i < H;i++) {
		for (int j = 0;j < W;j++) {
			ret += map[i][j] * hashmap[i][j];
			ret &= MOD;
		}
	}
	return ret;
} 

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	init();

	for (int tc = 1;tc <= T;tc++) {
		scanf("%d %d %d %d", &H, &W, &N, &M);

		char input[2001];
		for (int i = 0; i < H;i++) {
			scanf(" %s", input);
			for (int j = 0;j < W;j++) 
				pic[i][j] = input[j] == 'o' ? 1 : 0;
		}
		for (int i = 0;i < N;i++) {
			scanf(" %s", input);
			for (int j = 0;j < M;j++)
				map[i][j] = input[j] == 'o' ? 1 : 0;
		}

		long long target_val = hashval(pic);
		long long start_val = hashval(map);

		int res = 0;
		long long left[2000];
		long long right[2000];
		memset(left, 0, sizeof(long long) * 2000);
		memset(right, 0, sizeof(long long) * 2000);

		for (int i = 0;i <= N - H;i++) {
			if (i != 0) {
				for (int j = 0;j < W;j++) {
					start_val += MOD + 1;
					start_val -= map[i - 1][j] * hashmap[0][j];
					start_val &= MOD;
				}
				start_val *= PRIME_NUM_COL;
				start_val &= MOD;

				for (int j = 0;j < W;j++) {
					start_val += map[i + H - 1][j] * hashmap[H - 1][j];
					start_val &= MOD;
				}
			}
			long long cur_val = start_val;

			for (int j = 0; j <= M - W;j++) {
				if (j != 0) {
					if (i == 0) {
						for (int k = 0;k < H;k++) {
							left[j] += map[k][j - 1] * hashmap[k][0];
							left[j] &= MOD;
						}
						for (int k = 0;k < H;k++) {
							right[j] += map[k][j + W - 1] * hashmap[k][W - 1];
							right[j] &= MOD;
						}
					}
					else {
						left[j] += MOD + 1;
						left[j] -= map[i - 1][j - 1] * hashmap[0][0];
						left[j] &= MOD;
						left[j] *= PRIME_NUM_COL;
						left[j] += map[i + H - 1][j - 1] * hashmap[H - 1][0];
						left[j] &= MOD;

						right[j] += MOD + 1;
						right[j] -= map[i - 1][j + W - 1] * hashmap[0][W - 1];
						right[j] &= MOD;
						right[j] *= PRIME_NUM_COL;
						right[j] += map[i + H - 1][j + W - 1] * hashmap[H - 1][W - 1];
						right[j] &= MOD;
					}
					cur_val += MOD + 1;
					cur_val -= left[j];
					cur_val *= PRIME_NUM_ROW;

					cur_val += right[j];
					cur_val &= MOD;
				}

				if (cur_val == target_val) {
					res++;
				}
			}
		}
		printf("#%d %d\n", tc, res);
	}
}