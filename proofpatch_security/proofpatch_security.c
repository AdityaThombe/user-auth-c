#include <assert.h>
#include <string.h>
#include "auth.h"

void test_overflow() {
    user_t u;
    memset(&u, 0, sizeof(u));
    char long_name[1024];
    memset(long_name, 'A', sizeof(long_name) - 1);
    long_name[sizeof(long_name) - 1] = '\0';
    size_t len = set_username(&u, long_name);
    assert(len == strlen(u.name));
}

int main(void) {
    test_overflow();
    return 0;
}
