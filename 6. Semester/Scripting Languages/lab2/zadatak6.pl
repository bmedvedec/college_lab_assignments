#!/usr/bin/perl -w
use open ':locale';
use locale;
use utf8;

$prefiks = pop @ARGV;
#%popis;

while (<>) {
	chomp;
	tr/A-Z/a-z/;
	@lista_rijeci = $_ =~ m/\b(\w{$prefiks})/g;	

	foreach $rijec (@lista_rijeci) {
		$popis{$rijec} += 1;
	}
}

foreach $kljuc (sort keys %popis) {
	printf "%s : %d\n", $kljuc, $popis{$kljuc};
}
