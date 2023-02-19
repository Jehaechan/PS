#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 0x7FFFFFFFFFFFFFFF

typedef struct distance {
	int point1;
	int point2;
	long long value;
};

int x[1000];
int y[1000];
distance dist[1000000];
int parent[1000];
//int rank[1000];

// 구조체 qsort 방법 확인
int compare(const void* a, const void* b) {
	if (((distance*)a)->value - ((distance*)b)->value < 0)
		return -1;
	else
		return 1;
}

int find(int p) {
	if (p == parent[p])
		return p;
	return parent[p] = find(parent[p]);
}

void union_parent(int p1, int p2) {
	/*
	int r1 = rank[p1];
	int r2 = rank[p2];
	
	if (r2 > r1) {
		int temp = p1;
		p1 = p2;
		p2 = temp;
	}
	*/
	p1 = find(p1);
	p2 = find(p2);
	parent[p2] = p1;
	//if (r1 == r2)
	//	rank[p2]++;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		int N;
		scanf("%d", &N);
		int idx = 0;

		for (int i = 0; i < N; i++)
			scanf("%d", &x[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &y[i]);

		for (int i = 0;i < N; i++) {
			for (int j = i + 1;j < N;j++) {
				dist[idx].point1 = i;
				dist[idx].point2 = j;
				long long xdist = x[i] - x[j];
				long long ydist = y[i] - y[j];
				dist[idx++].value = xdist * xdist + ydist * ydist;
			}
		}
		
		qsort(dist, idx, sizeof(distance), compare);

		//int checklist[1000];
		//memset(checklist, 0, sizeof(int) * N);
		long long ans = 0;

		/*
		for (int i = 0;i < idx;i++) {
			int p1 = dist[i].point1;
			int p2 = dist[i].point2;
			if (checklist[p1] == 0 || checklist[p2] == 0) {
				ans += dist[i].value;
				checklist[p1] = 1;
				checklist[p2] = 1;
			}
		}
		// 이렇게 하면 전부 연결된 그래프가 안나옴. 그냥 여러 덩어리로 묶인 그래프가 나옴. 따라서 union-find 써야함.
		*/

		//memset(rank, 0, sizeof(int) * N);
		for (int i = 0; i < N;i++) {
			parent[i] = i;
		}

		for (int i = 0;i < idx;i++) {
			int p1 = dist[i].point1;
			int p2 = dist[i].point2;
			if (find(p1) == find(p2))
				continue;
			union_parent(p1, p2);
			ans += dist[i].value;
		}

		double E;
		scanf("%lf", &E);

		printf("#%d: %.0lf\n", test_case, E * ans);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

// prim 알고리즘, kruskal 알고리즘, union-find