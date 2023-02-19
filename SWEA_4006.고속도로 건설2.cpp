#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int s;
	int e;
	int cost;
}Edge;

Edge edge[200000];

int compare(const void* a, const void* b) {
	if (((Edge*)a)->cost < ((Edge*)b)->cost)
		return -1;
	else
		return 1;
}

int parent[50001];

int find(int node) {
	if (node == parent[node])
		return node;
	else
		return parent[node] = find(parent[node]);
}

void Union(int s_p, int e_p) {
	parent[e_p] = s_p;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		int N, M;
		scanf("%d %d", &N, &M);
		for (int i = 0;i < M;i++) {
			scanf("%d %d %d", &edge[i].s, &edge[i].e, &edge[i].cost);
		}

		qsort(edge, M, sizeof(Edge), compare);

		for (int i = 0; i < 50001;i++) {
			parent[i] = i;
		}

		int total_cost = 0;

		for (int i = 0;i < M;i++) {
			int S, E;
			S = edge[i].s;
			E = edge[i].e; 

			int s_p = find(S);
			int e_p = find(E);
			if (s_p == e_p)
				continue;
			else {
				Union(s_p, e_p);
				total_cost += edge[i].cost;
			}
		}

		printf("#%d %d\n", test_case, total_cost);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}