#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


using namespace std ;
void snippet();
void echoExec();
void cat() ;
void sharedFileDescriptor() ;
void pipes();
void fs();

int main()
{
	char name[100] ;
	// std::cout<<"Hello What is your name\n" ;
	// std::cin>>name ;
	// std::cout<<"Your name is " << name <<"\n";

	// snippet();
	// echoExec();
	// cat() ;
	// sharedFileDescriptor();
	// pipes();
	fs();

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


void cat(){


	char buf[5];
	int n ;
	for(;;)
	{

		n = read(0,buf,sizeof buf);
		if(n==0){
			// cout<<"EndOfFile!";
			break ;
		}
		if(n<0){
			// cout<<"Read error!" ;
			exit(0) ;
		}

		int m = write(1,buf,n); 
		// cout<<"\n"<<m<<":"<<n<<"\n";

		if(m!=n){
			cout<<"Write error!" ;
			exit(0) ;
		}



	}

	cout<<"Break!!" ;

}


void sharedFileDescriptor()
{
	if(fork()==0)
	{
		write(1,"hello ",6);
		exit(0);
	}
	else{
		wait(0) ;
		write(1,"world\en",6);
	}
}


void pipes(){

	int p[2];
	pipe(p);
	int pid = fork();

	if (pid==0)
	{
		close(0);
		dup(p[0]);
		char* argv[2];
		argv[0] = "wc";
		argv[1] = 0 ;
		close(p[0]);
		close(p[1]); // all write ends needed to be closed before read.
		execv("/bin/wc",argv);
	}
	else{

		close(p[0]);
		write(p[1],"hellow world\en",12);
		close(p[1]);
	}

}

void fs(){

	int fd = open("a",O_CREAT | O_WRONLY);
	link("a","b");
	write(fd,"hello\en",6);
	int fd2 = open("b",O_WRONLY);
	write(fd,"helloaa\en",8);
}