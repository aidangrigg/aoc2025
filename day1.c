#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char dir;
  int amount;
} Rotation;


int solveP1(Rotation rs[], size_t rs_len);

int solveP1(Rotation rs[], size_t rs_len) {
  int zeros = 0, current = 50;

  for (int i = 0; i < rs_len; i++) {
    Rotation r = rs[i];
    int d = r.dir == 'R' ? r.amount : -r.amount;

    current += d;

    while (current < 0) {
      current += 100;
    }

    while (current > 99) {
      current -= 100;
    }

    printf("current: %d\n", current);

    if (current == 0) {
      zeros += 1;
    }
  }

  return zeros;
}

#define BUFFER_SIZE 10000

int main() {
  FILE* fptr = fopen("./inputs/day1.real", "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  Rotation rotations[BUFFER_SIZE];
  size_t rotations_len = 0;

  char line[100];
  while (fgets(line, sizeof(line), fptr)) {
    rotations[rotations_len] = (Rotation){
      .dir = line[0],
      .amount = atoi(&line[1])
    };

    rotations_len += 1;

    if (rotations_len > BUFFER_SIZE) {
      printf("Input does not fit into buffer\n");
      return 1;
    }
  }

  printf("Part 1: %d \n", solveP1(rotations, rotations_len));

  fclose(fptr);
  return 0;
}

