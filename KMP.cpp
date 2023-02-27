#include <stdio.h>

const char str[12] = "abababacabc";
int pi[11];

int main() {
	int i = 0;	// 직전까지 겹친 개수
	for (int j = 1;j < 11;j++) {
		while (i != 0 && str[i] != str[j]) {
			i = pi[i - 1];
		}
		if (str[i] == str[j])
			i++;
		pi[j] = i;
	}

	for (int i = 0;i < 11;i++)
		printf("%d ", pi[i]);
}