#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 10000

int solveP1(char *filename);
long long solveP2(char *filename);

int solveP1(char *filename) {
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  int ans = 0;

  while (fgets(line, sizeof(line), fptr) != NULL) {
    int len = strlen(line);
    int max_idx = 0;
    for (int i = 0; i < len - 2; i++) {
      if (line[i] - '0' > line[max_idx] - '0') {
        max_idx = i;
      }
    }

    int other = max_idx + 1;
    for (int i = max_idx + 1; i < len - 1; i++) {
      if (line[i] - '0' > line[other] - '0') {
        other = i;
      }
    }

    char res[] = {line[max_idx], line[other], '\0'};
    ans += atoi(res);
  }

  return ans;
}

long long solveP2(char *filename) {
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  long long ans = 0;

  while (fgets(line, sizeof(line), fptr) != NULL) {
    int len = strlen(line);

    char ns[13];
    ns[12] = '\0';
    char *prev = line;

    for (int i = 0; i < 12; i++) {
      char *max = i == 0 ? prev : prev + 1;

      for (char *curr = max; curr < (line + len) - 12 + i; curr++) {
        if (*curr > *max) {
          max = curr;
        }
      }

      prev = max;
      ns[i] = *max;
    }

    printf("%lld\n", atoll(ns));

    ans += atoll(ns);
  }

  return ans;
}

int main() {
  char *filename = "./inputs/day3.real";
  printf("Part 1: %d \n", solveP1(filename));
  printf("Part 2: %lld\n", solveP2(filename));

  return 0;
}
