#include "call.h"
const char *HD = "HD";

// this function is copied from superblock.c in lab3
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

// this function is copied from inode.c in lab4
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

int open_t(char *pathname)
{
	int inode_number;
	// write your code here.
	int fd = open("./HD", O_RDWR);
	/*
	superblock *sb = read_sb(fd);
	if(sb == NULL){
		return -1;
	}
	*/
	inode *ip = read_inode(fd, 0);
	if(ip == NULL){
		return -1;
	}

	inode_number = 0;
	char *dir_name = strtok(pathname, "/"); // split pathname separated by "/"
	while(dir_name != NULL){ // if dir_name is not the deepest one, continue spliting
		// take reference in lab4 print_dir_mapping
		inode *next_ip;
		next_ip = read_inode(fd, inode_number);		
		if(next_ip->f_type != DIR)
		{
			printf("Wrong path!\n");
			return -1;
		}
		DIR_NODE* p_block = (DIR_NODE* )malloc(BLK_SIZE);
		int blk_number = next_ip->direct_blk[0];
		int currpos = lseek(fd, D_OFFSET + blk_number * BLK_SIZE, SEEK_SET);
		read(fd, p_block, BLK_SIZE);
		for (int file_idx = 0; file_idx < ip->f_num; file_idx++){
			if (strcmp(p_block[file_idx].dir_name, dir_name) == 0){
				inode_number = p_block[file_idx].i_number;
				break;
			}
		}
		free(p_block);

		dir_name = strtok(NULL,"/"); // split pathname separated by "/"
	}
	close(fd);
	return inode_number;
}


int read_t(int i_number, int offest, void *buf, int count)
{
	int read_bytes;
	// write your code here.
	int fd = open("./HD", O_RDWR);
	inode *ip = read_inode(fd, i_number);
	if(ip == NULL){
		return -1;
	}
	if(ip->f_type != FILE)
	{
		printf("No a file.\n");
		return -1;
	}

	read_bytes = count;

	int a = offest/BLK_SIZE; // start block
	int b = offest%BLK_SIZE;

	int a2 = (offest + count - 1)/BLK_SIZE; // end block
	int b2 = (offest + count - 1)%BLK_SIZE;

	printf("a:%d b:%d\n", a, b);
	printf("a2:%d b2:%d\n", a2, b2);

	// handle error
	if (offest > ip->f_size){ // handle case 8
		//printf("Offset out of range\n");
		return 0;
	}
	if (count > ip->f_size){ // handle case 9 (error)
		//printf("Access the maximum number of blocks\n");
		read_bytes = ip->f_size - offest;
		// then go to case 5
	}

	int cell[BLK_SIZE/4];
	for (int i = 0; i < BLK_SIZE/4 ; i++){
		// store the integer pointers of indirect block into cell[]
		lseek(fd, D_OFFSET + ip->indirect_blk * BLK_SIZE + i * sizeof(int), SEEK_SET); // move the cursor
		read(fd, &cell[i], sizeof(int));
		// Now, cell[0] to cell[1023] stores the integer pointers of indirect block
		//printf("cell[%d]: %d, D_OFFSET + ip->indirect_blk * BLK_SIZE + i * sizeof(int): %d\n\n", i, cell[i], D_OFFSET + ip->indirect_blk * BLK_SIZE + i * sizeof(int));
	}

	if (offest + count > ip->f_size && count <= ip->f_size){ // handle case 7
		//printf("Overflowing original file test\n");
		// in our case, ip->f_size = 1239081, 1239081/4 = 302.51...
		// so there are 301 indirect blocks
		read_bytes = ip->f_size - offest;
		// then go to case 6
	}

	if (a < 2 && a2 == a){
		// handle the case that begin at direct, end in same
		// handle case 0, case 1
		//printf("%d %d\n", ip->direct_blk[0], ip->direct_blk[1]); // output 13, 14
		lseek(fd, D_OFFSET + ip->direct_blk[a] * BLK_SIZE + b, SEEK_SET); // move the cursor
		read(fd, (char*)buf, read_bytes);
		close(fd);
		return read_bytes;
	}

	if (a >= 2 && a2 == a){
		// handle the case that begin at indirect, end in same
		// handle case 2, case 3
		lseek(fd, D_OFFSET + cell[a-2] * BLK_SIZE + b, SEEK_SET);
		read(fd, (char*)buf, read_bytes);
		close(fd);
		return read_bytes;
	}

	if (a == 0 && a2 == 1){
		// handle the case that begins at direct, end in another direct
		// i.e. begins at ip->direct_blk[0], end in ip->direct_blk[1]
		// handle case 4
		lseek(fd, D_OFFSET + ip->direct_blk[a] * BLK_SIZE + b, SEEK_SET);
		read(fd, (char*)buf, read_bytes);
		close(fd);
		return read_bytes;
	}

	if ((a == 0 || a == 1) && a2 >= 2){
		// handle the case that begins at direct, end in indirect
		// handle case 5
		lseek(fd, D_OFFSET + ip->direct_blk[a] * BLK_SIZE + b, SEEK_SET);
		read(fd, (char*)buf, BLK_SIZE * 2 - b);
		for(int i = 2; i <= a2; i++){
			lseek(fd, D_OFFSET + cell[i - 2] * BLK_SIZE, SEEK_SET);
			read(fd, (char*)buf + BLK_SIZE * i - b, i == a2 ? b2 + 1 : BLK_SIZE);
		}
		close(fd);
		return read_bytes;
	}

	if (a >= 2){
		// handle the case that begins at indirect, end in indirect
		// handle case 6
		lseek(fd, D_OFFSET + cell[a - 2] * BLK_SIZE + b, SEEK_SET);
		read(fd, (char*)buf, BLK_SIZE - b);
		for(int i = a + 1; i <= a2; i++){
			lseek(fd, D_OFFSET + cell[i - 2] * BLK_SIZE, SEEK_SET);
			read(fd, (char*)buf + BLK_SIZE * (i - a) - b, i == a2 ? b2 + 1 : BLK_SIZE);
		}
		close(fd);
		return read_bytes;
	}
	return read_bytes; 
}

// you are allowed to create any auxiliary functions that can help your implementation. But only "open_t()" and "read_t()" are allowed to call these auxiliary functions.