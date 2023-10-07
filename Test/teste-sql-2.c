#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/fila.h"
#include "../Library/tad.h"
#include "../Library/leituraArquivo.h"
#include "../Library/filaI.h"
#include "../Library/listaColuna.h"
#include "../Library/listaTabela.h"
#include "../Library/sql.h"

int main(void) {
	BancoDado *B;
	DescFilaString F;
	leituraArquivo(&F, "scriptdboficina.txt");
	carregaScript(&B, &F);
	exibeBanco(B);
}
