# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
#include <signal.h>
# include<readline/readline.h>
# include<readline/history.h>

# include<signal.h>

// Signal handler function for Ctrl-C (SIGINT)
void sigint_handler(int signum) {
    printf("Custom Ctrl-C behavior: SIGINT received. Exiting.\n");
    exit(EXIT_SUCCESS);
}

// Signal handler function for Ctrl-\ (SIGQUIT)
void sigquit_handler(int signum) {
    printf("Custom Ctrl-\\ behavior: SIGQUIT received. Ignoring.\n");
}

// Signal handler function for EOF (Ctrl-D)
void eof_handler(int signum) {
	printf("signum %i",signum);
    printf("Custom EOF behavior: EOF received. Exiting.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Create signal action structures
    struct sigaction sigint_action, sigquit_action;

    // Set up SIGINT handler
    sigint_action.sa_handler = sigint_handler;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    if (sigaction(SIGINT, &sigint_action, NULL) == -1) {
        perror("Unable to register SIGINT handler");
        exit(EXIT_FAILURE);
    }

    // Set up SIGQUIT handler (Ctrl-\)
    sigquit_action.sa_handler = sigquit_handler;
    sigemptyset(&sigquit_action.sa_mask);
    sigquit_action.sa_flags = 0;
    if (sigaction(SIGQUIT, &sigquit_action, NULL) == -1) {
        perror("Unable to register SIGQUIT handler");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl-C, Ctrl-\\, or Ctrl-D to trigger custom behavior:\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do nothing, just keep the program running
        char ch;
        // if (read(STDIN_FILENO, &ch, 1) == 0) {
        if (read(0, &ch, 1) == 0) {
            // EOF detected (Ctrl-D)
            eof_handler(SIGPIPE);
        }
    }

    return 0;
}
