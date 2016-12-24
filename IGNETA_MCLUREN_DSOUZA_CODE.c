/*************************************************************************
*********** Defend against Clogging attack for Diffie Hellman ************
**************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

/**
* @desc Create users
* @params N(Integer)- Threshold value associated with user
         timer(time_t) Timer 
**/
struct users
{
	int N;
	time_t timer;
}user[10];

int T=8;
int interval=5;

/**
* @desc Compute reciever Public Key
* @params b(long int)- Reciever private Key
*         g(int)- Public value agreed by Reciever and Sender
*	  p(int)- Public value agreed by Reciever and Sender
* @return Public key 
**/
long int computeRecieverPublicKey(long int b,int g,int p)
{
	return (long int)pow((float)g,(float)b)%p;
}

/**
* @desc Compute reciever Private Key
* @params b(long int)- Reciever private Key
*         Xa(int)- Public Key sent by Sender
*	  p(int)- Public value agreed by Reciever and Sender
* @return Private Key
**/
long int computeRecieverPrivateKey(long int Xa,long int b,int p)
{
	return (long int)pow((float)Xa,(float)b)%p;
}

/**
* @desc Compute Key using Diffie Hellman
* @params g(int)- Public value agreed by Reciever and Sender
*	  p(int)- Public value agreed by Reciever and Sender
	  publicKey(int)- Public Key sent by Sender
**/
void diffieHellman(int g,int p,int publicKey)
{
	int b,YB,k;
	printf("DiffieHellman Key computation\n");
	b=random()%10;
	YB=computeRecieverPublicKey(b,g,p);
	printf("Sending YB %d...\n",YB);
	k=computeRecieverPrivateKey(publicKey,b,p);
	printf("Shared Key %d\n",k);
}


/**
* @desc Process Key Exchange Request
* @params userID(int)- ID of user requesting for sharing secret key
*	  g(int)- Public value agreed by Reciever and Sender
*	  p(int)- Public value agreed by Reciever and Sender
	  publicKey(int)- Public Key sent by Sender
**/
void requestKeyExchange(int userID,int g,int p,int publicKey)
{
	printf("\nRequest from user %d...\n",userID);
	if(user[userID].N==0)   //New user
	{
		user[userID].N++;
		user[userID].timer=time(NULL);
		diffieHellman(g,p,publicKey);
	}
	else
	{
		user[userID].N++;
		if(user[userID].N>T)
		{
			printf("Request OLD_KEY...\n\n");
		}
		else
		{
			if(time(NULL)-user[userID].timer<interval)
			{
				printf("Time elapsed %ld seconds... Request Denied...\n\n",time(NULL)-user[userID].timer);
			}
			else
			{
				user[userID].timer=time(NULL);
				diffieHellman(g,p,publicKey);
			}

		}
		
	}
}

/**
* Execution Starts Here
**/
void main()
{
	int i;
	//Clogging attack
	for(i=1;i<=10;i++)
	{
		requestKeyExchange(1,5,23,i+3);
		sleep(1);
	}
	

}

