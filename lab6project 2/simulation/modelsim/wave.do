onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix hexadecimal /testbench/Clk
add wave -noupdate -radix hexadecimal /testbench/S
add wave -noupdate -radix hexadecimal /testbench/Run
add wave -noupdate -radix hexadecimal /testbench/Reset
add wave -noupdate -radix hexadecimal /testbench/Continue
add wave -noupdate -radix hexadecimal /testbench/LED
add wave -noupdate -radix hexadecimal /testbench/HEX0
add wave -noupdate -radix hexadecimal /testbench/HEX1
add wave -noupdate -radix hexadecimal /testbench/HEX2
add wave -noupdate -radix hexadecimal /testbench/HEX3
add wave -noupdate -radix hexadecimal /testbench/HEX4
add wave -noupdate -radix hexadecimal /testbench/HEX5
add wave -noupdate -radix hexadecimal /testbench/HEX6
add wave -noupdate -radix hexadecimal /testbench/HEX7
add wave -noupdate -radix hexadecimal /testbench/CE
add wave -noupdate -radix hexadecimal /testbench/UB
add wave -noupdate -radix hexadecimal /testbench/LB
add wave -noupdate -radix hexadecimal /testbench/OE
add wave -noupdate -radix hexadecimal /testbench/WE
add wave -noupdate -radix hexadecimal /testbench/ADDR
add wave -noupdate -radix hexadecimal /testbench/Data
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/PCR/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R0/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R1/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R2/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R3/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R4/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R5/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R6/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/regf/R7/out
add wave -noupdate /testbench/sim/my_slc/MARR/out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/ADDR1_out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/ADDR2_out
add wave -noupdate -radix hexadecimal /testbench/sim/my_slc/ADDR_out
add wave -noupdate /testbench/sim/my_slc/state_controller/State
add wave -noupdate /testbench/sim/my_slc/Imm6_ext
add wave -noupdate /testbench/sim/my_slc/IR
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {316814 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 223
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {285310 ps} {351528 ps}
