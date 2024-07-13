// dataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件







#include "common.h"


#if 0


class Array
{
public:
	Array(int size = 10) :mCur_(0), mCap_(size)
	{
		mpArr = new int[mCap_];
	}
	~Array()
	{
		delete[]mpArr;
		mpArr = nullptr;
	}

public:
	void push_back(int val)
	{
		if (mCur_ == mCap_)
			expand(2 * mCap_);
		mpArr[mCur_++] = val;
	}
	void pop_back()
	{
		if (mCur_ == 0)
			return;
		--mCur_;
	}

	void insert(int pos, int val)
	{
		if (pos < 0 || pos > mCur_)
			return;

		if (mCur_ == mCap_)
			expand(2 * mCap_);

		for (int i = mCur_ - 1 ; i >= pos; i--)
		{
			mpArr[i + 1] = mpArr[i];
		}
		mpArr[pos] = val;
		mCur_++;
	}
	//void erase(int val)
	//{
	//	if (mCur_ == 0)
	//		return;
	//	int i = 0, j = 0;
	//	while (i < mCur_)
	//	{
	//		if (mpArr[i] != val)
	//			mpArr[j++] = mpArr[i++];
	//		else
	//			++i;
	//	}
	//	mCur_ = j;
	//}

	void erase(int pos)
	{
		if (pos < 0 || pos >= mCur_)
			return;
		if (mCur_ == 0)
			return;
		for (int i = pos + 1; i < mCur_; ++i)
		{
			mpArr[i-1] = mpArr[i];
		}
		mCur_--;
	}

	int find(int val)
	{
		for (int i = 0; i < mCur_; ++i)
		{
			if (mpArr[i] == val)
				return i;
		}

		return -1;
	}

	void show()
	{
		for (int i = 0; i < mCur_; ++i)
		{
			cout << mpArr[i] << " ";
		}
		cout << endl;
	}

private:
	void expand(int size)
	{
		int* tmp = new int[size];
		memcpy(tmp, mpArr, sizeof(int) * mCap_);
		delete[]mpArr;
		mpArr = tmp;
		mCap_ = size;
	}

private:
	int* mpArr;
	int mCap_;
	int mCur_;
};


int main()
{
	srand(time(0));
	Array array;
	for (int i = 0; i < 10; ++i)
	{
		array.push_back(rand() % 100);
	}
	array.show();

	array.pop_back();
	array.show();

	array.insert(1, 100);
	array.show();
	int ret = array.find(100);
	if (ret != -1)
	{
		array.erase(ret);
	}
	array.show();
}
#endif 

#if 0
void reverse(char arr[], int size)
{
	char *p = arr;
	char *q = arr + size - 1;

	while (p < q)
	{
		char ch = *p;
		*p = *q;
		*q = ch;
		p++;
		q--;
	}
}

int main()
{
	char arr[] = "hello world";
	reverse(arr, strlen(arr));
	cout << arr << endl;
}
#endif


#if 0
//奇偶交换
void func(int nums[], int size)
{
	int* p = nums;
	int* q = nums + size - 1;

	while (p < q)
	{
		while (p < q)
		{
			if ((*p & 0x1))
			{
				break;
			}
			++p;
		}
		while (p < q)
		{
			if (!(* q & 0x1))
			{
				break;
			}
			--q;
		}
		if (p < q)
		{
			int temp = *q;
			*q = *p;
			*p = temp;
			++p;
			--q;
		}
		
	}
}

int main()
{
	srand(time(0));
	int arr[10];
	for (int i = 0; i < 10; ++i)
	{
		arr[i] = (rand() % 100);
	}
	for (auto v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
	func(arr, 10);

	for (auto v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}

#endif

