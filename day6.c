#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFFER_LEN 10000

int input[BUFFER_LEN][BUFFER_LEN];
size_t rows = 0;
size_t cols = 0;

char operations[BUFFER_LEN];
size_t ops_len = 0;

long long solveP1();
long long solveP2();

long long solveP1() {
  long long ans = 0;

  /* printf("cols: %zu, ops_len: %zu\n", cols, ops_len); */
  assert(cols == ops_len);
  for(int c = 0; c < cols; c++) {
    long long sum = operations[c] == '+' ? 0 : 1;
    for (int r = 0; r < rows; r++) {
      if (operations[c] == '+') {
        /* printf("add: %d\n", input[r][c]); */
        sum += input[r][c];
      } else {
        /* printf("mult: %d\n", input[r][c]); */
        sum *= input[r][c];
      }
    }
    /* printf("sum: %lld\n", sum); */
    ans += sum;
  }
  return ans;
}

long long solveP2() {
  long long ans = 0;
  return ans;
}

int main() {
  FILE *fptr = fopen("./inputs/day6.real", "r");

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
      } else if(*tok != '\n') {
        /* printf("token: %s\n", tok); */
        input[rows][col] = atoi(tok);
        col += 1;
      }

      cols = col > cols ? col : cols;
      tok = strtok(NULL, " ");
    }
    rows += 1;
  }
  rows -= 1;

  printf("Part 1: %lld\n", solveP1());
  printf("Part 2: %lld\n", solveP2());

  return 0;
}
