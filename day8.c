#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 2000

typedef struct {
  long x;
  long y;
  long z;
} junction_t;

junction_t junctions[BUFFER_LEN];
size_t junction_len = 0;

double distances[BUFFER_LEN][BUFFER_LEN];

long long solveP1(int connections);
long long solveP2();

typedef struct {
  size_t root[BUFFER_LEN];
  size_t rank[BUFFER_LEN];
  long circuits[BUFFER_LEN];
} DSU;

// TODO: put this in a helper file
void dsu_init(DSU *dsu);
size_t dsu_find(DSU *dsu, size_t x);
void dsu_union(DSU *dsu, size_t a, size_t b);

void dsu_init(DSU *dsu) {
  for (int i = 0; i < BUFFER_LEN; i++) {
    dsu->root[i] = i;
    dsu->rank[i] = 0;
    dsu->circuits[i] = 1;
  }
}

size_t dsu_find(DSU *dsu, size_t x) {
  if (x == dsu->root[x]) {
    return x;
  } else {
    return dsu->root[x] = dsu_find(dsu, dsu->root[x]);
  }
}

void dsu_union(DSU *dsu, size_t a, size_t b) {
  a = dsu_find(dsu, a), b = dsu_find(dsu, b);
  if (a == b) {
    return;
  }
  if (dsu->rank[a] > dsu->rank[b]) {
    size_t tmp = a;
    a = b;
    b = tmp;
  }
  dsu->circuits[b] += dsu->circuits[a];
  dsu->circuits[a] = 0;
  dsu->root[a] = b;

  if (dsu->rank[a] == dsu->rank[b]) {
    dsu->rank[b] += 1;
  }
}

double compute_distance(const junction_t *j1, const junction_t *j2) {
  return sqrt(pow(j2->x - j1->x, 2) + pow(j2->y - j1->y, 2) +
              pow(j2->z - j1->z, 2));
}

void compute_distances() {
  const size_t n = junction_len;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      distances[i][j] = compute_distance(&junctions[i], &junctions[j]);
      distances[j][i] = distances[i][j];
    }
  }
}

int comp(const void *a, const void *b) { return (*(long *)b - *(long *)a); }

long long solveP1(int connections) {
  DSU dsu;
  dsu_init(&dsu);
  const size_t n = junction_len;

  for (int con = 0; con < connections; con++) {
    double smallest = 1000000000;
    size_t si = 0, sj = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (distances[i][j] > 0 && distances[i][j] < smallest) {
          si = i;
          sj = j;
          smallest = distances[i][j];
        }
      }
    }
    dsu_union(&dsu, si, sj);

    distances[si][sj] = -1;
    distances[sj][si] = -1;
  }

  qsort(dsu.circuits, n, sizeof(dsu.circuits[0]), comp);
  return dsu.circuits[0] * dsu.circuits[1] * dsu.circuits[2];
}

long long solveP2() {
  DSU dsu;
  dsu_init(&dsu);
  const size_t n = junction_len;

  bool new_connection = true;
  size_t si = 0, sj = 0;
  while (true) {
    double smallest = 1000000000;
    si = 0, sj = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (distances[i][j] > 0 && distances[i][j] <= smallest) {
          si = i;
          sj = j;
          smallest = distances[i][j];
        }
      }
    }

    dsu_union(&dsu, si, sj);
    distances[si][sj] = -1;
    distances[sj][si] = -1;

    printf("---\n");
    for (int i = 0; i < junction_len; i++) {
      printf("circuit: %ld\n", dsu.circuits[i]);
    }

    if (dsu.circuits[dsu_find(&dsu, sj)] >= n) {
      break;
    }
  }

  printf("si: %zu\n", junctions[si].x);
  printf("sj: %zu\n", junctions[sj].x);

  return junctions[si].x * junctions[sj].x;
}

int main() {
  char *filename = "./inputs/day8.example";
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL) {
    printf("An error occured reading the file\n");
    return 1;
  }

  char line[BUFFER_LEN];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    junction_t j;
    char *token = strtok(line, ",");
    j.x = atol(token);
    token = strtok(NULL, ",");
    j.y = atol(token);
    token = strtok(NULL, ",");
    j.z = atol(token);
    junctions[junction_len] = j;
    junction_len += 1;
  }

  fclose(fptr);

  compute_distances();

  printf("Part 1: %lld\n", solveP1(10));
  printf("Part 2: %lld\n", solveP2());

  /* for (int i = 0; i < junction_len; i++) { */
  /*   printf("circuit: %ld\n", dsu.circuits[i]); */
  /* } */
  /* for (int i = 0; i < n; i++) { */
  /*   for (int j = 0; j < n; j++) { */
  /*     printf("%f, ", distances[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  return 0;
}
