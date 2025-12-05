#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 10000

typedef struct {
  long long start;
  long long end;
} Range;

Range ranges[BUFFER_LEN];
size_t ranges_len = 0;

long long ingredients[BUFFER_LEN];
size_t ingredients_len = 0;

int solveP1();
long long solveP2();
bool check(long long ingredient);
bool overlapping(Range r1, Range r2);

bool check(long long ingredient) {
  for (int i = 0; i < ranges_len; i++) {
    Range r = ranges[i];

    if (r.start <= ingredient && r.end >= ingredient) {
      return true;
    }
  }
  return false;
}

int solveP1() {
  int ans = 0;
  for (int i = 0; i < ingredients_len; i++) {
    ans += check(ingredients[i]);
  }
  return ans;
}

bool overlapping(Range r1, Range r2) {
  return r1.start <= r2.end && r2.start <= r1.end;
}

long long solveP2() {
  long long ans = 0;

  for (int i = 0; i < ranges_len; i++) {
    if(ranges[i].start == -1) continue;
    for (int j = i + 1; j < ranges_len; j++) {
      Range r1 = ranges[i];
      Range r2 = ranges[j];
      if (r1.start != -1 && r2.start != -1 && overlapping(r1, r2)) {
        long long start = r1.start < r2.start ? r1.start : r2.start;
        long long end = r1.end > r2.end ? r1.end : r2.end;

        ranges[i].start = start;
        ranges[i].end = end;
        ranges[j].start = -1; // sorta ugly, but mark merged ranges with -1
        j = i + 1;
      }
    }
  }

  for (int i = 0; i < ranges_len; i++) {
    if(ranges[i].start == -1) continue;
    printf("%lld, %lld\n", ranges[i].start, ranges[i].end);
    ans += ranges[i].end - ranges[i].start + 1;
  }

  return ans;
}

int main() {
  FILE *fptr = fopen("./inputs/day5.real", "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  bool fresh = true;

  while (fgets(line, sizeof(line), fptr) != NULL) {
    if (strcmp(line, "\n") == 0) {
      fresh = false;
    }

    if (fresh) {
      Range r;
      char *token = strtok(line, "-");
      r.start = atoll(token);
      token = strtok(NULL, "-");
      r.end = atoll(token);
      ranges[ranges_len] = r;
      ranges_len += 1;
    } else {
      ingredients[ingredients_len] = atoll(line);
      ingredients_len += 1;
    }
  }

  printf("Part 1: %d\n", solveP1());
  printf("Part 2: %lld\n", solveP2());

  return 0;
}
