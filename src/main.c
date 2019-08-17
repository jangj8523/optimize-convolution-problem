#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>




void _run_convolution(unsigned int row, unsigned int col)
{
  unsigned char filter [] = {-1, 0, 1};
  unsigned char m_matrix [row][col];
  srand(0);
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
        m_matrix[i][j] = (unsigned char) (rand()%256);
    }
  }


}



int main()
{
  printf("========= RUNNING Convolve Optimization =========!\n");
  unsigned int row;
  unsigned int col;

  printf( "Enter the size of row: ");
  scanf("%d", &row);
  printf( "Enter the size fo col: ");
  scanf("%d", &col);

  printf ("\n ========= SIMULATING convolution =========\n");
  printf ("With %d rows and %d cols\n", row, col);

  _run_convolution(row, col);

  return 0;
}

#endif
