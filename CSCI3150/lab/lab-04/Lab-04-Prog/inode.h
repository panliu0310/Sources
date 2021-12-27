#ifndef _INODE_H_
#define _INODE_H_
#include <time.h>

#define FILE 0
#define DIR 1

typedef struct _inode_ 
{
	int i_number;
	time_t c_time;
	int f_type;
	int f_size;
	int blk_num;
	int direct_blk[2];
	int indirect_blk;
	int f_num;
}inode;

typedef struct dir_mapping
{
	char dir_name[20];
	int i_number;
}DIR_NODE;

inode* read_inode(int fd, int i_number);
void print_inode_info(inode* ip);
void print_inode_region(int fd, int i_number);
void print_dir_mappings(int fd, int i_number);
#endif

