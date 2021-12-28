#!/bin/bash
lower=3
upper=30
testCount=5
rm result.txt

for (( size=$lower; size<$upper; size++ ))
do
    rm result$size.txt
done

for (( size=$lower; size<$upper; size++ ))
do
    echo "Current size - $size"
    echo "Calc for $size" >> result.txt

    ./test-gen2 $testCount $size > test.txt
    ./main >> result.txt
done
printf "\n"