#!/bin/bash

mkdir -p results/drift

#echo Seeds > results/drift/seed2.txt

NUMSTEP=10
STARTA="0.50000"
TESTVALS="0.50000 0.50001 0.50010 0.50100 0.51000 0.60000 0.70000 0.80000 0.90000 0.50005 0.50050 0.50500 0.55000"
TESTDEVS="1.0 2.0 4.0 8.0 16.0"
CARCAP=1000.0
DELTRAT=1.0
NUMREAD=262144

TESTVALS="0.50005 0.50050 0.50500 0.55000"

for STARTB in $TESTVALS
do
	for NOISE in $TESTDEVS
	do
		ran=$(head -c8 /dev/urandom | od -An -vtu8)
		echo $ran >> results/drift/seed2.txt
		../spht/builds/bin_x64_linux/spht drift --start-A $STARTA --start-B $STARTB --cap-A $CARCAP --cap-B $CARCAP --noise-A $NOISE --noise-B $NOISE --dtdt0-A $DELTRAT --dtdt0-B $DELTRAT --steps-A $NUMSTEP --steps-B $NUMSTEP --reads-A $NUMREAD --reads-B $NUMREAD --nquad 4096 --nrepeat 4096 --nnull 4096 --nstat 4096 --nmcmc 81920 --seed $ran --thread 256 | gzip > results/drift/res_"$NUMSTEP"_"$NOISE"_"$STARTA"_"$STARTB"_"$NUMREAD".tsv.gz
	done
done


