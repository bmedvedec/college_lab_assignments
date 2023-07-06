#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Usage: ./zadatak6.sh [directory_path1] [directory_path2]"
	exit 1
fi

dir1=$1
dir2=$2
	
if [ ! -d $dir1 ]; then
	echo "Directory $dir1 does not exist, try a different one!"
	echo "Usage: ./zadatak6.sh [directory_path1] [directory_path2]"
	exit 1
fi

if [ ! -d $dir2 ]; then
	echo "Directory $dir2 does not exist, try a different one!"
	echo "Usage: ./zadatak6.sh [directory_path1] [directory_path2]"
	exit 1
fi

for file in "$dir1"/*;
do
	naziv=$(basename $file)
	
	if [ "$file" -nt "$dir2/$naziv" ]; then
		echo "$file --> $dir2"
	fi
done

for file in "$dir2"/*;
do
	naziv=$(basename $file)
	
	if [ "$file" -nt "$dir1/$naziv" ]; then
		echo "$file --> $dir1"
	fi
done
