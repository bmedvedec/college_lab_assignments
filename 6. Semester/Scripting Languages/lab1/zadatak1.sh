#!/bin/bash

proba="Ovo je proba"
echo $proba

lista_datoteka=*
echo $lista_datoteka

proba3="$proba. $proba. $proba. "
echo $proba3

a=4
b=3
c=7
d=$(( ($a+4)*$b%$c ))
echo $a
echo $b
echo $c
echo $d

broj_rijeci=$(wc -w *.txt)
echo $broj_rijeci

ls ~
