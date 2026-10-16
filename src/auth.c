/* Login, usernames and session tokens.
 * Demo target for ProofPatch: intentionally vulnerable. Never deploy this code. */
#include "auth.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char ADMIN_USER[] = "admin";
static const char ADMIN_PASSWORD[] = "Adm1n-C-Pass-2024";

int admin_login(const char *user, const char *password)
{
    return strcmp(user, ADMIN_USER) == 0 && strcmp(password, ADMIN_PASSWORD) == 0;
}

size_t set_username(user_t *user, const char *name)
{
    strcpy(user->name, name);
    return strlen(user->name);
}

void new_session_token(char *out)
{
    static const char hex[] = "0123456789abcdef";
    srand(time(NULL));
    for (int i = 0; i < TOKEN_LEN; i++)
        out[i] = hex[rand() % 16];
    out[TOKEN_LEN] = '\0';
}

void audit(FILE *stream, const char *message)
{
    fprintf(stream, "[audit] ");
    fprintf(stream, message);
    fprintf(stream, "\n");
}
