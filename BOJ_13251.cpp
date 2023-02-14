#include<stdio.h>

double combination(int a, int b) {
	if (a < b)
		return 0.0;
	if (a < b * 2)
		b = a - b;
	if (!b)
		return 1.0;
	double sum = 0.0;
	sum += (double)a;
	for (int i = 1;i < b;i++)
		sum *= (double)a - (double)i;
	for (;b > 0;b--)
		sum /= (double)b;
	return sum;
}

int main() {
	int flag = 0, M, K, sum = 0;
	double numer = 0.0;
	int arr[50];
	scanf("%d", &M);
	for (int i = 0;i < M;i++)
		scanf("%d", arr + i);
	scanf("%d", &K);
	for (int i = 0;i < M;i++) {
		sum += arr[i];
		numer += combination(arr[i], K);
	}
	for (;K > 0;K--) {
		numer /= (double)(sum - (K - 1));
		numer *= (double)K;
	}
	printf("%.20f\n", numer);
}

/*
유효숫자
float: 6자리
double: 16자리
long double: 19자리
*/

/*
#include <iostream>
using namespace std;

int nCm[11][11];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0) nCm[i][j] = 1;
			else if (i != 0) nCm[i][j] = nCm[i - 1][j - 1] + nCm[i - 1][j];
		}
	}

	printf("%d", nCm[n][k]);
}
*/