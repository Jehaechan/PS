#include <stdio.h>
#include <string.h>
#define MAX_NODE 100002

struct Node {
	int c_i;
	Node* nextnode;
};

int parent[MAX_NODE];		// �ش� ����� �θ� ��� ��ȣ�� �����س��� ��
Node mallocnode[MAX_NODE];	// �ڽ� ���� �̸� ��Ƶα�
Node* child[MAX_NODE];		// �ش� ����� �ڽ� ��带 ���� ����Ʈ�� �̾���� ��
int malloc_node_idx;
int dp[MAX_NODE][17];

void init() {
	memset(child, 0, sizeof(Node*) * MAX_NODE);
	malloc_node_idx = 0;
}

Node* newnode(int childnum) {
	mallocnode[malloc_node_idx].c_i = childnum;
	mallocnode[malloc_node_idx].nextnode = nullptr;
	return &mallocnode[malloc_node_idx++];
}

int log2(int n) {
	int res = 0;
	for (int i = 1;i <= n;i *= 2)
		res++;
	return res - 1;
}

int main() {
	int test_case;
	int T; 
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		init();
		int N;
		scanf("%d", &N);
		/*
		for (int i = 1;i < 100;i++) {
			printf("%d %d\n", i, log2(i));
		}
		*/
		return 0;
		for (int i = 2;i <= N;i++) {
			int p_i;
			scanf("%d", &p_i);
			parent[i] = p_i;
			
		}
		long long distance = 0;
		printf("#%d %lld\n", test_case, distance);
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}