#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct pair {
	int x;
	int idx;
}p;

int compare_x(const void* a, const void* b) {
	p* tempa = (p*)a;
	p* tempb = (p*)b;
	if (tempa->x > tempb->x)
		return 1;
	else if (tempa->x < tempb->x)
		return -1;

	return 0;
}

int compare_idx(const void* a, const void* b) {
	p* tempa = (p*)a;
	p* tempb = (p*)b;
	if (tempa->idx > tempb->idx)
		return 1;
	else if (tempa->idx < tempb->idx)
		return -1;

	return 0;
}

int main() {
	int N;
	p* arr;
	scanf("%d", &N);
	arr = (p*)malloc(sizeof(p) * N);
	for (int i = 0;i < N;i++) {
		scanf("%d", &arr[i].x);
		arr[i].idx = i;
	}
	qsort(arr, N, sizeof(p), compare_x);
	int cnt = 0;
	int flag;
	for (int i = 0;i < N - 1;i++) {
		flag = 0;
		if (arr[i].x == arr[i + 1].x)
			flag = 1;
		arr[i].x = cnt++;
		cnt -= flag;
	}
	arr[N - 1].x = cnt;
	qsort(arr, N, sizeof(p), compare_idx);
	for (int i = 0;i < N;i++)
		printf("%d ", arr[i].x);
}

/*
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	vector<int> v(n); //���� ����
	// �Է�
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	vector<int> cv(v); // ���� ���͸� �����Ͽ� �ߺ� �� ���� �����ϰ� ������ ���� �� ����.
	sort(cv.begin(), cv.end()); //�������� ����
	// �ߺ� ����
	cv.erase(unique(cv.begin(), cv.end()), cv.end());
	for (int i = 0; i < n; i++)
	{
		// i��° ��Ұ��� ��ġ it
		auto it = lower_bound(cv.begin(), cv.end(), v[i]);
		// it���� cv������ ���� �ּҰ��� ���� ���� ��
		cout << it - cv.begin() << ' ';
	}

	return 0;
}
*/

/*
�迭 �ϳ� �� �����ؼ� ���� �� �ߺ�����.
���� �迭���� �ϳ��� �̾ƺ��� lower_bound�Լ�(���� Ž�� ������� �ش��ϴ� ������ ũ�ų� ���� ���� ���� ó�� �����ϴ� ��ġ�� ����)�� ���ĵ� ����Ʈ�� ���°�� ��ġ�ϰ� �ִ��� ã���� ��.
*/

/*
#include <stdio.h>
#include <algorithm>
using namespace std;

char in[11000000], *op = in;
int ans[1000003];
struct Data { int k, i; } a[1000003];

int readN() {
	static char *p = in;
	int r, b = 1;
	while (*p < 45) p++;
	if (*p == 45) b = -1, p++;
	for (r = *p & 15; *++p & 16; r = r * 10 + (*p & 15));
	return r * b;
}

inline void wrtN(int n) {
	char temp[10], *t = temp;
	if (n < 0) *op++ = '-', n = -n;
	do *t++ = n % 10 | 48; while(n /= 10);
	do *op++ = *--t; while(t != temp);
	*op++ = ' ';
}

int main()
{
	fread(in, 1, sizeof(in), stdin);
	int N = readN(), i, pos = 0;

	for (i = 0; i < N; ++i) a[i].k = readN(), a[i].i = i;

	sort(a, a + N, [](Data &p, Data &q) { return p.k < q.k; });

	ans[a[0].i] = 0;
	for (i = 1; i < N; ++i) {
		if (a[i].k != a[i-1].k) pos++;
		ans[a[i].i] = pos;
	}

	for (i = 0; i < N; ++i) wrtN(ans[i]);
	fwrite(in, 1, op - in, stdout);
	return 0;
}
*/