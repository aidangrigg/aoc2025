#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 150
#define VISITED_SPLIT '+'
#define BEAM '|'

char input[BUFFER_LEN][BUFFER_LEN];
size_t rows = 0;
size_t cols = 0;

long timelines[BUFFER_LEN][BUFFER_LEN];

long long solveP1();
long long solveP2();
long count_timelines(int row, int col);
void traverse_beam(int r, int c);

void traverse_beam(int r, int c) {
  if (c < 0 || c >= cols)
    return;
  for (int r1 = r; r1 < rows; r1++) {
    if (input[r1][c] == BEAM || input[r1][c] == VISITED_SPLIT) {
      return;
    }
    if (input[r1][c] == '^') {
      input[r1][c] = VISITED_SPLIT;
      traverse_beam(r1, c - 1);
      traverse_beam(r1, c + 1);
      return;
    } else {
      input[r1][c] = '|';
    }
  }
}

long long solveP1() {
  long long ans = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      printf("%c", input[r][c]);
      ans += input[r][c] == VISITED_SPLIT;
    }
  }
  return ans;
}

long count_timelines(int row, int col) {
  for (int r = row; r < rows; r++) {
    if (input[r][col] == VISITED_SPLIT) {
      if (timelines[r][col] <= 0) {
        timelines[r][col] = count_timelines(r, col + 1) + count_timelines(r, col - 1);
      }
      return timelines[r][col];
    }
  }

  return 1;
}

long long solveP2() {
  for (int c = 0; c < cols; c++) {
    if (input[0][c] == 'S') {
      timelines[0][c] = 1;
      return count_timelines(0, c);
    }
  }

  return -1;
}

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

  for (int c = 0; c < cols; c++) {
    if (input[0][c] == 'S') {
      traverse_beam(1, c);
      break;
    }
  }

  fclose(fptr);
  printf("Part 1: %lld\n", solveP1());
  printf("Part 2: %lld\n", solveP2());

  return 0;
}
