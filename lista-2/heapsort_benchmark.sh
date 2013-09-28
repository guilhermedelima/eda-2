#!/bin/bash

FILE=resources/heapsort_benchmark_data.csv

rm -f $FILE

echo "Starting heapsort benchmark for LOCAL structure and SEPARATED structure"
for SIZE in 10 25 50 100 250 500 1000 10000 25000 50000 
do
	echo "Size = $SIZE..."
	echo "$(bin/heapsort $SIZE)" | sed -e 's/\./,/g' >> $FILE
done
echo -e "\nFinished heapsort benchmark, result is on file $FILE.\nThe CSV columns are \"vector_size;local_data;separated_data\""