#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 1000

char input[BUFFER_LEN][BUFFER_LEN];
size_t rows = 0;
size_t cols = 0;

long long solveP1();
long long solveP2();

bool check(size_t r, size_t c) {
  return r >= 0 && r < rows && c >= 0 && c < cols && input[r][c] == '@';
}

bool accessable(size_t r, size_t c) {
  int surrounding = 0;
  surrounding += check(r + 1, c);
  surrounding += check(r - 1, c);
  surrounding += check(r, c + 1);
  surrounding += check(r, c - 1);

  surrounding += check(r + 1, c + 1);
  surrounding += check(r - 1, c - 1);
  surrounding += check(r - 1, c + 1);
  surrounding += check(r + 1, c - 1);
  return surrounding < 4;
}

long long solveP1() {
  long long ans = 0;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (input[r][c] == '@') {
        ans += accessable(r, c);
      }
    }
  }

  return ans;
}

long long solveP2() {
  long long ans = 0;
  int removals = -1;

  while (removals != 0) {
    removals = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (input[r][c] == '@' && accessable(r, c)) {
          input[r][c] = '.';
          ans += 1;
          removals += 1;
        }
      }
    }
  }

  return ans;
}

int main() {
  FILE *fptr = fopen("./inputs/day4.real", "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];

  while (fgets(line, sizeof(line), fptr) != NULL) {
    strcpy(input[rows], line);
    cols = strlen(line);
    rows += 1;
  }

  printf("Part 1: %lld\n", solveP1());
  printf("Part 2: %lld\n", solveP2());

  return 0;
}
