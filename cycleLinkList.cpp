#include "common.h"

//单向循环链表

#if 0
class CycleLink
{
public:
	CycleLink()
	{
		head_ = new Node;
		head_->next_ = head_;
		tail_ = head_;
	}
	~CycleLink()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		
	}

public:
	void insertTail(int val)  //O(1)
	{
		Node* node = new Node(val);
		node->next_ = tail_->next_;
		tail_->next_ = node;
		tail_ = node;
	}

	void insertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		if (node->next_ == head_)
		{
			tail_ = node;
		}
	}

	void remove(int val)
	{
		Node* q = head_;
		Node* p = head_->next_;

		while (p != head_)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				if (q->next_ == head_)
				{
					tail_ = q;
				}
				return;
			}
			else 
			{
				q = p;
				p = p->next_;
			}
		}
	}
	//查询
	bool find(int val) const
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
				return true;
		}
		return false;
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
	struct Node
	{
		Node(int data = 0) :data_(data), next_(nullptr) {}
		int data_;
		Node* next_;

	};

	Node* head_;
	Node* tail_;	
};

int main()
{
	CycleLink clink;

	srand(time(0));

	for (int i = 0; i < 10; ++i)
	{
		clink.insertTail(rand() % 100);
	}
	clink.show();
	for (int i = 0; i < 10; ++i)
	{
		clink.insertHead(rand() % 100);
	}
	clink.show();
	clink.insertHead(100);
	clink.insertTail(200);
	clink.show();
	clink.remove(100);
	clink.show();
}
#endif

#if 0
struct Node {
	Node(int data = 0) :data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

void Joseph(Node* head, int k, int m)
{
	Node* p = head;
	Node* q = head;

	while (q->next_ != head)
	{	
		q = q->next_;
	}

	for (int i = 1; i < k; ++i)
	{
		q = p;
		p = p->next_;
	}
	while (1)
	{
		for (int i = 1; i < m; ++i)
		{
			q = p;
			p = p->next_;
		}
		cout << p->data_ << " ";
		if (q == p)
		{
			delete p;
			break;
		}
		q->next_ = p->next_;
		delete p;
		p = q->next_;
		
	}

}

int main(){
	Node* head = new Node(1);
	Node* n1 = new Node(2);
	Node* n2 = new Node(3);
	Node* n3 = new Node(4);
	Node* n4 = new Node(5);
	Node* n5 = new Node(6);
	Node* n6 = new Node(7);
	Node* n7 = new Node(8);
	head->next_ = n1;
	n1->next_ = n2;
	n2->next_ = n3;
	n3->next_ = n4;
	n4->next_ = n5;
	n5->next_ = n6;
	n6->next_ = n7;
	n7->next_ = head;
	
	Joseph(head, 1, 1);
	return 0;
}
#endif