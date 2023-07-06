#!/usr/bin/perl
print "Upisi brojeve: (CTRL-D za prekid):\n";
chomp(@brojevi=<STDIN>);
$n=@brojevi;
foreach my $broj (@brojevi){
 $zbroj += $broj;
}
$arsr=$zbroj/$n;
printf "\nAritmetička sredina je: %.2f\n",$arsr;
