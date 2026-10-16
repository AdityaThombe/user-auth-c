#include "auth.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int check(int ok, const char *what)
{
    if (!ok)
        fprintf(stderr, "FAILED: %s\n", what);
    return ok ? 0 : 1;
}

int main(int argc, char **argv)
{
    const char *which = argc > 1 ? argv[1] : "";
    if (strcmp(which, "login_ok") == 0)
        return check(admin_login("admin", "Adm1n-C-Pass-2024") == 1, "admin can log in");
    if (strcmp(which, "login_bad") == 0)
        return check(admin_login("admin", "wrong") == 0 && admin_login("guest", "Adm1n-C-Pass-2024") == 0,
                     "wrong credentials are rejected");
    if (strcmp(which, "username") == 0) {
        user_t u = {0};
        return check(set_username(&u, "alice") == 5 && strcmp(u.name, "alice") == 0, "short username stored");
    }
    if (strcmp(which, "token") == 0) {
        char token[TOKEN_LEN + 1];
        new_session_token(token);
        int ok = strlen(token) == TOKEN_LEN;
        for (int i = 0; ok && i < TOKEN_LEN; i++)
            ok = isxdigit((unsigned char)token[i]);
        return check(ok, "token is 32 hex characters");
    }
    if (strcmp(which, "audit") == 0) {
        char buf[128] = {0};
        FILE *f = tmpfile();
        if (!f)
            return 1;
        audit(f, "user alice logged in");
        rewind(f);
        size_t n = fread(buf, 1, sizeof buf - 1, f);
        fclose(f);
        buf[n] = '\0';
        return check(strcmp(buf, "[audit] user alice logged in\n") == 0, "audit line written");
    }
    fprintf(stderr, "unknown test %s\n", which);
    return 2;
}
