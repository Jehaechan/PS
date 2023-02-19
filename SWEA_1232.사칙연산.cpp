#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 2000

typedef struct Node {
	int data;
	int left;
	int right;
};

Node node[MAX_LEN];
double BSTf[MAX_LEN];

void getnode(int cur_idx, int data, int left, int right) {
	node[cur_idx].data = data;
	node[cur_idx].left = left;
	node[cur_idx].right = right;
}

void traversal(int idx) {
	int left = node[idx].left;
	int right = node[idx].right;
	if (left)
		traversal(left);
	if (right)
		traversal(right);

	if (node[idx].data > -1) {
		BSTf[idx] = (double)node[idx].data;
	}
	else if (node[idx].data == -1) {
		BSTf[idx] = BSTf[left] + BSTf[right];
	}
	else if (node[idx].data == -2) {
		BSTf[idx] = BSTf[left] - BSTf[right];
	}
	else if (node[idx].data == -3) {
		BSTf[idx] = BSTf[left] * BSTf[right];
	}
	else if (node[idx].data == -4) {
		BSTf[idx] = BSTf[left] / BSTf[right];
	}
}

int main(int argc, char** argv) {
	int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);

	for (test_case = 1; test_case <= T; ++test_case) {
		int N;
		scanf("%d", &N);
		for (int i = 0;i < N;i++) {
			int idx;
			char buffer[10];
			Node* newnode;
			scanf("%d", &idx);
			scanf(" %s", buffer);
			char op = buffer[0];
			if (op <= '9' && op >= '0') {
				getnode(idx, atoi(buffer), 0, 0);
				continue;
			}

			int left, right, op2int;
			scanf("%d %d", &left, &right);

			if (op == '+') {
				op2int = -1;
			}
			else if (op == '-') {
				op2int = -2;
			}
			else if (op == '*') {
				op2int = -3;
			}
			else if (op == '/') {
				op2int = -4;
			}

			getnode(idx, op2int, left, right);
		}
		
		traversal(1);
		printf("#%d %d\n", test_case, (int)BSTf[1]);
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
얘는 앞전 문제와 다르게 노드 번호가 순서대로 쌓이는게 아니므로 자식 노드 번호를 저장해야 함을 유의
*/