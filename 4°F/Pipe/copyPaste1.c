#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file destination_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipefd[0]); // Close read end of pipe
        
        FILE *source_file = fopen(argv[1], "r");
        if (source_file == NULL) {
            perror("open source file");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0) {
            size_t bytes_written = write(pipefd[1], buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("write to pipe");
                fclose(source_file);
                exit(EXIT_FAILURE);
            }
        }

        if (ferror(source_file)) {
            perror("read from source file");
            fclose(source_file);
            exit(EXIT_FAILURE);
        }

        fclose(source_file);
        close(pipefd[1]); // Close write end of pipe
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipefd[1]); // Close write end of pipe
        
        FILE *dest_file = fopen(argv[2], "w");
        if (dest_file == NULL) {
            perror("open destination file");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            ssize_t bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
            if (bytes_written != bytes_read) {
                perror("write to destination file");
                fclose(dest_file);
                exit(EXIT_FAILURE);
            }
        }

        if (bytes_read == -1) {
            perror("read from pipe");
            fclose(dest_file);
            exit(EXIT_FAILURE);
        }

        fclose(dest_file);
        close(pipefd[0]); // Close read end of pipe

        // Wait for the child process to finish
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        }

        exit(EXIT_SUCCESS);
    }

    return 0; // Unreachable
}
