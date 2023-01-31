#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct childnode {
	int child;
	childnode* nextptr;
};

int idx, fin_idx;
int parent[100002];               // 부모를 저장해두는 리스트
childnode mallocnode[100002];
childnode* childlist[100002];      // 자식을 저장해두는 리스트
childnode* lastptr[100002];         // 마지막 ptr를 저장해두는 리스트

int depth[100002];               // depth를 저장해두는 리스트
int dp[100002][17];               // dp[a][b]   a노드의 2^(b)번째 조상

void init() {
	idx = 0;
	fin_idx = 0;
	memset(parent, 0, sizeof(int) * 100002);
	memset(depth, 0, sizeof(int) * 100002);
	memset(mallocnode, 0, sizeof(childnode) * 100002);
	memset(childlist, 0, sizeof(childnode*) * 100002);
	memset(lastptr, 0, sizeof(childnode*) * 100002);
	memset(dp, 0, sizeof(int) * 100002 * 17);
}

int log2(int N) {
	int ret = 0;
	while (N) {
		N /= 2;
		ret++;
	}
	return ret - 1;
}

void maketree(int i, int input) {   // input은 parent_idx
	parent[i] = input;         // 부모노드 저장

	mallocnode[i].child = i;

	if (lastptr[input] == nullptr) {
		childlist[input] = &mallocnode[i];
	}      // 자식이 하나도 없다면 처음으로 연결
	else {
		lastptr[input]->nextptr = &mallocnode[i];
	}      // 자식이 있다면 마지막에 연결

	lastptr[input] = &mallocnode[i];      // 마지막 node update

	depth[i] = depth[input] + 1;         // depth 저장

	int loop = log2(depth[i]) + 1;
	int cur_parent = i;
	dp[i][0] = input;
	for (int exp2 = 1; exp2 < loop; exp2++) {
		dp[i][exp2] = dp[parent[cur_parent]][exp2 - 1];
		cur_parent = dp[cur_parent][exp2 - 1];
	}
}

int LCA(int prev, int cur) {
	int diff = depth[cur] - depth[prev];
	//printf("%d\n", diff);

	while (diff != 0) {
		int tmp_cur = cur;
		cur = dp[cur][log2(diff)];
		diff -= depth[tmp_cur] - depth[cur];
	}

	for (int i = log2(depth[cur]);i >= 0;i--) {
		if (dp[cur][i] != dp[prev][i]) {
			cur = dp[cur][i];
			prev = dp[prev][i];
		}
	}
	if (cur != prev)
		cur = dp[cur][0];
	return depth[cur];
}

int main() {
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		init();
		depth[1] = 0;      // depth는 0부터 시작
		int N;
		scanf("%d", &N);
		for (int i = 2; i <= N; i++) {
			int input;
			scanf("%d", &input);
			maketree(i, input);
		}

		/*
		printf("\n\n\nTC: %d\n", test_case);
		for (int i = 1; i  <= N; i++) {
		   printf("<i>:%d\n", i);
		   printf("parent: %d\n", parent[i]);
		   printf("child: ");
		   childnode* cur = childlist[i];
		   while (cur != nullptr) {
			  printf("%d ", cur->child);
			  cur = cur->nextptr;
		   }
		   puts("");
		   printf("depth: %d\n\n", depth[i]);
		}
		*/

		int bfs_stack[100002];
		bfs_stack[fin_idx++] = 1;
		int lca_prev = 1;
		int lca_cur;
		long long res = 0;			// long long type로 해줘야 함을 유의!

		while (idx != fin_idx) {
			lca_cur = bfs_stack[idx++];
			// printf("%d ", cur_num);
			childnode* cur_node = childlist[lca_cur];
			while (cur_node != nullptr) {
				bfs_stack[fin_idx++] = cur_node->child;
				cur_node = cur_node->nextptr;
			}

			//printf("%d %d\n", lca_prev, lca_cur);
			int lca_depth = LCA(lca_prev, lca_cur);
			// printf("%d\n", lca_depth); 
			res += depth[lca_prev] + depth[lca_cur] - 2 * lca_depth;

			lca_prev = lca_cur;
		}
		printf("#%d %ld\n", test_case, res);
	}
	return 0;
}
