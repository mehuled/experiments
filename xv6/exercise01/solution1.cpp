// #include <stdio.h>
// #include <iostream>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <fcntl.h>

// using namespace std ;


int main()
{
	int p12[2],p21[2];
	pipe(p12);
	pipe(p21);

	int pid = fork();

	// cout<<"\n"<<p12[0]<<p12[1]<<p21[0]<<p21[1] ;


	if(pid==0)
	{
		//this is process 1
		char *msg = "alpha" ;
		
		close(p12[1]);
		int w = write(p12[0],msg,sizeof msg);
		// cout<<"\nWrote bytes by P1 : "<<w;
		char* recvmsg ;
		close(p21[0]);
		int r = read(p21[1],recvmsg,100);
		close(p21[1]);

		// cout<<"\nBytes read by P1 : "<<r;



	} else {
		wait(0);
		//this is process 2
		char * nmsg ;
		close(p12[0]);
		int r = read(p12[1],nmsg,100);
		close(p12[1]);

		// cout<<"\nBytes read by P2 is  :"<<r;

		close(p21[1]);
		int w = write(p21[0],nmsg,1);
		// cout<<"\nBytes wrote by P2 is : "<<w;
		close(p21[0]);		


	}


	return 0 ;
}