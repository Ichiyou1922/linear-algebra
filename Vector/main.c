#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int dim;
  double *val;
} Vector;

//ベクトルの作成
Vector *create_vector(int size) { //Vectorのアドレスを渡す
  Vector* new_vector = (Vector *)malloc(sizeof(Vector));
  if (new_vector == NULL) {
    printf("Failed to allocate structure memory");
    free(new_vector);
    exit(1);
  }
  new_vector->dim = size;
  new_vector->val = (double *)calloc(size, sizeof(double));
  if (new_vector->val == NULL) {
    printf("Failed to allocate val memory");
    free(new_vector->val);
    exit(1);
  }
  return new_vector;
}

void free_vector(Vector *v) {
  if (v->val != NULL) {
    free(v->val);
  }
  free(v);
}

//0ベクトルを返す
Vector *zero_vector(int dim) {
  Vector *zero_vector = (Vector *)malloc(sizeof(Vector));
  if (zero_vector == NULL) {
    printf("Failed to allocate structure memory(zero)");
    free(zero_vector);
    exit(1);
  }
  zero_vector->dim = dim;
  zero_vector->val = (double *)calloc(dim, sizeof(double));
  if (zero_vector->val == NULL) {
    printf("Failed to allocate val memory(zero)");
    free(zero_vector->val);
    exit(1);
  }
  return zero_vector;
}

void prind_vector(Vector *v) {
  if (v->val == NULL) {
    printf("Data NULL");
    exit(1);
  }
  for (int i = 0; i < v->dim; i++) {
    printf("%f\n", v->val[i]);
  }
}


Vector *linear_combination(double a, Vector *u, double b, Vector *v) {
  if (u->dim != v->dim) {
    printf("Different vector size");
    exit(1);
  }

  Vector *w = create_vector(u->dim);
  for (int i = 0; i < w->dim; i++) {
    w->val[i] = a * u->val[i] + b * v->val[i];
  }
  return w;
}

int main() {
  Vector *u = create_vector(3);
  u->val[0] = 1; u->val[1] = 0; u->val[2] = -1;
  Vector *v = create_vector(3);
  v->val[0] = 2, v->val[1] = 5; v->val[2] = 1;
  Vector *w = linear_combination(3, u, -2, v);
  for (int i = 0; i < w->dim; i++) {
    printf("%.2f\n", w->val[i]);
  }
  free_vector(u);
  free_vector(v);
  free_vector(w);
  return 0;
}
