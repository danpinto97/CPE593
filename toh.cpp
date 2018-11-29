#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
using namespace std;

const int MAP_SIZE = 5000;

class MyHashmap {
private:
    struct Node {
        string key;
        Node* next;
        Node(string s, Node* node) : key(s), next(node){}
    };
    vector<Node *> vec;
    int count;

    static int hash (const string& key) {
        int hash = 0;
        for (auto c : key)
            hash += c;
        return (hash % MAP_SIZE);
    }

public:
    MyHashmap() : count(0) { vec.resize(MAP_SIZE, nullptr); }
    void add(const string& s) {
        Node * new_node = new Node(s, vec[hash(s)]); //make a new node with string value s and next value whatever is at hash(s) -- it could be nullptr or series of nodes
        vec[hash(s)] = new_node;//then set that node at the key
        ++count;
    }
    bool contains(const string& s) const {
        if(vec[hash(s)] == nullptr) return false;
        Node* p = vec[hash(s)];
        while (p != nullptr){
            if (p->key == s)
              return true;
            p = p->next;
        }
        return false;
    }
    int getCount(){ return count; }
    void histogram (){
        for (int i = 0; i <MAP_SIZE; ++i) {
            Node* p = vec[i];
            int display_count = 0;
            while ( p != nullptr ) {
                ++display_count;
                p = p->next;
            }
            if (display_count > 0)
              cout << "Hash Key: " << i << " Number of nodes stored: " << display_count << endl;
        }
    }
  };

  void getIndices(int& first, int& second, string& word) {
      first = word.at(0) - 'a';
      second = word.at(1) - 'a';
      if (word.find('\r') != string::npos)
        word = word.substr(2,word.length()-3);
      else
        word = word.substr(2,word.length()-1);

  }

int main(){
  MyHashmap h[26][26];
  ifstream f("dict.txt");
  ifstream spell("spell.txt");
  string s;

  while (getline(f,s)){//loading the dict
    int first, second;
    getIndices(first, second, s);
    h[first][second].add(s);
    //cout << s << '\n';

  }

  while (getline(spell,s)){
    string original_word = s;
    int first, second;
    getIndices(first, second, s);
    if(h[first][second].contains(s))
      cout << original_word << " is a word in dict.txt\n\n";
    else
      cout << original_word << " is NOT a word in dict.txt\n\n";
  }

  cout << "All HashMap inserts/collisions for \'aa\' \n";
  h[0][0].histogram();
  //change to h[0][1] to see ab
}
