#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

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
        close(pipefd[1]); // Close write end of pipe
        int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (dest_fd == -1) {
            perror("open destination file");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            if (write(dest_fd, buffer, bytes_read) != bytes_read) {
                perror("write to destination file");
                exit(EXIT_FAILURE);
            }
        }

        if (bytes_read == -1) {
            perror("read from pipe");
            exit(EXIT_FAILURE);
        }

        close(dest_fd);
        close(pipefd[0]); // Close read end of pipe
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipefd[0]); // Close read end of pipe
        int source_fd = open(argv[1], O_RDONLY);
        if (source_fd == -1) {
            perror("open source file");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
            ssize_t bytes_written = write(pipefd[1], buffer, bytes_read);
            if (bytes_written != bytes_read) {
                if (bytes_written == -1)
                    perror("write to pipe");
                else
                    fprintf(stderr, "write to pipe: incomplete write\n");
                exit(EXIT_FAILURE);
            }
        }

        if (bytes_read == -1) {
            perror("read from source file");
            exit(EXIT_FAILURE);
        }

        close(source_fd);
        close(pipefd[1]); // Close write end of pipe

        // Wait for the child process to finish
        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0; // Unreachable
}
