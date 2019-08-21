#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>

#define LEFT_BIT 128


typedef enum { FALSE, TRUE } boolean;
static size_t row;
static size_t col;
const unsigned char filter [3] = {-1, 0, 1};




void **_init_matrix(int num_elem)
{
  void **m_matrix;
  int *dummy_pointer;
  m_matrix = malloc(row * sizeof(dummy_pointer));
  for (size_t i = 0; i < row; i++) {
    *(m_matrix + (i*num_elem)) = calloc(col, num_elem);
  }
  return m_matrix;
}

void **_init_dx_matrix(int num_elem)
{
  void **m_matrix;
  int *dummy_pointer;
  m_matrix = malloc(row * sizeof(dummy_pointer));
  size_t num_col = col+2;
  for (size_t i = 0; i < row; i++) {
    *(m_matrix + (i*num_elem)) = calloc(num_col, num_elem);
  }
  return m_matrix;
}

void **_init_dy_matrix(int num_elem)
{
  void **m_matrix;
  int *dummy_pointer;
  size_t num_row = row + 2;
  m_matrix = malloc(num_row * sizeof(dummy_pointer));
  for (size_t j = 0; j < num_row; j++)
  {
    *(m_matrix + (j*num_elem)) = calloc(col, num_elem);
  }
  return m_matrix;
}




void _populate_m_matrix(unsigned char **m_matrix)
{
  for (size_t i = 0; i < row; i++)
  {
    for (size_t j = 0; j < col; j++)
    {
        m_matrix[i][j] = (unsigned char) (rand()%256);
    }
  }
}

void _print_m_matrix(unsigned char ** m_matrix)
{
  for (size_t i = 0; i < row; i++)
  {
    for (size_t j = 0; j < col; j++)
    {
        printf ("value %hhu\n", m_matrix[i][j]);
    }
  }
}



void _fill_convolution_table(unsigned char **m_matrix, signed int **matrix, size_t start, size_t end, boolean isRow)
{
  if (isRow)
  {
    for (size_t i = start; i <= end; i++)
    {
      for (size_t j = 0; j < col; j++)
      {
        // printf("%zu %zu\n", i, j);
        // size_t counter = 0;
        // matrix[i][j] += ((filter[0] + m_matrix[i][j]) % 255);
        // if (j+2 < col)
        //   matrix[i][j+2] += m_matrix[i][j];
      }
    }
  }
  else
  {

  }
}

void _run_convolution()
{
  srand(0);
  unsigned char **m_matrix = (unsigned char **)_init_matrix(sizeof(unsigned char));
  signed int **dx_matrix = (signed int **)_init_dx_matrix(sizeof(signed int));
  signed int **dy_matrix = (signed int **)_init_dy_matrix(sizeof(signed int));
  _populate_m_matrix(m_matrix);
  // _print_m_matrix(m_matrix);

  _fill_convolution_table(m_matrix, dx_matrix, 0, row-1, TRUE);





  // m_matrix: 2D _run_convolution
  // x[k]   =  [-1, 0, 1]
  // h[j-k] =  [a, b, c, d, e]
  // x[j] * h[j] = x[k] * h[j-k]
  // sum over: x[k] * x[j-k]


}



int main()
{
  printf("========= RUNNING Convolve Optimization =========!\n");
  // static size_t row;
  // static size_t col;

  printf( "Enter the size of row: ");
  scanf("%zd", &row);
  printf( "Enter the size fo col: ");
  scanf("%zd", &col);
  printf ("\n ========= SIMULATING convolution =========\n");
  printf ("With %zu rows and %zu cols\n", row, col);

  _run_convolution();

  return 0;
}

#endif
