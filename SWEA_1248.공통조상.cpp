#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

char cnt_list[10001];

struct Node {
	int child[2];
	int parent;
};

Node node[10001];

int main(int argc, char** argv) {
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);

	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		memset(cnt_list, 0, sizeof(char) * 10001);
		int V, E, node1, node2;
		scanf("%d %d %d %d", &V, &E, &node1, &node2);

		for (int i = 0;i < E;i++) {
			int parent, child;
			scanf("%d %d", &parent, &child);
			node[parent].child[cnt_list[parent]++] = child;
			node[child].parent = parent;
		}

		int idx1 = 0, idx2 = 0;
		int parent_list1[10001], parent_list2[10001];
		while (node1 != 1) {
			parent_list1[idx1++] = node[node1].parent;
			node1 = node[node1].parent;
		}
		while (node2 != 1) {
			parent_list2[idx2++] = node[node2].parent;
			node2 = node[node2].parent;
		}

		int root = 1;
		for (int i = 1;;i++) {
			if (parent_list1[idx1 - i] != parent_list2[idx2 - i])
				break;
			root = parent_list1[idx1 - i];
		}

		int cnt = 0;
		queue<int>q;
		q.push(root);
		while (!q.empty()) {
			cnt++;
			int next = q.front();
			q.pop();
			for (int j = 0;j < cnt_list[next];j++)
				q.push(node[next].child[j]);
		}
		printf("#%d %d %d\n", test_case, root, cnt);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
queue 사용법 숙지하기!
(BFS 까지도!!!)
*/