#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
//function used for creating children process
int execute(char **cmd)
{
int pid = fork();

        if(pid==-1)
        {
        perror("fork fail");
        exit(1);
	}
        else if(pid == 0)
        {
                if(execvp(cmd[0],cmd)!=0)perror("fork fail");
	exit(0);
        }
	else
	{
	wait(NULL);
	}
return 0;
}

//function used to fetch the cmd line entred by the user into a vector of vector<string> 
vector<vector<string> > params(string chaine)
{
chaine.push_back(' ');
string arg;
vector<string> args;
vector<vector<string> > commandes;

 char check;
char checkbis;
bool comments = false;
	for(string::iterator it= chaine.begin(); it !=chaine.end();++it)
	{

		 check = *it;
	        if(check ==' '||check=='	'|| check==';'||it==chaine.end()|| check=='#' )
		{	
			if(check=='#')
			{
			checkbis=*(it-1);
				if(checkbis == ' ')
				{
				if(arg.size()>=2)args.push_back(arg);
				comments=true;
				}
			}
			if(arg.size()>=2)args.push_back(arg);
		arg.clear();	
		}
		else if(!comments)
		{
		
		arg.push_back(*it);
		}
		
		if( (check ==';' || it==chaine.end()-1 ) && args.size()>0)
		{
		commandes.push_back(args);
		args.clear();
		}
	}
	
return commandes;
}
//function used to get user commands 
string prompt()
{
string toReturn;
cout<<"$";
getline(cin,toReturn);
return toReturn;
}


//THIS IS THE MAIN FUNCTION 
int main(int argc, char **argv)
{

string chaine;
vector<string> args;
	while(true)
	{
	chaine = prompt();
		if(chaine =="exit")
		{
		break;
		}
		else
		{
		vector<vector<string> > commandes = params(chaine);
		vector<vector<char *> > commandeChar;
		vector<char *> commandeCharSolo;
		for(int i=0;i<commandes.size();i++)
		{
			for(int j=0;j<commandes[i].size();j++)
			{
			commandeCharSolo.push_back((char *)commandes[i][j].c_str());//pushback the command/flags casted into char* to a char* vect named commandeCharSolo
				if(j==commandes[i].size()-1)
				{
				commandeCharSolo.push_back(NULL);
				commandeChar.push_back(commandeCharSolo);
				commandeCharSolo.clear();//fill the vector commandeChar which contains vectors(commandeCharSolo) of char* and finally clean this vector for the next loop in (for i)
				}
			//			cout<<commandes[i][j]<<endl;
			}
		}
		char **cmd;
		for(int k =0;k< commandeChar.size();k++)
		{
		cmd=&commandeChar[k][0];
		execute(cmd);
		}	
	/*	args=params(chaine);
		vector<char *> vecky;
		for(int i=0;i<args.size();i++)
		{
		vecky.push_back((char *)args[i].c_str());
		}	
		vecky.push_back(NULL);
		char **cmd =&vecky[0];	
		execute(cmd);	*/
		}
	}
return 0;
}
