grep -i -E "banana|jabuka|jagoda|dinja|lubenica" namirnice.txt

grep -i -v -E "banana|jabuka|jagoda|dinja|lubenica" namirnice.txt

grep -r -E "[A-Z]{3}[0-9]{6}" ~/projekti

find $PWD -type f -mtime +7 -mtime -14 -ls

for i in {1..15}; do echo $i; done

kraj=15; for i in $(seq 1 15); do echo $i; done
#kraj=15; for i in {1..$kraj}; do echo $i; done -> ispisuje "{1..15}"
