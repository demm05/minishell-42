#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_COMMANDS 3  // Number of commands in the pipeline

//char *my_strcat(char *strg1, char *strg2)
//{
//    char *start = strg1;
//
//    while(*strg1 != '\0')
//    {
//        strg1++;
//    }
//
//    while(*strg2 != '\0')
//    {
//        *strg1 = *strg2;
//        strg1++;
//        strg2++;
//    }
//
//    *strg1 = '\0';
//    return start;
//}

int main() {
    int pipes[NUM_COMMANDS - 1][2]; // Array of pipes
    pid_t pids[NUM_COMMANDS]; // Array of process IDs
	//char command_base_path[] = "/bin/";
	

    // Commands to execute
    char *commands[NUM_COMMANDS][3] = {
        {"/bin/ls", NULL},           // First command: ls
        {"/bin/grep", "c", NULL},    // Second command: grep c
        {"/usr/bin/wc", "-l", NULL}      // Third command: wc -l
    };

    // Create pipes
    for (int i = 0; i < NUM_COMMANDS - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork processes
    for (int i = 0; i < NUM_COMMANDS; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) { // Child process
            // If not the first command, read from the previous pipe
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO); // Replace stdin with previous pipe read end
            }

            // If not the last command, write to the next pipe
            if (i < NUM_COMMANDS - 1) {
                dup2(pipes[i][1], STDOUT_FILENO); // Replace stdout with current pipe write end
            }

            // Close all pipes in child
            for (int j = 0; j < NUM_COMMANDS - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Execute command
            //char *command_path = my_strcat(command_base_path, commands[i][0]);
			//printf("%s\n", command_path);
            execve(commands[i][0], commands[i], NULL);
            perror("execve"); // If exec fails
            exit(EXIT_FAILURE);
        }
    }

    // Parent closes all pipes
    for (int i = 0; i < NUM_COMMANDS - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Parent waits for all children
    for (int i = 0; i < NUM_COMMANDS; i++) {
        wait(NULL);
    }

    return 0;
}
