#!/usr/bin/perl
$i = 0;
while (<>) {
	($datum) = $ARGV =~ m/([\d]{4}-[\d]{2}-[\d]{2})/;
	($sat) = $_ =~ m/[\d]{4}:([\d]{2}):[\d]{2}:[\d]{2}/;
	
	if ($i == 0) {
		print "\nDatum: $datum\n";
		print "sat : broj ponavljanja\n";
		print "------------------------------";
		$polje{$sat}++;
		$i++;
	}
	else {
		$polje{$sat}++;
	}
	
	if (eof) {
		foreach $sat (sort keys %polje) {
			printf "\n%d : %d", $sat, $polje{$sat};
		}
		print "\n";
		$i = 0;
		%polje = ();
	}
}
