////////////////////////////////// main //////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, REMOVE, PRINT, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD:
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL:
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM:
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case REMOVE:
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT:
			cnt = getList(output);
			i = 0;
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case END:
			return;
		}
	}
}

int main(void) {
	//setbuf(stdout, NULL);
	//freopen("sll_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("#%d\n", t);
		init();
		run();
		printf("\n");
	}

	return 0;
}


//////////////////////////////// User Code /////////////////////////////////
#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	nodeCnt = 0;
	head = &node[nodeCnt++];
	head->next = nullptr;
}

void addNode2Head(int data)
{
	Node* newnode = getNode(data);
	newnode->next = head->next;
	head->next = newnode;
}

void addNode2Tail(int data)
{
	Node* tempnode = head;
	while (tempnode->next != nullptr)
		tempnode = tempnode->next;
	Node* newnode = getNode(data);
	newnode->next = tempnode->next;
	tempnode->next = newnode;
}

void addNode2Num(int data, int num)
{
	Node* tempnode = head;
	for (int i = 1; i < num;i++) {
		tempnode = tempnode->next;
		if (tempnode->next == nullptr)
			break;
	}
	Node* newnode = getNode(data);
	newnode->next = tempnode->next;
	tempnode->next = newnode;
}

void removeNode(int data)
{
	Node* tempnode = head;
	while (tempnode->next != nullptr && tempnode->next->data != data)
		tempnode = tempnode->next;
	if (tempnode->next != nullptr)
		tempnode->next = tempnode->next->next;
}

int getList(int output[MAX_NODE])
{
	int i = 0;
	Node* tempnode = head->next;
	while (tempnode!=nullptr) {
		output[i++] = tempnode->data;
		tempnode = tempnode->next;
	}
	return i;
}