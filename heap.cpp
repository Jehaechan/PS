#include <algorithm>
#include <cassert>

class MaxHeap {
#define parent (i >> 1)
#define left (i << 1)
#define right (i << 1 | 1)

	static constexpr size_t MAX_N = 100000;

	int data[MAX_N + 1];
	size_t size;

public:
	MaxHeap() = default;

	void push(int x) {
		data[++size] = x;
		for (int i = size; i != 1 && data[i] > data[parent]; i >>= 1) {
			int temp = data[i];
			data[i] = data[parent];
			data[parent] = temp;
		}
	}

	int top() const {
		assert(size != 0);
		return data[1];
	}

	int pop() {
		assert(size != 0);
		data[1] = data[size--];
		for(int i = 1;i<size)
	}
};