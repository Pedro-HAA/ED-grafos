#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int destino;
	int custo;
	struct lista *prox;
} lista;

void inicializar(lista **g, int n) {
	for(int i = 0; i <= n; i++) {
		g[i] = NULL;
	}
}

lista *inserirLista(lista *l, int d, int c) {
	lista *no = malloc(sizeof(lista));
	no->destino = d;
	no->custo = c;
	no->prox = l;
	return no;
}

void inserirAresta(lista **g, int origem, int destino, int custo) {
	g[origem] = inserirLista(g[origem], destino, custo);
}

lista *removerLista(lista *l, int d) {
    if(l == NULL) {
        return NULL;
    } else {
	    if(l->destino == d) {
	        lista *aux = l;
	        l = l->prox;
	        free(aux);
	        return l;
	    }	
	    l->prox = removerLista(l->prox, d);
	    return l;
    }
}

void removerAresta(lista **g, int origem, int destino) {
	g[origem] = removerLista(g[origem], destino);
}

void imprimirLista(lista *l) {
	if(l != NULL) {
		printf("- (%d, %d)", l->destino, l->custo);
		imprimirLista(l->prox);
	}
} 

void imprimirGrafo(lista **g, int n) {
	printf("Grafo: ");
	for(int i = 0; i <= n; i++) {
		printf("\n\t%d", i);
		imprimirLista(g[i]);
	}
}

void imprimirGraus(lista **g, int n, int v) {
    int grauSaida = 0;
    int grauEntrada = 0;
    lista *aux;
    aux = g[v];
    
    while(aux != NULL) {
        grauSaida++;
        aux = aux->prox;
    }

    for(int i = 0; i <= n; i++) {
        aux = g[i];
        while(aux != NULL) {
            if(aux->destino == v) {
                grauEntrada++;
            }
            aux = aux->prox;
        }
    }

    printf("Vertice %d:\n", v);
    printf("Grau de entrada: %d\n", grauEntrada);
    printf("Grau de saida: %d\n", grauSaida);
}

int existeAresta(lista **g, int origem, int destino) {
    lista *aux = g[origem];

    while(aux != NULL) {
        if(aux->destino == destino) {
            return 1;
        }
        aux = aux->prox;
    }

    return 0;
}

int grafoCompleto(lista **g, int n) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if(i == j)
                continue;
            if(!existeAresta(g, i, j))
                return 0;
        }
    }

    return 1;
}

int main() {
	int choice;
	int getOut = 0;
	int n;
	int origem, destino, custo, v;
	
	printf("Digite o número de vértices que terá o grafo:\n");
	scanf("%d", &n);
	lista **g;
	g = malloc((n+1)*sizeof(lista *));
	inicializar(g, n);
	
	while(1) {
		printf("\nEscolha o que deseja fazer:\n");
		printf("1 - Inserir uma aresta no grafo.\n");
		printf("2 - Remover uma aresta do grafo.\n");
		printf("3 - Imprimir grafo.\n");
		printf("4 - Imprimir os graus de entrada e saída de um vértice.\n");
		printf("5 - Verificar se um grafo é completo.\n");
		printf("6 - Sair.\n");
		
		scanf("%d", &choice);
		printf("\nOpção escolhida: %d, ", choice);
		switch (choice) {
			case 1:
				printf("Inserir uma aresta no grafo.\n");
			    printf("Origem: ");
			    scanf("%d", &origem);
			    printf("Destino: ");
			    scanf("%d", &destino);
				printf("Custo: ");
			    scanf("%d", &custo);
			    inserirAresta(g, origem, destino, custo);
				break;
			case 2:
				printf("Remover uma aresta do grafo.\n");
			    printf("Origem: ");
			    scanf("%d", &origem);
			    printf("Destino: ");
			    scanf("%d", &destino);
			    removerAresta(g, origem, destino);
			    break;
			case 3:
				printf("Imprimir grafo.\n");
				imprimirGrafo(g, n);
				break;
			case 4:
				printf("Imprimir os graus de entrada e saída de um vértice.\n");
			    printf("Digite o vertice: ");
			    scanf("%d", &v);
			    imprimirGraus(g, n, v);
				break;
			case 5:
				printf("Verificar se um grafo é completo.\n");
				if(grafoCompleto(g, n)) {
			        printf("O grafo é completo.\n");
			    } else {
			        printf("O grafo não é completo.\n");
				}
				break;
			case 6:
				printf("Sair.\n");
				getOut = 1;
				break;
		}
		if(getOut == 1) break;
	}	
}
