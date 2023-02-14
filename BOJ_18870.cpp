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
	vector<int> v(n); //원본 벡터
	// 입력
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	vector<int> cv(v); // 원본 벡터를 복사하여 중복 된 수를 제거하고 정렬을 시행 할 벡터.
	sort(cv.begin(), cv.end()); //오름차순 정렬
	// 중복 제거
	cv.erase(unique(cv.begin(), cv.end()), cv.end());
	for (int i = 0; i < n; i++)
	{
		// i번째 요소값의 위치 it
		auto it = lower_bound(cv.begin(), cv.end(), v[i]);
		// it에서 cv벡터의 시작 주소값을 빼준 값이 답
		cout << it - cv.begin() << ' ';
	}

	return 0;
}
*/

/*
배열 하나 더 선언해서 정렬 후 중복제거.
원래 배열에서 하나씩 뽑아보며 lower_bound함수(이진 탐색 기반으로 해당하는 값보다 크거나 같은 값이 제일 처음 등장하는 위치를 리턴)로 정렬된 리스트의 몇번째에 위치하고 있는지 찾으면 됨.
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