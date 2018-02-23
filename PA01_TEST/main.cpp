#include <iostream>
#include <string>
#include "db.h"

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
    string function;
    int index = 0;
    int numDBs = 0;
    //int numTbls = 0;
    
    //Array of dbs to use in the program.
    Database dbs[50];
    
    //Set all database use flags to false 
    for(int i = 0; i < 50; i++)
    {
        dbs[i].useFlag = false;
    }

    //No databases exist at start
    bool dbExists = false;
    

    //Running a while loop with an internal termination
    while(true)
    {
        cin.getline(nextLine, 200, '\n');
        string fullCommand(nextLine);

        //While loop termination
        if(fullCommand.compare(".EXIT") == 0 || fullCommand.compare("\n.EXIT") == 0 || fullCommand.compare(".EXIT\n") == 0)
	    {
            cout<<"All done."<<endl;
            return 0;
	    }
        
        //Removes the ; So we just have a Command.
        fullCommand.erase(fullCommand.length() - 1, fullCommand.length() - 1);

        //Parsing of complete command into individual tokens/commands
        string params;
        command = fullCommand.substr(0,fullCommand.find(spaceDelim));
        fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());

        item = fullCommand.substr(0,fullCommand.find(spaceDelim));
        fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());

        name = fullCommand.substr(0,fullCommand.find(spaceDelim));
        fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());
        
        //Used for creating a table. Storage of the parameters of the table.
        if(fullCommand[0] == '(')
        {
            params = fullCommand.substr(1, fullCommand.find(')'));
        }

        //Alter of table command. Grabs the new parameter to add to the specified table.
        if(command.compare("ALTER") == 0 || command.compare("\nALTER") == 0)
        {
            function = fullCommand.substr(0,fullCommand.find(spaceDelim));
            fullCommand.erase(0, fullCommand.find(spaceDelim) + spaceDelim.length());

            params = fullCommand;
            
        }
        
        //Use database command
        if(command.compare("USE") == 0 || command.compare("\nUSE") == 0)
            {
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
                        cout << "Using Database "  + item + "." << endl; 
                    }

                    else
                    {
                        dbs[j].useFlag = false; 
                    }
                }

                //Cannot find db, report error.
                if(!found)
                {
                    dbs[useIndex].useFlag = true;
                    
                    cout << "Cannot use " + item + " because it does not exist." << endl; 
                }
            }

        //Select table command
        else if(command.compare("SELECT") == 0 || command.compare("\nSELECT") == 0)
        {
            int useDB = 0;
            params = fullCommand;
            while(dbs[useDB].useFlag == false)
            {
                useDB++;    
            }

            if(dbs[useDB].numTbls > 0)
            {
                for(int i = 0; i < dbs[useDB].numTbls; i++)
                {
                    if(dbs[useDB].arrTables[i].name.compare(params) == 0 )
                    {
                        cout << dbs[useDB].arrTables[i].element << endl;
                    }

                    if(i == dbs[useDB].numTbls && dbs[useDB].arrTables[i].name != params)
                    {
                        cout << "Table " + params + " does not exist in " + dbs[useDB].name + "." << endl;
                    }
                }

            }

            //Table does not exist in current database.
            else
            {
                cout << "!Failed to query table " + params + " because it does not exist." << endl;
            }

            
        }
        
        else if(item.compare("DATABASE") == 0 || item.compare("\nDATABASE") == 0)
        {
            //Database commands logic
            //Create Database Command
            if(command.compare("CREATE") == 0 || command.compare("\nCREATE") == 0)
            {
                //Check to see if the database is in the database array.
                    //If it is, return an error.

                    //If it is not, create it and add it to the dbs array at numDBd
                if(numDBs >= 0)
                {
                    //Checking to see if Database of name already exists
                    for(int i = 0; i < numDBs; i++)
                    {
                        if(dbs[i].name == name)
                        {
                            cout << "!Failed to create database " + name + " because it already exists." << endl;
                            dbExists = true;
                        }
                    }

                    //Database does not exist.
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

            //Drop Database command
            else if(command.compare("\nDROP") == 0 || command.compare("DROP") == 0)
            {
                
                
                int dbIndex = 0;
                while(dbs[dbIndex].name != name)
                {
                    dbIndex++;
                    if(dbIndex > numDBs)
                        break;
                }

                //if database to drop exists is not in the dbs array, notify user of error.
                if(dbIndex >= numDBs)
                {
                    cout << "!Failed to delete " + name + " because it does not exist." << endl;
                }

                //if it does exist, deleter it and shuffle the databases down the array.
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
        
        //Table Commands
        else if(item.compare("TABLE") == 0 || item.compare("\nTABLE") == 0)
        {
            //Table Create Command
            if(command.compare("CREATE") == 0 || command.compare("\nCREATE") == 0)
            {
                bool tblExists = false;
                //Find which database is in use, then break out.
                int useDB = 0;
                for(useDB; useDB < numDBs; useDB++)
                {
                    if(dbs[useDB].useFlag == true)
                    {
                        break;
                    }
                }
                
                if(dbs[useDB].numTbls >= 0)
                {
                    for(int i = 0; i < dbs[useDB].numTbls; i++)
                    {
                        //If table exists in database array of tables
                        if(dbs[useDB].arrTables[i].name == name)
                        {
                            cout << "!Failed to create table" + name + " because it already exists." << endl;
                            tblExists = true;
                        }
                    }
                    
                    //Table does not exist, create it in the current database.
                    if(tblExists == false)
                    {
                        Table tb;
                        dbs[useDB].arrTables[dbs[useDB].numTbls] = tb;
                        dbs[useDB].arrTables[dbs[useDB].numTbls].name = name;


                        while(params.find(',') != -1)
                        {
                            params.insert(params.find(','), " |");
                            params.erase(params.find(','), 1);
                        }

                        dbs[useDB].arrTables[dbs[useDB].numTbls].element = params;
                        cout << "Table " + name + " created."<<endl;
                        //numTbls++;
                        dbs[useDB].numTbls++;
                    }
                    
                 }

            }

            //Table delete/drop command
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
                    if(tblIndex > dbs[useDB].numTbls)
                        break;
                }

                //Checked all of the tables, not in the database!
                if(tblIndex >= dbs[useDB].numTbls)
                {
                    cout << "!Failed to delete " + name + " because it does not exist." << endl;
                }

                //Delete table becasue it was found in the database.
                else
                {
                    
                    for(tblIndex = 0;tblIndex < dbs[useDB].numTbls;tblIndex++)
                    {
                        dbs[useDB].arrTables[tblIndex] = dbs[useDB].arrTables[tblIndex+1];
                    }
                    
                    dbs[useDB].numTbls--;
                    cout << "Table " + name + " deleted." << endl;
                }
                
            }
            
            //Alter table command, change the table
            else if(command.compare("ALTER") == 0 || command.compare("\nALTER") == 0)
            {
                //if tbl in _tbls array
                //add the item into the table
                int useDB = 0;
                params = fullCommand;
                while(dbs[useDB].useFlag == false)
                {
                    useDB++;    
                }
                
                //If a table exists, check to see if it exists in the database.
                if(dbs[useDB].numTbls > 0)
                {
                    for(int i = 0; i < dbs[useDB].numTbls; i++)
                    {
                        if(dbs[useDB].arrTables[i].name.compare(name) == 0)
                        {
                            dbs[useDB].arrTables[i].element = dbs[useDB].arrTables[i].element + " | " + params;
                            cout << "Table " + dbs[useDB].arrTables[i].name + " modified." << endl;
                        }

                        else
                        {
                            cout << "Table " + params + " does not exist in " + dbs[useDB].name + "." << endl;
                        }
                    }

                }

                //Table does not exist in current db, cannot alter non existing table.
                else
                {
                    cout << "No tables in" + dbs[useDB].name + ". Cannot add to non-existing table." << endl;
                }

            }
            
            else
            {
                //cout << "Table Command " + command + " not recognized." << endl;
            }

           
           
        }
        
        //Invalid command
        else
        {
            cout << "Command Not Recognized. Please enter new command." << endl;
        }
        
        dbExists = false;

    }
    
    //End of program.
    cout << "Exiting Program" << endl;
    return 0;
}

