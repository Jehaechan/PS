#include <stdio.h>

int main() {
	int test_case;
	int T;
	
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		int n, p;
		scanf("%d %d", &n, &p);

		int start, fin;
		scanf("%d", &start);

		/*
		if (n == 1) {
			printf("#%d %d\n", test_case, n + p);
			continue;
		}
		*/

		int distance[200000];
		distance[0] = 0;
		for (int i = 1;i < n;i++) {
			scanf("%d", &fin);
			distance[i] = fin - start;
			start = fin;
		}
		
		for (int i = 1;i < n;i++)
			distance[i] += distance[i - 1];

		
		//for (int i = 0;i < n;i++) {
		//	printf("%d ", distance[i]);
		//}
		//puts("");
		
		int head = 0, tail = n - 1;
		int max_distance = distance[tail];  
		//printf("dist: %d, head: %d, tail: %d\n", max_distance,head,tail);

		
		while (head != tail && max_distance > p) {
			int mid = head + (tail - head) / 2;
			int down_dist, up_dist;
			if ((tail - head) % 2) {	// 홀수개일 때
				down_dist = distance[mid] - distance[head];
				up_dist = distance[tail] - distance[mid];
				down_dist < up_dist?
			}
			else {	// 짝수개일 때

			}
		}
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
head == tail인데 distance가 p보다 크다면 그냥 점 하나만
*/