#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char *url) {
  int err = 0;
  char dst[128];
  const char *query = strchr(url, '?');
  if (query == NULL || *(query + 1) == '\0') {
    return err;
  }

  size_t query_len = strlen(query + 1);
  if (query_len >= sizeof(dst)) {
    return err;
  }

  strncpy(dst, query + 1, sizeof(dst) - 1);
  dst[sizeof(dst) - 1] = '\0';

  char *begin = dst;
  char *delim = "&";
  char *tok = strtok(begin, delim);
  while (tok) {
    char *second = strchr(tok, '=');
    if (second == NULL) {
      tok = strtok(NULL, delim);
      continue;
    }
    *second = '\0';
    printf("key = %s, value = %s\n", tok, second + 1);

    tok = strtok(NULL, delim);
  }
  return 1;
}

int main() {
  const char *test_url =
      "https://cn.bing.com/search?name=John&age=30&city=New+York";

  printf("Parsing URL: %s\n", test_url);
  printf("Parameters:\n");

  parse_url(test_url);

  return 0;
}
