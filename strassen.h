//Definição da struct para armazenar um pixel RGB
typedef struct {
    int r, g, b;
} Pixel;

Pixel **alocarMatriz(int altura, int largura);
void lerMatriz(Pixel **matriz, int altura, int largura);
void imprimirMatriz(Pixel **matriz, int altura, int largura, const char *nomeMatriz);
void liberarMatriz(Pixel **matriz, int altura);
Pixel **adicao(Pixel **matriz1, Pixel **matriz2, int largura);
Pixel **subtracao(Pixel **matriz1, Pixel **matriz2, int largura);
Pixel **multiplicacao(Pixel **matriz1, Pixel **matriz2, int largura);
Pixel** strassen(Pixel **matriz1, Pixel **matriz2, int largura);
