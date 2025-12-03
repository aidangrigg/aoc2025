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
  return 0l;
}

int main() {
  printf("Part 1: %d \n", solveP1("./inputs/day3.real"));
  /* printf("Part 2: %lld\n", solveP2("./inputs/day3.real")); */

  return 0;
}
