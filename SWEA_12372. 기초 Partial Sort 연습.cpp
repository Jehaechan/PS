#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

extern void init();
extern void addUser(int uID, int income);
extern int getTop10(int result[10]);

static int input[MAX_INPUT];

static unsigned int seed = 13410;

static unsigned int pseudoRand() {
	seed = seed * 214013 + 2531011;
	return (unsigned int)(seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen) {
	for (int i = 0; i < inputLen; i++) {
		input[i] = pseudoRand();
	}
}

static int run() {
	int N, userNum, uID = 0;
	int score = 100, result[10], cnt;
	int sum, check;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &userNum);
		makeInput(userNum);
		for (int j = 0; j < userNum; j++) {
			addUser(uID++, input[j]);
		}
		cnt = getTop10(result);

		sum = 0;
		for (int j = 0; j < cnt; j++) {
			sum += result[j];
		}
		scanf("%d", &check);
		if (check != sum)
			score = 0;
	}
	return score;
}

int main(void) {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		printf("#%d %d\n", tc, run());
	}
	return 0;
}



//////////// User Code ////////////////
typedef struct Node {
	int id;
	int income;
}node;

node Maxheap[100001];
int size;

void init()	{
	size = 0;
}

#define parent (i >> 1)
#define left (i << 1)
#define right (i << 1 | 1)

int compare(int par, int cur) {
	if (Maxheap[par].income == Maxheap[cur].income)
		return Maxheap[par].id > Maxheap[cur].id;
	return Maxheap[par].income < Maxheap[cur].income;
}
//  par < cur: return 1

void addUser(int uID, int height) {
	Maxheap[++size].id = uID;
	Maxheap[size].income = height;
	for (int i = size;i != 1 && compare(parent, i); i = parent) {
		node temp = Maxheap[parent];
		Maxheap[parent] = Maxheap[i];
		Maxheap[i] = temp;
	}
}

void pop() {
	Maxheap[1] = Maxheap[size--];
	for (int i = 1;left <= size;) {
		if (size == left) {
			if (compare(i, left)) {
				node temp = Maxheap[left];
				Maxheap[left] = Maxheap[i];
				Maxheap[i] = temp;
			}
			return;
		}
		else {
			if (compare(right, left)) {	// left가 더 크다면
				if (compare(i, left)) {
					node temp = Maxheap[left];
					Maxheap[left] = Maxheap[i];
					Maxheap[i] = temp;
					i = left;
				}
				else {
					return;
				}
			}
			else {
				if (compare(i, right)) {
					node temp = Maxheap[right];
					Maxheap[right] = Maxheap[i];
					Maxheap[i] = temp;
					i = right;
				}
				else {
					return;
				}
			}
		}
	}
}

int getTop10(int result[10]) {
	int cnt;
	node arr[10];
	int temp_size = size;
	for (cnt = 0; cnt < temp_size && cnt < 10; cnt++) {
		arr[cnt] = Maxheap[1];
		result[cnt] = Maxheap[1].id;
		pop();
	}
	
	for (int i = 0;i < cnt;i++) 
		addUser(arr[i].id, arr[i].income);
	
	return cnt;
}