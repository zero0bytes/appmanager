
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h> 
#include <sys/types.h> 

using namespace std;

#include "Timer.h"

Timer timer;
string App_name;
string App_path;
string App_param1;
string App_param2;

string exec(string cmd)
{
string data;
FILE* stream;
const int max_buffer = 256;
char buffer[max_buffer];
cmd.append(" 2>&1");
stream = popen(cmd.c_str(), "r");
 if (stream)
 {
  while (!feof(stream))
   if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
  pclose(stream);
 }
return data;
}

bool SYSTEM_is_bin_running(string name)
{
  // ps ax | grep mgn :OR: pidof mgn
  string cmd = "pidof " + name; 
  string res = exec(cmd.c_str());
  if(res.empty() == true)
  {
	return false; 
  }else
  {
	return true;
  }
return false;
}

void TM_callback()
{
 if(SYSTEM_is_bin_running(App_name) == true)
 {
	printf(App_name.c_str()); 
	printf(": ");
	printf("LIVE!"); 
	printf("\n");
 }else
 {
	printf("\n"); 
	printf("Your app is not running"); 
	printf("\n");
	printf("Try to execute.."); 
	printf("\n");
	
	int status;
    pid_t parent_pid;
    pid_t child_pid;
    
    
	   parent_pid = getpid();
 	   child_pid = fork();
	   switch( child_pid )
	   {
		  case -1:
			 printf("\n"); 
	         printf("fork-exec: fork failed"); 
			 //exit( EXIT_FAILURE );
			 break;
	 
		  case 0:
			 execlp( App_path.c_str(), App_path.c_str(), App_param1.c_str(), App_param2.c_str(), NULL );
			 perror( "fork-exec: exec failed" );
			 //exit( EXIT_FAILURE );
			 break;
	 
		  default:
			 
			 break;
	   }
    
 } 
 
}

void Setup()
{
 printf("Welcome to appmanager v 1.0\n");	
 printf("Setup...\n");
 printf("Initialize timer...\n");
 timer.every(15000,TM_callback,true);
}

int main(int argc, const char *argv[])
{
	
	Setup();
	
	if (argc > 2)
     {
	    App_name = string(argv[1]);
	    App_path = string(argv[2]);
	    App_param1 = string(argv[3]);
	    App_param2 = string(argv[4]);
	    printf("You want to monitor: ");
	    printf(argv[1]);
	    printf("\n");
	    printf("path: ");
	    printf(argv[2]);
	    printf("\n");
	    printf("param1: ");
	    printf(argv[3]);
	    printf("\n");
	    printf("param2: ");
	    printf(argv[4]);
	    printf("\n");  	  	  	 
	 }else
	 {
		printf("\n"); 	   
		printf("Usage: appmanager app-name app-path app-param1 app-param2");
		printf("\n");
		printf("Example: appmanager nginx /usr/sbin/nginx -v -something");
		printf("\n");
		exit(EXIT_SUCCESS);  	   
	 }
		
          	
	while (1)
    {		
	  timer.update();  
	  usleep(1777);
	}
return 0;
}


