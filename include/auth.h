#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <stddef.h>
#include <stdio.h>

#define USERNAME_MAX 16
#define TOKEN_LEN 32

typedef struct {
    char name[USERNAME_MAX];
    int is_admin;
} user_t;

/* Returns 1 when user/password are the operator credentials, otherwise 0. */
int admin_login(const char *user, const char *password);

/* Stores the display name of a user. Returns the stored length. */
size_t set_username(user_t *user, const char *name);

/* Writes a TOKEN_LEN hex session token plus '\0' into out (TOKEN_LEN + 1 bytes). */
void new_session_token(char *out);

/* Writes an audit line for the given message to the stream. */
void audit(FILE *stream, const char *message);

#endif
