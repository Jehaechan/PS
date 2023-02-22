#include <stdio.h>
#include <string.h>
long long mod = 0xFFFFFFFFFFFF;

int len;
long long hashval[100001];

void init() {
	hashval[1] = 157;
	for (int i = 2;i < 100001;i++) {
		hashval[i] = hashval[i - 1] * 157;
		hashval[i] &= mod;
	}
}

long long hash(char* str) {
	long long res = 0;
	for (int i = len;i > 0;i--) {
		res += *str++ * hashval[i];
		res &= mod;
	}
	return res;
}

int main() {
	init();
	int T;
	scanf("%d", &T);

	for (int tc = 1;tc <= T;tc++) {
		char book[600001];
		char word[200001];
		scanf(" %s", book);
		scanf(" %s", word);
		len = strlen(word);
		int booklen = strlen(book);
		long long target_hash = hash(word);
		long long cur_hash = hash(book);

		int res = 0;
		for (int i = 0; i <= booklen - len;i++) {
			if (target_hash == cur_hash)
				res++;

			cur_hash -= book[i] * hashval[len];
			cur_hash = (cur_hash + mod + 1) & mod;
			cur_hash *= 157;
			cur_hash &= mod;
			cur_hash += book[i + len] * 157;
			cur_hash &= mod;
		}

		printf("#%d %d\n", tc, res);
	}
}