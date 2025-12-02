#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10000

typedef struct {
  unsigned long long start;
  unsigned long long end;
} Range;

unsigned long long solveP1(Range rs[], size_t rs_len);
unsigned long long solveP2(Range rs[], size_t rs_len);

unsigned long long solveP1(Range rs[], size_t rs_len) {
  unsigned long long ans = 0ll;
  char number_str[1000];
  char start[1000];
  char end[1000];

  for (int i = 0; i < rs_len; i++) {
    Range r = rs[i];
    for (unsigned long long j = r.start; j <= r.end; j++) {
      sprintf(number_str, "%llu", j);

      int len = strlen(number_str);
      strcpy(end, number_str + len / 2);

      number_str[len / 2] = '\0';
      strcpy(start, number_str);

      if (!strcmp(start, end)) {
        ans += j;
      }
    }
  }
  return ans;
}

unsigned long long solveP2(Range rs[], size_t rs_len) {
  unsigned long long ans = 0;

  char number_str[1000];
  size_t n = 0;
  for (int i = 0; i < rs_len; i++) {
    Range r = rs[i];
    for (unsigned long long j = r.start; j <= r.end; j++) {
      sprintf(number_str, "%llu", j);
      int len = strlen(number_str);

      for (int stridx = 1; stridx <= len / 2; stridx++) {
        if (len % stridx != 0) {
          continue;
        }

        bool is_pattern = true;
        for (int i = stridx; i < len; i++) {
          if (number_str[i] != number_str[i % stridx]) {
            is_pattern = false;
            break;
          }
        }

        if (is_pattern) {
          ans += j;
          break;
        }
      }
    }
  }

  return ans;
}

int main() {
  FILE *fptr = fopen("./inputs/day2.real", "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  Range ranges[BUFFER_SIZE];
  size_t ranges_len = 0;

  char line[BUFFER_SIZE];

  if (fgets(line, sizeof(line), fptr) == NULL) {
    printf("An error occured reading a line from the file\n");
    return 1;
  }

  char *end_str;
  char *token = strtok_r(line, ",", &end_str);

  while (token != NULL) {
    Range r;
    char *end_token;
    char *token2 = strtok_r(token, "-", &end_token);
    r.start = atoll(token2);
    token2 = strtok_r(NULL, "-", &end_token);
    r.end = atoll(token2);
    ranges[ranges_len] = r;
    ranges_len += 1;

    token = strtok_r(NULL, ",", &end_str);
  }

  printf("Part 1: %llu \n", solveP1(ranges, ranges_len));
  printf("Part 2: %llu \n", solveP2(ranges, ranges_len));

  fclose(fptr);
  return 0;
}
