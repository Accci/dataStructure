#include "common.h"

#if 0
struct Node
{
	Node(int data = 0) :
		data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{}
	int data_;
	Node* pre_;
	Node* next_;
};

//双向链表
class DoubleLink
{
public:
	DoubleLink()
	{
		head_ = new Node();
	}

	~DoubleLink()
	{
		Node * p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

public:
	void insertHead(int val)
	{
		Node* node = new Node(val);

		node->next_ = head_->next_;
		node->pre_ = head_;
		if(head_->next_ != nullptr)
			head_->next_->pre_ = node;
		head_->next_ = node;
	}

	void insertTail(int val)
	{
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}
		Node* node = new Node(val);
		node->pre_ = p;
		p->next_ = node;

	}

	void remove(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				if (p->next_ != nullptr)
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

	void removeAll(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				if (p->next_ != nullptr)
					p->next_->pre_ = p->pre_;
				Node* next = p->next_;
				delete p;
				p = next;
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
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				return true;
			}
			else
			{
				p = p->next_;
			}
		}
	}

	void show()
	{
		Node* p = head_->next_;

		while (p != nullptr)
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
	DoubleLink dlink;

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