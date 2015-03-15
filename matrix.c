#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

Matrix* matrix_create(int n, int m) {

  Matrix* mat = (Matrix *) malloc(sizeof(Matrix));

  if (mat == NULL) {
    printf("Not enough memory! \n");
    exit(1);
  }

  mat->number_of_rows = n;
  mat->number_of_columns = m;

  mat->v = (float *) malloc(n * m * sizeof(float));


  return mat;
}

void matrix_free(Matrix* mat) {
  free(mat->v);
  free(mat);
}

float matrix_access(Matrix* mat, int i, int j) {
  return mat->v[i * mat->number_of_columns + j];
}

void matrix_set(Matrix* mat, int i, int j, float v) {
  mat->v[i * mat->number_of_columns + j] = v;
}

int matrix_number_of_rows(Matrix* mat) {
  return mat->number_of_rows;
}

int matrix_number_of_columns(Matrix* mat) {
  return mat->number_of_columns;
}
