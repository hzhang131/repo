transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/Mem2IO.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/tristate.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/register.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/ISDU.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/SLC3_2.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/test_memory.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab5project {C:/Quartusprime/Lab projects/lab5project/HexDriver.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/slc3.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/memory_contents.sv}
vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/lab6_toplevel.sv}

vlog -sv -work work +incdir+C:/Quartusprime/Lab\ projects/lab6project {C:/Quartusprime/Lab projects/lab6project/testbench(2).sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  testbench

add wave *
view structure
view signals
run 10000 ns
