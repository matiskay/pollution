#define BOMB_MARK 2
#define POLLUTION_MARK 100
#define ASCII_CODE_FOR_ZERO 48
#define END_OF_LINE '\n'

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

float matrix_get(Matrix* mat, int i, int j);

void matrix_set(Matrix* mat, int i, int j, float v);

int matrix_number_of_rows(Matrix* mat);

int matrix_number_of_columns(Matrix* mat);

void matrix_display(Matrix* mat);

void matrix_display_integers(Matrix* mat);

int matrix_equal(Matrix* mat1, Matrix* mat2);

