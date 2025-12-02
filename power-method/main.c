#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int rows;
  int cols;
  double *value;
} Matrix;

typedef struct {
  int dim;
  double *value;
} Vector;

void free_matrix(Matrix *m) {
  if (m->value != NULL) {
    free(m->value);
  }
  free(m);
}

void free_vector(Vector *v) {
  if (v->value != NULL) {
    free(v->value);
  }
  free(v);
}

Matrix *create_matrix(int rows, int cols) {
  Matrix *m = (Matrix *)malloc(sizeof(Matrix));
  if (m == NULL) {
    printf("Failed to allocate Matrix memory\n");
    exit(1);
  }
  m->rows = rows;
  m->cols = cols;
  m->value = (double *)calloc(rows * cols, sizeof(double));
  if (m->value == NULL) {
    printf("Failed to allocate Matrix value memory\n");
    free_matrix(m);
    exit(1);
  }
  return m;
}

Vector *create_vector(int dim) {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  if (v == NULL) {
    printf("Failed to allocate Vector memory\n");
    exit(1);
  }
  v->dim = dim;
  v->value = (double *)calloc(dim, sizeof(double));
  if (v->value == NULL) {
    printf("Failed to allocate Vector value memory\n");
    free_vector(v);
    exit(1);
  }
  return v;
}

// set matrix element
void sme(Matrix *m, int row, int col, double value) {
  if (row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error(sme)");
    exit(1);
  }
  int k = row * m->cols + col;
  m->value[k] = value;
}

// set vector element
void sve(Vector *v, int index, double value) {
  if (index < 0 || index > v->dim) {
    printf("Value Error(sve)");
    exit(1);
  }
  v->value[index] = value;
}

// get matrix element
double gme(Matrix *m, int row, int col) {
  if (row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error(gme)\n");
    exit(1);
  }
  int k = row * m->cols + col;
  double ans = m->value[k];
  return ans;
}

// get vector element
double gve(Vector *v, int index) {
  if (index < 0 || index > v->dim) {
    printf("Value Error(gve)");
    exit(1);
  }
  double ans = v->value[index];
  return ans;
}

// 行列ベクトル積 
Vector *mat_vec_mult(Matrix *A, Vector *v) {
  if (A->cols != v->dim) {
    printf("Different size(mat_vec)\n");
    exit(1);
  }
  Vector *ans = create_vector(v->dim);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      ans->value[i] += gme(A, i, j) * gve(v, j);
    }
  }
  return ans;
}

//ループ内で使用するmat_vec_mult
void mat_vec_mult_overwrite(Matrix *A, Vector *v, Vector *result) {
  if (A->cols != v->dim) {
    printf("Different size(mat-overwrite)\n");
    exit(1);
  }

  // 修正: 初期化プロセス. 前回の計算結果が残らないよう.
  for (int i = 0; i < A->rows; i ++) {
    result->value[i] = 0.0;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      result->value[i] += gme(A, i, j) * gve(v, j);
    }
  }
  
}

// ベクトルの値をコピー
void copy_vector_values(Vector *src, Vector *dst) {
  if (src->dim != dst->dim) {
    printf("Different dim\n");
    exit(1);
  }
  for (int i = 0; i < src->dim; i++) {
    dst->value[i] = src->value[i];
  }
}

// 行列積
Matrix *mat_mult(Matrix *A, Matrix *B) {
  if (A->cols != B->rows) {
    printf("Different size of Matrixes");
    exit(1);
  }

  Matrix *C = create_matrix(A->rows, B->cols);
  for (int i = 0; i < C->rows; i++) {
    for (int j = 0; j < C->cols; j++) {
      double tmp_ans = 0;
      for (int k = 0; k < A->cols; k++) {
        tmp_ans += gme(A, i, k) * gme(B, k, j);
      }
      sme(C, i, j, tmp_ans);
    }
  }
  return C;
}

// ノルム計算
double norm(Vector *v) {
  double tmp_ans = 0;
  for (int i =  0; i < v->dim; i++) {
    tmp_ans += v->value[i] * v->value[i];
  }
  double ans = sqrt(tmp_ans);
  return ans;
}

// 内積計算
double inner_product(Vector *u, Vector*v) {
  if (u->dim != v->dim) {
    printf("Different dim");
    exit(1);
  }
  double ans = 0;
  for (int i = 0; i < u->dim; i++) {
    ans += u->value[i] * v->value[i];
  }
  return ans;
}

// べき乗法power method
double power_method(Matrix *A, int max_iter, double epsilon) {
  Vector *v = create_vector(A->cols);
  // vを正規化
  for (int index = 0; index < v->dim; index++) {
    v->value[index] = 1;
  }

  double v_norm = norm(v);
  for (int i = 0; i < v->dim; i++) {
    v->value[i] /= v_norm;
  }

  Vector *w = create_vector(v->dim);
  double mu = 0;
  double old_mu = 0;
  for (int k = 0; k < max_iter; k++) {
    // w = A v で上書き
    mat_vec_mult_overwrite(A, v, w);
    // mu = v \cdot w (vは長さ1なので分母不要)
    mu = inner_product(v, w);

    double w_norm = norm(w);
    // wを正規化(次のvを正規化)
    for (int i = 0; i < w->dim; i++) {
      w->value[i] /= w_norm;
    }

    if (fabs(mu - old_mu) < epsilon) {
      break;
    }
    // v に w をコピー(v^{k-1})
    copy_vector_values(w, v);
    old_mu = mu;

  }
  free_vector(v);
  free_vector(w);
  return mu;
}

int main() {
  double iter_step = 10000;
  double epsilon = 0.0001;

  Matrix *A = create_matrix(2, 2);
  sme(A, 0, 0, 6);
  sme(A, 0, 1, -1);
  sme(A, 1, 0, 2);
  sme(A, 1, 1, 3);

  double ans = power_method(A, iter_step, epsilon);
  printf("%.3f\n", ans);

  return 0;
}
