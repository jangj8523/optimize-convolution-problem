#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef enum { FALSE, TRUE } boolean;
static size_t ROW;
static size_t COL;

// Unused
// const signed char filter [3] = {-1, 0, 1};






void **_init_matrix(int num_elem)
{
  void **m_matrix;
  int *dummy_pointer;
  m_matrix = malloc(ROW * sizeof(dummy_pointer));
  for (size_t i = 0; i < ROW; i++) {
    *(m_matrix + (i*num_elem)) = calloc(COL, num_elem);
  }
  return m_matrix;
}

void **_init_dx_matrix(int num_elem)
{
  void **m_matrix;
  int **dummy_pointer;
  m_matrix = malloc(ROW * sizeof(dummy_pointer));
  size_t num_col = COL+2;
  for (size_t i = 0; i < ROW; i++) {
    *((int **)m_matrix + i) = calloc(num_col, num_elem);
  }
  printf ("size of dx matrix: row %zu, col %zu\n", ROW, num_col);
  return m_matrix;
}

void **_init_dy_matrix(int num_elem)
{
  void **m_matrix;
  int **dummy_pointer;
  size_t num_row = ROW + 2;
  m_matrix = malloc(num_row * sizeof(dummy_pointer));
  for (size_t j = 0; j < num_row; j++)
  {
    *((int**)m_matrix + j) = calloc(COL, num_elem);
  }
  printf ("size of dy matrix: row %zu, col %zu\n", num_row, COL);
  return m_matrix;
}




void _populate_m_matrix(unsigned char **m_matrix)
{
  for (size_t i = 0; i < ROW; i++)
  {
    for (size_t j = 0; j < COL; j++)
    {
        m_matrix[i][j] = (unsigned char) (rand()%256);
    }
  }
}


// Debugging purposes
void _print_m_matrix(unsigned char ** m_matrix)
{
  for (size_t i = 0; i < ROW; i++)
  {
    for (size_t j = 0; j < COL; j++)
    {
        printf ("value %hhu\n", m_matrix[i][j]);
    }
  }
}



void _fill_convolution_table(signed short int **matrix, unsigned char **m_matrix, size_t start, size_t end, boolean isRow)
{
  if (isRow)
  {
    for (size_t i = start; i <= end; i++)
    {
      for (size_t j = 0; j < COL; j++)
      {
        matrix[i][j] -= m_matrix[i][j];
        matrix[i][j+2] += m_matrix[i][j];
      }
    }
  }
  else
  {
    for (size_t i = 0; i < ROW; i++)
    {
      for (size_t j = start; j <= end; j++)
      {

        matrix[i][j] -= m_matrix[i][j];
        matrix[i+2][j] += m_matrix[i][j];

      }
    }
  }
}

void _free_m_matrix(unsigned char **m_matrix)
{
  for (size_t i = 0; i < ROW; i++)
  {
    free(m_matrix[i]);
  }
  free(m_matrix);
}

void _free_dx_matrix(signed short int ** dx_matrix)
{

  for (size_t i = 0; i < ROW; i++) {
    free(dx_matrix[i]);
  }
  free(dx_matrix);
}


void _free_dy_matrix(signed short int ** dy_matrix)
{
  size_t num_row = ROW + 2;
  for (size_t i = 0; i < num_row; i++) {
    free(dy_matrix[i]);
  }
  free(dy_matrix);
}



void _search_min_max_dx_matrix(signed short int **matrix, signed short int arr[])
{
  signed short int max_val = SHRT_MIN;
  signed short int min_val = SHRT_MAX;
  size_t new_col = COL+2;
  for (size_t i = 0; i < ROW; i++)
  {
    for (size_t j = 0; j < new_col; j++)
    {
      if (max_val < matrix[i][j])
      {
        max_val = matrix[i][j];
      }
      if (min_val > matrix[i][j])
      {
        min_val = matrix[i][j];
      }
    }
  }
  arr[0] = min_val;
  arr[1] = max_val;

}


void _search_min_max_dy_matrix(signed short int **matrix, signed short int arr[])
{
  signed int max_val = SHRT_MIN;
  signed int min_val = SHRT_MAX;
  size_t new_row = ROW+2;
  for (size_t i = 0; i < new_row; i++)
  {
    for (size_t j = 0; j < COL; j++)
    {
      if (max_val < matrix[i][j])
      {
        max_val = matrix[i][j];
      }
      if (min_val > matrix[i][j])
      {
        min_val = matrix[i][j];
      }
    }
  }
  arr[0] = min_val;
  arr[1] = max_val;
}


void _run_convolution()
{
  // srand(0);
  clock_t start_time;
  clock_t end_time;
  signed short int dx_min_max [2];
  signed short int dy_min_max [2];

  unsigned char **m_matrix = (unsigned char **)_init_matrix(sizeof(unsigned char));
  signed short int **dx_matrix = (signed short int  **)_init_dx_matrix(sizeof(signed int));
  signed short int **dy_matrix = (signed short int **)_init_dy_matrix(sizeof(signed int));
  _populate_m_matrix(m_matrix);
  // _print_m_matrix(m_matrix);
  // free_m_matrix(m_matrix);



  printf("\n================== RESULTS ===================\n");
  start_time = clock();
  _fill_convolution_table(dx_matrix, m_matrix, 0, ROW-1, TRUE);
  end_time = clock();
  printf("Time it took to compute Dx matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);
  start_time = clock();
  _fill_convolution_table(dy_matrix, m_matrix, 0, COL-1, FALSE);
  end_time = clock();

  printf("Time it took to compute Dy matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);
  _free_m_matrix(m_matrix);


  _search_min_max_dx_matrix(dx_matrix, dx_min_max);
  _search_min_max_dy_matrix(dy_matrix, dy_min_max);

  printf("Min value in Dx matrix: %hd\n", dx_min_max[0]);
  printf("Max value in Dx matrix: %hd\n\n", dx_min_max[1]);

  printf("Min value in Dy matrix: %hd\n", dy_min_max[0]);
  printf("Max value in Dy matrix: %hd\n", dy_min_max[1]);

  _free_dx_matrix(dx_matrix);
  _free_dy_matrix(dy_matrix);


}



int main()
{
  printf("========= RUNNING Convolve Optimization =========!\n");
  printf( "Enter the size of row: ");
  scanf("%zd", &ROW);
  printf( "Enter the size fo col: ");
  scanf("%zd", &COL);
  printf ("\n ========= SIMULATING convolution =========\n");
  printf ("With %zu rows and %zu cols\n", ROW, COL);

  _run_convolution();
  printf ("\n ========= SIMULATION done =========\n");


  return 0;
}

#endif
