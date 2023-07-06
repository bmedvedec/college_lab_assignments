#!/usr/bin/perl
$i = 0;
%rezultati;
while (defined($redak = <>)) {
	if ($redak =~ /^#/ or $redak =~ /^\s*$/) {
		next;
	}
	chomp $redak;
	
	
	if ($i == 0) {
		@faktori = split /;/, $redak;
		$i++;
	}
	else {
		($jmbag, $prezime, $ime, @bodovi) = split /;/, $redak;
		
		$ukupno = 0;
		for $j (0..$#bodovi) {
			if ($bodovi[$j] eq '-') {
				next;
			}
			$ukupno += $bodovi[$j] * $faktori[$j];
		}
		
		$rezultati{$ukupno} = {
			jmbag => $jmbag,
			prezime => $prezime,
			ime => $ime
		};
	}
}

print "Lista po rangu:\n";
print "--------------------\n";
$counter = 1;
foreach $kljuc (sort {$b <=> $a} keys %rezultati) {
	$student = $rezultati{$kljuc};
	$jmbag = $student->{jmbag};
	$prezime = $student->{prezime};
	$ime = $student->{ime};
	$prezime_ime_jmbag = $prezime . ', ' . $ime . ' (' . $jmbag . ')';
	
	printf "%3d. %-35s : %.2f\n",$counter, $prezime_ime_jmbag, $kljuc;
	$counter++;	
}
