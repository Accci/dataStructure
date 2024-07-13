#include "common.h"

#if 0
//顺序栈

class Stack
{
public:
	Stack(int size = 10)
		:msize(size)
		,mtop(0)
	{
		mpStack = new int[size];
	}
	~Stack()
	{
		delete[]mpStack;
		mpStack = nullptr;
	}
public:

	void push(int val)
	{
		if (mtop == msize)
			expand(2 * msize);

		mpStack[mtop++] = val;
	}

	void pop()
	{
		if (mtop == 0)
			throw "stack is empty!";
		--mtop;
	}
	int top()const  
	{ 
		if (mtop == 0)
			throw "stack is empty!";

		return mpStack[mtop - 1]; 
	}
	bool empty()const { return mtop == 0; }
	int size() const { return msize; }

private:
	int* mpStack;
	int mtop;
	int msize;

	void expand(int size)
	{
		int* tmp = new int[size];
		memcpy(tmp, mpStack, mtop);
		delete[]mpStack;
		mpStack = tmp;
		msize = size;
	}
};

int main()
{
	Stack s;
	int arr[] = { 12,4,56,7,89,31,53,78 };
	for (int v : arr)
	{
		s.push(v);
	}
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}
#endif 


#if 0
//链式栈

class linkStack
{
public:
	linkStack():size_(0)
	{
		head_ = new Node;
	}
	~linkStack()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

public:
	void push(int val)
	{
		//头插
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		size_++;
	}
	void pop()
	{
		if (head_->next_ == nullptr)
		{
			throw "stack is empty!";
		}
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		size_--;
	}

	int top()const
	{
		if(head_->next_ == nullptr)
			throw "stack is empty!";
		return head_->next_->data_;
	}

	bool empty() const
	{
		return head_->next_ == nullptr;
	}

	int size()const
	{
		return size_;
	}
private:
	struct Node
	{
		Node(int data = 0) :data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_;
	int size_;
};

int main()
{
	linkStack s;
	int arr[] = { 12,4,56,7,89,31,53,78 };
	for (int v : arr)
	{
		s.push(v);
	}
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}
#endif

#if 0
//中缀表达式转后缀表达式

#include <stack>

bool Priority(char ch, char topch)
{
	if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
		return true;
	if (ch == ')')
		return false;
	if (topch == '(')
		return true;
	return false;
}

string MiddleToEndExpr(string expr)
{
	string result;

	stack<char> s;

	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result.push_back(ch);
			continue;
		}

	
		while (1)
		{
			if (s.empty() || ch == '(')
			{
				s.push(ch);
				break;
			}
			//比较当前符号和栈顶符号top优先级
			char topch = s.top();
			if (Priority(ch, topch))
			{
				s.push(ch);
				break;
			}
			else
			{
				s.pop();
				if (topch == '(')
					break;
				result.push_back(topch);
			}
		}

	}

	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}

	return result;
}

int main()
{
	cout << MiddleToEndExpr("(1+2)*(3+4)") << endl;
	cout << MiddleToEndExpr("2+(4+6)/2+6/3") << endl;
}

#endif


