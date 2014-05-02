
#Execucao1
HOJEPRECISO=`date "+%d%m%y%H%M%S"`
mkdir bench/$HOJEPRECISO
DIRTRAB=bench/$HOJEPRECISO
TABELA=$DIRTRAB/trab2.csv

while IFS=, read bench conj tam assoc repl
do
	if [ "$bench" == "^" ];
	then
		simulacao=$conj-$tam-$assoc-$repl
		./sim-cache -max:inst 400000000 -redir:sim $DIRTRAB/$simulacao.txt \
		-cache:il1 il1:$conj:$tam:$assoc:$repl -cache:il2 none \
		-cache:dl1 dl1:$conj:$tam:$assoc:$repl -cache:dl2 none \
		bench/$benchmark.ss -funroll-loops -fforce-mem -fce-follow-jumps -O bench/cccp.i -o bench/cccpi.s
		Icache=`cat $DIRTRAB/$simulacao.txt |grep il1.miss_rate |tr -s " *" " " |cut -d' ' -f2`
		Dcache=`cat $DIRTRAB/$simulacao.txt |grep dl1.miss_rate |tr -s " *" " " |cut -d' ' -f2`
		RateIcache=`echo "$Icache * 100" |bc -l`
		RateDcache=`echo "$Dcache * 100" |bc -l`
		echo ";$conj;$tam;$assoc;$repl;$RateIcache;$RateDcache" >> $TABELA
	else
		echo "" $TABELA
		echo "$bench;N_Conj;Tam_Bloco;Assoc;Politica;Icache(%);Dcache(%)" >> $TABELA
		benchmark=$bench
	fi

done <dados3-trab2.txt
#done <dados2-trab2.txt
#done <dados1-trab2.txt
