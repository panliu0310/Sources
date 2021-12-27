#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <time.h>

#include "inode.h"
#include "superblock.h"


inode* read_inode(int fd, int i_number){
	inode* ip = malloc(sizeof(inode));
	int currpos=lseek(fd, I_OFFSET + i_number * sizeof(inode), SEEK_SET);
	if(currpos<0){
		printf("Error: lseek()\n");
		return NULL;
	}
	
	//read inode from disk
	int ret = read(fd, ip, sizeof(inode));
	if(ret != sizeof (inode) ){
		printf("Error: read()\n");
		return NULL;
	}
	return ip;
}

void print_inode_info(inode* ip){
	printf("the inode information: \n");
	printf("i_number:	%d\n", ip->i_number);
	printf("c_time:	%s", ctime(& ip->c_time));
	printf("f_type:		%d\n", ip->f_type);
	printf("f_size:		%d\n", ip->f_size);
	printf("blk_num:	%d\n", ip->blk_num);
	printf("direct_blk[0]:	%d\n", ip->direct_blk[0]);
	printf("direct_blk[1]:	%d\n", ip->direct_blk[1]);
	printf("indirect_blk:	%d\n", ip->indirect_blk);
	printf("f_num:	%d\n", ip->f_num);
}

void print_inode_region(int fd, int i_number){
	printf("the inode region on disk:\n");
	unsigned int buf[sizeof(inode) / 4];
	int currpos = lseek(fd, I_OFFSET + i_number * sizeof(inode), SEEK_SET);
	read(fd, buf, sizeof(inode));
	int i;
	for (i = 0; i < sizeof(inode) / 4; i++){
		printf("%04x\n", buf[i]);
	}
}

void print_dir_mappings(int fd, int i_number)
{
	inode* ip;
	ip = read_inode(fd, i_number);
	if(ip->f_type != DIR)
	{
		printf("Wrong path!\n");
		return;
	}

	DIR_NODE* p_block = (DIR_NODE* )malloc(BLK_SIZE);
	// Consider that SFS only supports at most 100 inodes so that only direct_blk[0] will be used,
	// the implementation is much easier
	int blk_number = ip->direct_blk[0];
	int currpos=lseek(fd, D_OFFSET + blk_number * BLK_SIZE, SEEK_SET);
	read(fd, p_block, BLK_SIZE);

	int file_idx = 0;
	printf("dir \t inode_number\n");
	for(file_idx = 0; file_idx < ip->f_num; file_idx++)
	{
		printf("%s \t %d\n", p_block[file_idx].dir_name, p_block[file_idx].i_number);
	}
	free(p_block);
}
