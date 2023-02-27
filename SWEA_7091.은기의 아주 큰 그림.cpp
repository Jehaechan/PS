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
	hashmap[1999][1999] = PRIME_NUM_ROW;
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

	/*
	for (int i = 0;i < 5;i++) {
		printf("%lld ", hashmap[0][i]);
	}
	puts("");
	for (int i = 0;i < 5;i++) {
		printf("%lld ", (hashmap[1][i] * 173) & MOD);
	}
	puts("");
	*/
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
		//printf("target_val: %lld\tcur_val: %lld\n", target_val, cur_val);

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
				//printf("%lld\n", start_val);

				for (int j = 0;j < W;j++) {
					start_val += map[i + H - 1][j] * hashmap[H - 1][j];
					start_val &= MOD;
				}
			}
			long long cur_val = start_val;
			//printf("<1>cur:%lld\ttarget:%lld\n", cur_val, target_val);

			//printf("%lld\n", cur_val);

			for (int j = 0; j <= M - W;j++) {
				if (j != 0) {
					if (i == 0) {
						for (int k = 0;k < H;k++) {
							left[j] += map[k][0] * hashmap[k][0];
							left[j] &= MOD;
						}
						for (int k = 0;k < H;k++) {
							right[j] += map[k][W] * hashmap[k][W - 1];
							right[j] &= MOD;
						}
					}
					/*
					for (int k = i;k < i + H;k++) {
						cur_val += MOD + 1;
						cur_val -= map[k][j - 1] * hashmap[k - i][0];
						cur_val &= MOD;
					}
					cur_val *= PRIME_NUM_ROW;
					cur_val &= MOD;

					for (int k = i;k < i + H;k++) {
						cur_val += map[k][j + W - 1] * hashmap[k - i][W - 1];
						cur_val &= MOD;
					}
					*/
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
					// check map idx(case1 -> correct cause all 1 / but case2 -> diff val 0/1) ////// maybe hashmap
					cur_val += MOD + 1;
					cur_val -= left[j];
					cur_val &= MOD;
					cur_val *= PRIME_NUM_ROW;
					cur_val &= MOD;

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
/*
printf("a%lld\n", cur_val);
cur_val += MOD + 1;
printf("b%lld %lld\n", cur_val, left[j]);
cur_val -= left[j];
printf("c%lld\n", cur_val);
cur_val &= MOD;
printf("d%lld\n", cur_val);
cur_val *= PRIME_NUM_ROW;
printf("e%lld\n", cur_val);
cur_val &= MOD;
printf("f%lld\n", cur_val);

cur_val += right[j];
printf("g%lld\n", cur_val);
cur_val &= MOD;
printf("h%lld\n", cur_val);
*/