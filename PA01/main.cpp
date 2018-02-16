#include <iostream>
#include <strings>
#include <db.h>
#include <map>


using namespace std;

int main()
{
    map<string, int> _dbs = new map<int, string>();
    map<string, int> _tbls = new map<int, string>();
    
    string fullCommand = "";
    cout << "Please enter a command." << endl;
    cin >> fullCommand;
    string command = "";
    string item = "";
    string name = "";
    
    //While the command EXIT is not in the full command call.
    while(fullCommand.find("EXIT") == -1 )
    {
        
        
        if(strcmp(item, "DATABASE") == 0)
        {
            //Database commands logic
            if(strcmp(command,"CREATE") == 0)
            {
                //if db already in map
                //cout << "!Failed to create database" + name(db_1) " because it already exists." << endl;
                
                //else
                //create new db
                //cout << "Database " + name(db_2) + " created." << endl;
            }
            
            else if(strcmp(command, "DROP") == 0)
            {
                //if map contains name, delete it
                //cout << "Database " + name(db_2) + "deleted." << endl;
                
                //else 
                //cout << "!Failed to delete " + name(db_2) + " because it does not exist." << endl;
            }
            
            else if(strcmp(command, "USE") == 0)
            {
                //if name in map
                //cout << "Using " + name + "." << endl;
            
                //else
                //cout << "Cannot use " + name + " because it does not exist." << endl; 
            }
            
            else
            {
                //Command for database !recognized
            }
        }
        
        else if(strcmp(item, "TABLE") == 0)
        {
            //Table commands logic
            if(strcmp(command,"CREATE") == 0)
            {
                //if tbl ! in map _tbls
                //create new table
                //cout << "Table " + name(tbl_1) + " created." << endl;
                
                //else
                //cout << "!Failed to create table " + name(tbl_1) + " because it already exists." << endl;
            }
            
            else if(strcmp(command,"DROP") == 0)
            {
                //if tbl in map _tbls
                //delete it
                //cout << "Table " + name(tbl_1) + " deleted." << endl;
                
                //else
                //cout << "!Failed to delete " + name(tbl_1) +  " because it does not exist." << endl;
                
            }
            
            else if(strcmp(command, "SELECT") == 0)
            {
                //if tbl in _tbls map
                //cout << table << endl;
                
                //else
                //cout << "Could not select " + name + " because it does not exist." << endl;
            }
            
            else if(strcmp(command, "ALTER") == 0)
            {
                //if tbl in _tbls map
                //add the item into the table
                
                //else
                //cout << "Could not alter " + name + " because it does not exist." << endl;
            }
            
            else
            {
                //cout << "Table Command " + command + " not recognized." << endl;
            }
           
        }
        
        else
        {
            cout << "Command Not Recognized. Please enter new command." << endl;
        }
        
        cin >> fullCommand;
    }
    
    cout << "Exiting Program" << endl;
    return 0;
}