#include "Vmatrix_multiplication.h"

#include "verilated.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void matrixMultiply(uint8_t A[4][4], uint8_t B[4][4], uint16_t C[4][4]) {
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      C[i][j] = 0;
      for (size_t k = 0; k < 4; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void runTest(Vmatrix_multiplication *dut, uint8_t A[4][4], uint8_t B[4][4],
             const char *name) {

  uint16_t expected[4][4];

  // copy code into the module
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      dut->matrixA[i][j] = A[i][j];
      dut->matrixB[i][j] = B[i][j];
    }
  }

  dut->eval();

  matrixMultiply(A, B, expected);

  bool pass = true;
  std::cout << "\n===" << name << " ===\n";
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << "C[" << i << "][" << j << "] = HW:" << dut->matrixC[i][j]
                << "  REF:" << expected[i][j];

      if (dut->matrixC[i][j] != expected[i][j]) {
        std::cout << "  <-- FAIL";
        pass = false;
      }

      std::cout << "\n";
    }
  }

  std::cout << (pass ? "PASS\n" : "FAIL\n");
}

int main(int argc, char const *argv[]) {
  auto dut = new Vmatrix_multiplication;

  uint8_t zeroA[4][4] = {{0}};
  uint8_t zeroB[4][4] = {{0}};
  runTest(dut, zeroA, zeroB, "Zero Matrix Test");

  uint8_t I[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  uint8_t testIA[4][4] = {
      {2, 3, 1, 5}, {4, 1, 0, 2}, {9, 8, 3, 1}, {1, 1, 1, 1}};

  runTest(dut, testIA, I, "Identity Matrix Test");

  srand(time(nullptr));
  uint8_t randA[4][4];
  uint8_t randB[4][4];

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      randA[i][j] = rand() % 10;
      randB[i][j] = rand() % 10;
    }

  runTest(dut, randA, randB, "Random Matrix Test");

  uint8_t boundA[4][4];
  uint8_t boundB[4][4];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      boundA[i][j] = 127;
      boundB[i][j] = 127;
    }

  runTest(dut, boundA, boundB, "Boundary Overflow Test");

  return 0;
}
