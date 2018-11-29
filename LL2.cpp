/*
  Author: Daniel Pinto
  LinkedList2: Singly linked with a pointer to head and tail
  Resources used: geeksforgeeks.org for quicksort algorithm+ help with
  reversing
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

class LinkedList2{
private:
	class Node{
	public:
		int val;
		Node* next;
		Node (int val, Node* next): val(val), next(next) {}
	};
	Node* head;
	Node* tail;
public:
	LinkedList2() : head(nullptr), tail(nullptr) {}
	~LinkedList2(){
		Node* q;
		for (Node* p = head; p!= nullptr; p = q){
			q = p->next;
			delete p;
		}
	}

	//Node* head;
	//Node* tail;

	friend ostream& operator <<(ostream& s, LinkedList2 list){
		for(Node* p = list.head; p != nullptr; p = p->next)
			s << p->val<<' ';
		return s;
	}

  void print_l(){
  for(Node* p = head; p!=nullptr; p=p->next){
    if (p->next == nullptr)
      cout << p->val;
    else
      cout << p->val << " --> ";
    }

  }

	void addStart(int val){
		if(head == nullptr){
			head = tail = new Node(val,nullptr);
			return;
		}
		Node* temp = new Node(val, head);
		head = temp;
	}
	void addEnd(int val){
		if(head == nullptr){
			head = tail = new Node(val, nullptr);
			return;
		}
		Node* temp = new Node(val, nullptr);
		tail->next = temp;
		tail = temp;
	}
	void removeEnd(){
		if(tail == nullptr)
			return;
		if(head->next == nullptr){
			delete head;
			head = tail = nullptr;
      return;
		}
    Node* p;
    Node* q = p->next;
    for (p = head; q->next != nullptr; p = q, q = q->next) //O(n)
      ;
    // q points to the last element
    // p points to 2nd to last
    delete q;
    p->next = nullptr;
    tail = p;
	}
	void removeStart(){
		if(head == nullptr)
			return;
		if(head-> next == nullptr){
			delete head;
			head = tail = nullptr;
      return;
		}
		Node* temp = head;
		head = head-> next;
		delete temp;
	}
  /* Function to reverse the linked list */
void reverse()
{
    // Initialize current, previous and
    // next pointers
    Node *current = head;
    Node *prev = NULL, *next = NULL;


    while (current != NULL)
    {
        // Store next
        next = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    head = prev;
}
  void modThree(){
    if(head == nullptr)
			return;

    //need to also check head%3
    Node* temp = head;
    head = head->next;
    delete temp;
    Node* p = head;
    Node* q = p->next;

    int indices = 2;
    for(q,p; q != nullptr; p=q, q=p->next, indices++){
      if (indices % 3 == 0){
        p->next = q->next;
        //p now points at what q pointed at
        free(q);
        //free q's memory
      }
    }
  }
};

int main(){
  int arr[1000000];
  //ARRAY OF 1000000 hopefully the user doesn't exceed this :)
  LinkedList2 a;
  ifstream f ("linkedlist.dat");
  int number;
  int count = 0;

  while(f >> number){
    //read numbers into array
    arr[count++] = number;
  }

  int arr2[count-1];
  for(int i = 0; i < count; i++)
    arr2[i] = arr[i];
  //copy all read numbers into a linked list of currect size

  quickSort(arr2, 0, sizeof(arr2)/4 );
  //quicksort new array and put into LinkedList2
  for (int i = sizeof(arr2)/4; i >= 0 ; i--)
    a.addStart(arr2[i]);
  a.print_l();
  cout << '\n';
  a.modThree();
  a.print_l();
  cout << '\n';
  a.modThree();
  a.print_l();
  cout << '\n';
  a.reverse();
  a.print_l();
  cout << '\n';


}
