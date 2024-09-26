#include <stdio.h>
#include <stdlib.h>
#include "strassen.h"

int main() {
    int largura, altura, max;
    char cabecalho[3];

    //Ler cabeçalho
    scanf("%s", cabecalho); //lê o formato
    scanf("%d %d", largura, altura); //lê as dimensões
    scanf("%d", max); //lê o valor máximo de cor

    //Alocar as matrizes de pixels
    Pixel **matriz1 = alocarMatriz(altura, largura);
    Pixel **matriz2 = alocarMatriz(altura, largura);
    Pixel **matrizR;

    //Ler os dados das duas matrizes
    lerMatriz(matriz1, altura, largura);
    lerMatriz(matriz2, altura, largura);

    matrizR = strassen(matriz1, matriz2, largura);

    //Imprimir as matrizes
    //imprimirMatriz(matriz1, altura, largura, "Matriz 1");
    //imprimirMatriz(matriz2, altura, largura, "Matriz 2");
    //imprimirMatriz(matrizR, altura, largura, "Matriz 2");


    //Liberar memória alocada
    liberarMatriz(matriz1, altura);
    liberarMatriz(matriz2, altura);
    liberarMatriz(matrizR, altura);


    return 0;
}
