#!/bin/bash

FILE=resources/heapsort_benchmark_data.csv

rm -f $FILE

echo -e "Starting heapsort benchmark for LOCAL structure and SEPARATED structure.\n"

echo "Demostration before:"
echo -e "$(bin/heapsort 7 Y)\n"

echo "Now the performance testes:"
for ((SIZE=10; SIZE < 5000000; SIZE*=2))
do
	echo "Size = $SIZE..."
	echo "$(bin/heapsort $SIZE N)" | sed -e 's/\./,/g' >> $FILE
done
echo -e "\nFinished heapsort benchmark, result is on file $FILE.\nThe CSV columns are \"vector_size;local_structure;separated_structure\""