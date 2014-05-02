
chr() {
  [ ${1} -lt 256 ] || return 1
  printf \\$(printf '%03o' $1)
}

for i in `cat 8.txt`; do chr $((0x$i)); done
