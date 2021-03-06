#!/usr/bin/python

import math

#convert scientific to decimal - http://www.webmath.com/sn_convert.html

k=1
B=1
m=1
#ex1 p1
y=500.0
u=2000.0
k=52.0
B=50
m=1
k=1

##ex3 p1
#y=30
##Ets=50
#u=(1.0/(50.0/1000.0))
#m=3

#ex11 p1
#y=30
#Ets=50
#u=(1.0/(50.0/1000.0))
#k=2
#m=3


##ex1 - gateway
#y=125.0
#u=500.0
#k=15.0

#ex2 - datacenter
#y=240.0/60.0
#u=800.0/176.0
#k=1.0

#ex1 - redes filas abertas
#y=4
#u=4.54
#k=1.0

#ex 5 filas caixa MM1
#y=10.0/5.0
#u=4.0

#ex 5 filas caixa MMm
#y=10.0
#u=4.0*5.0


dict_filas = {
    "m": "nodes",
    "y": "taxa de chegada de tarefas",
    "u": "taxa de saida de tarefas",
    "Et": "tempo medio entre chegadas de tarefas",
    "Ets": "tempo medio que cada tarefa ocupa o servidor",
    "p": "intensidade de trafego",
    "U": "utilizacao do servidor (n>=1)",
    "En": "(N) numero medio de tarefas no sistema",
    "Pn": "prob. que hajam n ou mais tarefas no sistema",
    "Er": "(T) tempo medio de permanencia das tarefas no sistema",
    "Enq": "(Nq) numero medio de tarefas na fila(tarefas esperando)",
    "Erq": "(Tq) tempo medio de permanencia das tarefas na fila",
#    "EnqB": "(Nq) numero medio de tarefas na fila(tarefas esperando) com limite B",
#		"p0": "prob0 para limite B",
#		"pn": "probn para limite B"
#		"pm"  "ro MMm"
    }

Et = 1.0/y
Ets = 1.0/u
p = y/(m*u)
U = p
En = p/(1.0-p)
Enq = p**2.0/(1.0-p)
Pn = p**k
Er = En/y #Teorema de Little
Er = 1/(u-y)
Erq = Enq/y

#pm = y/m*u
#
##com B
#EnqB = (p/(1.0-p))-p*((1.0+B*(p**B))/(1.0-(p**(B-1.0))))
#p0=1.0/(1.0+(1.0-(p**(B-m+1))*(p**m)*m**m)/(1-p))
#pn=(y**B)/(u**B)*p0

def pe(n):
    if (n==0):
        return 1.0-p
    else:
        return p^n(1.0-p)

#determinar "k" onde P(n>=k)=x
def ka(x):
    return math.log(x,p)
#ex1 - gateway
#print "ka(10^-6)=" + str(ka(10**-6))
#print "ka(10^-6)=" + str(ka(Enq))
#verificar no modelo se precisa subtrair 1 de n


keys_filas = dict_filas.viewkeys()
for key in keys_filas:
    print key + "=" + str(locals()[key]) + " #" + dict_filas[key] 

