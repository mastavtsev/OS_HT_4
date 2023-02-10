#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char **argv) {
	int fd_read;
	int fd_write;
	size_t size = 32;
	char string[size+1];
	size_t all_size = 0;
	ssize_t RBytes;
	
	if (argc != 3) {
		printf("Wrong number of arguments. Please input: ./codename WORD1 WORD2");
		exit(1);
	}
	
	char *input = argv[1]; // word is a pointer to char
    	char *output = argv[2];
    	
    	if ((fd_read = open(input, O_RDONLY, 0666)) < 0) {
		printf("Can not open file\n");
		exit(-1);
	}
	
	do { 
		RBytes = read(fd_read, string, size);
		if (RBytes == -1) { 
			printf("Can't read this file \n");
			exit(-1);
		}
		
		all_size += RBytes;		
	} while (RBytes == size);
	
	
	if (close(fd_read) < 0) {
		printf("Can\'t close the file\n");
	}
	
	if ((fd_read = open(input, O_RDONLY, 0666)) < 0) {
		printf("Can not open file\n");
		exit(-1);
	}
	
	
	char string_write[all_size+1];
	
	read(fd_read, string_write, all_size);
	
	
	if ((fd_write = open(output, O_WRONLY | O_CREAT, 0666)) < 0) {
		printf("Can not open file\n");
		exit(-1);
	}
	
	printf("%s", string_write);	
	
	
	write(fd_write, string_write, all_size);
	
	
	if (close(fd_write) < 0) {
		printf("Can not close file\n");
		exit(1);
	}
	
	
	return 0;
}
