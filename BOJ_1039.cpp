#include <stdio.h>
#include <string.h>

int check_digit(int input) {
	int digit = 0;
	while (input) {
		digit++;
		input /= 10;
	}
	return digit;
}

int pow_func(int digit) {
	int ret = 1;
	for (int i = 1;i < digit;i++)
		ret *= 10;
	return ret;
}

int max, idx, cur_val[360], update_val[360];

void add_update(int val) {
	for (int i = 0;i < idx;i++)
		if (update_val[i] == val)
			return;
	// printf("add: %d %d\n", idx, val);
	update_val[idx++] = val;
}

int main() {
	int N, K;
	//while (1) {
		scanf("%d %d", &N, &K);
		// printf("%d\n", check_digit(N));
		// printf("%d\n\n", pow_func(check_digit(N)));
		cur_val[idx++] = N;
		int digit = check_digit(N);
		if (digit == 1) {
			printf("-1");
			return 0;
		}
		for (int i = 0;i < K;i++) {
			max = 0;
			int loop = idx;
			idx = 0;
			for (int j = 0;j < loop;j++) {
				int cur = cur_val[j];
				for (int swp1 = 1; swp1 < digit; swp1++) {
					for (int swp2 = swp1 + 1; swp2 < digit + 1; swp2++) {
						//printf("%d %d\n", swp1, swp2);
						int temp1 = (cur % pow_func(swp1 + 1)) / pow_func(swp1);
						int temp2 = (cur % pow_func(swp2 + 1)) / pow_func(swp2);
						int new_val = cur + (temp2 - temp1) * pow_func(swp1) + (temp1 - temp2) * pow_func(swp2);
						if (new_val > max)
							max = new_val;
						add_update(new_val);
					}
				}
			}
			if (check_digit(max) != digit) {
				printf("-1");
				return 0;
			}
			memcpy(cur_val, update_val, sizeof(int) * 360);
		}
		printf("%d", max);
	//}
}
/*
왜 나올 수 있는 최대 케이스가 n!이 아닌 n!/2인가?
즉, 여섯자리 수는 최대 720가지 케이스가 아닌 360가지 케이스만 나오게 된다.(한 step에 나올 수 있는 case)
왜 그럴까?
*/


/*
#include <stdio.h>

int int_to_arr(int num, int* arr) {
	int ret_val = 0, digit=0;
	while (num != 0) {
		arr[digit++] = num % 10;
		num /= 10;
	}
	return digit - 1;
}

int arr_to_int(int digit, int* arr) {
	int ret = 0;
	for (; digit > -1;digit--) {
		ret *= 10;
		ret += arr[digit];
	}
	return ret;
}

int check_max(int digit, int* arr) { 
	int max = 0;
	int temp_arr[7];
	int swap_arr[7];
	for (int i = digit;i > 0;i--) {
		for (int j = i - 1;j > -1;j--) {
			for (int k = 0;k < 7;k++)
				swap_arr[k] = arr[k];
			// memcpy(swap_arr, arr, sizeof(int)*7);
			int tmp = swap_arr[i];
			swap_arr[i] = swap_arr[j];
			swap_arr[j] = tmp;
			int res = arr_to_int(digit, swap_arr);
			if (res > max) {
				max = res;
				for (int k = 0;k < 7;k++)
					temp_arr[k] = swap_arr[k];
				// memcpy(temp_arr, swap_arr, sizeof(int)*7);
			}
		}
	}
	for (int i = 0;i < 7;i++)
		arr[i] = temp_arr[i];
	//memcpy(arr, temp_arr, sizeof(int) * 7);
	return max;
}

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	int num_arr[7];
	int digit = int_to_arr(N, num_arr);
	if (digit < 1) {
		printf("-1");
		return 0;
	}
	int result;
	int trash_arr[7];
	for (int i = 0;i < K; i++) {
		result = check_max(digit, num_arr);
		if (digit != int_to_arr(result, trash_arr)) {
			printf("-1");
			return 0;
		}
	}
	printf("%d", result);
	return 0;
	*/
	/*
	printf("%d\n", digit);
	for (int i = 6;i >= 0;i--)
		printf("%d", num_arr[i]);
	*/
// }

/*
이 문제의 접근을 greedy하게 가져가도 될 것인가?
될 듯?
1. int로 받고
2. int를 arr에 담아서 반환해주는 함수. return값은 몇자리인지
3. input을 일단 넣어 한자리수면 -1 리턴
4. bfs돌리고 그걸 int로 돌려서 max보다 크면 max를 바꿔주기
5. 자리수가 더 줄어들었다면 return 0;

반례 4188 2, 1488 2
따라서 안된다.
*/