/*
Ver1

#include <stdio.h>
#define N 6
#define INF 987654321

int graph[N][N] = {
	{0,2,5,1,INF,INF},
	{2,0,3,2,INF,INF},
	{5,3,0,3,1,5},
	{1,2,3,0,1,INF},
	{INF,INF,1,1,0,2},
	{INF,INF,5,INF,2,0}
};

int dist[N];
int visited[N];
int cnt = 0;

void dijkstra() {
	while (1) {
		if (cnt == N)
			return;
		int cur = -1;
		for (int i = 0; i < N; i++) {
			if (visited[i])
				continue;
			if (cur == -1 || dist[i] < dist[cur])
				cur = i;
		}

		visited[cur] = 1;
		cnt++;

		int cur_dist = dist[cur];
		for (int i = 0; i < N;i++) {
			if (visited[i])
				continue;
			int update = cur_dist + graph[cur][i];
			if (update < dist[i])
				dist[i] = update;
		}
	}
}

int main() {
	for (int i = 0; i < N; i++)
		dist[i] = INF;
	dist[0] = 0;
	dijkstra();

	for (int i = 0;i < N;i++) {
		printf("%d->%d : %d\n", 0, i, dist[i]);
	}
	printf("\n");

	return 0;
}
*/

/*
ver2

#include < stdio.h >
#define MAX_N 6
#define INF (987654321)

int graph[MAX_N][MAX_N] = {
	{0,2,5,1,INF,INF},
	{2,0,3,2,INF,INF},
	{5,3,0,3,1,5},
	{1,2,3,0,1,INF},
	{INF,INF,1,1,0,2},
	{INF,INF,5,INF,2,0}
};

int getMinIdx(int nodes[MAX_N], int visited[MAX_N]) {
	int min = -1;
	for (int i = 0;i < MAX_N;i++) {
		if (visited[i]) continue;
		if (min<0 || nodes[min] > nodes[i]) min = i;
	}
	return min;
}

void dijkstra2(int arr[MAX_N][MAX_N], int start, int dist[MAX_N]) {
	int visited[MAX_N] = { 0, };
	for (int i = 0;i < MAX_N;i++) {
		dist[i] = arr[start][i];
	}
	visited[start] = 1;

	for (int i = 0;i < MAX_N - 1;i++) {
		int n_new = getMinIdx(dist, visited);
		visited[n_new] = 1;
		for (int j = 0;j < MAX_N;j++) {
			if (visited[j]) continue;
			if (dist[j] > dist[n_new] + arr[n_new][j])
				dist[j] = dist[n_new] + arr[n_new][j];
		}
	}
}

int main() {
	int dist[MAX_N];
	int start = 0;
	dijkstra2(graph, start, dist);
	for (int i = 0;i < MAX_N;i++) {
		printf("%d->%d : %d\n", start, i, dist[i]);
	}
	printf("\n");
	return 0;
}
*/


// ver3(priority queue) - visited 추가하면 성능 향상?

#include < stdio.h >
#include <queue>
#define MAX_N 6
#define INF (987654321)

using namespace std;

int graph[MAX_N][MAX_N] = {
	{0,2,5,1,INF,INF},
	{2,0,3,2,INF,INF},
	{5,3,0,3,1,5},
	{1,2,3,0,1,INF},
	{INF,INF,1,1,0,2},
	{INF,INF,5,INF,2,0}
};

void dijkstra2(int arr[MAX_N][MAX_N], int start, int dist[MAX_N]) {
	for (int i = 0; i < MAX_N;i++)
		dist[i] = INF;
	dist[start] = 0;
	priority_queue<pair<int, int>>pq;
	pq.push({ dist[start], start});

	while (!pq.empty()) {
		int distance = -pq.top().first;
		int node = pq.top().second;
		pq.pop();

		for (int i = 0; i < MAX_N;i++) {
			int new_dist = distance + arr[node][i];
			if (new_dist < dist[i]) {
				dist[i] = new_dist;
				pq.push({ -new_dist, i });
			}
		}
	}
}

int main() {
	int dist[MAX_N];
	int start = 0;
	dijkstra2(graph, start, dist);
	for (int i = 0;i < MAX_N;i++) {
		printf("%d->%d : %d\n", start, i, dist[i]);
	}
	printf("\n");
	return 0;
}