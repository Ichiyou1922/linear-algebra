#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int dim;
  double *value;
} Vector;

typedef struct {
  int rows;
  int cols;
  double *value;
} Matrix;

void free_vector(Vector *v) {
  if (v->value != NULL) {
    free(v->value);
  }
  free(v);
}

void free_matrix(Matrix *m) {
  if (m->value != NULL) {
    free(m->value);
  }
  free(m);
}

Vector *create_vector(int dim) {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  if (v == NULL) {
    printf("Failed to allocate Vector memory\n");
    exit(1);
  }
  v->value = (double *)calloc(dim, sizeof(double));
  if (v->value == NULL) {
    printf("Failed to allocate Vector value memory\n");
    free_vector(v);
    exit(1);
  } 
  return v;
}

Matrix *create_matrix(int rows, int cols) {
  Matrix *m = (Matrix *)malloc(sizeof(Matrix));
  if (m == NULL) {
    printf("Failed to allocate Matrix memory\n");
    exit(1);
  }
  m->value = (double *)calloc(rows * cols, sizeof(double));
  if (m->value == NULL) {
    printf("Failed to allocate Matrix value memory\n");
    free_matrix(m);
    exit(1);
  } 
  return m;
}

void sme(Matrix *m, int row, int col, double value) {
  if (row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error(sme)\n");
    exit(1);
  }
  int k = row * m->cols + col;
  m->value[k] = value;
}

// set matrix col
void smc(Matrix *Q, int j, Vector *q) {
  if (Q->rows != q->dim) {
    printf("Failed to put q to Q\n");
    exit(1);
  }
  for (int i = 0; i < Q->rows; i++) {
    sme(Q, i, j, q->value[i]);
  }
}

// get matrix element col
void gmec_over(Vector *u, Matrix *A, int col) {
  for (int i = 0; i < A->rows; i++) {
    int k = i * A->cols + col;
    u->value[i] = A->value[k];
  }
}

double inner_product(Vector *q, Vector *a) {
  if (q->dim != a->dim) {
    printf("Different size of Vector\n");
    exit(1);
  }
  double ans = 0;
  for (int i = 0; i < q->dim; i++) {
    ans += q->value[i] + a->value[i];
  }
  return ans;
}

double norm(Vector *u) {
  double ans = 0;
  for (int i = 0; i < u->dim; i++) {
    ans += u->value[i] * u->value[i];
  }
  return sqrt(ans);
}

Matrix *mat_mult(Matrix *A, Matrix *B) {
  if (A->cols != B->rows || A->rows != B->cols) {
    printf("Different size of Matrix\n");
    exit(1);
  }
  Matrix *ans = create_matrix(A->rows, B->cols);
  for (int i = 0; i < A->rows; i++) {
    for (int k = 0; k < i; k++) {
      for (int j = 0; j < A->cols; j++) {
        int l = i * A->cols + j;
        int m = j * B->cols + k;
        int s = i * ans->cols + k;
        ans->value[s] += A->value[l] * B->value[m];
      }
    }
  }
  return ans;
}

void qr_decomposition(Matrix *A, Matrix *Q, Matrix *R) {
  Vector *u = create_vector(A->rows);
  Vector *a = create_vector(A->rows);
  Vector *q = create_vector(A->rows);
  Vector *norm_q = create_vector(A->rows);
  double r = 0;

  for (int k = 0; k < A->cols; k++) {
    gmec_over(a, A, k);
    u = a;
    q->value[k] = u->value[k] / norm(u);
    for (int j = 0; j < k; j++) {
      r = inner_product(q, a);
      sme(R, j, k, r);
      u->value[k] -=  r * q->value[j];
    }
    norm_q->value[k] = q->value[k] / norm(q);
    sme(R, k, k, norm(u));
    smc(Q, k, norm_q);
  }
  free_vector(u);
  free_vector(a);
  free_vector(q);
  free_vector(norm_q);
}

void print_matrix(Matrix *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      int k = i * A->cols + j;
      printf("%f  ", A->value[k]);
      if (j == A->cols - 1) {
        printf("\n");
      }
    }
  }
}

int main() {
  Matrix *A = create_matrix(3, 3);
  sme(A, 0, 0, 1);
  sme(A, 0, 1, 1);
  sme(A, 0, 2, 0);
  sme(A, 1, 0, 1);
  sme(A, 1, 1, 0);
  sme(A, 1, 2, 1);
  sme(A, 2, 0, 0);
  sme(A, 2, 1, 1);
  sme(A, 2, 2, 1);
  
  Matrix *Q = create_matrix(3, 3);
  Matrix *R = create_matrix(3, 3);

  qr_decomposition(A, Q, R);
  printf("Q\n");
  print_matrix(Q);
  printf("n");
  print_matrix(R);

  Matrix *QR = create_matrix(3, 3);
  QR = mat_mult(Q, R);
  printf("QR\n");
  print_matrix(QR);
  
  /*
  Matrix *QTQ = create_matrix(3, 3);
  QTQ = mat_mult(Q)
  */
  free_matrix(A);
  free_matrix(Q);
  free_matrix(R);
  free_matrix(QR);
  //free_matrix(QTQ);
  return 0;
}
