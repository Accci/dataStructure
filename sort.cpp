#include "common.h"

void bubbleSort(int arr[], int size);
void choiceSort(int arr[], int size);
void insertSort(int arr[], int size);
void shellSort(int arr[], int size);
void quickSort(int arr[], int size);
void heapSort(int arr[], int size);
void mergeSort(int arr[], int size);
void radixSort(int arr[], int size);

#if 0
int main()
{
	int arr[10];
	srand(time(0));

	for (int i = 0; i < 10; ++i)
	{
		arr[i] = (rand() % 100);
	}
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	radixSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}
#endif



#if 0
//测试4种排序的性能

/*
bubbleSort spend: 31.232s
choiceSort spend: 10.168s
insertSort spend: 6.931s
shellSort spend: 0.025s
*/
int main()
{
	const int COUNT = 100000;
	int* arr = new int[COUNT];
	int* brr = new int[COUNT];
	int* crr = new int[COUNT];
	int* drr = new int[COUNT];
	srand(time(NULL));

	for (int i = 0; i < COUNT; ++i)
	{
		
		int val = rand() % COUNT;
		arr[i] = val;
		brr[i] = val;
		crr[i] = val;
		drr[i] = val;
	}

	clock_t begin, end;

	begin = clock();
	bubbleSort(arr, COUNT);
	end = clock();
	cout << "bubbleSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	choiceSort(brr, COUNT);
	end = clock();
	cout << "choiceSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	insertSort(crr, COUNT);
	end = clock();
	cout << "insertSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	shellSort(drr, COUNT);
	end = clock();
	cout << "shellSort spend: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;



	return 0;
}

#endif

//冒泡排序  0(n^2)  ,交换次数多，比较也多，性能最差
void bubbleSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		bool flag = false;
		for (int j = 0; j < size - 1 -i; ++j)
		{

			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				flag = true;
			}
			
		}
		if (!flag)
			break;
	}
}


//选择排序 O（n^2）交换次数少， 比较较多， 比冒泡性能好，因为交换次数少
void choiceSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int k = i, minVal = arr[i];
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] < minVal)
			{
				minVal = arr[j];
				k = j;
			}
		}
		if (k != i)
		{
			int temp = arr[i];
			arr[i] = arr[k];
			arr[k] = temp;
		}
		
	}
}

//插入排序。 如果数据趋于有序，那么插入排序是所有排序算法中，效率最高的排序算法
//最差 O(n^2), 如果每次都往末尾插，性能最好，可以退化为O(n), 无交换，比较较少
void insertSort(int arr[], int size)
{
	for (int i = 1; i < size; ++i)
	{
		int val = arr[i];
		int j = i - 1;
		for (; j >= 0; --j)
		{
			if (arr[j] <= val)
			{
				break;
			}
			arr[j + 1] = arr[j];
		}
		arr[j+1] = val;
	}
}

//希尔排序  对数据进行分组插入排序
void shellSort(int arr[], int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; ++i)
		{
			int val = arr[i];
			int j = i - gap;
			for (; j >= 0; j-=gap)
			{
				if (arr[j] <= val)
				{
					break;
				}
				arr[j + gap] = arr[j];
			}

			arr[j + gap] = val;
		}
	}
}

//快排 选取一个基准数，把小于基准数的元素放到基准左边，大于的放到右边

//快排分割处理函数
int partation(int arr[], int l, int r)
{
	int val = arr[l];
	while (l < r)
	{
		

		while (l < r && arr[r] > val) { r--; }
		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}
		while (l < r && arr[l] < val) { l++; }
		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
		
	}
	arr[l] = val;
	return l;
}

void  quickSorthelper(int arr[], int begin, int end)
{

	if (begin >= end)
	{
		return;
	}

	int pos = partation(arr, begin, end);
	quickSorthelper(arr, begin, pos - 1);
	quickSorthelper(arr, pos + 1, end);
}

void quickSort(int arr[], int size)
{
	return quickSorthelper(arr, 0, size - 1);
}

//归并过程函数
void merge(int arr[], int l, int m, int r)
{
	int* p = new int[r - l + 1];
	int idx = 0;
	int i = l;
	int j = m + 1;
	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			p[idx++] = arr[i++];
		}
		else
		{
			p[idx++] = arr[j++];
		}
	}

	while (i <= m)
	{
		p[idx++] = arr[i++];
	}
	while (j <= r)
	{
		p[idx++] = arr[j++];
	}

	for (i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}

	delete[] p;
}


void mergeSortHelper(int arr[], int begin, int end)
{
	if (begin >= end)
		return;
	int mid = (begin + end) / 2;

	//先递
	mergeSortHelper(arr, begin, mid);
	mergeSortHelper(arr, mid + 1, end);
	//再归并
	merge(arr, begin, mid, end);

}
void mergeSort(int arr[], int size)
{
	mergeSortHelper(arr, 0, size - 1);
}

#if 0
//堆排序， 数组存储， 完全二叉树（最后一层的叶子节点全都是靠左排列）
//当前节点 i  --》左孩子 2 * i + 1   右  2 * i + 2
#include <functional>
//优先级队列的实现
class PriorityQueue
{
public:
	using Comp = function<bool(int, int)>;
	PriorityQueue(int cap = 20, Comp cmp = greater<int>())
		:size_(0)
		, cap_(cap)
		, comp_(cmp)
	{
		que_ = new int[cap_];
	}

	PriorityQueue(Comp cmp)
		:size_(0)
		, cap_(20)
		, comp_(cmp)
	{
		que_ = new int[cap_];
	}

	~PriorityQueue()
	{
		delete[] que_;
		que_ = nullptr;
	}
public:
	//入堆操作
	void push(int val)
	{
		//扩容
		if (size_ == cap_)
		{
			int* p = new int[2 * cap_];
			memcpy(p, que_, cap_);
			delete[] que_;
			que_ = p;
			cap_ *= 2;

		}
		if (size_ == 0)   
			que_[size_] = val;   //只有一个元素
		else
		{
			shiftUp(size_, val);
		}
		size_++;
	}

	void pop()
	{
		if (size_ == 0)
			throw "container is empty!";
		size_--;
		if (size_ > 0)
		{
			shiftDown(0, que_[size_]);
		}
	}

	bool  empty() const { return size_ == 0; }
	int top() const
	{
		if (size_ == 0)
			throw "container is empty!";
		return que_[0];
	}

	int size()const{ return size_; }
private:
	int* que_;
	int size_;
	int cap_;
	Comp comp_;

	void shiftUp(int i, int val)
	{
		while (i > 0)
		{
			int father = (i - 1) / 2;
			if (comp_(val, que_[father]))
			{
				que_[i] = que_[father];
				i = father;
			}
			else
			{
				break;
			}
		}
		que_[i] = val;
	}

	void shiftDown(int i, int val)
	{
		while (i < size_/ 2 )
		{
			int child = 2 * i + 1;

			if (child + 1 < size_ && comp_(que_[child + 1], que_[child]))  //右孩子 > 左孩子
			{
				child = child + 1;  // child记录右孩子的下标
			}

			if (comp_(que_[child], val))
			{
				que_[i] = que_[child];
				i = child;
			}
			else
			{
				break;    //已经满足堆的性质
			}
		}

		que_[i] = val;
	}
};

int main()
{
	PriorityQueue que([](int a, int b) {return a < b; });
	srand(time(0));

	for (int i = 0; i < 10; ++i)
	{
		que.push(rand() % 100);
	}

	while (!que.empty())
	{
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;
}

#endif 

//堆排序
//从第一个非叶子节点开始，把二叉堆调整成一个大根堆 (n-1)/2


//堆的下沉调整
void shiftDown(int arr[], int i, int size)
{
	int val = arr[i];
	while(i < size / 2)
	{
		
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}

		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child;
		}
		else
		{
			break;
		}

	}
	arr[i] = val;
}


void heapSort(int arr[], int size)
{
	int n = size - 1;   
	//从第一个非叶子节点开始
	for (int i = (n - 1) / 2; i >= 0 ; --i)
	{
		shiftDown(arr, i, size);
	}

	//把堆顶元素与末尾元素进行交换
	for (int i = n; i > 0; --i)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		shiftDown(arr, 0, i);
	}
}


//基数排序
#include <string>
#include <vector>
void radixSort(int arr[], int size)
{
	int maxdata = arr[0];
	for (int i = 0; i < size; ++i)
	{
		if (maxdata < arr[i])
		{
			maxdata = arr[i];
		}
	}

	int len = to_string(maxdata).size();
	vector<vector<int>> vecs;
	int mod = 10;
	int dev = 1;
	for (int i = 0; i < len; ++i, mod *= 10, dev *= 10)
	{
		vecs.resize(10);
		for (int j = 0; j < size; ++j)
		{
			int index = arr[j] % mod / dev;
			vecs[index].push_back(arr[j]);
		}
		int idx = 0;
		for (auto vec : vecs)
		{
			for (auto v : vec)
			{
				
				arr[idx++] = v;
			}
		}

		vecs.clear();
	}
}