#!/bin/bash

FILE=resources/heapsort_benchmark_data.csv

rm -f $FILE

echo -e "Starting heapsort benchmark for LOCAL structure and SEPARATED structure.\n"

echo "Demostration before:"
echo -e "$(bin/heapsort 7 Y)\n"

echo "Now the performance testes:" 
echo "Size;Heapsort in-place;Heapsort not-in-place" >> $FILE
for ((SIZE=10000; SIZE <= 1000000; SIZE+=10000))
do
	echo "Size = $SIZE..."
	echo "$(bin/heapsort $SIZE N)" | sed -e 's/\./,/g' >> $FILE
done
echo -e "\nFinished heapsort benchmark, result is in file $FILE."