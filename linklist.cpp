#include "common.h"
#if 0
struct Node
{
	Node(int data = 0) :data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};
class linkList
{
public:
	linkList()
	{
		head_ = new Node();
	}
	~linkList()
	{
		Node* p = head_;
		while (p)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		head_ = nullptr;
	}

	bool find(int val)
	{
		Node* p = head_->next_;
		while (p)
		{
			if (p->data_ == val)
				return true;
			else
				p = p->next_;
		}
		return false;
	}

public:
	//链表尾插法
	void insertTail(int val)
	{
		//先找到当前链表的末尾节点
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		Node* node = new Node(val);
		p->next_ = node;
	}

	void insertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
	}
	void show()
	{
		Node* node = head_->next_;
		while (node)
		{
			cout << node->data_ << " ";
			node = node->next_;
		}
		cout << endl;
	}
	//void remove(int val)
	//{
	//	Node* pre = head_;
	//	Node* p = head_->next_;
	//	while (p && p->data_ != val)
	//	{
	//		pre = p;
	//		p = p->next_;
	//	}
	//	if (p)
	//	{
	//		pre->next_ = p->next_;
	//		delete p;
	//	}
	//}

	void remove(int val)
	{
		Node* pre = head_;
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				pre->next_ = p->next_;
				delete p;
				return;
			}
			else
			{
				pre = p;
				p = p->next_;
			}
		}
	}

	void removeAll(int val)
	{
		Node* pre = head_;
		Node* p = head_->next_;
		while (p)
		{
			if (p->data_ == val)
			{
				pre->next_ = p->next_;
				delete p;
				p = pre->next_;
			}
			else
			{
				pre = p;
				p = p->next_;
			}
		}
	}

	
private:
	Node* head_;
	friend void reverse(linkList& list);
	friend void merge(linkList& list1, linkList& list2);
};

void reverse(linkList& list)
{
	Node* p = list.head_->next_;
	Node* next = p;
	list.head_->next_ = nullptr;
	while (p)
	{
		next = p->next_;
		p->next_ = list.head_->next_;
		list.head_->next_ = p;
		p = next;
	}
}

void merge(linkList& list1, linkList& list2)
{
	Node* p = list1.head_->next_;
	Node* q = list2.head_->next_;
	Node* last = list1.head_;
	list2.head_->next_ = nullptr;

	while (p && q)
	{
		if (p->data_ < q->data_)
		{
			last->next_ = p;
			p = p->next_;
			last = last->next_;
		}
		else
		{
			last->next_ = q;
			q = q->next_;
			last = last->next_;
		}
	}
	if (q)
	{
		last->next_ = q;
	}
	else
	{
		last->next_ = p;
	}
}

int main()
{

	srand(time(0));
	linkList list;
	linkList list2;
	int arr[] = { 13, 45, 64, 77, 78 };
	for (auto v : arr)
	{
		list.insertTail(v);
	}
	int ar[] = { 15, 46, 63, 74, 76 };
	for (auto v : ar)
	{
		list2.insertTail(v);
	}
	merge(list, list2);
	list.show();
}
#endif

#if 0
int main()
{
	srand(time(0));
	linkList list;
	for (int i = 0; i < 10; ++i)
	{
		if (i & 0x1)
			list.insertHead(5);
		else
		list.insertHead(rand() % 100);
	}
	list.show();
	for (int i = 0; i < 10; ++i)
	{
		list.insertTail(rand() % 100);
	}
	list.show();
	list.insertTail(2);
	list.show();
	list.removeAll(5);

	return 0;
}
#endif