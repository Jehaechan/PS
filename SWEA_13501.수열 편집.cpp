#include<stdio.h>
struct Node {
	int data;
	Node* next;
};

Node node[3000];
int idx;
Node* head;

void init() {
	idx = 0;
	head = &node[idx++];
	head->next = nullptr;
}

Node* getnode(int data) {
	Node* newnode = &node[idx++];
	newnode->data = data;
	newnode->next = nullptr;
	return newnode;
}

void add2last(int data) {
	Node* tempnode = head;
	while (tempnode->next != nullptr)
		tempnode = tempnode->next;
	Node* newnode = getnode(data);
	tempnode->next = newnode;
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	// freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	// printf("%d\n", T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		int N, M, L;
		scanf("%d %d %d", &N, &M, &L);
		// printf("%d %d %d\n", N, M, L);
		int temp;
		for (int i = 0;i < N;i++) {
			scanf("%d", &temp);
			add2last(temp);
		}
		for (int i = 0;i < M;i++) {
			char mode[2];
			scanf(" %s", mode);
			int x, y;
			Node* tempnode, * newnode;
			switch (mode[0]) {
				case 'I':
					scanf("%d %d", &x, &y);
					// printf("%c %d %d\n", mode[0], x, y);
					tempnode = head;
					for (int j = 0;j < x;j++)
						tempnode = tempnode->next;
					newnode = getnode(y);
					newnode->next = tempnode->next;
					tempnode->next = newnode;
					break;
				case 'D':
					scanf("%d", &x);
					// printf("%c %d\n", mode[0], x);
					tempnode = head;
					for (int j = 0;j < x;j++)
						tempnode = tempnode->next;
					tempnode->next = tempnode->next->next;
					break;
				case 'C':
					scanf("%d %d", &x, &y);
					// printf("%c %d %d\n", mode[0], x, y);
					tempnode = head;
					for (int j = 0;j < x;j++)
						tempnode = tempnode->next;
					tempnode->next->data = y;
			}
		}
		Node* printnode = head;
		for (int i = 0;i < L;i++) {
			printnode = printnode->next;
			if (printnode->next == nullptr)
				break;
		}
		printf("#%d ", test_case);
		if (printnode->next) {
			printf("%d\n", printnode->next->data);
		}
		else {
			printf("-1\n");
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
scanf 공백 포함하는 법
-> scanf("%[^\n]s", input);
*/
