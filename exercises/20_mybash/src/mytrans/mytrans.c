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
        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '#') {
            if (in_entry && current_word[0]) {
                hash_table_insert(table, current_word, current_translation);
                (*dict_count)++;
            }
            strncpy(current_word, line + 1, sizeof(current_word) - 1);
            trim(current_word);
            current_translation[0] = '\0';
            in_entry = 1;
        } else if (strncmp(line, "Trans:", 6) == 0) {
            strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
        }
    }

    if (in_entry && current_word[0]) {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
    }

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");

  // 从 text 文件路径推导 dict.txt 路径（同目录）
  char dict_path[512];
  strncpy(dict_path, filename, sizeof(dict_path) - 1);
  dict_path[sizeof(dict_path) - 1] = '\0';
  char *last_slash = strrchr(dict_path, '/');
  if (last_slash) {
    strcpy(last_slash + 1, "dict.txt");
  } else {
    strcpy(dict_path, "dict.txt");
  }

  uint64_t dict_count = 0;
  if (load_dictionary(dict_path, table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}