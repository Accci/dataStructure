#include "common.h"


#if 0
//数组环形队列
class Queue
{
public:
	Queue(int size = 10)
		:front_(0)
		,rear_(0)
		,size_(size)
		,cnt(0)
	{
		mQue = new int[size];
	}
	~Queue()
	{
		delete[]mQue;
		mQue = nullptr;
	}

public:
	void push(int val)
	{
		if ((rear_ + 1) % size_ == front_)
			expand(2 * size_);
		mQue[rear_] = val;
		rear_ = (rear_ + 1) % size_;
		cnt++;
	}

	void pop()
	{
		if (rear_ == front_)
			throw"Queue is empty!";
		front_ = (front_ + 1) % size_;
		cnt--;
	}
	int front()const
	{
		if (rear_ == front_)
			throw"Queue is empty!";
		return mQue[front_];
	}

	int back()const
	{
		if (rear_ == front_)
			throw"Queue is empty!";
		return mQue[(rear_ - 1 + size_)% size_];
	}

	bool empty() { return rear_ == front_; }

	int size() const 
	{ 
		return cnt; 
		//int cnt = 0;
		//for (int i = front_; i != rear_; i = (i + 1) % size_)
		//{
		//	cnt++;
		//}
	}

private:
	int* mQue;
	int front_;
	int rear_;
	int size_;
	int cnt;   //元素个数

	void expand(int size)
	{
		int* p = new int[size];
		int index = 0;
		for (int i = front_; i != rear_; i = (i + 1) % size_)
		{
			p[index++] = mQue[i];
		}
		delete[] mQue;
		mQue = p;
		front_ = 0;
		rear_ = index;
		size_ = size;
	}
};


int main()
{
	Queue que;
	int arr[] = { 12,4,56,7,89,31,53,78 };
	for (int v : arr)
	{
		que.push(v);
	}

	cout << que.back() << endl;
	cout << que.front() << endl;

	que.push(100);
	que.push(200);
	que.push(300);

	while (!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}
	cout << endl;
}
#endif

#if 0
//双向循环链表实现队列

class LinkQueue
{
public:
	LinkQueue():size_(0)
	{
		head_ = new Node();
		head_->next_ = head_;
		head_->pre_ = head_;
	}
	~LinkQueue()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			p->next_->pre_ = head_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
	}

public:
	void push(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head_->pre_;
		node->next_ = head_;
		head_->pre_->next_ = node;
		head_->pre_ = node;
		size_++;
	}

	void pop()
	{
		Node* p = head_->next_;
		head_->next_ = p->next_;
		p->next_->pre_ = head_;
		delete p;
		size_--;
	}

	int front()const
	{
		if (head_->next_ == head_)
			throw "LinkQueue is empty";
		return head_->next_->data_;
	}
	int back()const
	{
		if (head_->next_ == head_)
			throw "LinkQueue is empty";
		return head_->pre_->data_;
	}
	bool empty()const
	{
		return head_->next_ == head_;
	}

	int size() { return size_; }

private:
	struct Node
	{
		Node(int data = 0) :data_(data), pre_(nullptr), next_(nullptr) {}
		int data_;
		Node* pre_;
		Node* next_;
	};

	Node* head_;  //指向头节点
	int size_;

};

int main()
{
	LinkQueue que;
	int arr[] = { 12,4,56,7,89,31,53,78 };
	for (int v : arr)
	{
		que.push(v);
	}

	cout << que.back() << endl;
	cout << que.front() << endl;

	que.push(100);
	que.push(200);
	que.push(300);
	cout << que.size() << endl;

	while (!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}


	cout << endl;
}
#endif

