# SSP_energy_hardware_bio
## how to run hardware algorithims

run file: driverHorowitz-Naive.c
example (on a linux machine): gcc driverHorowitz-Naive.c -o driverHorowitz-Naive.exe  && ./driverHorowitz-Naive.exe

## how to run biological estimation program
first run: targets.py
then run: parse_txt.py 

To determine how many CPU cores are running on a machine run: cat /proc/cpuinfo | grep "cpu cores"
