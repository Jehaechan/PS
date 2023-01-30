#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct childnode {
	int child;
	childnode* nextptr;
};

int idx;
int parent[100002];
childnode mallocnode[100002];
childnode* childlist[100002];
childnode* lastptr[100002];

int depth[100002];
int dp[100002][14];		// dp[a][b]   a노드의 2^(b)번째 조상

void init() {
	idx = 0;
	memset(mallocnode, 0, 100002);
	memset(childlist, 0, sizeof(childlist) * 100002);
	memset(lastptr, 0, sizeof(childlist) * 100002);
}

int log2(int N) {
	int ret = 0;
	while (N) {
		N /= 2;
		ret++;
	}
	return ret - 1;
}

int main() {
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {

	}
	return 0;
}

/*
LCA 알고리즘
https://www.crocus.co.kr/660
*/