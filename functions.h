float matrix_distance(Matrix*, Matrix*);

float matrix_maximun_value(Matrix*);

Matrix* create_board(Matrix*);

Matrix* create_initial_board(void);

void copy_board(Matrix*, Matrix*);

float stop_criterion(Matrix*, Matrix*);

float make_operation(Matrix*, Matrix*, int, int);

float left(Matrix*, int, int);

float right(Matrix*, int, int);

float top(Matrix*, int, int);

float bottom(Matrix*, int, int);

void print_board(char*, Matrix*);

void write_data_to_file(float);

float stop_condition;

Matrix* create_initial_board_from_file(char*);

FILE* file_stop_criterion;

int is_empty_line(const char *);
