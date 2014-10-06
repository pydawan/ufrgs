#!/usr/bin/python


# Variaveis globais
B=[]
G=[]
A=[]




# Dados de entrada
N = 2 #tarefas no sistema
M = 3 #nro estacoes
U = [0.3,0.5,0.25]
p = [0.0,2.0,0.0]


# Etapas
#1. escolher um dos F's para ser y. calcular A via teorema de jackson
A=[0.6,1.0,1.0]

#2 calcular B 
for i in range(0,M): 
    B.append(A[i]/U[i])
    #print "B["+str(i)+"]="+str(B[i])

#3 calcular G[N]
for n in range(0,N+1):
    G.insert(n,0.0) #inicializa G
G[0] = 1.0

for m in range(0,M): #para cada node
    for n in range(1,N+1): #para cada tarefa
        G[n] = G[n] + (B[m]*G[n-1])
        #print "G["+str(n)+"]="+str(G[n])



#4 resultado
nom = 1
for i in range(0,M):
    nom = nom * B[i]**p[i]
    #print str(B[i]) + " ** " + str(p[i])
#print nom
resultado = nom / G[N]
print resultado

