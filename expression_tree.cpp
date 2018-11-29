/*
	hw8: expression Tree
	Daniel Pinto
	Help from: https://github.com/sponsar , https://rosettacode.org/wiki/Parsing/RPN_calculator_algorithm#C.2B.2B
  -- most of the program logic
	Was having a lot of trouble so found this to figure out how it works.
  Basically used same idea/logic just slightly different. couldn't think of a better way to do it.

*/
#include<iostream>
#include<fstream>
#include<string>
#include <stack>
#include <sstream>
#include<regex>
#include <cmath>
using namespace std;

class Tree{
  class Node{
  public:
    string kind;
    int number;
    char _operator;
    string variable;
    Node* left = nullptr;
    Node* right = nullptr;
    //make three different constructors based on what kind of character is passed to it.
    Node(int num): kind("number"), number(num){}
    Node(string variable): kind("variable"), variable(variable){}
    Node(char _operator): kind("operator"), _operator(_operator){}
  };
  Node* root;
public:
  Tree() : root(nullptr){}
  ~Tree(){
  deleteLeaf(root);
  }
  Node* getRoot()
	{
		return root;
	}

  void deleteLeaf(Node* leaf){//deletes tree starting at specified node going down. used in destructor to delete the whole tree by starting with root.
    if( leaf!=nullptr){
      deleteLeaf(leaf->left);
      deleteLeaf(leaf->right);
      delete leaf;
    }
  }

  void getAns()
  {
    opt(root);
    //need two different options for printing variable or number based answer

    if (root->kind == "number")
      cout << "Optimized answer: " << root->number << '\n';
    else
      cout << "Optimized answer: " << root->variable << '\n';
  }

  void opt(Node* node)//optimizes tree
	{
		if (node->kind == "operator")
		{
			Node* left = node->left;
			Node* right = node->right;


			if (left->kind == "operator" || right->kind == "operator")//if a child is operator, we need to first get the answer to that. This we we finish bottom of the tree first by searching for all operators.
			{
				opt(left);
				opt(right);
				opt(node);
			}
      //basic optimization by comparing kind and values
			else if (left->kind == "number" && right->kind == "number")
			{
				node->kind = "number";
				switch (node->_operator)
				{
				case '+':
					node->number = left->number + right->number;
					break;
				case '-': node->number = left->number - right->number;
					break;
				case '*': node->number = left->number * right->number;
					break;
				case '/': node->number = left->number / right->number;
					break;
				case '^': node->number = (int)pow(left->number, right->number);
					break;
				case '%': node->number = left->number % right->number;
					break;
				}
			}

			else if ((left->kind == "number" && right->kind == "variable") || (left->kind == "variable" && right->kind == "number"))
			{
				if (left->kind == "variable" && right->number == 1 && node->_operator == '*')//x*1=x
				{
					node->kind = "variable";
					node->variable = left->variable;
				}
				else if (left->number == 1 && right->kind == "variable" && node->_operator == '*')//1*x=x
				{
					node->kind = "variable";
					node->variable = right->variable;
				}
				else if (left->kind == "variable" && right->number == 0 && node->_operator == '*')//x*0=0
				{
					node->kind = "number";
					node->number = 0;
				}
				else if (left->number == 0 && right->kind == "variable" && node->_operator == '*')//0*x=0
				{
					node->kind = "number";
					node->number = 0;
				}
				else if (left->kind == "variable" && right->number == 0 && node->_operator == '+')//x+0=x
				{
					node->kind = "variable";
					node->variable = left->variable;
				}
				else if (left->number == 0 && right->kind == "variable" && node->_operator == '+')//0+x=x
				{
					node->kind = "variable";
					node->variable = right->variable;
				}
				else//cheat x+2=x
				{
					node->kind = "variable";
					if (left->kind == "variable")
						node->variable = left->variable;
					else
						node->variable = right->variable;
				}
			}

			else if (left->kind == "variable" && right->kind == "variable")
			{
				if (left->variable == right->variable && node->_operator == '-')
				{
					node->kind = "number";
					node->number = 0;
				}
				else if (left->variable == right->variable && node->_operator == '/')
				{
					node->kind = "number";
					node->number = 1;
				}
				else
				{
					node->kind = "variable";
					node->variable = left->variable + node->_operator + right->variable;
				}
			}
		}
	}

  void RPN_tree(string str)//passed one RPN line from the file
	{
    //basically puts the RPN into a tree based on what they are after matching using regular expression
		deleteLeaf(root);
		istringstream iss(str);
		string current_character;
		regex _operator("[+,\\-,*,/,^,%]");//use regex to find whether operator, number, or variable
		regex num("[0-9]+");
		regex variable("[A-Za-z]+");
		stack<Node*> stack;
		while (iss >> current_character)//check each character of line and add to tree based on type
		{
			if (regex_match(current_character, num))
			{
				string::size_type sz;
				int value = stoi(current_character, &sz); //if it's a number we need to convert to an int format
				Node* node = new Node(value);
				stack.push(node);
			}
			else if (regex_match(current_character, variable))
			{//current_character is already a string so just add it to the stack as is
				Node* node = new Node(current_character);
				stack.push(node);
			}
			else if (regex_match(current_character, _operator))
			{
        //if we have reached an operator must convert to char  and then add its children from the stack
				char ch = current_character[0];
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


  //for orders we need to check what kind is each time to determine which to print (number, _operator, or variable)
  void inOrder(Node* n)
  {
    if (n)
    {
      inOrder(n->left);
      if (n->kind == "number")
        cout << n->number << " ";
      else if (n->kind == "operator")
        cout << n->_operator << " ";
      else if (n->kind == "variable")
        cout << n->variable << " ";
      inOrder(n->right);
    }
  }
  void preOrder(Node* n)
  {
    if (n)
    {
      if (n->kind == "number")
        cout << n->number << " ";
      else if (n->kind == "operator")
        cout << n->_operator << " ";
      else if (n->kind == "variable")
        cout << n->variable << " ";
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
      if (n->kind == "number")
        cout << n->number << " ";
      else if (n->kind == "operator")
        cout << n->_operator << " ";
      else if (n->kind == "variable")
        cout << n->variable << " ";
    }
}

};


int main()
{
    ifstream f("hw8inp.dat");
  	string RPN;
  	Tree t;
  	while (getline(f, RPN)){
      cout << "Original RPN line: " << RPN << '\n';
      t.RPN_tree(RPN);
      cout << "Inorder: ";
      t.inOrder(t.getRoot());
      cout << '\n';
      cout << "Preorder: ";
      t.preOrder(t.getRoot());
      cout << '\n';
      cout << "Postorder: ";
      t.postOrder(t.getRoot());
      cout << '\n';
      t.getAns();
      cout << '\n';
      cout << '\n';

    }
}
