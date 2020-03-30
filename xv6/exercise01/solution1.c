// #include <stdio.h>
// #include <iostream>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <fcntl.h>

// using namespace std ;
#include <unistd.h>
#include <stdio.h> 


void pingpong();

int main()
{

	pingpong();
	return 0 ;

}


void pingpong()
{
	int p12[2],p21[2];
	int s1 = pipe(p12);
	int s2 = pipe(p21);
	
	// printf("%d\n", s1);
	// printf("%d\n", s2);

	int pid = fork();
	// cout<<"\n"<<p12[0]<<p12[1]<<p21[0]<<p21[1] ;
	if(pid==0)
	{
	
	for(int i = 1 ; i<=10 ; i++)
		{

		char wmsg[1] = "x" ;

		int w = write(p12[1],wmsg,1);
		// close(p12[1]);
		printf("WP1 : %d : %s \n",w,wmsg);
		char rmsg[1] ;
		int r = read(p21[0],rmsg,1);
		printf("RP1 : %d : %s \n",r,rmsg);
		if(wmsg[0]==rmsg[0])
		{
			printf("==== %d CYCLE COMPLETED! ====\n",i);
		}

	}

	} else {

			for(int i = 1 ; i<=10 ; i++)
		{

		char rmsg[1] ;
		int r = read(p12[0],rmsg,1);
		printf("RP2 : %d : %s \n",r,rmsg);
		int w = write(p21[1],rmsg,1);
		// close(p21[1]);		
		printf("WP2 : %d : %s \n",w,rmsg);
	}
		}



}