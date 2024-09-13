#include "util/prompts.h"

// Credit: https://stackoverflow.com/a/4023921
bool prompt(char *prompt, char *buffer, size_t size) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prompt != NULL) {
        printf ("%s", prompt);
        fflush (stdout);
    }

    if (fgets (buffer, size, stdin) == NULL)
        return false;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buffer[strlen(buffer) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra != 1);
    }

    // Otherwise remove newline and give string back to caller.
    buffer[strlen(buffer) - 2] = '\0';
    return true;
}