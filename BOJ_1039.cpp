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
�� ���� �� �ִ� �ִ� ���̽��� n!�� �ƴ� n!/2�ΰ�?
��, �����ڸ� ���� �ִ� 720���� ���̽��� �ƴ� 360���� ���̽��� ������ �ȴ�.(�� step�� ���� �� �ִ� case)
�� �׷���?
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
�� ������ ������ greedy�ϰ� �������� �� ���ΰ�?
�� ��?
1. int�� �ް�
2. int�� arr�� ��Ƽ� ��ȯ���ִ� �Լ�. return���� ���ڸ�����
3. input�� �ϴ� �־� ���ڸ����� -1 ����
4. bfs������ �װ� int�� ������ max���� ũ�� max�� �ٲ��ֱ�
5. �ڸ����� �� �پ����ٸ� return 0;

�ݷ� 4188 2, 1488 2
���� �ȵȴ�.
*/