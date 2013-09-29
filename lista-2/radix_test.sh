#!/bin/bash



for(( i=100000; i<=2000000; i=i+100000 ))
do
	echo -n "$i "
	./bin/radix_sort $i
done

