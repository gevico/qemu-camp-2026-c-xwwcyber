#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // 找到 '?' 后面的参数部分
    const char *query = strchr(url, '?');
    if (!query) {
        err = -1;
        goto exit;
    }
    query++; // 跳过 '?'

    // 复制参数字符串用于 strtok
    char *params = strdup(query);
    if (!params) {
        err = -ENOMEM;
        goto exit;
    }

    char *pair = strtok(params, "&");
    while (pair) {
        char *eq = strchr(pair, '=');
        if (eq) {
            *eq = '\0';
            printf("key = %s, value = %s\n", pair, eq + 1);
        }
        pair = strtok(NULL, "&");
    }

    free(params);

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}