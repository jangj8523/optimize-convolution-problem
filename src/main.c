#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "thread_pool.h"

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



void _run_convolution(void *args)
{
  // srand(0);

  size_t row = *(int *)args;
  size_t col = *((int*)args + 1);
  size_t loop = *((int*)args+2);
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

  // printf("\n================== RESULTS ===================\n");
  size_t i = 0;
  while (i < 9000) {
    start_time = clock();
    _fill_convolution_table(m_matrix, dx_matrix, row, total_size);
    end_time = clock();
    i+=1;
  }
  // printf("Time it took to compute Dx matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);

  while (i < 15000) {
    start_time = clock();
    _fill_convolution_table(m_matrix, dy_matrix, col, total_size);
    end_time = clock();
    i+=1;
  }
  // printf("Time it took to compute Dy matrix: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);

  //_print_m_matrix(dx_matrix, (row+2)*col);
  free(m_matrix);



  _search_min_max(dx_matrix, row*(col+2), dx_min_max);
  _search_min_max(dy_matrix, (row+2)*col, dy_min_max);

  // printf("Min value in Dx matrix: %hd\n", dx_min_max[0]);
  // printf("Max value in Dx matrix: %hd\n\n", dx_min_max[1]);
  //
  // printf("Min value in Dy matrix: %hd\n", dy_min_max[0]);
  // printf("Max value in Dy matrix: %hd\n", dy_min_max[1]);

  free(dx_matrix);
  free(dy_matrix);
  //
  // _free_dx_matrix(dx_matrix);
  // _free_dy_matrix(dy_matrix);
  printf("Done with work %ld\n", loop);
}



int main()
{
  printf("========= RUNNING Convolve Optimization =========!\n");
  size_t row;
  size_t col;
  thread_pool_t *thread_pool = create_thread_pool(8);


  while (true)
  {
    printf( "Enter the size of row: ");
    scanf("%zd", &row);
    printf( "Enter the size of col: ");
    scanf("%zd", &col);
    printf ("\n ========= SIMULATING convolution =========\n");
    printf ("With %zu rows and %zu cols\n", row, col);
    if (row != 0 && col != 0)
      break;
    printf("========== ROW AND COL CANNOT BE ZERO ========\n");
  }


  clock_t start_time = clock();
  for (size_t i = 1; i <= 50; i++)
  {
    int *args = malloc(sizeof(int) * 3);
    *args = row;
    *(args+1) = col;
    *(args+2) = i;
    threadpool_add_work(thread_pool, _run_convolution, args);
  }
  threadpool_wait(thread_pool);
  clock_t end_time = clock();

  printf("Time it took to compute finish all the tasks: %f seconds\n", ((double)(end_time - start_time))/CLOCKS_PER_SEC);
  threadpool_destroy(thread_pool);
  printf ("\n ========= SIMULATION done =========\n");
  // free (args);


  return 0;
}

#endif
