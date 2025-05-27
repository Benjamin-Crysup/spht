#!/bin/bash

mkdir -p results/plinko

echo Seeds > results/plinko/seed1.txt

NUMINIT=21
STARTA=10
PROBA=0.5
PROBB=0.5

for STARTB in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
do
	for NUMSTEP in 1 2 3 4 5
	do
		ran=$(head -c8 /dev/urandom | od -An -vtu8)
		echo $ran >> results/plinko/seed1.txt
		../spht/builds/bin_x64_linux/spht plinko --zero-card $NUMINIT --steps-A $NUMSTEP --steps-B $NUMSTEP --add-A $PROBA --add-B $PROBB --start-A $STARTA --start-B $STARTB --nrepeat 65536 --nnull 16384 --nstat 16384 --nmcmc 1280 --thread 256 --seed $ran | gzip > results/plinko/res_"$NUMSTEP"_"$STARTA"_"$STARTB"_"$PROBA"_"$PROBB".tsv.gz 
	done
done

