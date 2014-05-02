#!/usr/bin/python

############################################################################################
## 1. Bibliotecas
import sys
import random
import string

############################################################################################
## 3. Classes
class c_regra:
	def __init__(self, esquerda="", direita="", probabilidade=0.00):
		self.esquerda = esquerda
		self.direita = direita
		self.probabilidade = probabilidade*10000

class c_producao:
	def __init__(self,variavel="",lista=[]):
		self.variavel = ""
		self.lista = []
	def adiciona(self, x):
		self.lista.append(x)
	def ordena(self):
		listatemp=[]
		while len(self.lista) > 0:
			x=0
			menor=self.lista[x]
			x=x+1
			while x < len(self.lista):
				if menor.probabilidade > self.lista[x].probabilidade:
					menor=self.lista[x]
				x=x+1
			listatemp.append(menor)
			self.lista.remove(menor)
		self.lista=listatemp
			
		


############################################################################################
## 4. Variaveis Globais
file_gramatica=sys.argv[1]
lista_variaveis=[]
indice_variavel=0
lista_regras=[]
etapa=""
inicial=""
frase=""
############################################################################################
## 5. Funcoes Auxiliares


def VarreProducao(lista_regras,variavel):
	for producao in lista_regras:
		if producao.variavel == variavel:
			ImprimeTerminal(lista_regras,producao)
			


def ImprimeTerminal(lista_regras,producao):
	n=random.random()*10000
	for regra in producao.lista:
		if n <= regra.probabilidade:
			n=99999999
			if regra.direita[0] == string.lower(regra.direita[0]):
				global frase
				frase=frase + " " + regra.direita
			else:
				dir = regra.direita.split(' ')
				VarreProducao(lista_regras,dir[0])
				VarreProducao(lista_regras,dir[1])

############################################################################################
## 6. Programa

fd=open(file_gramatica)
lines=fd.readlines()
fd.close()

for rawline in lines:
	line = rawline.split(' ')
	#descubro em q etapa do arquivo de gramatica estou
	if line[0] == "Inicial\n":
		etapa=line[0]
		continue
	if line[0] == "Regras\n":
		etapa=line[0]
		continue
	#atuo conforme etapa do arquivo
	if etapa == "Inicial\n":
		inicial = line[1]
	if etapa == "Regras\n":
		#cria a regra
		#caso DIR(terminal)
		if len(line) == 8:
			nova_regra = c_regra(line[1],line[5],float(line[7][1:]))
		#caso DIR(variavel, variavel)
		elif len(line) == 11:
			nova_regra = c_regra(line[1],line[5] + " " + line[8],float(line[10][1:]))
		#coloca a regra na lista referente sua variavel
		#trivial para primeira variavel a montar sua lista de producoes
		if len(lista_regras) == 0:
			#print "vou criar as producoes para: " + line[1]
			producoes = c_producao()
			producoes.variavel = line[1]
			producoes.adiciona(nova_regra)
			lista_regras.append(producoes)
		else:
			for producoes in lista_regras:		
				jaexistia=0
				#print producoes.variavel + " vs " + line[1]
				# se ja houver producoes para esta variavel
				if producoes.variavel == line[1]:
					#somo a prob anterior, assim a teremos prob entre 1 e 10000 para uma variavel
					#print "probs"
					#print nova_regra.probabilidade
					#print producoes.lista[0].probabilidade
					nova_regra.probabilidade=nova_regra.probabilidade+producoes.lista[0].probabilidade
					producoes.adiciona(nova_regra)	
					producoes.lista.reverse()
					jaexistia=1
			if jaexistia == 0:
				#print "vou criar as producoes para: " + line[1]
				producoes = c_producao()
				producoes.variavel = line[1]
				producoes.adiciona(nova_regra)
				lista_regras.append(producoes)
				

for line in lista_regras:
	line.ordena()
#	print "var: " + line.variavel
#	for i in line.lista:
#		print i.direita
#		print i.probabilidade	
#	print ""

VarreProducao(lista_regras,inicial)
print frase
