# Top module
TOP = counter
TB_CPP = sim_main.cpp

# Default target: build and run
all: run

# Build and run simulation
run:
	verilator --cc $(TOP).v --exe $(TB_CPP) --trace
	make -C obj_dir -f V$(TOP).mk V$(TOP)
	./obj_dir/V$(TOP)

# Clean generated files
clean:
	rm -rf obj_dir wave.vcd
