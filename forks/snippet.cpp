#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


void snippet();
void echoExec();

int main()
{
	char name[100] ;
	std::cout<<"Hello What is your name\n" ;
	std::cin>>name ;
	std::cout<<"Your name is " << name <<"\n";

	// snippet();
	echoExec();

	return 0 ;
}

void snippet(){

	for (int i = 0 ; i <10 ; i++ ){

	int pid = fork();
	std::cout<<"PID is : "<<pid<<"\n" ;

	if (pid>0){
		std::cout<<"parent : child = " << pid<<"\n" ;
	
	// pid = wait(0);
		sleep(10);
	std::cout<<"Child " << pid << " is done."<<"\n" ;
	}
	else if (pid==0){
	std::cout<<"parent : Child exiting!!!!"<<"\n" ;
	exit(0);
	}
	else{
		std::cout<<"Fork error!"<<"\n" ;
	}

}

}


void echoExec(){
	char *argv[3];
	argv[0] = "dummy-arg" ;
	argv[1] = "/home/i0656/";
	argv[2] = 0 ;

	execv("/bin/ls",argv) ;
	std::cout<<"Exec error!!" ;
}