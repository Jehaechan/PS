#include <stdio.h>

int init(int N, int sCity[], int eCity[], int mCost[]);
void add(int sCity, int eCity, int mCost);
int cost(int mHub);

/////////////////////////////////////////////////////////////////////////

#define MAX_N 1400
#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_COST 3

static bool run() {
	int q;
	scanf("%d", &q);

	int n;
	int sCityArr[MAX_N], eCityArr[MAX_N], mCostArr[MAX_N];
	int sCity, eCity, mCost, mHub;
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			okay = true;
			scanf("%d", &n);
			for (int j = 0; j < n; ++j) {
				scanf("%d %d %d", &sCityArr[j], &eCityArr[j], &mCostArr[j]);
			}
			scanf("%d", &ans);
			ret = init(n, sCityArr, eCityArr, mCostArr);
			if (ans != ret)
				okay = false;
			break;
		case CMD_ADD:
			scanf("%d %d %d", &sCity, &eCity, &mCost);
			add(sCity, eCity, mCost);
			break;
		case CMD_COST:
			scanf("%d %d", &mHub, &ans);
			ret = cost(mHub);
			if (ans != ret)
				okay = false;
			break;
		default:
			okay = false;
			break;
		}
	}
	return okay;
}

int main() {
	freopen("input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}


/////////////////// User Code ///////////////////////////
#include <string.h>
#include <queue>
#define INT_MAX 987654321
#define MAX_NODE 600

using namespace std;

int match[MAX_NODE];
int graph[MAX_NODE][MAX_NODE];

int idx;

int match_idx(int input) {
	for (int i = 0;i < idx;i++) {
		if (match[i] == input)
			return i;
	}
	match[idx] = input;
	return idx++;
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
	idx = 0;
	for (int i = 0;i < MAX_NODE;i++) {
		for (int j = 0;j < MAX_NODE;j++) {
			graph[i][j] = INT_MAX;
		}
	}
	for (int i = 0; i < N; i++) {
		int start = sCity[i];
		int end = eCity[i];
		int cost = mCost[i];

		int start_idx = match_idx(start);
		int end_idx = match_idx(end);

		//printf("%d %d\n", start_idx, end_idx);
		graph[start_idx][end_idx] = cost;
	}
	for (int i = 0;i < idx;i++)
		graph[i][i] = 0;
	return idx;
}

void add(int sCity, int eCity, int mCost) {
	int start = match_idx(sCity);
	int end = match_idx(eCity);
	graph[start][end] = mCost;
}

int visited[MAX_NODE];
int dijk_cost[MAX_NODE];
int cnt;

void init_dijk() {
	memset(visited, 0, sizeof(int) * idx);
	for (int i = 0;i < idx;i++) {
		dijk_cost[i] = INT_MAX;
	}
	cnt = 0; 
}

void dijk(int start, int mode) {
	init_dijk();
	int start_idx = match_idx(start);
	dijk_cost[start_idx] = 0;

	while (cnt != idx) {
		int cur_idx = -1;
		for (int i = 0; i < idx; i++) {
			if (visited[i])
				continue;
			if (cur_idx == -1 || dijk_cost[i] < dijk_cost[cur_idx]) {
				cur_idx = i;
			}
		}

		//printf("cur_idx: %d %d %d\n", cur_idx,start_idx,idx);
		int cur_cost = dijk_cost[cur_idx];
		visited[cur_idx] = 1;
		cnt++;

		for (int i = 0;i < idx;i++) {
			if (visited[i])
				continue;
			int tmp = mode ? graph[i][cur_idx] : graph[cur_idx][i];
			if (tmp == INT_MAX)
				continue;
			int new_cost = cur_cost + tmp;
			//printf("cur: %d,	i: %d	cost: %d\n",cur_idx,i,new_cost);
			if (new_cost < dijk_cost[i])
				dijk_cost[i] = new_cost;
		}
	}
}

/*
void printdijk() {
	for (int i = 0;i < idx;i++) {
		printf("%d ", dijk_cost[i]);
	}
	puts("");
} 
*/

void dijk2(int start, int mode) {
	for (int i = 0;i < idx;i++) {
		dijk_cost[i] = INT_MAX;
	}
	priority_queue < pair<int, int>> pq;
	int start_idx = match_idx(start);

	pq.push({ 0, start_idx });

	while (!pq.empty()) {
		int cur_val = -pq.top().first;
		int cur_idx = pq.top().second;

		pq.pop();

		for (int i = 0;i < idx;i++) {
			int new_val = mode ? graph[i][cur_idx] : graph[cur_idx][i];
			if (new_val == INT_MAX)
				continue;

			new_val += cur_val;
			if (new_val < dijk_cost[i]) {
				dijk_cost[i] = new_val;
				pq.push({ -new_val, i });
			}
		}
	}
}

void dijk3(int start, int mode) {
	for (int i = 0;i < idx;i++) {
		dijk_cost[i] = INT_MAX;
	}
	memset(visited, 0, sizeof(int) * idx);
	priority_queue < pair<int, int>> pq;
	int start_idx = match_idx(start);

	pq.push({ 0, start_idx });

	while (!pq.empty()) {
		int cur_val = -pq.top().first;
		int cur_idx = pq.top().second;
		visited[cur_idx] = 1;

		pq.pop();

		for (int i = 0;i < idx;i++) {
			if (visited[i])
				continue;
			int new_val = mode ? graph[i][cur_idx] : graph[cur_idx][i];
			if (new_val == INT_MAX)
				continue;

			new_val += cur_val;
			if (new_val < dijk_cost[i]) {
				dijk_cost[i] = new_val;
				pq.push({ -new_val, i });
			}
		}
	}
}

int cost(int mHub) {
	int res = 0;
	dijk2(mHub, 0);
	//printdijk();
	for (int i = 0;i < idx;i++)
		res += dijk_cost[i];
	dijk2(mHub, 1);
	for (int i = 0;i < idx;i++)
		res += dijk_cost[i];
	return res;
}