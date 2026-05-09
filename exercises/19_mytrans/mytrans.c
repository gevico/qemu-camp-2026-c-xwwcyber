// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    char *start = str;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != str) memmove(str, start, strlen(start) + 1);
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) *end-- = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    while (fgets(line, sizeof(line), file)) {
        // 去掉换行符
        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '#') {
            // 保存上一个词条
            if (in_entry && current_word[0]) {
                hash_table_insert(table, current_word, current_translation);
                (*dict_count)++;
            }
            // 新词条
            strncpy(current_word, line + 1, sizeof(current_word) - 1);
            trim(current_word);
            current_translation[0] = '\0';
            in_entry = 1;
        } else if (strncmp(line, "Trans:", 6) == 0) {
            strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
        }
    }

    // 保存最后一个词条
    if (in_entry && current_word[0]) {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
    }

  fclose(file);
  return 0;
}
