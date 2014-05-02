Icache=`cat bench/281109180717/32-32-1-l.txt |grep il1.miss_rate |tr -s " *" " " |cut -d' ' -f2`
echo "$Icache * 100" |bc -l
