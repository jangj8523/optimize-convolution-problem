# optimize_convolution_problem


Implementation approach:
1). Dynamically allocate three matrices (Dx, Dy, M)
2). Randomly initialize unsigned char for all entries of matrix M using rand() % 256 
3). Convolve and fill in the Dx, Dy matrices in O(n^2) each: 
  - aimed for simplicity to avoid writing new functions (or even inline functions)
  - leveraged the fact that the filter is -1, 0, 1. So each Dx[i][j] was the difference M[1][j+1] subtracted by M[i][j-1].
  and therefore stored all my integers as shorts (2 bytes) rather than as a signed int (4 bytes)
  
Future Optimization: 
1). Multithreading capabilities: I have written my |fill_convolution_table| function to take specific index range as argument so that the program can later multithread and fill in a certain submatrix of Dx or Dy (the convolution along each row and column do not take shared resources so we don't need to worry too much about race conditions here). <br /> 
2). Compiler optimization: the program is currently compiled using gcc -O3 flag <br /> 
3). Specify the program to run on GPU (I do want to try this using my own GPU computer)
4). Explore quantizing the integer even more!! -> Because the arithmetic operations were quite simple, we did not have to perform any bitwise operations but integer storage definitely takes up lots of space when the matrices have a dimension of a million by million. 
