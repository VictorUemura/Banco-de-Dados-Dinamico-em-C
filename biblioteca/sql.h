void carregaScript(BancoDado **B, DescFilaString *F) {
	char string[100], stringColuna[100], stringTabela[100];
	DescFilaString fila;
	Tabela *T;
	PColuna *C, *C2;
	init(&fila);
	
	while(!filaVazia(F)) {
		unqueue(&(*F), string);
		if(strcmp("CREATE", string) == 0) {
			unqueue(&(*F), string);
			
			if(strcmp("DATABASE", string) == 0) {
				initBancoDado(&(*B));
				unqueue(&(*F), string);
				novoBancoDado(&(*B), string);
				unqueue(&(*F), string);
			}
			else if(strcmp("TABLE", string) == 0) {
				unqueue(&(*F), string);
				insereTabela(&(*B), string);
				strcpy(stringTabela, string);
				
				do {
					unqueue(&(*F), string);
					if(strcmp(string, "(") == 0)
						enqueue(&fila, string);
					
					else if(strcmp(string, ")") == 0)
						unqueue(&fila, string);
					
					else if(strcmp(string, "INTEGER") == 0)
						insereColunaTabela(&(*B), stringColuna, 'I', 'N', stringTabela);
					
					else if(strcmp(string, "CHARACTER") == 0) {
							unqueue(&(*F), string);
							unqueue(&(*F), string);
							if(strcmp(string, "20") == 0) {
								insereColunaTabela(&(*B), stringColuna, 'T', 'N', stringTabela);
							} else {
								insereColunaTabela(&(*B), stringColuna, 'C', 'N', stringTabela);
							}
							unqueue(&(*F), string);
					}
					
					else if(strcmp(string, "DATE") == 0)
						insereColunaTabela(&(*B), stringColuna, 'D', 'N', stringTabela);
					
					else if(strcmp(string, "NUMERIC") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						insereColunaTabela(&(*B), stringColuna, 'N', 'N', stringTabela);
					}
					
					else if(strcmp(string, "CONSTRAINT") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						if(strcmp(string, "PRIMARY") == 0) {
							unqueue(&(*F), string);
							if(strcmp(string, "KEY") == 0) {
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								buscaTabela(&(*B), stringTabela, &T);
								buscaColuna(T, string, &C);
								C->pk = 'S';
								unqueue(&(*F), string);
							}
						}
					}
					
					else if(strcmp(string, ",") != 0)
						strcpy(stringColuna, string);
				
				} while(filaVazia(F) == 0 && filaVazia(&fila) == 0);
			}
		}
		else if(strcmp(string, "ALTER") == 0) {
			unqueue(&(*F), string);
			if(strcmp(string, "TABLE") == 0) {
				unqueue(&(*F), string);
				buscaTabela(&(*B), string, &T);
				unqueue(&(*F), string);
				if(strcmp(string, "ADD") == 0) {
					unqueue(&(*F), string);
					if(strcmp(string, "CONSTRAINT") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						if(strcmp(string, "FOREIGN") == 0) {
							unqueue(&(*F), string);
								if(strcmp(string, "KEY") == 0) {
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								buscaColuna(T, string, &C);
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								if(strcmp(string, "REFERENCES") == 0) {
									unqueue(&(*F), string);
									buscaTabela(&(*B), string, &T);
									unqueue(&(*F), string);
									unqueue(&(*F), string);
									buscaColuna(T, string, &C2);
									C->fk = C2;
								}
							}
						}
					}
				}
			}
		}
			
	}
}

// Envia uma fila de string e retorna outra fila de string e uma se tiver tabela na primeira
// linha do select
void comandoSelect(DescFilaString *F, DescFilaString *C, DescFilaString *T) {
	char string[100], stringAntes[100], stringDepois[100];
	int verifica = -1;
	init(&(*C));
	init(&(*T));
	do {
		unqueue(&(*F), string);
		buscaPonto(string, &verifica);
		if(verifica > -1) {
			verifica = -1;
			separaPonto(string, stringAntes, stringDepois);
			enqueue(&(*T), stringAntes);
			enqueue(&(*C), stringDepois);
		} 
		else
			enqueue(&(*C), string);
		topoFilaString(*F, string);
		if(strcmp(string, ",") == 0)
			unqueue(&(*F), string);
	} while(strcmp(string, "FROM") != 0);
}

void comandoFrom(BancoDado **B, DescFilaString *F, ListaTabela **L) {
	char string[100];
	Tabela *T;
	initListaT(&(*L));
	do {
		unqueue(&(*F), string);
		buscaTabela(&(*B), string, &T);
		if(T != NULL)
			insereListaT(&(*L), &T);
		topoFilaString(*F, string);
		if(strcmp(string, ",") == 0)
			unqueue(&(*F), string);
	} while(strcmp(string, ";") != 0 && strcmp(string, "WHERE") != 0);
}

void criaListaColuna(ListaTabela **L, DescFilaString *C, DescFilaString *T) {
	char string[100], string2[100];
	PColuna *col;
	ListaTabela *caixa;
	topoFilaString(*C, string);
	if(strcmp(string, "*") == 0) {
		unqueue(&(*C), string);
		caixa = (*L);
		while(caixa != NULL) {
			col = caixa->tabela->coluna;
			while(col != NULL) {
				insereListaC(&(caixa->listaColuna), &col);
				col = col->prox;
			}
			caixa = caixa->prox;
		}
	}
	else if(filaVazia(&(*T))) {
		while(!filaVazia(C)) {	
			unqueue(&(*C), string);
			buscaColuna((*L)->tabela, string, &col);
			insereListaC(&((*L)->listaColuna), &col);
		}
	}
	else {
		while(!filaVazia(C)) {
			unqueue(&(*C), string);
			unqueue(&(*T), string2);
			buscaListaT(&(*L), string2, &caixa);
			buscaColuna(caixa->tabela, string, &col);
			insereListaC(&(caixa->listaColuna), &col);
		}
	}
}

// Funcao que retorna uma fila com linhas em que se encontram aquela condicao aplicada
// Obs.: A condicao e enviada como uma string dividida por DescFilaString
// A contagem das linha se inicia por 0
// Enviar uma fila auxiliar e depois fazer as comparacoes
void comandoWhere(ListaTabela **L, DescFilaString *F, char pIteracao) {
	int linha = 0, valorI, verifica, valorProxI, i;
	double valorN, valorProxN;
	char string[100], condicao[100], valorC, valorT[100], stringAntes[100], stringDepois[100], tipo, valorProxT[100], valorProxC, achou;
	ListaColuna *col1 = NULL, *col2 = NULL;
	ListaTabela *tab1, *tab2 = NULL, *copiaAux;
	DescFilaI filaA1, filaA2, filaA3;
	Dado *D, *auxDado;
	unqueue(&(*F), string);
	unqueue(&(*F), string);
	buscaPonto(string, &verifica);
	if(verifica > -1) {
		verifica = -1;
		separaPonto(string, stringAntes, stringDepois);
		buscaListaT(&(*L), stringAntes, &tab1);
		buscaListaC(&(tab1->listaColuna), stringDepois, &col1);
	}
	// Significa que existe uma apenas tabela dentro da lista
	else
		buscaListaC(&((*L)->listaColuna), string, &col1);
	unqueue(&(*F), string);
	strcpy(condicao, string);
	
	unqueue(&(*F), string);
	buscaPonto(string, &verifica);
	// e numero ou nome de coluna
	if(verifica > -1 || col1->coluna->tipo == 'N') {
		verifica = -1;
		// Coluna tipo = 0
		if((string[0] >= 65 && string[0] <= 90) || (string[0] >= 97 && string[0] <= 122)) {
			separaPonto(string, stringAntes, stringDepois);
			buscaListaT(&(*L), stringAntes, &tab2);
			buscaListaC(&(tab2->listaColuna), stringDepois, &col2);
			tipo = '0';
		}
		// Numero tipo = 1
		else {
			valorN = atof(string);
			tipo = '1';
		}
	}
	else if(col1->coluna->tipo == 'C') {
		// Caracter tipo = 2
		tipo = '2';
		unqueue(&(*F), string);
		valorC = string[0];
		unqueue(&(*F), string);
	}
	else if(col1->coluna->tipo == 'D' || col1->coluna->tipo == 'T') {
		// Texto tipo = 3
		tipo = '3';
		unqueue(&(*F), string);
		strcpy(valorT, string);
		unqueue(&(*F), string);
	}
	else {
		// Inteiro tipo = 4
		tipo = '4';
		converteNumeroI(string, &valorI);
	}
	if(strcmp(condicao, "BETWEEN") == 0) {
		unqueue(&(*F), string);
		unqueue(&(*F), string);
		buscaPonto(string, &verifica);
		if(verifica > -1) {
			verifica = -1;
			valorN = atof(string);
		}
		if(col1->coluna->tipo == 'C') {
			unqueue(&(*F), string);
			valorProxC = string[0];
			unqueue(&(*F), string);
		}
		else if(col1->coluna->tipo == 'D' || col1->coluna->tipo == 'T') {
			unqueue(&(*F), string);
			strcpy(valorProxT, string);
			unqueue(&(*F), string);
		}
		else
			converteNumeroI(string, &valorProxI);
	}
	if(pIteracao) {
		copiaAux = (*L);
		while(copiaAux != NULL) {
			D = copiaAux->tabela->coluna->pDados;
			for(int j = 0; D != NULL; j++, D = D->prox)
				enqueueI(&copiaAux->descFilaI, j);
			copiaAux = copiaAux->prox;
		}
	}
	
	initI(&filaA1);
	
	while(!filaVaziaI(tab1->descFilaI)) {
		unqueueI(&tab1->descFilaI, &i);
		enqueueI(&filaA1, i);
	}
	if(tab2 != NULL) {
		initI(&filaA2);
		initI(&filaA3);
		while(!filaVaziaI(tab2->descFilaI)) {
			unqueueI(&tab2->descFilaI, &i);
			enqueueI(&filaA2, i);
		}
	}
	
	while(!filaVaziaI(filaA1)) {
		unqueueI(&filaA1, &linha);
		buscaDado(col1->coluna, linha, &D);	
		// Tipo inteiro
		if(tipo == '4') {
			if(strcmp(condicao, "BETWEEN") == 0 && D->tipo.valorI >= valorI && D->tipo.valorI <= valorProxI)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "=") == 0 && D->tipo.valorI == valorI)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<") == 0 && D->tipo.valorI < valorI)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<=") == 0 && D->tipo.valorI <= valorI)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">") == 0 && D->tipo.valorI > valorI)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">=") == 0 && D->tipo.valorI >= valorI)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<>") == 0 && D->tipo.valorI != valorI)
				enqueueI(&tab1->descFilaI, linha);
				
		// Tipo caracter
		} else if(tipo == '2') {
			if(strcmp(condicao, "BETWEEN") == 0 && D->tipo.valorC >= valorC && D->tipo.valorC <= valorProxC)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "=") == 0 && D->tipo.valorC == valorC)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<") == 0 && D->tipo.valorC < valorC)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<=") == 0 && D->tipo.valorC <= valorC)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">") == 0 && D->tipo.valorC > valorC)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">=") == 0 && D->tipo.valorC >= valorC)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<>") == 0 && D->tipo.valorC != valorC)
				enqueueI(&tab1->descFilaI, linha);
		// Tipo numero
		} else if(tipo == '1') {
			if(strcmp(condicao, "BETWEEN") == 0 && D->tipo.valorN >= valorN && D->tipo.valorN <= valorProxN)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "=") == 0 && D->tipo.valorN == valorN)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<") == 0 && D->tipo.valorN < valorN)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<=") == 0 && D->tipo.valorN <= valorN)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">") == 0 && D->tipo.valorN > valorN)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">=") == 0 && D->tipo.valorN >= valorN)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<>") == 0 && D->tipo.valorN != valorN)
				enqueueI(&tab1->descFilaI, linha);
				
		// Tipo coluna
		} else if(tipo == '0') {
			while(!filaVaziaI(filaA2)) {
				unqueueI(&filaA2, &i);
				buscaDado(col2->coluna, i, &auxDado);
				if(col1->coluna->tipo == 'I' && auxDado->tipo.valorI == D->tipo.valorI) {
					enqueueI(&tab2->descFilaI, i);
					if(!existeI(linha, tab1->descFilaI))
						enqueueI(&tab1->descFilaI, linha);
				} else if(col1->coluna->tipo == 'C' && auxDado->tipo.valorC == D->tipo.valorC) {
					enqueueI(&tab2->descFilaI, i);
					if(!existeI(linha, tab1->descFilaI))
						enqueueI(&tab1->descFilaI, linha);
				} else if((col1->coluna->tipo == 'T' || col1->coluna->tipo == 'D') && (strcmp(auxDado->tipo.valorT, D->tipo.valorT) == 0 || strcmp(auxDado->tipo.valorD, D->tipo.valorD) == 0)) {
					enqueueI(&tab2->descFilaI, i);
					if(!existeI(linha, tab1->descFilaI))
						enqueueI(&tab1->descFilaI, linha);
				} else if(col1->coluna->tipo == 'N' && auxDado->tipo.valorN == D->tipo.valorN) {
					enqueueI(&tab2->descFilaI, i);
					if(!existeI(linha, tab1->descFilaI))
						enqueueI(&tab1->descFilaI, linha);
				}
				 else {
					enqueueI(&filaA3, i);
				}
			}
			while(!filaVaziaI(filaA3)) {
				unqueueI(&filaA3, &i);
				enqueueI(&filaA2, i);
			}
			
		// Tipo texto
		} else if(tipo == '3') {
			if(strcmp(condicao, "BETWEEN") == 0 && strcmp(D->tipo.valorT, valorT) >= 0 && strcmp(D->tipo.valorT, valorProxT) <= 0)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "=") == 0 && strcmp(D->tipo.valorT, valorT) == 0)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<") == 0 && strcmp(D->tipo.valorT, valorT) < 0)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<=") == 0 && strcmp(D->tipo.valorT, valorT) <= 0)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">") == 0 && strcmp(D->tipo.valorT, valorT) > 0)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, ">=") == 0 && strcmp(D->tipo.valorT, valorT) >= 0)
				enqueueI(&tab1->descFilaI, linha);
			else if(strcmp(condicao, "<>") == 0 && strcmp(D->tipo.valorT, valorT) != 0)
				enqueueI(&tab1->descFilaI, linha);
				
		}
	}

	while(!filaVaziaI(filaA2))
		unqueueI(&filaA2, &i);

}

void comandoInsert(BancoDado **B, DescFilaString *I){
	char string[100],stringTabela[100], stringColuna[100];
	DescFilaString COLUNA, VALORES;
	Tabela *T;
	PColuna *C;
	Dado *D;
	
	init(&COLUNA);
	init(&VALORES);
	
	unqueue(&(*I), string);
	while(!filaVazia(I) && strcmp(string, ";") != 0){
		if(strcmp(string,"INSERT")==0){
			unqueue(&(*I), string);
			if(strcmp(string, "INTO")==0){
				unqueue(&(*I), string);
				strcpy(stringTabela, string);
				unqueue(&(*I), string);
				do{
					if(strcmp(string, "(") == 0)
						unqueue(&(*I), string);
					else if(strcmp(string, ")") == 0)
						unqueue(&(*I), string);
					else if(strcmp(string, ",") == 0)
						unqueue(&(*I), string);
					else{
						enqueue(&COLUNA, string);
						unqueue(&(*I), string);
					}
				}while(stricmp(string, "VALUES") != 0 && !filaVazia(I));
			}
		}
		else if(stricmp(string, "VALUES") == 0){
			unqueue(&(*I), string);
			do{
				if(strcmp(string, "(") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ")") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ",") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, "'") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ";") != 0){
						enqueue(&VALORES, string);
						unqueue(&(*I), string);
				}					
			
			}while(!filaVazia(I) && strcmp(string, ";") != 0);
		}
		else
			unqueue(&(*I), string);
	}
	buscaTabela(&(*B), stringTabela, &T);
	while(!filaVazia(&COLUNA) || !filaVazia(&VALORES)){
		unqueue(&COLUNA, stringColuna);
		buscaColuna(T, stringColuna, &C);
		unqueue(&VALORES, string);
		insereDado(&C, string);
	}
}
