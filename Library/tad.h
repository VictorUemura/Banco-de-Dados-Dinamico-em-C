
typedef struct Dado {
	union {
		int valorI;
		float valorN;
		char valorD[11];
		char valorC;
		char valorT[21];
	};
	struct Dado *prox;
} Dado;

typedef struct PColuna {
	char tipo;
	char *campo;
	char pk;
	Dado *pDados;
	struct PColuna *fk;	
	struct PColuna *prox;
} PColuna;

typedef struct Tabela {
	char *nome;
	PColuna *coluna;
	struct Tabela *ant;
	struct Tabela *prox;
} Tabela;

typedef struct BancoDado {
	char *nome;
	Tabela *tabela;
} BancoDado;

