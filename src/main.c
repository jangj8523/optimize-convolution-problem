#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef enum { FALSE, TRUE } boolean;


// Unused
// const signed char filter [3] = {-1, 0, 1};






void *_init_matrix(size_t type_size, size_t row, size_t col)
{
  void *m_matrix;
  m_matrix = malloc(row * col * sizeof(type_size));
  return m_matrix;
}

void _populate_m_matrix(unsigned char *m_matrix, size_t total_size)
{
  size_t counter = 0;
  for (size_t i = 0; i < total_size; i++)
  {
    m_matrix[i] = (unsigned char) (rand()%256);
  }
}

// Debugging purposes
void _print_m_matrix(int *m_matrix, size_t total_size)
{
  for (size_t i = 0; i < total_size; i++)
  {
    printf ("value %d\n", m_matrix[i]);
  }
}


void _fill_convolution_table(unsigned char* m_matrix, int *matrix, size_t fixed_axis, size_t total_size)
{
  size_t next_point = 0;
  size_t curr_point = -2;
  for (size_t i = 0; i < total_size; i++)
  {

    if(i == next_point) {
      curr_point+=2;
      next_point+=fixed_axis;
      matrix[curr_point] = 0;
      matrix[curr_point+1] = 0;
    }

    matrix[curr_point] -= m_matrix[i];
    matrix[curr_point+2] = m_matrix[i];
    curr_point+=1;
  }
}

void _search_min_max(int *matrix, size_t total_size, int arr[])
{
  signed int max_val = INT_MIN;
  signed int min_val = INT_MAX;
  for (size_t i = 0; i < total_size; i++)
  {
    if (max_val < matrix[i])
    {
      max_val = matrix[i];
    }
    if (min_val > matrix[i])
    {
      min_val = matrix[i];
    }
  }
  arr[0] = min_val;
  arr[1] = max_val;

}



void _run_convolution(size_t row, size_t col)
{
  // srand(0);
  clock_t start_time;
  clock_t end_time;
  int dx_min_max [2];
  int dy_min_max [2];
  size_t total_size = row * col;

  unsigned char *m_matrix = (unsigned char *)_init_matrix(sizeof(unsigned char), row, col);
  int *dx_matrix = (int *)_init_matrix(sizeof(int), row, col+2);
  int *dy_matrix = (int *)_init_matrix(sizeof(int), row+2, col);
  _populate_m_matrix(m_matrix, total_size);
  // _print_m_matrix(m_matrix);
  // free_m_matrix(m_matrix);

  printf("\n================== RESULTS ===================\n");

  start_time = clock();
  _fill_convolution_table(m_matrix, dx_matrix, row, total_size);
  end_time = clock();
  printf("Time it took to compute Dx matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);


  start_time = clock();
  _fill_convolution_table(m_matrix, dy_matrix, col, total_size);
  end_time = clock();
  printf("Time it took to compute Dy matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);

  //_print_m_matrix(dx_matrix, (row+2)*col);
  free(m_matrix);


  //
  //
  // printf("Time it took to compute Dx matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);
  // start_time = clock();
  // _fill_convolution_table(m_matrix, dy_matrix, 0, COL-1, FALSE);
  // end_time = clock();
  //
  // printf("Time it took to compute Dy matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);
  // _free_m_matrix(m_matrix);
  //
  //
  _search_min_max(dx_matrix, row*(col+2), dx_min_max);
  _search_min_max(dy_matrix, (row+2)*col, dy_min_max);

  printf("Min value in Dx matrix: %hd\n", dx_min_max[0]);
  printf("Max value in Dx matrix: %hd\n\n", dx_min_max[1]);

  printf("Min value in Dy matrix: %hd\n", dy_min_max[0]);
  printf("Max value in Dy matrix: %hd\n", dy_min_max[1]);

  free(dx_matrix);
  free(dy_matrix);
  //
  // _free_dx_matrix(dx_matrix);
  // _free_dy_matrix(dy_matrix);


}



int main()
{
  printf("========= RUNNING Convolve Optimization =========!\n");
  size_t row;
  size_t col;

  printf( "Enter the size of row: ");
  scanf("%zd", &row);
  printf( "Enter the size of col: ");
  scanf("%zd", &col);
  printf ("\n ========= SIMULATING convolution =========\n");
  printf ("With %zu rows and %zu cols\n", row, col);

  _run_convolution(row, col);
  printf ("\n ========= SIMULATION done =========\n");


  return 0;
}

#endif
