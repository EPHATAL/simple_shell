#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void execute_command(char *args[]) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    
    while (1) {
        printf("shell> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit the shell if the user enters "exit" or "quit"
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }

        // Tokenize the input
        char *args[MAX_INPUT_SIZE];
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Execute the command
        execute_command(args);
    }

    return 0;
}

