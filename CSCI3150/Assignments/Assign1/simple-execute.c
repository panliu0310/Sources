
//CSCI3150 Assignment 1
//Lam Wai To Keith 1155133260
//Liu Hoi Pan 1155127464

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int shell_execute(char ** args, int argc)
{
    int wait_return, status, pipe_pid, pipe_num = 0;
    int child_pid, child1_pid, child2_pid; //child pid
    int arglen = 0, arglen1 = 0, argle	n2 = 0; //command length
    int pipecnt = 0; //keep track of no. of pipes
    char *exec_args[256]; //arguments that needs to be executed
    char *exec1_args[256];
    char *exec2_args[256];
    
    int p1_fd[2], p2_fd[2], p3_fd[2]; // pipes

    pipe(p1_fd);
    pipe(p2_fd);
    pipe(p3_fd);

    if ( strcmp(args[0], "EXIT") == 0 )
        return -1; 

    //detect pipes    
    for ( int cnt = 0; args[cnt] != NULL; cnt++){
        if ( *args[cnt] == '|'){
            pipe_num++; // count the pipe number
            args[cnt] = NULL; // make all "|" becomes null
            arglen = cnt; // count the argument length
	    pipecnt++;
        }
	if ( pipecnt == 1 && args[cnt] != NULL )
		arglen1++;
	if ( pipecnt == 2 && args[cnt] != NULL )
		arglen2++; 
    }


    if (pipe_num == 0){
	//case of no pipe
        if( (child_pid = fork()) < 0 ){
            printf("fork() error \n");
        }else if (child_pid == 0 ){
            // child process
            if ( execvp(args[0], args) < 0){ 
                printf("execvp() error \n");
                exit(-1);
            }
        }else{
            // parent process
            if ( (wait_return = wait(&status) ) < 0 )
                printf("wait() error \n"); 
        }

    }else if (pipe_num == 1){
        //case of only one pipe
        if ( (child_pid = fork()) < 0){
            printf("fork() error \n");
        }else if (child_pid == 0){
            // child process
            // close 0 and dup p1 to make input of command2 as the writing end of the pipe
            close(0); dup(p1_fd[0]);
            //close all file descriptors
            close(p1_fd[0]); close(p1_fd[1]);
            //use for loop to recreate a exec_args for execute the second command
	    int execlen = 0;
	    for ( int i = arglen + 1; args[i] != NULL; i++){
		exec_args[i-arglen-1] = args[i];
		execlen = i - arglen;
	    }
	    exec_args[execlen] = NULL;
            if ( execvp(exec_args[0], exec_args) < 0){ 
                printf("execvp() error \n");
                exit(-1);
            }
        }else{
            // parent process
            close(1); dup(p1_fd[1]);
            close(p1_fd[0]); close(p1_fd[1]);

            if ( execvp(args[0], args) < 0){ 
                printf("execvp() error \n");
                exit(-1);
            }
        }

    }else if (pipe_num == 2){
        //case of two pipes
	if ( (child_pid = fork()) < 0){
            printf("fork() error \n");
        }else if (child_pid == 0){
            // child process
            if ( (child1_pid = fork()) < 0){
                printf("fork() error \n");
            }else if (child1_pid == 0){
                // child process of child process
                close(0); dup(p2_fd[0]);
                // close all file descriptors
                close(p1_fd[0]); close(p1_fd[1]); close(p2_fd[0]); close(p2_fd[1]);
                //use for loop to recreate a exec_args for execute the second command
	    	int execlen = 0;
	    	for ( int i = arglen + 1; args[i] != NULL; i++){
			exec_args[i-arglen-1] = args[i];
			execlen = i - arglen;
	    	}
	    	exec_args[execlen] = NULL;

                if ( execvp(exec_args[0], exec_args) < 0){
                    printf("execvp() error \n");
                    exit(-1);
                }
            }else{
                // parent process of child process
                close(0); dup(p1_fd[0]);
                close(1); dup(p2_fd[1]);
                // close all file descriptors
                close(p1_fd[0]); close(p1_fd[1]); close(p2_fd[0]); close(p2_fd[1]);
                //use for loop to recreate a exec_args for execute the second command
	    	int execlen = 0;
	    	for ( int i = arglen1 + 1; args[i] != NULL; i++){
			exec1_args[i-arglen1 - 1] = args[i];
			execlen = i - arglen1;
	    	}
	    	exec1_args[execlen] = NULL;

                if ( execvp(exec1_args[0], exec1_args) < 0){
                    printf("execvp() error \n");
                    exit(-1);
                }
            }
        }else{
            // parent process
            close(1); dup(p1_fd[1]);
            close(p1_fd[0]); close(p1_fd[1]);

            if ( execvp(args[0], args) < 0){
                printf("execvp() error \n");
                exit(-1);
            }
        }

    }else if (pipe_num == 3){
	//case of three pipes
        if ( (child_pid = fork()) < 0){
            printf("fork() error \n");
        }else if (child_pid == 0){
            // child process
            if ( (child1_pid = fork()) < 0){
                printf("fork() error \n");
            }else if (child1_pid == 0) {
                // child process of child process
                if ( (child2_pid = fork()) < 0){
                    printf("fork() error \n");
                }else if (child2_pid == 0){
                    // child process of child process of child process
                    close(0); dup(p3_fd[0]);
                    // close all file descriptors
                    close(p1_fd[0]); close(p1_fd[1]); close(p2_fd[0]); close(p2_fd[1]); close(p3_fd[0]); close(p3_fd[1]);
                    int execlen = 0;
	    	    for ( int i = arglen + 1; args[i] != NULL; i++){
			exec_args[i-arglen-1] = args[i];
			execlen = i - arglen;
	    	    }
	    	    exec_args[execlen] = NULL;
                    if ( execvp(exec_args[0], exec_args) < 0){
                        printf("execvp() error \n");
                        exit(-1);
                    }
                }else{
                    // parent process of child process of child process
                    close(0); dup(p2_fd[0]);
                    close(1); dup(p3_fd[1]);
                    // close all file descriptors
                    close(p1_fd[0]); close(p1_fd[1]); close(p2_fd[0]); close(p2_fd[1]); close(p3_fd[0]); close(p3_fd[1]);
                    int execlen = 0;
	    	    for ( int i = arglen1 + 1; args[i] != NULL; i++){
			exec1_args[i-arglen1 - 1] = args[i];
			execlen = i - arglen1;
	    	    }
	    	    exec1_args[execlen] = NULL;
                    if ( execvp(exec1_args[0], exec1_args) < 0){
                        printf("execvp() error \n");
                        exit(-1);
                    }
                }
                
            }else{
                // parent process of child process
                close(0); dup(p1_fd[0]);
                close(1); dup(p2_fd[1]);
                close(p1_fd[0]); close(p1_fd[1]); close(p2_fd[0]); close(p2_fd[1]); close(p3_fd[0]); close(p3_fd[1]);
                int execlen = 0;
	    	for ( int i = arglen2 + 1; args[i] != NULL; i++){
			exec2_args[i-arglen2 - 1] = args[i];
			execlen = i - arglen2;
	    	}
	    	exec2_args[execlen] = NULL;
                if ( execvp(exec2_args[0], exec2_args) < 0){
                    printf("execvp() error \n");
                    exit(-1);
                }
            }
        }else{
            // parent process
            close(1); dup(p1_fd[1]);
            close(p1_fd[0]); close(p1_fd[1]); close(p2_fd[0]); close(p2_fd[1]); close(p3_fd[0]); close(p3_fd[1]);
            
            if ( execvp(args[0], args) < 0){
                printf("execvp() error \n");
                exit(-1);
            }
        }


    }
    return 0;

}


