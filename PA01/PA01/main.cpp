#include <iostream>
#include <string>
#include "db.h"
#include <map>


using namespace std;

int main()
{
    
    cout << "Please enter a command." << endl;
    char nextLine[200];
    string spaceDelim = " ";
    
    string params;
    string command;
    string item;
    string name;
    int index = 0;
    int numDBs = 0;
    int numTbls = 0;
    
    Database dbs[50];
    for(int i = 0; i < 50; i++)
    {
        dbs[i].useFlag = false;
    }
    bool dbExists = false;
    

    //While true == true
    while(true)
    {
        cin.getline(nextLine, 200, ';');
        string fullCommand(nextLine);

        if(fullCommand.find("EXIT") == 0)
            return 0;
        
        string params;
        command = fullCommand.substr(0,fullCommand.find(spaceDelim));
        fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());

        item = fullCommand.substr(0,fullCommand.find(spaceDelim));
        fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());

        name = fullCommand.substr(0,fullCommand.find(spaceDelim));
        fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());
        if(fullCommand[0] == '(')
        {
            params = fullCommand.substr(1, fullCommand.find(')') - 1);
        }


        if(command.compare("USE") == 0 || command.compare("\nUSE") == 0)
            {
                //if name in map
                //cout << "Using " + name + "." << endl;
                int useIndex = 0;
                while(dbs[useIndex].useFlag != true )
                {
                    useIndex++;
                }
                
                bool found = false;
                for(int j = 0; j < numDBs; j++)
                {
                    if(item == dbs[j].name)
                    {   
                        dbs[j].useFlag = true;
                        found = true;
                    }

                    else
                    {
                        dbs[j].useFlag = false; 
                    }
                }

                if(!found)
                {
                    dbs[useIndex].useFlag = true;
                    
                    cout << "Cannot use " + item + " because it does not exist." << endl; 
                }
            }
        
        else if(item.compare("DATABASE") == 0 || item.compare("\nDATABASE") == 0)
        {
            //Database commands logic
            if(command.compare("CREATE") == 0 || command.compare("\nCREATE") == 0)
            {
                //if db already in map
                //cout << "!Failed to create database" + name(db_1) " because it already exists." << endl;
                if(numDBs >= 0)
                {
                    for(int i = 0; i < numDBs; i++)
                    {
                        if(dbs[i].name == name)
                        {
                            cout << "!Failed to create database" + name + " because it already exists." << endl;
                            dbExists = true;
                        }
                    }

                    if(dbExists == false)
                    {
                        Database db;
                        dbs[numDBs] = db;
                        dbs[numDBs].name = name;
                        cout << "Database " + name + " created."<<endl;
                        numDBs++;
                    }
                    
                 }

            }
            
            else if(command.compare("\nDROP") == 0 || command.compare("DROP") == 0)
            {
                //if map contains name, delete it
                
                int dbIndex = 0;
                while(dbs[dbIndex].name != name)
                {
                    dbIndex++;
                }

                if(dbIndex == numDBs)
                {
                    cout << "!Failed to delete " + name + " because it does not exist." << endl;
                }

                else
                {
                    for(dbIndex;dbIndex < numDBs;dbIndex++)
                    {
                        dbs[dbIndex] = dbs[dbIndex+1];
                    }

                    numDBs--;
                    cout << "Database " + name + " deleted." << endl;
                }
               
            }
            
        }
        
        else if(item.compare("TABLE") == 0 || item.compare("\nTABLE") == 0)
        {
            //Table commands logic
            if(command.compare("CREATE") == 0 || command.compare("\nCREATE") == 0)
            {
                int useDB = 0;
                for(useDB; useDB < numDBs; useDB++)
                {
                    if(dbs[useDB].useFlag == true)
                    {
                        break;
                    }
                }
                
                if(numTbls >= 0)
                {
                    for(int i = 0; i < numTbls; i++)
                    {
                        if(dbs[useDB].arrTables[i].name == name)
                        {
                            cout << "!Failed to create table" + name + " because it already exists." << endl;
                        }
                    }

                    if(dbExists == false)
                    {
                        Table tb;
                        dbs[useDB].arrTables[numTbls] = tb;
                        dbs[useDB].arrTables[numTbls].name = name;
                        dbs[useDB].arrTables[numTbls].element = params;
                        cout << "Table " + name + " created."<<endl;
                        cout<<dbs[useDB].arrTables[numTbls].element<<endl;
                        numTbls++;
                    }
                    
                 }

            }
            
            else if(command.compare("DROP") == 0 || command.compare("\nDROP") == 0)
            {
                int useDB = 0;
                for(useDB; useDB < numDBs; useDB++)
                {
                    if(dbs[useDB].useFlag == true)
                    {
                        break;
                    }
                }
                
                int tblIndex = 0;
                while(dbs[useDB].arrTables[tblIndex].name != name)
                {
                    tblIndex++;
                }

                if(tblIndex == numTbls)
                {
                    cout << "!Failed to delete " + name + " because it does not exist." << endl;
                }

                else
                {
                    
                    for(tblIndex = 0;tblIndex < numTbls;tblIndex++)
                    {
                        dbs[useDB].arrTables[tblIndex] = dbs[useDB].arrTables[tblIndex+1];
                        cout << tblIndex << endl;
                    }

                    numTbls--;
                    cout << "Table " + name + " deleted." << endl;
                }
                
                //if tbl in map _tbls
                //delete it
                //cout << "Table " + name(tbl_1) + " deleted." << endl;
                
                //else
                //cout << "!Failed to delete " + name(tbl_1) +  " because it does not exist." << endl;
                
            }
            
            else if(command.compare("SELECT") == 0 || command.compare("\nSELECT") == 0)
            {
                //if tbl in _tbls map
                //cout << table << endl;
                
                //else
                //cout << "Could not select " + name + " because it does not exist." << endl;
            }
            
            else if(command.compare("ALTER") == 0 || command.compare("\nALTER") == 0)
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
        
        dbExists = false;

    }
    
    cout << "Exiting Program" << endl;
    return 0;
}

