#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int input, i, mask = 0;
		scanf("%d", &input);
		for (i = 1;mask^0x3FF;i++) {
			int checknum = i * input;
			while (checknum) {
				int num = checknum % 10;
				checknum /= 10;
				int checkmask = 1 << num;
				mask |= checkmask;
			}
		}
		printf("#%d %d\n", test_case, (i - 1) * input);
	}
	return 0;
}