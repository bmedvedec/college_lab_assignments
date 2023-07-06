#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Usage: ./zadatak3.sh [directory_path] [file_names]"
	exit 1
fi

dir=$1
	
if [ ! -d $dir ]; then
	echo "That directory does not exist, try a different one!"
	echo "Usage: ./zadatak3.sh [directory_path] [file_names]"
	exit 1
fi

dir=$1
files=$2
total=0

echo "Navedeni direktorij: $dir"
echo "Navedeni nazivi datoteka u obliku: $files"
echo

for file in $(find "$dir" -type f -name "$files");
do
	total=$(( total + $(wc -l < "$file") ))
done

echo "Ukupno redaka: $total"
