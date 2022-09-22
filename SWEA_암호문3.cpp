#include<stdio.h>
#include<string.h>
# define MAX_NODE 54000

struct Node {
	char data[7];
	Node* next;
};

Node node[MAX_NODE];

int idx;
Node* head;

void init() {
	idx = 0;
	head = &node[idx++];
	head->next = nullptr;
}

Node* getnode(char* data) {
	Node* newnode = &node[idx++];
	memcpy(newnode->data, data, sizeof(char) * 7);
	newnode->next = nullptr;
	return newnode;
}

void add2last(char* data) {
	Node* temp = head;
	while (temp->next != nullptr)
		temp = temp->next;
	Node* newnode = getnode(data);
	temp->next = newnode;
}

void print_list() {
	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
		printf("%s ", temp->data);
	}
}

Node* find_node(int N) {
	Node* temp = head;
	for (int i = 0; i < N;i++)
		temp = temp->next;
	return temp;
}

int main(int argc, char** argv) {
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		init();
		scanf("%d", &N);
		char buffer[7];
		for (int i = 0;i < N;i++) {
			scanf("%s", buffer);
			//printf("\n%d %s\n", i, buffer);
			add2last(buffer);
		}
		//print_list();
		// return 0;
		//printf("\n%d\n", idx);
		int M;
		scanf("%d", &M);
		for (int i = 0;i < M;i++) {
			// printf("\n%d\n", i);
			char mode[2];
			scanf("%s", &mode);
			// printf("\nscan: %c\n", mode[0]);
			int x, y;
			Node* startpoint, * finpoint;
			switch (mode[0]) {
				case 'I':
					// printf("\nmode: I\n");
					scanf("%d %d", &x, &y);
					startpoint = find_node(x);
					// printf("\n%s\n", startpoint->data);
					for (int j = 0;j < y;j++) {
						scanf("%s", buffer);
						Node* tempnode = getnode(buffer);
						tempnode->next = startpoint->next;
						startpoint->next = tempnode;
						startpoint = tempnode;
					}
					break;
				case 'D':
					// printf("\nmode: D\n");
					scanf("%d %d", &x, &y);
					startpoint = find_node(x);
					// printf("\n%s\n", startpoint->data);
					finpoint = find_node(x + y);
					// printf("\n%s\n", finpoint->data);
					startpoint->next = finpoint->next;
					break;
				case 'A':
					// printf("\nmode: A\n");
					scanf("%d", &y);
					for (int j = 0;j < y;j++) {
						scanf("%s", buffer);
						add2last(buffer);
					}
			}
		}
		printf("#%d", test_case);
		Node* printnode = head;
		for (int i = 0;i < 10;i++) {
			printnode = printnode->next;
			printf(" %s", printnode->data);
		}
		puts("");
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
mode를 %c로 input을 받아서 문제가 생겼었다.
*/