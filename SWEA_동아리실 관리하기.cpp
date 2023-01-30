#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	int test_case;
	int T;
	scanf("%d", &T);
	int cnt_cur[16];
	int cnt_temp[16];
	for (test_case = 1; test_case <= T; ++test_case)
	{
		char input[10001];
		scanf(" %s", input);
		int len = strlen(input);
		memset(cnt_cur, 0, sizeof(int)*16);
		cnt_cur[1] = 1;
		for (int i = 0;i < len;i++) {
			memset(cnt_temp, 0, sizeof(int) * 16);
			int bitmask = 1 << (input[i] - 'A');
			for (int cur = 1;cur < 16;cur++)
				if (cur & bitmask)
					for (int prev = 1;prev < 16;prev++)
						if (cur & prev) {
							cnt_temp[cur] += cnt_cur[prev];
							cnt_temp[cur] %= 1000000007;
						}
			memcpy(cnt_cur, cnt_temp, sizeof(int) * 16);
		}
		int cnt = 0;
		for (int i = 1;i < 16;i++) {
			cnt += cnt_cur[i];
			cnt %= 1000000007;
		}
		printf("#%d %d\n", test_case, cnt);
	}
	return 0;
}

/*
memset은 Byte단위로 memset하므로 int형에 0이 아닌 숫자를 memset하게 되면 이상한 숫자가 나오게 됨을유의!
*/