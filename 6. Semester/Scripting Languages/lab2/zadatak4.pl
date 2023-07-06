#!/usr/bin/perl
$i = 0;
while (<>) {
	chomp;
	if ($i == 0) {
		$i++;
		next;
	}
	
	($jmbag, $prezime, $ime, $termin, $zakljucano) = split /;/;
	
	$termin =~ s/ A[\d]+//;
	
	($datum_poc) = $termin =~ m/([\d]{4}-[\d]{2}-[\d]{2})/;
	($datum_pred) = $zakljucano =~ m/([\d]{4}-[\d]{2}-[\d]{2})/;
	
	($vrijeme_poc) = $termin =~ m/([\d]{2}):/;
	($vrijeme_pred) = $zakljucano =~ m/([\d]{2}):/;
	
	if ( ($datum_poc ne $datum_pred) or ($vrijeme_poc ne $vrijeme_pred) ) {
		print "$jmbag $prezime $ime - PROBLEM: $termin --> $zakljucano\n";
	}	
}
