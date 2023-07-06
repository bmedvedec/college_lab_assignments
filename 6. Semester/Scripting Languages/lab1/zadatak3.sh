#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage: ./zadatak3.sh [directory_name]."
	exit 1
fi

dir=$1
	
if [ ! -d $dir ]; then
	echo "That directory does not exist, try a different one!"
	echo "Usage: ./zadatak3.sh [directory_name]."
	exit 1
fi

for file in $(ls $dir/localhost_access_log.*-02-*); 
do
	echo $file | sed -r "s/.*\.([0-9]+)-([0-9]+)-([0-9]+).*/datum: \3-\2-\1/"
  	echo "-----------------------------------------------------"
	cat $file | cut -d'"' -f 2 | sort | uniq -c | sort -rn | sed -r "s/\s+([0-9]*)(\s+)(.*)/    \1  :  \3/"
	echo
done
