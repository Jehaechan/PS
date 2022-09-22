//////////////////////////////////////// main /////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, FIND, REMOVE, PRINT, PRINT_REVERSE, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int findNode(int data);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);
extern int getReversedList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i = 0;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD: // 1
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL: // 2
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM: // 3
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case FIND: // 4
			scanf("%d", &data);
			num = findNode(data);
			printf("%d\n", num);
			break;
		case REMOVE: // 5
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT: // 6
			cnt = getList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case PRINT_REVERSE: // 7
			cnt = getReversedList(output);
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
	//freopen("dll_input.txt", "r", stdin);

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


////////////////////////////// User Code ////////////////////////////////
#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	nodeCnt = 0;
	head = getNode(0);
}

void addNode2Head(int data)
{
	Node* newnode = getNode(data);
	newnode->prev = head;
	newnode->next = head->next;
	if (newnode->next != nullptr)
		newnode->next->prev = newnode;
	newnode->prev->next = newnode;
}

void addNode2Tail(int data)
{
	Node* cur = head;
	while (cur->next != nullptr)
		cur = cur->next;
	Node* newnode = getNode(data);
	newnode->prev = cur;
	cur->next = newnode;
}

void addNode2Num(int data, int num)
{
	Node* cur = head;
	for (int i = 1;i < num;i++)
		cur = cur->next;
	Node* newnode = getNode(data);
	newnode->prev = cur;
	newnode->next = cur->next;
	if (newnode->next != nullptr)
		newnode->next->prev = newnode;
	newnode->prev->next = newnode;
}

int findNode(int data)
{
	Node* cur = head;
	int i;
	for (i = 0;cur->data != data && cur->next != nullptr;i++)
		cur = cur->next;
	return i;
}

void removeNode(int data)
{
	Node* cur = head;
	while(cur->next != nullptr && cur->next->data != data)
		cur = cur->next;
	if (cur->next != nullptr) {
		cur->next = cur->next->next;
		if (cur->next != nullptr)
			cur->next->prev = cur;
	}
}

int getList(int output[MAX_NODE])
{
	Node* cur = head->next;
	int i = 0;
	while (cur != nullptr) {
		output[i++] = cur->data;
		cur = cur->next;
	}
	return i;
}

int getReversedList(int output[MAX_NODE])
{
	Node* cur = head;
	while (cur->next != nullptr)
		cur = cur->next;
	int i = 0;
	while (cur != head) {
		output[i++] = cur->data;
		cur = cur->prev;
	}
	return i;
}