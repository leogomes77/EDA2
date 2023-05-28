/**
 * @file Grafo.c
 * @author Leonardo Gomes (a20609@alunos.ipca.pt)
 * @brief Trabalho prático de AED2
 * @version 0.1
 * @date 2023-05-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Grafo.h"

/**
 * @brief Converte para radianos
 * 
 * @param degree 
 * @return double 
 */
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

/**
 * @brief Verifica se existe o Vertice no grafo
 * 
 * @param grafo 
 * @param cod 
 * @return true 
 * @return false 
 */
bool ExisteVertice(PontoRecolha* grafo, int cod) {
    PontoRecolha* atual = grafo;
    while (atual != NULL) {
        if (atual->cod == cod) {
            return true; 
        }
        atual = atual->next;
    }
    return false; 
}


/**
 * @brief Cria um Vertice
 * 
 * @param cidade 
 * @param cod 
 * @param coordenadas 
 * @return PontoRecolha* 
 */
PontoRecolha* CriaVertice(char* cidade, int cod, char* coordenadas) {
    PontoRecolha* novo = (PontoRecolha*)malloc(sizeof(PontoRecolha));
    if (novo == NULL) {
        return NULL;
    }

    novo->cod = cod;

    strcpy(novo->cidade, cidade);

    // Extrair as coordenadas em formato de graus decimais
    double latitude, longitude;
    sscanf(coordenadas, "%lf,%lf", &latitude, &longitude);
    sprintf(novo->coordenadas, "%.6f,%.6f", latitude, longitude);

    novo->next = NULL;
    novo->adjacentes = NULL;
    return novo;
}

/**
 * @brief Cria uma Adjacencia
 * 
 * @param cod 
 * @param dist 
 * @return Adj* 
 */
Adj* CriaAdj(int cod, float dist) {
    Adj* novo = (Adj*)malloc(sizeof(Adj));
    if (novo == NULL) {
        return NULL;
    }
    novo->cod = cod;
    novo->dist = dist;
    novo->next = NULL;
    return novo;
}

/**
 * @brief Calcula a distancia entre coordenadas
 * 
 * @param geocode1 
 * @param geocode2 
 * @return double 
 */
double calcularDistanciaGeocodes(const char* geocode1, const char* geocode2) {
    double lat1, lon1, lat2, lon2;
    sscanf(geocode1, "%lf,%lf", &lat1, &lon1);
    sscanf(geocode2, "%lf,%lf", &lat2, &lon2);

    double lat1Rad = toRadians(lat1);
    double lon1Rad = toRadians(lon1);
    double lat2Rad = toRadians(lat2);
    double lon2Rad = toRadians(lon2);

    double dlat = lat2Rad - lat1Rad;
    double dlon = lon2Rad - lon1Rad;

    double a = pow(sin(dlat / 2), 2) + cos(lat1Rad) * cos(lat2Rad) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distancia = R * c;
    return distancia;
}

/**
 * @brief Insere um vertice no grafo
 * 
 * @param g 
 * @param novo 
 * @return PontoRecolha* 
 */
PontoRecolha* InsereVertice(PontoRecolha* g, PontoRecolha* novo) {
    if (ExisteVertice(g, novo->cod)) {
        printf("O vertice com o codigo %d ja existe no grafo.\n\n", novo->cod);
        return g;  // Retorna o grafo original sem inserir um novo vértice
    }

    if (g == NULL) {
        g = novo;
        return g;
    } else {
        PontoRecolha* aux = g;
        PontoRecolha* ant = aux;
        while (aux && strcmp(aux->cidade, novo->cidade) < 0) {
            ant = aux;
            aux = aux->next;
        }
        if (aux == g) {
            novo->next = g;
            g = novo;
        } else {
            novo->next = aux;
            ant->next = novo;
        }
    }
    return g;
}

/**
 * @brief Insere uma adjacência no vertice 
 * 
 * @param g 
 * @param origem 
 * @param dest 
 * @return PontoRecolha* 
 */
PontoRecolha* InsereAdjacenteVertice(PontoRecolha* g, char* origem, char* dest) {
    if (g == NULL) {
        return g;
    }

    PontoRecolha* aux = g;
    while (aux != NULL && strcmp(aux->cidade, origem) != 0) {
        aux = aux->next;
    }

    if (aux == NULL) {
        printf("Vertice de origem nao encontrado.\n");
        return g;
    }

    PontoRecolha* destino = g;
    while (destino != NULL && strcmp(destino->cidade, dest) != 0) {
        destino = destino->next;
    }

    if (destino == NULL) {
        printf("Vertice de destino nao encontrado.\n");
        return g;
    }

    // Verificar se a adjacência já existe
    if (ExisteAdjacencia(aux, destino->cod)) {
        printf("Adjacencia ja existe.\n\n");
        return g;
    }

    const char* geocode1 = aux->coordenadas;
    const char* geocode2 = destino->coordenadas;
    double distancia = calcularDistanciaGeocodes(geocode1, geocode2);

    Adj* novoAdj = CriaAdj(destino->cod, distancia);
    if (novoAdj == NULL) {
        printf("Erro ao criar adjacencia.\n");
        return g;
    }

    if (aux->adjacentes == NULL) {
        aux->adjacentes = novoAdj;
    } else {
        Adj* temp = aux->adjacentes;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoAdj;
    }

    return g;
}

/**
 * @brief Verifica se uma adjacência existe na lista de adjacências.
 * 
 * @param h 
 * @param cod 
 * @return true 
 * @return false 
 */
bool ExisteAdjacentes(Adj* h, int cod) {
	if (h == NULL) return false;
	if (h->cod == cod) return true;
	return ExisteAdjacentes(h->next, cod);
}

/**
 * @brief Verifica se uma adjacência existe na lista de vértices.
 * 
 * @param vertice 
 * @param cod 
 * @return true 
 * @return false 
 */
bool ExisteAdjacencia(PontoRecolha* vertice, int cod) {
    Adj* aux = vertice->adjacentes;
    while (aux != NULL) {
        if (aux->cod == cod) {
            return true;
        }
        aux = aux->next;
    }
    return false;
}

/**
 * @brief Insere um adjacência
 * 
 * @param h 
 * @param novo 
 * @return Adj* 
 */
Adj* InsereAdj(Adj* h, Adj* novo) {
	
	if (novo == NULL)	//Se novo adjacente é nulo, ignora operação
		return h;
		
	if (ExisteAdjacentes(h, novo->cod) == true) return h; // Se novo adj existe, ignorar operação
	
	if (h == NULL) {	//Se lista de adjacencias é vazia, esta é a primeira adjacencia
		h = novo;
		return h;
	}
	//senão insere no início das adjacências! Podia ser de outra forma!
	novo->next = h;
	h = novo;

	return h;
}

/**
 * @brief Procura um vértice pelo código.
 * 
 * @param g 
 * @param cod 
 * @return PontoRecolha* 
 */
PontoRecolha* ProcuraVerticeCod(PontoRecolha* g, int cod) {
	if (g == NULL) return NULL;
	if (g->cod==cod) return g;
	return(ProcuraVerticeCod(g->next, cod));
}

/**
 * @brief Insere Adjacente a partir dos códigos dos vertices.
 * 
 * @param g 
 * @param codOrigem 
 * @param codDest 
 * @return PontoRecolha* 
 */
PontoRecolha* InsereAdjacenteVerticeCod(PontoRecolha* g, int codOrigem, int codDest) {
	if (g == NULL) return g;	//<! se grafo está vazio, ignora operação

	PontoRecolha* o = ProcuraVerticeCod(g, codOrigem);	//<! procura vertice origem
	PontoRecolha* d = ProcuraVerticeCod(g, codDest);	//<! procura vertice destino
	if (o == NULL || d == NULL) return g;		//<! Se não encontrou vertice origem e destino, ignora operação

	if (ExisteAdjacentes(o->adjacentes, codDest) == true)
		return g; //Se já foi registado esta adjacencia, ignorar a operação

    const char* geocode1 = o->coordenadas;
    const char* geocode2 = d->coordenadas;
    double distancia = calcularDistanciaGeocodes(geocode1, geocode2);

	//Insere nova adjacencia no vertice "Origem"
	Adj* novoAdj = CriaAdj(codDest, distancia);
	o->adjacentes = InsereAdj(o->adjacentes, novoAdj);
	return g;
}

/**
 * @brief Localiza todos os vertices no raio de 50km pelo coordenada fornecida
 * 
 * @param grafo 
 * @param geocodeReferencia 
 * @param raio 
 */
void LocalizarVerticesNoRaio(PontoRecolha* grafo, const char* geocodeReferencia, float raio) {   
    PontoRecolha* atual = grafo;
    while (atual != NULL) {
        const char* geocodeAtual = atual->coordenadas;
        double distancia = calcularDistanciaGeocodes(geocodeReferencia, geocodeAtual);

        if (distancia <= raio) {
            printf("\n\nCidade: %s, Coordenadas: %s, Distancia ate ao ponto: %.2f km\n\n", atual->cidade, atual->coordenadas, distancia);
        }

        atual = atual->next;
    }
}

/**
 * @brief Imprime o grafo
 * 
 * @param grafo 
 */
void ImprimirGrafo(PontoRecolha* grafo) {
    PontoRecolha* atual = grafo;
    while (atual != NULL) {
        printf("Vertice Cidade: %s\n", atual->cidade);
        printf("Vertice COD: %d\n", atual->cod);
        printf("Adjacencias:\n");
        Adj* adj = atual->adjacentes;
        while (adj != NULL) {
            PontoRecolha* destino = grafo;
            while (destino != NULL && destino->cod != adj->cod) {
                destino = destino->next;
            }
            if (destino != NULL) {
                printf("Destino: %s, Distancia: %.2f\n", destino->cidade, adj->dist);
            }
            adj = adj->next;
        }
        printf("\n");
        atual = atual->next;
    }
}

/**
 * @brief Grava os vertices do grafo num ficheiro .bin
 * 
 * @param grafo 
 * @param nomeFicheiro 
 * @return int 
 */
int gravaVerticesBinario(PontoRecolha* grafo, char* nomeFicheiro)
{
    char nome[100];

    if (grafo == NULL)
    {
        return -1;
    }

    FILE* fp;
    fp = fopen(nomeFicheiro, "wb");
    if (fp == NULL)
    {
        return -2;
    }

    PontoRecolha* aux = grafo;
    PontoRecolhaFile auxFicheiro;

    while (aux != NULL)
    {
        auxFicheiro.cod = aux->cod;
        strcpy(auxFicheiro.cidade, aux->cidade);
        strcpy(auxFicheiro.coordenadas, aux->coordenadas);
        fwrite(&auxFicheiro, sizeof(PontoRecolhaFile), 1, fp);
        strcpy(nome, nomeFicheiro); 
        strcat(nome, aux->cidade);
        if (aux->adjacentes) {
            gravaAdjacenciasBinario(aux->adjacentes, aux->cidade, aux->cod);
        }
        aux = aux->next;
    }
    fclose(fp);
    return 1;
}

/**
 * @brief Grave as adjacências dos vertices num ficheiro
 * 
 * @param head 
 * @param nomeFicheiro 
 * @param codVerticeOrigem 
 * @return int 
 */
int gravaAdjacenciasBinario(Adj* head, char* nomeFicheiro, int codVerticeOrigem)
{
    if (head == NULL)
    {
        return -1;
    }

    FILE* fp;
    fp = fopen(nomeFicheiro, "ab");
    if (fp == NULL)
    {
        return -2;
    }

    Adj* aux = head;
    AdjFile auxFicheiro;

    while (aux != NULL)
    {
        auxFicheiro.codDestino = aux->cod;
        auxFicheiro.codOrigem = codVerticeOrigem;
        auxFicheiro.dist = aux->dist;
        fwrite(&auxFicheiro, sizeof(AdjFile),1, fp);
        aux = aux->next;
    }
    fclose(fp);
    return 1;
}

/**
 * @brief Lê os vertices guardados no ficheiro para o grafo
 * 
 * @param grafo 
 * @param nomeFicheiro 
 * @param resLeitura 
 * @return PontoRecolha* 
 */
PontoRecolha* leVerticesBinario(PontoRecolha* grafo, char* nomeFicheiro, bool* resLeitura)
{
    resLeitura = false;

	FILE* fp = fopen(nomeFicheiro, "rb");

    if (fp == NULL)
    {
        return NULL;
    }

    PontoRecolhaFile aux;
    PontoRecolha* novo;

    while (fread(&aux, 1, sizeof(PontoRecolhaFile), fp)) 
    {
        novo = CriaVertice(aux.cidade, aux.cod,aux.coordenadas);
        grafo = InsereVertice(grafo, novo);
    }
    fclose(fp);
    return grafo;
}

/**
 * @brief Lê as adjacências do ficheiro para o grafo
 * 
 * @param grafo 
 * @param resLeitura 
 * @return PontoRecolha* 
 */
PontoRecolha* leAdjacenciaBinario(PontoRecolha* grafo, bool* resLeitura)
{
    resLeitura = false;

   FILE* fp;
   
    /*
    if (grafo == NULL)
    {
        return ;
    } 
    */

    AdjFile aux;
    PontoRecolha* auxGraph = grafo;

    while (auxGraph) 
    {
        fp = fopen(auxGraph->cidade, "rb");
        if (fp != NULL) {
            while (fread(&aux, 1, sizeof(AdjFile), fp)) {
                grafo = InsereAdjacenteVerticeCod(grafo, aux.codOrigem, aux.codDestino);
            }
            fclose(fp);
        }
        auxGraph = auxGraph->next;
    }
    return grafo;
}

void menuGrafo() {

    bool res;
     
    PontoRecolha* graf = NULL;

    graf = leVerticesBinario(graf, "Vertices.bin", &res);
    graf = leAdjacenciaBinario(graf, &res);

    
    //Criar Vertices
    PontoRecolha* novoVertice = CriaVertice("Braga", 1, "21.41577999893519, -8.3880824260564");
    if (novoVertice != NULL) {
       novoVertice->next = graf;
       graf = InsereVertice(graf, novoVertice);
    }

    novoVertice = CriaVertice("PORTO", 2, "31.412232163618285, -8.422501688610403");
    if (novoVertice != NULL) {
        novoVertice->next = graf;
        graf = InsereVertice(graf, novoVertice);
    }

    novoVertice = CriaVertice("LISBOA", 3, "41.412232163618285, -8.422501688610403");
    if (novoVertice != NULL) {
        novoVertice->next = graf;
        graf = InsereVertice(graf, novoVertice);
    }


    //Criar Adjacencias
    graf = InsereAdjacenteVertice(graf, "Braga", "PORTO");
    graf = InsereAdjacenteVertice(graf, "PORTO", "Braga");
    graf = InsereAdjacenteVertice(graf, "PORTO", "LISBOA");
    
    
    // Imprimir o grafo
    ImprimirGrafo(graf);
    

    //Localizacao Cliente
    const char* geoCodeCliente = "41.3577999894519, -8.3880824260564";
    //Raio para encontrar Vertice
    float raio = 50.0; // Raio de 50 km
    

    printf("Pontos de Recolha no Raio de %.2f km:\n", raio);
    LocalizarVerticesNoRaio(graf, geoCodeCliente, raio);


    //Gravar Vertices e Adjacencias no Ficheiro
    gravaVerticesBinario(graf,"Vertices.bin");
    
}