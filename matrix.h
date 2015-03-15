/* ADT: Matrix */
/* Investigate why you need the structure here. */

struct matrix {
  int number_of_rows;
  int number_of_columns;
  float* v;
};

typedef struct matrix Matrix;

Matrix* matrix_create(int n, int m);

void matrix_free(Matrix* mat);

float matrix_access(Matrix* mat, int i, int j);

void matrix_set(Matrix* mat, int i, int j, float v);

int matrix_number_of_rows(Matrix* mat);

int matrix_number_of_columns(Matrix* mat);
