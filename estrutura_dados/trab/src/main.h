/*
funcao assim o compilador gera um codigo da funcao naquela posicao, eliminando overhead de chamar funcao (bkp registradores e restore dos registradores), porem deixa o codigo maior
	static inline void funcao( dsada )

predict no if
	provavelmente var eh zero
	if(unlikely(var))
	provavelmente var nao eh zero
	if(likely(var))


*/

#define DUAS 2
