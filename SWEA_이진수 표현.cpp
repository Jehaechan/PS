#include <stdio.h>

int main(int argc, char** argv)
{
	int test_case;
	int T;
	int bitmask[31] = { 0 };
	for (int i = 1;i < 31;i++)
		bitmask[i] = (bitmask[i - 1] << 1) | 1;
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N, M;
		scanf("%d %d", &N, &M);

		printf("#%d %s\n", test_case, (bitmask[N] ^ M) << (32 - N) ? "OFF" : "ON");
	}
	return 0;
}