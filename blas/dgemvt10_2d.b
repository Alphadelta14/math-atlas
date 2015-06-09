ROUTINE ATL_UGEMV;
   PARAMS :: M, N, A, lda, X, Y;
   INT :: M, N, lda;
   DOUBLE_PTR :: X, Y;
   DOUBLE_ARRAY [*][lda] :: A;
   UNROLL_ARRAY :: A(*,10);
ROUT_LOCALS
   INT :: i, j, ldam;
   DOUBLE :: y0, y1, y2, y3, y4, y5, y6, y7, y8, y9; 
   DOUBLE :: a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, x0;
ROUT_BEGIN  
   ldam = lda * 10;
   ldam = ldam - M;
   j = N;
   NLOOP:
      y0 = Y[0];
      y1 = Y[1];
      y2 = Y[2];
      y3 = Y[3];
      y4 = Y[4];
      y5 = Y[5];
      y6 = Y[6];
      y7 = Y[7];
      y8 = Y[8];
      y9 = Y[9];

      LOOP i = 0, M
      MUTUALLY_ALIGNED(32) :: *;
      LOOP_BODY
         x0 = X[0];

         a0 = A[0][0];
         y0 += a0 * x0;

         a1 = A[0][1];
         y1 += a1 * x0;

         a2 = A[0][2];
         y2 += a2 * x0;

         a3 = A[0][3];
         y3 += a3 * x0;

         a4 = A[0][4];
         y4 += a4 * x0;
         
         a5 = A[0][5];
         y5 += a5 * x0;
         
         a6 = A[0][6];
         y6 += a6 * x0;
         
         a7 = A[0][7];
         y7 += a7 * x0;
         
         a8 = A[0][8];
         y8 += a8 * x0;
         
         a9 = A[0][9];
         y9 += a9 * x0;
         
         A += 1;
         X += 1;
      LOOP_END
      Y[0] = y0;
      Y[1] = y1;
      Y[2] = y2;
      Y[3] = y3;
      Y[4] = y4;
      Y[5] = y5;
      Y[6] = y6;
      Y[7] = y7;
      Y[8] = y8;
      Y[9] = y9;
      
      A += ldam;
      Y += 10;
      X = X-M;
      j = j - 10;
      IF (j > 0) GOTO NLOOP;
ROUT_END

