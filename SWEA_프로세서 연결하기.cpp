#include <stdio.h>
#include <string.h>
struct coord {
	int x;
	int y;
};

coord list[12];
char map[12][12];
int max_processor;		// 현재까지 켜질 수 있는 max 프로세서
int cur_processor;		// 지금 켜져있는 프로세서
int min_len;
int cur_len;
int idx;
int map_size;

void recursive(int cur_idx) {
	if (cur_idx == idx || (idx - cur_idx + cur_processor) < max_processor) {
		if (cur_processor > max_processor) {
			max_processor = cur_processor;
			min_len = cur_len;
		}
		else if (cur_processor == max_processor) {
			if (cur_len < min_len)
				min_len = cur_len;
		}
		return;
	}
	int cur_x = list[cur_idx].x;
	int cur_y = list[cur_idx].y;
	int valid;
	int cur_cnt;

	valid = 1;
	cur_cnt = 0;
	for (int i = cur_x - 1;i >= 0;i--) {
		if (map[i][cur_y]) {
			valid = 0;
			break;
		}
	}
	if (valid) {
		for (int i = cur_x - 1;i >= 0;i--) {
			map[i][cur_y] = 2;
			cur_cnt++;
		}
		cur_len += cur_cnt;
		cur_processor++;
	}
	recursive(cur_idx + 1);
	if (valid) {
		for (int i = cur_x - 1;i >= 0;i--) {
			map[i][cur_y] = 0;
		}
		cur_len -= cur_cnt;
		cur_processor--;
	}

	valid = 1;
	cur_cnt = 0;
	for (int i = cur_x + 1;i < map_size;i++)
		if (map[i][cur_y]) {
			valid = 0;
			break;
		}
	if (valid) {
		for (int i = cur_x + 1;i < map_size;i++) {
			map[i][cur_y] = 2;
			cur_cnt++;
		}
		cur_len += cur_cnt;
		cur_processor++;
	}
	recursive(cur_idx + 1);
	if (valid) {
		for (int i = cur_x + 1;i < map_size;i++) {
			map[i][cur_y] = 0;
		}
		cur_len -= cur_cnt;
		cur_processor--;
	}

	valid = 1;
	cur_cnt = 0;
	for (int i = cur_y - 1;i >= 0;i--) {
		if (map[cur_x][i]) {
			valid = 0;
			break;
		}
	}
	if (valid) {
		for (int i = cur_y - 1;i >= 0;i--) {
			map[cur_x][i] = 2;
			cur_cnt++;
		}
		cur_len += cur_cnt;
		cur_processor++;
	}
	recursive(cur_idx + 1);
	if (valid) {
		for (int i = cur_y - 1;i >= 0;i--) {
			map[cur_x][i] = 0;
		}
		cur_len -= cur_cnt;
		cur_processor--;
	}

	valid = 1;
	cur_cnt = 0;
	for (int i = cur_y + 1;i < map_size;i++)
		if (map[cur_x][i]) {
			valid = 0;
			break;
		}
	if (valid) {
		for (int i = cur_y + 1;i < map_size;i++) {
			map[cur_x][i] = 2;
			cur_cnt++;
		}
		cur_len += cur_cnt;
		cur_processor++;
	}
	recursive(cur_idx + 1);
	if (valid) {
		for (int i = cur_y + 1;i < map_size;i++) {
			map[cur_x][i] = 0;
		}
		cur_len -= cur_cnt;
		cur_processor--;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d",&T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(map, 0, sizeof(char) * 12 * 12);		// map 초기화

		cur_processor = 0;
		max_processor = 0;
		min_len = 9999999;
		idx = 0;

		scanf("%d", &map_size);
		for (int i = 0;i < map_size;i++)
			for (int j = 0;j < map_size;j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] && i > 0 && j > 0 && i < map_size -1 && j < map_size -1) {
					list[idx].x = i;
					list[idx++].y = j;
				}
			} 

		/*for (int i = 0;i < len;i++) {
			for (int j = 0;j < len;j++)
				printf("%d ", map[i][j]);
			puts("");
		}*/

		/*for (int i = 0;i < idx;i++)
			printf("%d %d\n", list[i].x, list[i].y);
		puts("");*/
		cur_len = 0;
		recursive(0);
		printf("#%d %d\n", test_case, min_len);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
