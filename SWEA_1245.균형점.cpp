#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
	char arr[100];
	char arr2[100] = { 0, };
	int p, m;
	scanf(" %s", arr);
	scanf("%d %d", &p, &m);

	int idx = 1;
	int len = strlen(arr);
	int token_len = 0;
	int flag = 0;
	for (int i = 0;i < len;i++) {
		char cur = arr[i];
		if (idx == m && cur != '-')
			arr2[token_len] = cur;
		if (cur == '-') {
			if (token_len == 0)
				flag = 1;
			token_len = 0;
			idx++;
			continue;
		}
		token_len++;
		if (token_len > 4) {
			printf("INPUT ERROR!");
			return 0;
		}
	}

	if (idx < m) {
		printf("INPUT ERROR!");
		return 0;
	}

	char res[5] = "0000";
	int temp_len = strlen(arr2);
	strcpy(&res[4 - temp_len], arr2);

	for (int i = 0;i < 4;i++)
		printf("%c", ((res[i] - '0') + p) % 10 + '0');

}