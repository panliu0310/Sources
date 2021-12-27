#include "superblock.h"

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char ** args){
	if( argc != 2 ){
		printf("Usage: ./superblock-test HD\n");
		return -1;
	}

	int fd = open (args[1], O_RDWR);
	if(fd<0){       
		printf("Error: open()\n");
		return -1;
	}
	
	printf("Case 1: show the super block region on HD: \n");
	print_sb_region(fd);
	
	//read superblock into memory
	printf("\nCase 2: read superblock from hard disk into memory:\n");
	superblock* sb = read_sb(fd);
	if (sb == NULL){
		printf("Error: read_sb()\n");
		return -1;	
	}
	print_sb_info(sb);
}

