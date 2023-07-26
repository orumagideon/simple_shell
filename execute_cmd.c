#include "shell.h"

void free_tokens(char **tokens)
{
    char **current_token = tokens;
    while (*current_token)
    {
        free(*current_token);
        ++current_token;
    }
    free(tokens);
}
