#!/bin/bash

mkdir -p results/flip

echo Seeds > results/flip/seeds.txt

for FLIPA in 0.9375 0.8750 0.7500 0.5000 0.2500 0.1250 0.0625
do
	for FLIPB in 0.9375 0.8750 0.7500 0.5000 0.2500 0.1250 0.0625
	do
		ran=$(head -c8 /dev/urandom | od -An -vtu8)
		echo $ran >> results/flip/seeds.txt
		../spht/builds/bin_x64_linux/spht flippy --flip-A $FLIPA --flip-B $FLIPB --nrepeat 65536 --thread 256 --seed $ran | gzip > results/flip/res_"$FLIPA"_"$FLIPB".tsv.gz
	done
done


