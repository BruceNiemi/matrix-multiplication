#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  Vcounter top;
  Verilated::traceEverOn(true);
  VerilatedVcdC tfp;
  top.trace(&tfp, 99);
  tfp.open("wave.vcd");

  top.clk = 0;
  top.rst = 1;

  for (int i = 0; i < 20; i++) {
    if (i == 2)
      top.rst = 0;      // release reset
    top.clk = !top.clk; // toggle clock
    top.eval();
    tfp.dump(i);
    std::cout << "Time " << i << ": count = " << (int)top.count << std::endl;
  }

  tfp.close();
  return 0;
}
