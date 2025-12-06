#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 5000

int input[BUFFER_LEN][BUFFER_LEN];
size_t rows = 0;
size_t cols = 0;

char operations[BUFFER_LEN];
size_t ops_len = 0;

long long solveP1();
long long solveP2(char *filename);

long long solveP1() {
  long long ans = 0;

  assert(cols == ops_len);
  for (int c = 0; c < cols; c++) {
    long long sum = operations[c] == '+' ? 0 : 1;
    for (int r = 0; r < rows; r++) {
      if (operations[c] == '+') {
        sum += input[r][c];
      } else {
        sum *= input[r][c];
      }
    }
    ans += sum;
  }
  return ans;
}

long long solveP2(char *filename) {
  long long ans = 0;
  char numbers[5][BUFFER_LEN];
  int rows = 0;
  int cols = 0;
  char ops[BUFFER_LEN];

  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    if (*line == '+' || *line == '*') {
      strcpy(ops, line);
      cols = strlen(line);
    } else {
      strcpy(numbers[rows], line);
      rows += 1;
    }
  }

  fclose(fptr);

  for (int c = 0; c < cols; c++) {
    if (ops[c] == ' ')
      continue;
    char op = ops[c];

    int n_idx = c;
    long sum = op == '+' ? 0 : 1;
    while (true) {
      long n = 0;
      for (int r = 0; r < rows; r++) {
        if (numbers[r][n_idx] != ' ') {
          n *= 10;
          n += numbers[r][n_idx] - '0';
        }
      }

      n_idx += 1;

      if (n == 0 || n_idx >= cols)
        break;

      if (op == '+') {
        sum += n;
      } else {
        sum *= n;
      }
    }
    ans += sum;
  }

  return ans - 1;
}

int main() {
  char *filename = "./inputs/day6.real";
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    char *tok = strtok(line, " ");
    size_t col = 0;
    while (tok != NULL) {
      if (*tok == '+' || *tok == '*') {
        operations[ops_len] = *tok;
        ops_len += 1;
      } else if (*tok != '\n') {
        input[rows][col] = atoi(tok);
        col += 1;
      }

      cols = col > cols ? col : cols;
      tok = strtok(NULL, " ");
    }
    rows += 1;
  }
  rows -= 1;

  fclose(fptr);

  printf("Part 1: %lld\n", solveP1());
  printf("Part 2: %lld\n", solveP2(filename));

  return 0;
}
