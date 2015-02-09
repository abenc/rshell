#include <dirent.h> // directory header
#include <stdio.h> // printf()
#include <stdlib.h> // exit()
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
vector<string> sort(vector<string> vect) {}
int attribut(const char* file,bool hiddenfile,bool attr)
{
struct stat s;

if(!hiddenfile && file[0]=='.')
{
	return 0;
}

stat(file,&s);

//cout<<s.st_mode<<" ";


if(attr)
{
struct passwd *pw = getpwuid(s.st_uid);
struct group *gr = getgrgid(s.st_gid);
struct tm clock;


localtime_r(&s.st_mtime,&clock);
char bufferTime[256];
strftime(bufferTime,sizeof(bufferTime)," %b %e %R",&clock);



cout<<"-";
cout<<((s.st_mode&S_IRUSR)?"r":"-");//usr can read
cout<<((s.st_mode&S_IWUSR)?"w":"-");//usr can write
cout<<((s.st_mode&S_IXUSR)?"x":"-");//usr can exec


cout<<((s.st_mode&S_IRGRP)?"r":"-");//same, instead of the usr it's the group
cout<<((s.st_mode&S_IWGRP)?"w":"-");
cout<<((s.st_mode&S_IXGRP)?"x":"-");


cout<<((s.st_mode&S_IROTH)?"r":"-");
cout<<((s.st_mode&S_IWOTH)?"w":"-");
cout<<((s.st_mode&S_IXOTH)?"x":"-")<<" ";


cout<<s.st_nlink<<" ";
cout<<pw->pw_name<<" ";
cout<<gr->gr_name<<" ";
cout<<s.st_size<<" ";
cout<<bufferTime<<" ";
cout<<file<<endl;
}
else
{
cout<<file<<"	";
}


return 0;

}
int opendir(const char* path, vector<string> flags)
{
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    struct dirent *pent = NULL;
    bool hiddenfile = false;
    bool attr=false;
    vector<string> toReturn;	
	for(int i = 0;i<flags.size();i++)
	{
		if(flags[i][0] == '-')
		{
			for(int j=0;j<flags[i].size();j++)
			{
			if(flags[i][j] == 'a')hiddenfile=true;
			if(flags[i][j] == 'l')attr=true;
			}
		}
	}
    pdir = opendir (path); 
    if (pdir == NULL) 
    {
        perror ("\nERROR! pdir could not be initialised correctly"); exit (3);
    }

    while (pent = readdir (pdir)) 
    {
        if (pent == NULL) 
        {
            perror ("ERROR! pent could not be initialised correctly");
            exit (3);
        }
  	//  	  toReturn.push_back((string)pent->d_name); 
       attribut(pent->d_name,hiddenfile,attr);
    }

    closedir (pdir);
    cout<<endl;
return 0;
}
int main (int argc,const char** argv) // entry point of the program
{	/*
*/
vector <string> flags;
for(int i=0;i<argc;i++)
{
flags.push_back(argv[i]);
}
opendir(".",flags);


return 0;
}

