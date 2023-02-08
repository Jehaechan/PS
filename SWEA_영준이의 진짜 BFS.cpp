#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct childnode {
	int child;
	childnode* nextptr;
};

struct Node {
	int parent;
	int depth;
	childnode* child;
};

int idx;
Node node[100002];
int queue[100000];
int dp[100002][14];		// dp[a][b]   a노드의 2^(b)번째 조상

childnode mallocnode[100002];
int idx2;

childnode* newnode(int idx) {
	mallocnode[idx2].child = idx;
	mallocnode[idx2].nextptr = nullptr;
	return &mallocnode[idx2++];
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
	for (test_case = 1; test_case <= T; ++test_case)
	{
		idx2 = 0;
		int N;
		scanf("%d", &N);
		idx = 1;
		node[idx].parent = 0;
		node[idx].depth = 1;
		node[idx].child = nullptr;
		memset(dp, 0, sizeof(int) * 100002);
		dp[1][0] = 1;

		for (int i = 2;i < N + 1;i++) {
			int parent_idx, cur_depth;
			scanf("%d", &parent_idx);
			node[i].parent = parent_idx;
			cur_depth = node[parent_idx].depth + 1;
			node[i].depth = cur_depth;
			node[i].child = nullptr;
			if (node[parent_idx].child == nullptr) {
				node[parent_idx].child = newnode(i);
			}
			else {
				childnode* head = node[parent_idx].child;
				while (head->nextptr != nullptr)
					head = head->nextptr;
				head->nextptr = newnode(i);
			}
			int dp_idx = 0;
			dp[i][dp_idx++] = parent_idx;
			int loop = log2(cur_depth - 1);
			for(int j = 0; j < loop; j++) {
				dp[i][dp_idx] = dp[parent_idx][dp_idx-1];
				parent_idx = dp[i][dp_idx++];
			}
			// 여기서 구하는 방법을 잘 봐두어야 한다.
			// 2^n + 2^n = 2^(n+1)같은 느낌이다.
		}

		/*
		for (int i = 0;i < 13;i++) {
			for (int j = 0;j < 14;j++) {
				int tmp = dp[i][j];
				if (tmp)
					printf("i:%d, j:%d, dp:%d\n", i, j, tmp);
			}
		}
		*/

		/*
		for (int i = 1;i < N + 1;i++) {
			printf("%d - parent: %d,  depth: %d,  child: ", i, node[i].parent, node[i].depth);
			childnode* temp = node[i].child;
			while (temp != nullptr) {
				printf("%d ", temp->child);
				temp = temp->nextptr;
			}
			puts("");
		}
		puts("");
		*/

		int front = 0, rear = 0;
		int distance = 0;
		int cur_idx = 1;

		queue[front++] = 1;
		while (front != rear) {
			int next_idx = queue[rear];
			rear = (rear + 1) % 10000;
			childnode* tempnode = node[next_idx].child;
			while (tempnode != nullptr) {
				queue[front] = tempnode->child;
				front = (front + 1) % 10000;
				tempnode = tempnode->nextptr;
			}

			int cur_depth = node[cur_idx].depth;
			int next_depth = node[next_idx].depth;
			int next_idx_tmp = next_idx;
			int cur_idx_tmp = cur_idx;
			int max_level = 13;
			//printf("startpoint %d\n",next_idx_tmp);
			if (cur_depth != next_depth) {		// cur_idx <= next_idx
				for (int i = max_level; i >= 0;i--) {
					//printf("dp next_idx_tmp:%d, next_idx_tmp:%d, i:%d\n", dp[next_idx_tmp][i], next_idx_tmp, i);
					if (node[cur_idx_tmp].depth <= node[dp[next_idx_tmp][i]].depth)
						next_idx_tmp = dp[next_idx_tmp][i];
					//puts("");
					//printf("%d ", next_idx_tmp);
					//puts("");
				}
			}
			//printf("next_idx_tmp: %d\n", next_idx_tmp);
			int lca = cur_idx_tmp;
			if (cur_idx_tmp != next_idx_tmp) {
				for (int i = max_level; i >= 0;i--) {
					if (dp[cur_idx_tmp][i] != dp[next_idx_tmp][i]) {
						cur_idx_tmp = dp[cur_idx_tmp][i];
						next_idx_tmp = dp[next_idx_tmp][i];
					}
					// printf("cur_idx_tmp:%d, next_idx_tmp:%d\n", cur_idx_tmp, next_idx_tmp);
					lca = dp[cur_idx_tmp][i];
				}
			}
			//printf("cur: %d, next: %d, lca: %d\n", cur_idx,next_idx, lca);
			distance += node[cur_idx].depth + node[next_idx].depth - 2 * node[lca].depth;
			//printf("\n\n");
			//for (int k = 0;k < 14;k++)
				//printf("%d ", dp[6][k]);
			//printf("\n\n");

			cur_idx = next_idx;
		}
		printf("#%d %d\n", test_case, distance);
		/*
		int front = 0, rear = 0;

		int distance = 0;
		int cur_idx = 1;
		queue[front++] = 1;
		while (front != rear) {
			int next_idx = queue[rear];
			rear = (rear + 1) % 10000;
			childnode* tempnode = node[next_idx].child;
			while (tempnode != nullptr) {
				queue[front] = tempnode->child;
				front = (front + 1) % 10000;
				tempnode = tempnode->nextptr;
			}

			int cur_depth = node[cur_idx].depth;
			int next_depth = node[next_idx].depth;
			int dif = next_depth - cur_depth;
			int low_idx = next_idx;
			int high_idx = cur_idx;
			distance += dif;
			for (int i = 0;i < dif;i++)
				low_idx = node[low_idx].parent;
			while (low_idx != high_idx) {
				low_idx = node[low_idx].parent;
				high_idx = node[high_idx].parent;
				distance += 2;
			}
			cur_idx = next_idx;
		}
		*/
		// printf("#%d %d\n", test_case, distance);
	}
	return 0;
}

/*
LCA 알고리즘
https://www.crocus.co.kr/660
*/
