#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // 解析 s/old/new/ 格式
    const char *p = cmd + 2; // 跳过 "s/"
    const char *slash = strchr(p, '/');
    if (!slash) return -1;

    *old_str = strndup(p, slash - p);

    p = slash + 1;
    slash = strchr(p, '/');
    if (!slash) {
        free(*old_str);
        *old_str = NULL;
        return -1;
    }

    *new_str = strndup(p, slash - p);

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char *pos = strstr(str, old);
    if (!pos) return;

    int old_len = strlen(old);
    int new_len = strlen(new);
    int tail_len = strlen(pos + old_len);

    memmove(pos + new_len, pos + old_len, tail_len + 1);
    memcpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
