/*
CS 457: Database Management Systems
Project 01
Cody Lacy
John Widmeyer
*/

#include <iostream>
#include <string>

using namespace std;
/*
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
*/

/*
Table class:

        Data members: 
                    string name -> Stores the name of the current table
                    string element -> Stores the Column values. To be changed to columns later on.

        Uses: 
                    Data member of the Database class.
*/

class Table
{
    public:
	string name;
    string element;
	
};


/*
Database Class: 

        Data members:
                bool useFlag -> Used for designating which database is being used.
                string name -> Used for designating the name of the database for access in an array of databases.
                Table arrTables -> Array of tables since a database can have zero or more tables. 
                int numTbles -> Number of tables in current database.  

        Uses: 
              Created and stored databases in the main program.      
*/

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


