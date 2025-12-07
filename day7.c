#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 5000
#define VISITED_SPLIT '+'
#define BEAM '|'

char input[BUFFER_LEN][BUFFER_LEN];
size_t rows = 0;
size_t cols = 0;

long long solveP1();
long long solveP2();

void check_beam(int r, int c) {
  if (c < 0 || c >= cols)
    return;
  for (int r1 = r; r1 < rows; r1++) {
    if (input[r1][c] == BEAM || input[r1][c] == VISITED_SPLIT) {
      return;
    }
    if (input[r1][c] == '^') {
      input[r1][c] = VISITED_SPLIT;
      check_beam(r1, c - 1);
      check_beam(r1, c + 1);
      break;
    } else {
      input[r1][c] = '|';
    }
  }
}

long long solveP1() {
  long long ans = 0;

  for (int c = 0; c < cols; c++) {
    if (input[0][c] == 'S') {
      check_beam(1, c);
      break;
    }
  }

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      printf("%c", input[r][c]);
      ans += input[r][c] == VISITED_SPLIT;
    }
  }
  return ans;
}

long long solveP2() {}

int main() {
  char *filename = "./inputs/day7.real";
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    strcpy(input[rows], line);
    rows += 1;
  }
  cols = strlen(input[0]);

  fclose(fptr);
  printf("Part 1: %lld\n", solveP1());
  printf("Part 2: %lld\n", solveP2());

  return 0;
}
