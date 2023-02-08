#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

int N;

typedef struct coordinate {
	int x;
	int y;
}coord;

coord mv[4] = { {0,1},{0,-1},{1,0},{-1,0} };

void printall(char input[][100]) {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			printf("%d ", input[i][j]);
		}
		puts("");
	}
}

void bfs(char input[][100], char visit[][100], coord first) {
	queue<coord> q;
	q.push(first);
	while (!q.empty()) {
		coord cur = q.front();
		q.pop();
		int x = cur.x;
		int y = cur.y;
		if (visit[x][y])
			continue;
		visit[x][y] = 1;
		input[x][y]--;
		for (int i = 0;i < 4;i++) {
			coord tmp = mv[i];
			coord next;
			next.x = x + tmp.x;
			next.y = y + tmp.y;
			if (next.x<0 || next.y<0 || next.x>N - 1 || next.y>N - 1)
				continue;
			if (visit[next.x][next.y])
				continue;
			if (input[next.x][next.y] > 0) {
				q.push(next);
			}
		}
	}
}

int main(void)
{
	int test_case;
	int T;
	char input[100][100];
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &N); // 한 변의 길이
		int loop = 0;
		for (int i = 0;i < N;i++)
			for (int j = 0;j < N;j++) {
				scanf("%d", &input[i][j]);
				if (loop < input[i][j])
					loop = input[i][j];
			}
		int max = 0;
		for (int i = 0;i < loop;i++) {
			char visit[100][100];
			int cnt = 0;
			memset(visit, 0, sizeof(char) * 100 * 100);
			for (int j = 0;j < N;j++)
				for (int k = 0;k < N;k++) {
					if (visit[j][k])
						continue;
					int valid = input[j][k] > 0 ? 1 : 0;
					if (!valid)
						continue;
					cnt += valid;
					coord cur;
					cur.x = j;
					cur.y = k;
					bfs(input, visit, cur);
					//printall(input);
				}
			if (max < cnt)
				max = cnt;
		}
		printf("#%d %d\n", test_case, max);
	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}

/*
1. malloc하지 않은 이차원 배열을 파라미터로 넘기는 방법
- 파라미터를 char input[][100]과 같이 받아서 char*까지는 괜찮으니까 그 이후로는 데이터 사이즈를 알 수 있도록 해준다.

2. 이차원배열 그냥 for문 안쓰고 바로 memset해도 된다.

3. 이차원 배열 선언하고 초기화 하는법 int arr[3][3] = { {1,2,3}, {1,2,3}, {1,2,3} }

4. 구조체 초기화 방법도 위와 같다.

5. if else문을 쓸 때에는 brace를 잊지 말자
*/

/*
#include <iostream>
using namespace std;

int n;
int map[100][100];
bool is_sink[100][100];
bool visit[100][100];
int didj[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

bool is_all_sink() {
   for (int i = 0; i < n; i++) {
	  for (int j = 0; j < n; j++) {
		 if (!is_sink[i][j]) return false;
	  }
   }
   return true;
}

void sink(int year) {
   for (int i = 0; i < n; i++) {
	  for (int j = 0; j < n; j++) {
		 if (map[i][j] <= year) is_sink[i][j] = true;
	  }
   }
}

void init_visit() {
   for (int i = 0; i < n; i++) {
	  for (int j = 0; j < n; j++) {
		 visit[i][j] = false;
	  }
   }
}

void init_sink() {
   for (int i = 0; i < n; i++) {
	  for (int j = 0; j < n; j++) {
		 is_sink[i][j] = false;
	  }
   }
}

void dfs(int i, int j) {
   if (i < 0 || i >= n || j < 0 || j >= n) return;
   if (visit[i][j] || is_sink[i][j]) return;
   visit[i][j] = true;

   for (int k = 0; k < 4; k++) {
	  int ni = i + didj[k][0];
	  int nj = j + didj[k][1];
	  dfs(ni, nj);
   }
}

int cal_area_cnt() {
   init_visit();
   int area_cnt = 0;
   for (int i = 0; i < n; i++) {
	  for (int j = 0; j < n; j++) {
		 if (!visit[i][j] && !is_sink[i][j]) {
			dfs(i, j);
			area_cnt++;
		 }
	  }
   }
   return area_cnt;
}

int main() {
   int T;
   scanf("%d", &T);
   for (int t = 1; t <= T; t++) {
	  scanf("%d", &n);

	  for (int i = 0; i < n; i++) {
		 for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		 }
	  }

	  int year = 1;
	  int ans = cal_area_cnt();
	  while (!is_all_sink()) {
		 sink(year);
		 int tmp_ans = cal_area_cnt();
		 if (tmp_ans > ans) ans = tmp_ans;
		 year++;
	  }

	  printf("#%d %d\n", t, ans);
	  init_sink();
   }
}
*/
