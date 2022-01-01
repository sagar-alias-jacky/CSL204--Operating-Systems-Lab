#!/bin/bash

echo -n "Enter a number: "
read num

if [ num == 0 -o num == 1 ]; then
	echo "$num factorial is 1"
else
	fact=1

	for ((i = 2; i <= num; i++)); do
		fact=$((fact * i))
	done

	echo "$num factorial is $fact"
fi
