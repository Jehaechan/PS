#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	for (test_case = 1; test_case <= T; ++test_case) {
		int N;
		int valid = 1;
		scanf("%d", &N);
		if (N % 2 == 0)
			valid = 0;
		for (int i = 0;i < N;i++) {
			int idx;
			char buffer[20];
			scanf("%d", &idx);
			scanf("%[^\n]s", buffer);
			if (idx <= N / 2) {
				if (buffer[1] <= '9' && buffer[1] >= '0') 
					valid = 0;
			}
			else {
				if (buffer[1] > '9' || buffer[1] < '0') 
					valid = 0;
			}
		}
		printf("#%d %d\n", test_case, valid);
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}