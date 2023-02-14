#include <stdio.h>

int main() {
	int N;
	int cnt = 0, idx = 0, cur_idx = 0;
	int arr[10] = { 0 };

	scanf("%d", &N);

	int flag = 0;
	// update�� �־��� ��� �׻� i = cur_idx - 1,�� ���� �� arr[i]=i�� i==0���� ���� ���� cur_idx = 0�� ���༭ idx 0���� ���캸�� �ȴ�.
	// cur_idx���� update�� �Ұ����� ��� cur_idx�� �ϳ� �÷��ش�.
	// cur_idx == 10�� �Ǵ� ���� return
	while (N != cnt && cur_idx < 10) {
		if (flag) {
			for (int i = cur_idx - 1;i > -1;i--)
				arr[i] = i;
			cur_idx = 0;
			flag = 0;
			cnt++;
		}
		else if (arr[cur_idx + 1] > arr[cur_idx] + 1) {
			arr[cur_idx]++;
			flag = 1;
		}
		else {
			if (idx == cur_idx) {
				if (arr[cur_idx] == 9)
					idx++;
				else {
					do {
						arr[cur_idx]++;
					} while (arr[cur_idx] < cur_idx);
					flag = 1;
				}
			}
			else
				cur_idx++;
		}
	}
	if (cur_idx == 10)
		printf("-1");
	else
		for (int i = idx;i > -1;i--)
			printf("%d", arr[i]);
	return 0;
}

/*
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int n;

void bfs() {
   queue<vector<int>> q;
   vector<int> init_v = { 10 };
   q.push(init_v);
   int cnt = -1;

   while (!q.empty()) {
	  vector<int> cur_v = q.front();
	  int last_num = cur_v[cur_v.size() - 1];
	  if (last_num == 10) cur_v.clear();
	  q.pop();

	  for (int i = 0; i < last_num; i++) {
		 vector<int> new_v = cur_v;
		 new_v.push_back(i);
		 q.push(new_v);
		 cnt++;
		 if (cnt == n) {
			for (int a : new_v) printf("%d", a);
			return;
		 }
	  }
   }
   printf("-1");
   return;
}

int main() {
   scanf("%d", &n);
   bfs();
}
*/

/*
#include <stdio.h>

int main() {
	int N;
	int cnt = 0, idx = 0, cur_idx = 0;
	int arr[10] = { 0 };

	//scanf("%d", &N);
	for (N = 0;N < 1024;N++) {
		int flag = 0;
		while (N != cnt && cur_idx < 10) {
			if (flag) {
				for (int i = cur_idx - 1;i > -1;i--)
					arr[i] = i;
				cur_idx = 0;
				flag = 0;
				cnt++;
			}
			else if (arr[cur_idx + 1] > arr[cur_idx] + 1) {
				arr[cur_idx]++;
				flag = 1;
			}
			else {
				if (idx == cur_idx) {
					if (arr[cur_idx] == 9)
						idx++;
					else {
						do {
							arr[cur_idx]++;
						} while (arr[cur_idx] < cur_idx);
						flag = 1;
					}
				}
				else
					cur_idx++;
			}
		}
		if (cur_idx == 10)
			printf("-1");
		else
			for (int i = idx;i > -1;i--)
				printf("%d", arr[i]);
		puts("a");
	}
}
*/