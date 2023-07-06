#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage: ./zadatak3.sh [directory_name]."
	exit 1
fi

dir=$1
	
if [ ! -d "$dir" ]; then
	echo "That directory does not exist, try a different one!"
	echo "Usage: ./zadatak4.sh [directory_path]."
	exit 1
fi

slike=$(find "$dir" -type f -name "*.jpg" | sort)

brojac=0
mjesec=0
slj_mjesec=0

for slika in ${slike[@]};
do
	datum=$(basename $slika | cut -c 5-6,1-4)
	god=${datum:0:4}
	slj_mjesec=${datum:4}
	
	if [ $slj_mjesec != $mjesec ]; then
		if [ $brojac -ne 0 ]; then
			echo "--- Ukupno: $brojac slika ---"
			echo
		fi
		
		echo "$slj_mjesec-$god :"
		echo "---------------"
		brojac=0
	fi
	
	brojac=$(( $brojac+1 ))
	naziv=$(basename $slika)
	echo "$brojac. $naziv"
	mjesec=$slj_mjesec	
done

if [ $brojac -ne 0 ]; then
	echo "--- Ukupno: $brojac slika ---"
