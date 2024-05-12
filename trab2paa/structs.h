/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as definições das estruturas utilizadas.
 */

#ifndef __STRUCTS__
#define __STRUCTS__

//============================================================//
//------------------------- STRUCTS --------------------------//
//============================================================//

/**
 * Estrutura: Point
 *   Define um ponto no espaço com coordenadas inteiras x e y.
 * 
 *   Utilizado para armazenar os pontos descritos no arquivo de
 *   entrada input.txt
 * 
 * Atributos:
 *   (int) x: Coordenada x do ponto
 *   (int) y: Coordenada y do ponto
 */
typedef struct{
    int x;
    int y;
}Point;

/**
 * Estrutura: Elemento
 *   Define um elemento de uma lista de adjacências para repre-
 *   sentar um grafo.
 * 
 *   Utilizado para armazenar a lista de adjacências que des-
 *   creve a AGM computada durante o 2o passo do algoritmo, 
 *   para então realizar a busca do 3o passo.
 * 
 * Atributos:
 *   (int) index: Índice único que identifica dado Elemento com 
 *                o respectivo ponto no vetor de pontos.
 *   (struct elemento_str*) prox: Ponteiro para o próximo Ele-
 *                                mento na lista de adjacências
 *   (bool) visitado: Identificador de visita para a busca em
 *                    profundidade.
 */
typedef struct elemento_str{
    int index;
    struct elemento_str *prox;
    bool visitado;
}Elemento;

/**
 * Estrutura: Vertice
 *   Define um vértice do grafo, conforme necessário para o 2o
 *   passo do algoritmo.
 * 
 *   Utilizado para tratar o grafo na criação da AGM com o algo-
 *   ritmo de Prim, como também armazenar a AGM gerada ao final
 *   do 2o passo.
 * 
 * Atributos:
 *   (int) index: Índice único que identifica dado Vertice com
 *                o respectivo ponto no vetor de pontos.
 *   (int) pai: Índice do pai do Vertice atual, identificando
 *              seu respectivo ponto no vetor de pontos.
 *   (float) custo: Custo mínimo de cada vértice conforme compu-
 *                  tado pelo algoritmo de Prim. É dado pela
 *                  distância entre o vértice atual e seu pai.
 */
typedef struct vertice_str{
    int index;
    int pai;
    float custo;
}Vertice;

/**
 * Estrutura: Heap
 *   Define a estrutura do Heap.
 * 
 *   Utilizado durante a execução do algoritmo de Prim para arma-
 *   zenar o heap que guarda os vértices ainda não visitados.
 * 
 * Atributos:
 *   (Vertice*) array: Vetor do tipo Vertice que armazena todos
 *                     os vértices do grafo.
 *   (int) tamanho_heap: Tamanho atual do heap.
 *   (int) comprimento: Tamanho máximo do heap.
 */
typedef struct{
    Vertice* array;
    int tamanho_heap;
    int comprimento;
}Heap;


#endif