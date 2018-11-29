/*
	hw8: expression Tree
	Daniel Pinto
	Help from: https://github.com/sponsar -- most all of the program
	Was having a lot of trouble so found this to figure out how it works
*/
#include<iostream>
#include<fstream>
#include<string>
#include <stack>
#include <sstream>
#include<regex>
#include <cmath>
using namespace std;

#define OP 0
#define NUM 1
#define VAR 2

class Tree{//create tree by initializing each with 3 vals for node. 3 different constructors based on what is passed (variable, number, operator) and kind will be set when constructed based on predefined above.
	class Node
	{
	public:
		int kind;
		int key;
		char op;
		string var;
		Node* left=nullptr;
		Node* right=nullptr;
		Node(int key)//num
		{
			kind = NUM;
			this->key = key;
		}
		Node(string var)//var
		{
			kind = VAR;
			this->var = var;
		}
		Node(char op)//op
		{
			kind = OP;
			this->op = op;
		}
	};
	Node* root;
public:
	Tree()
	{
		root = nullptr;
	}
	~Tree()
	{
		freeNode(root);
	}

	void freeNode(Node* leaf)//deletes nodes from a starting node and chasing down left and then right
	{
		if (leaf)//if leaf is not nullptr then we begin to delete and call recursively
		{
			freeNode(leaf->left);
			freeNode(leaf->right);
			delete leaf;
		}
	}

	Node* getRoot()
	{
		return root;
	}
	void getAnswer()
	{
		optimize(root);
		if (root->kind == NUM)
			cout << "The answer is " << root->key << endl;
		else
			cout << "The answer is " << root->var << endl;
	}
	void optimize(Node* node)//root
	{
		if (node->kind == OP)
		{
			Node* left = node->left;
			Node* right = node->right;


			if (left->kind == OP || right->kind == OP)//if one of children is op
			{
				optimize(left);
				optimize(right);
				optimize(node);
			}

			else if (left->kind == NUM && right->kind == NUM)//if both children are num
			{
				node->kind = NUM;//turn op into num
				switch (node->op)
				{
				case '+':
					node->key = left->key + right->key;
					break;
				case '-': node->key = left->key - right->key;
					break;
				case '*': node->key = left->key * right->key;
					break;
				case '/': node->key = left->key / right->key;
					break;
				case '^': node->key = (int)pow(left->key, right->key);
					break;
				case '%': node->key = left->key % right->key;
					break;
				}
			}

			else if ((left->kind == NUM && right->kind == VAR) || (left->kind == VAR && right->kind == NUM))//if one is num another is var
			{
				if (left->kind == VAR && right->key == 1 && node->op == '*')//x*1=x
				{
					node->kind = VAR;
					node->var = left->var;
				}
				else if (left->key == 1 && right->kind == VAR && node->op == '*')//1*x=x
				{
					node->kind = VAR;
					node->var = right->var;
				}
				else if (left->kind == VAR && right->key == 0 && node->op == '*')//x*0=0
				{
					node->kind = NUM;
					node->key = 0;
				}
				else if (left->key == 0 && right->kind == VAR && node->op == '*')//0*x=0
				{
					node->kind = NUM;
					node->key = 0;
				}
				else if (left->kind == VAR && right->key == 0 && node->op == '+')//x+0=x
				{
					node->kind = VAR;
					node->var = left->var;
				}
				else if (left->key == 0 && right->kind == VAR && node->op == '+')//0+x=x
				{
					node->kind = VAR;
					node->var = right->var;
				}
				else//cheat x+2=x
				{
					node->kind = VAR;
					if (left->kind == VAR)
						node->var = left->var;
					else
						node->var = right->var;
				}
			}

			else if (left->kind == VAR && right->kind == VAR)
			{
				if (left->var == right->var && node->op == '-')
				{
					node->kind = NUM;
					node->key = 0;
				}
				else if (left->var == right->var && node->op == '/')
				{
					node->kind = NUM;
					node->key = 1;
				}
				else
				{
					node->kind = VAR;
					node->var = left->var + node->op + right->var;
				}
			}
		}
	}

	void RPN_stack(string str)//passed one RPN line from the file
	{
		freeNode(root);
		istringstream iss(str);
		string something;
		regex op("[+,\\-,*,/,^,%]");//use regex to find whether operator, number, or variable
		regex num("[0-9]+");
		regex var("[A-Za-z]+");
		stack<Node*> stack;
		while (iss >> something)//check each character of line and add to tree based on type
		{
			if (regex_match(something, num))
			{
				string::size_type sz;
				int value = stol(something, &sz);
				Node* node = new Node(value);
				stack.push(node);
			}
			else if (regex_match(something, var))
			{
				Node* node = new Node(something);
				stack.push(node);
			}
			else if (regex_match(something, op))
			{
				char ch = something[0];
				Node* node = new Node(ch);
				node->right = stack.top();
				stack.pop();
				node->left = stack.top();
				stack.pop();
				stack.push(node);
				root = node;
			}
		}
		stack.pop();
	}


	void inOrder(Node* n)
	{
		if (n)
		{
			inOrder(n->left);
			if (n->kind == NUM)
				cout << n->key << " ";
			else if (n->kind == OP)
				cout << n->op << " ";
			else if (n->kind == VAR)
				cout << n->var << " ";
			inOrder(n->right);
		}
	}
	void preOrder(Node* n)
	{
		if (n)
		{
			if (n->kind == NUM)
				cout << n->key << " ";
			else if (n->kind == OP)
				cout << n->op << " ";
			else if (n->kind == VAR)
				cout << n->var << " ";
			preOrder(n->left);
			preOrder(n->right);
		}
	}
	void postOrder(Node* n)
	{
		if (n)
		{
			postOrder(n->left);
			postOrder(n->right);
			if (n->kind == NUM)
				cout << n->key << " ";
			else if (n->kind == OP)
				cout << n->op << " ";
			else if (n->kind == VAR)
				cout << n->var << " ";
		}
	}

};

int main()
{
	ifstream f("hw8inp.dat");
	if (!f)//if no file is found
	{
		cerr << "No hw8inp.dat file " << endl;
		exit(1);
	}
	string RPN;
	Tree tree;
	while (getline(f, RPN))
	{
		cout << "The RPN line is " << RPN << endl;
		tree.RPN_stack(RPN);
		cout << "RPN InOrder : ";
		tree.inOrder(tree.getRoot());
		cout << endl;
		cout << "RPN PreOrder : ";
		tree.preOrder(tree.getRoot());
		cout << endl;
		cout << "RPN PostOrder : ";
		tree.postOrder(tree.getRoot());
		cout << endl;
		tree.getAnswer();
		cout << endl;
	}

}
