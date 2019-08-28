# optimize_convolution_problem

Implementation approach: <br /> 
1). Dynamically allocate three matrices (Dx, Dy, M) <br /> 
2). Randomly initialize unsigned char for all entries of matrix M using rand() % 256  
3). Convolve and fill in the Dx, Dy matrices in O(n^2) each:  <br /> 
  - aimed for simplicity to avoid writing new functions (or even inline functions)
  - leveraged the fact that the filter is -1, 0, 1. So each Dx[i][j] was the difference M[1][j+1] subtracted by M[i][j-1].
  and therefore stored all my integers as shorts (2 bytes) rather than as a signed int (4 bytes)
  
Future Optimization:  <br /> 
1). Multithreading capabilities: I have written my |fill_convolution_table| function to take specific index range as argument so that the program can later multithread and fill in a certain submatrix of Dx or Dy (the convolution along each row and column do not take shared resources so we don't need to worry too much about race conditions here). <br /> 
2). Compiler optimization: the program is currently compiled using gcc -O3 flag <br /> 
3). Specify the program to run on GPU (I do want to try this using my own GPU computer) <br /> 
4). Explore quantizing the integer even more!! -> Because the arithmetic operations were quite simple, we did not have to perform any bitwise operations but integer storage definitely takes up lots of space when the matrices have a dimension of a million by million.  <br /> 


MultiThreading Results: <br />
- Description: Implemented the thread pool class so that the program can leverage multi-threading to compute multiple convolution. With 4 threads,the processor takes up 20% of its maximum capacity. The time took to compute finish all the tasks ( 10000 by 10000 matrix, with 50 iterations) was 1335.287249 seconds. The singlethreaded program only took up 6% of its maximum capacity and took 111.048120 seconds. The reason why multithreading took longer than single-threading approach is having 100,000 by 100,000 matrix of signed int takes up a lot of RAM. So the program wouldn't be able to multithread.

However, computing the convolution of 100 by 100 matrix over 50,000 iteration. A single threaded approach took 10.115997 seconds while a multithreaded approach took  131.982776 seconds.
