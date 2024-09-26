#include <stdio.h>
#include <stdlib.h>
#include "strassen.h"

//Função para alocar memória para uma matriz de pixels
Pixel **alocarMatriz(int altura, int largura) {
    Pixel **matriz = (Pixel **)malloc(altura * sizeof(Pixel *));
    for (int i = 0; i < altura; i++) {
        matriz[i] = (Pixel *)malloc(largura * sizeof(Pixel));
    }
    return matriz;
}

//Função para ler os dados de uma matriz de pixels do arquivo
void lerMatriz(Pixel **matriz, int altura, int largura) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            scanf("%d %d %d", &matriz[i][j].r, &matriz[i][j].g, &matriz[i][j].b);
        }
    }
}

//Função para imprimir a matriz de pixels
void imprimirMatriz(Pixel **matriz, int altura, int largura, const char *nomeMatriz) {
    printf("%s:\n", nomeMatriz);
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            printf("(%d, %d, %d) ", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b);
        }
        printf("\n");
    }
}

//Função para liberar a memória alocada para a matriz
void liberarMatriz(Pixel **matriz, int altura) {
    for (int i = 0; i < altura; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

//Função para somar duas matrizes de pixel
Pixel **adicao(Pixel **matriz1, Pixel **matriz2, int largura){
    Pixel **aux = alocarMatriz(largura, largura);
    for(int i = 0; i < largura; i++){
        for(int j = 0; j < largura; j++){
            aux[i][j].r = matriz1[i][j].r + matriz2[i][j].r;
            aux[i][j].g = matriz1[i][j].g + matriz2[i][j].g;
            aux[i][j].b = matriz1[i][j].b + matriz2[i][j].b;
        }
    }
    return aux;
}

//Função para subtrair duas matrizes de pixel
Pixel **subtracao(Pixel **matriz1, Pixel **matriz2, int largura){
    Pixel **aux = alocarMatriz(largura, largura);
    for(int i = 0; i < largura; i++){
        for(int j = 0; j < largura; j++){
            aux[i][j].r = matriz1[i][j].r - matriz2[i][j].r;
            aux[i][j].g = matriz1[i][j].g - matriz2[i][j].g;
            aux[i][j].b = matriz1[i][j].b - matriz2[i][j].b;
        }
    }
    return aux;
}

Pixel **multiplicacao(Pixel **matriz1, Pixel **matriz2, int largura) {
    Pixel **matrizR = alocarMatriz(largura, largura);

    for (int i = 0; i < largura; i++) {
        for (int j = 0; j < largura; j++) {
            matrizR[i][j].r = 0;
            matrizR[i][j].b = 0;
            matrizR[i][j].g = 0;
        }
    }

    for (int i = 0; i < largura; i++) {
        for (int j = 0; j < largura; j++) {
            for (int k = 0; k < largura; k++) {
                matrizR[i][j].r += matriz1[i][k].r * matriz2[k][j].r;
                matrizR[i][j].b += matriz1[i][k].b * matriz2[k][j].b;
                matrizR[i][j].g += matriz1[i][k].g * matriz2[k][j].g;
            }
        }
    }

    return matrizR;
}


//Função para fazer multiplicação de matrizes pelo algoritmo de strassen
Pixel** strassen(Pixel **matriz1, Pixel **matriz2, int largura){
    int metade = largura/2;
    Pixel **matrizR;
    if (largura < 10){
        matrizR = multiplicacao(matriz1, matriz2, largura);
    } else { 

        matrizR = alocarMatriz(largura, largura);
        Pixel **A = alocarMatriz(largura, largura);
        Pixel **B = alocarMatriz(largura, largura);
        Pixel **C = alocarMatriz(largura, largura);
        Pixel **D = alocarMatriz(largura, largura);
        Pixel **E = alocarMatriz(largura, largura);
        Pixel **F = alocarMatriz(largura, largura);
        Pixel **G = alocarMatriz(largura, largura);
        Pixel **H = alocarMatriz(largura, largura);

        for(int i=0; i<metade; i++) {
		    for(int j=0; j<metade; j++) {
		        A[i][j].r = A[i][j].r;
		        B[i][j].r = A[i][metade+j].r;
		        C[i][j].r = A[metade+i][j].r;
		        D[i][j].r = A[metade+i][metade+j].r;
		        E[i][j].r = B[i][j].r;
		        F[i][j].r = B[i][metade+j].r;
		        G[i][j].r = B[metade+i][j].r;
		        H[i][j].r = B[metade+i][metade+j].r;
                A[i][j].b = A[i][j].b;
		        B[i][j].b = A[i][metade+j].b;
		        C[i][j].b = A[metade+i][j].b;
		        D[i][j].b = A[metade+i][metade+j].b;
		        E[i][j].b = B[i][j].b;
		        F[i][j].b = B[i][metade+j].b;
		        G[i][j].b = B[metade+i][j].b;
		        H[i][j].b = B[metade+i][metade+j].b;
                A[i][j].g = A[i][j].g;
		        B[i][j].g = A[i][metade+j].g;
		        C[i][j].g = A[metade+i][j].g;
		        D[i][j].g = A[metade+i][metade+j].g;
		        E[i][j].g = B[i][j].g;
		        F[i][j].g = B[i][metade+j].g;
		        G[i][j].g = B[metade+i][j].g;
		        H[i][j].g = B[metade+i][metade+j].g;
	   		}
		}

        Pixel **P1 = strassen(A, subtracao(F, H, metade), metade);
        Pixel **P2 = strassen(adicao(A, B, metade), H, metade);
        Pixel **P3 = strassen(adicao(C, D, metade), E, metade);
        Pixel **P4 = strassen(D, subtracao(G, E, metade), metade);
        Pixel **P5 = strassen(adicao(A, D, metade), adicao(E, H, metade), metade);
        Pixel **P6 = strassen(subtracao(B, D, metade), adicao(G, H, metade), metade);
        Pixel **P7 = strassen(subtracao(A, C, metade), adicao(E, F, metade), metade);

        Pixel **AEBG = subtracao(adicao(adicao(P5, P4, metade), P6, metade), P2, metade);
        Pixel **AFBH = adicao(P1, P2, metade);
        Pixel **CEDG = adicao(P3, P4, metade);
        Pixel **CFDH = subtracao(subtracao(adicao(P5, P1, metade), P3, metade), P7, metade);

        for(int i = 0; i < metade; i++) {
		    for(int j = 0; j < metade; j++) {
		        matrizR[i][j].r = AEBG[i][j].r;
		        matrizR[i][j+metade].r = AFBH[i][j].r;
		        matrizR[metade+i][j].r = CEDG[i][j].r;
		        matrizR[metade+i][metade+j].r = CFDH[i][j].r;
                matrizR[i][j].b = AEBG[i][j].b;
		        matrizR[i][j+metade].b = AFBH[i][j].b;
		        matrizR[metade+i][j].b = CEDG[i][j].b;
		        matrizR[metade+i][metade+j].b = CFDH[i][j].b;
                matrizR[i][j].g = AEBG[i][j].g;
		        matrizR[i][j+metade].g = AFBH[i][j].g;
		        matrizR[metade+i][j].g = CEDG[i][j].g;
		        matrizR[metade+i][metade+j].g = CFDH[i][j].g;
		    }
		}

        return matrizR;
    }

    return matrizR;
}