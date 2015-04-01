#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#define __NR_cp 545 //the system call number

long connect_p(int fd, struct addrinfo* ai, int size)
{
	return syscall(__NR_cp, fd, ai,size);
}

int main(int argc, char *argv[])
{
	long int err;
	int sd;

//	SERHAT: Test code for getaddrinfo
	int s;
	struct addrinfo hints;
	struct addrinfo *result;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;    
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          

	s = getaddrinfo("www.google.com", "80", &hints, &result);
	if (s != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("SERHAT: result->ai_addr->sa_family: %d\n", result->ai_addr->sa_family);
	}

	sd = socket (AF_INET, SOCK_STREAM, 0);
	err = connect_p(sd, result, 0);	
	printf("System call returned %ld\n", err);
	return 0;
}
