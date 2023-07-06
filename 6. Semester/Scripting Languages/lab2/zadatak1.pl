#!/usr/bin/perl
print "Unesi niz znakova: ";
$niz = <STDIN>;
print "Unesi broj ponavljanja: ";
chomp($n = <STDIN>);
for my $i (1..$n) {
	print "$niz";
}
