#include "superblock.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

#define HD "./HD"

superblock* read_sb(int fd){
	superblock* sb = malloc(sizeof(superblock));
	int currpos=lseek(fd, SB_OFFSET, SEEK_SET);
	if(currpos<0){
		printf("Error: lseek()\n");
		return NULL;
	}
	
	//read superblock from disk
	int ret = read(fd, sb, sizeof(superblock));
	if(ret != sizeof (superblock) ){
		printf("Error: read()\n");
		return NULL;
	}
	return sb;
}

void print_sb_info(superblock* sb){
	printf("the super block information:\n");
	printf("i_offset:			%d\n", sb->i_offset);
	printf("d_offset:			%d\n", sb->d_offset);
	printf("max_inode:			%d\n", sb->max_inode);
	printf("max_data_blk:			%d\n", sb->max_data_blk);
	printf("next_available_inode:		%d\n", sb->next_available_inode);
	printf("next_available_blk:		%d\n", sb->next_available_blk);
	printf("blk_size:			%d\n", sb->blk_size);
}

void print_sb_region(int fd){
	printf("the super block region on disk:\n");
	unsigned int buf[sizeof(superblock) / 4];
	int currpos=lseek(fd, SB_OFFSET, SEEK_SET);
	read(fd, buf, sizeof(superblock));
	int i;
	for (i = 0; i < sizeof(superblock) / 4; i++){
		printf("%04x\n", buf[i]);
	}
}

