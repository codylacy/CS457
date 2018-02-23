#include <iostream>
#include <string>

using namespace std;

class List
{
	struct Node
	{
		string element; 
		Node* next;
	};

	Node* head;

	public:
		List()
		{
			head = NULL;
		}

		~List()
		{
			while(head != NULL)
			{
				Node * n = head->next;
				delete head;
				head = n;
			}
		}

		void add(int value)
		{
			Node * n = new Node;
			n->element = value;
			n->next = head;
			head = n;
		}

};

class Table
{
    public:
	string name;
    string element;
	
};



class Database
{
    public:
	bool useFlag;
	string name;
	Table arrTables[50];
    int numTbls;

};

/**
class Data
{
	bool flag;//true = int, false = string
	int num;
	string str;

	string ToString()
	{

	}
}

*/


