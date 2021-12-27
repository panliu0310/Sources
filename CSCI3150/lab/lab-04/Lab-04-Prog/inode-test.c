#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

#include "superblock.h"
#include "inode.h"

int main(int argc, char ** args){
	if( argc != 2 ){
		printf("Usage: ./inode-test file_name\n");
		return -1;
	}
	int fd = open (args[1], O_RDWR);
	if(fd<0){       
		printf("Error: open()\n");
		return -1;
	}

	// read the root dir inode into memory
	inode* ip = read_inode(fd, 0);
	if(ip == NULL){
		printf("Error: read_inode()\n");
		return -1;
	}
	printf("Case 1: show the root dir inode info:\n");
	print_inode_info(ip);
	printf("\nshow the inode region on hard disk:\n");
	print_inode_region(fd, 0);

	//test dir-mapping
	printf("\nCase 2: show the dir mappings under root dir\n");
	print_dir_mappings(fd, 0);
}

