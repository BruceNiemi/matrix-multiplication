#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>

void M4x4_SSE(float *A, float *B, float *C) {
  __m128 row1 = _mm_load_ps(&B[0]);
  __m128 row2 = _mm_load_ps(&B[4]);
  __m128 row3 = _mm_load_ps(&B[8]);
  __m128 row4 = _mm_load_ps(&B[12]);
  for (int i = 0; i < 4; i++) {
    __m128 brod1 = _mm_set1_ps(A[4 * i + 0]);
    __m128 brod2 = _mm_set1_ps(A[4 * i + 1]);
    __m128 brod3 = _mm_set1_ps(A[4 * i + 2]);
    __m128 brod4 = _mm_set1_ps(A[4 * i + 3]);
    __m128 row = _mm_add_ps(
        _mm_add_ps(_mm_mul_ps(brod1, row1), _mm_mul_ps(brod2, row2)),
        _mm_add_ps(_mm_mul_ps(brod3, row3), _mm_mul_ps(brod4, row4)));
    _mm_store_ps(&C[4 * i], row);
  }
}

static void print_mat(const char *name, const float *M) {
  printf("%s:\n", name);
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c)
      printf("%8.3f ", M[r * 4 + c]);
    printf("\n");
  }
  printf("\n");
}

// gcc -O3 -msse -o test_simd mat_multi.c
int main(void) {
  /* 16-byte alignment for SSE loads/stores */
  float A[16] __attribute__((aligned(16))) = {1, 2,  3,  4,  5,  6,  7,  8,
                                              9, 10, 11, 12, 13, 14, 15, 16};
  float B[16] __attribute__((aligned(16))) = {16, 15, 14, 13, 12, 11, 10, 9,
                                              8,  7,  6,  5,  4,  3,  2,  1};
  float C[16] __attribute__((aligned(16)));

  print_mat("A", A);
  print_mat("B", B);

  M4x4_SSE(A, B, C);

  print_mat("C = A * B", C);
  return 0;
}