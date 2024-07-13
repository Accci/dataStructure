#include "common.h"
#if 0
struct Node 
{
	Node(int data = 0)
		:data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{}
	int data_;
	Node* pre_;
	Node* next_;
};

class DCycleLink
{
public:
	DCycleLink()
	{
		head_ = new Node();
		head_->pre_ = head_;
		head_->next_ = head_;
	}
	~DCycleLink()
	{
		Node* p = head_->next_;
	

		while (p != head_)  //始终删除第一个节点
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
	void insertHead(int val)
	{
		Node* node = new Node(val);

		node->pre_ = head_;
		node->next_ = head_->next_;
		head_->next_->pre_ = node;
		head_->next_ = node;
	}

	void insertTail(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head_->pre_;
		node->next_ = head_;
		head_->pre_->next_ = node;
		head_->pre_ = node;
	}

	void remove(int val)
	{
		Node* p = head_->next_;
		while(p != head_)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				p->next_->pre_ = p->pre_;
				delete p;
				return;
			}
			else
			{
				p = p->next_;
			}
		}
	}
	bool find(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
				return true;
			else
				p = p->next_;
		}
	}

	void show()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}

private:
	Node* head_;
};

int main()
{
	DCycleLink dlink;

	dlink.insertTail(10);
	dlink.insertTail(20);
	dlink.insertTail(40);
	dlink.insertTail(50);
	dlink.insertTail(60);
	dlink.insertTail(70);
	dlink.show();
	dlink.insertHead(11);
	dlink.insertHead(21);
	dlink.insertHead(31);
	dlink.insertHead(41);
	dlink.insertHead(51);
	dlink.insertHead(61);
	dlink.show();

	dlink.remove(51);
	dlink.show();

	dlink.remove(61);
	dlink.show();
	dlink.remove(70);
	dlink.show();
	return 0;
}

#endif