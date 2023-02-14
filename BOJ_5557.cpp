#include <stdio.h>
#include <string.h>

int main() {
	int N, temp, flag = 0;
	long long arr1[21] = { 0 };
	long long arr2[21] = { 0 };
	scanf("%d", &N);
	scanf("%d", &temp);
	arr1[temp]++;
	for (int i = 1;i < N - 1;i++) {
		scanf("%d", &temp);
		long long* target = flag ? arr2 : arr1;
		long long* result = flag ? arr1 : arr2;
		memset(result, 0, sizeof(long long) * 21);
		for (int j = 0;j < 21;j++) {
			long long add = j + temp;
			long long sub = j - temp;
			if (add < 21)
				result[add] += target[j];
			if (sub > -1)
				result[sub] += target[j];
		}
		flag ^= 1;
	}
	scanf("%d", &temp);
	long long* print_arr = flag ? arr2 : arr1;
	printf("%lld", print_arr[temp]);
}

/*
XOR¿¬»êÀÚ ^
0 0		1
0 1		0
1 0		0
1 1		1
*/