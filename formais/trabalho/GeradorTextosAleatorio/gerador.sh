#!/bin/bash

cat $1 |sed -e 's/#.*$//g' |sed -e 's/	*$//g' > /tmp/gramatica
python GeradorTextosAleatorio.py /tmp/gramatica
