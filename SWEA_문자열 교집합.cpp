#include <stdio.h>
#include <string.h>

#define SIZE 8192

int djb2(char* str) {
	int hash = 5381;
	int c;
	
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash & (SIZE - 1);
}
// SIZE가 2의 배수일 때 SIZE - 1이랑 bitwise and 연산 해주면 나머지 연산과 같은 효과
// 나누기를 쓴다면 그냥 hash % SIZE 해야한다.

struct Node {
	char str[51];
	Node* next;
};

Node node[100001];
int idx;

Node* hash[SIZE];

void init() {
	idx = 0;
	memset(hash, 0, sizeof(Node*) * SIZE);
}

Node* newnode(char* str) {
	strcpy(node[idx].str, str);
	node[idx].next = nullptr;
	
	return &node[idx++];
}

int main() {
	int test_case;
	int T=1;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		int N, M;
		scanf("%d %d", &N, &M);
		
		char buffer[51];
		for (int i = 0;i < N;i++) {
			scanf("%s", buffer);
			int key = djb2(buffer);
			if (hash[key] == nullptr) {
				hash[key] = newnode(buffer);
			}
			else {
				Node* temp = hash[key];
				while (temp->next != nullptr)
					temp = temp->next;
				temp->next = newnode(buffer);
			}
		}

		int cnt = 0;

		for (int i = 0;i < M;i++) {
			scanf("%s", buffer);
			int key = djb2(buffer);
			if (hash[key] == nullptr)
				continue;
			Node* temp = hash[key];
			while (temp != nullptr) {
				if (!strcmp(buffer, temp->str)) {
					cnt++;
					break;
				}
				else {
					temp = temp->next;
				}
			}
		}

		printf("#%d %d\n", test_case, cnt);
		/*
		for (int i = 0;i < SIZE;i++) {
			if (hash[i] != nullptr)
				printf("%d %s\n", i, hash[i]->str);
		}
		return 0;
		*/
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}