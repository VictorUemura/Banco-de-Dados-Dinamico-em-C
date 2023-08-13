
// Implementação -> String dinâmica
typedef struct Character {
	struct Character *prox;
	struct Character *ant;
	char *C;
} Character;

typedef struct String {
	int tam;
	Character *inicio;
	Character *fim;
} String;

void inicString(String *string) {
	string->inicio = NULL;
	string->fim = NULL;
	string->tam = 0;
}

