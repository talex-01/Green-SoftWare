#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Função auxiliar para manipular bits de doubles
uint64_t doubleToSortableUint64(double d) {
    uint64_t u;
    memcpy(&u, &d, sizeof(double));
    // Se o número for negativo, inverte todos os bits (complemento de 1)
    // Se for positivo, inverte apenas o bit do sinal
    return (u & 0x8000000000000000ULL) ? ~u : u ^ 0x8000000000000000ULL;
}

// Função inversa: de volta para double
double sortableUint64ToDouble(uint64_t u) {
    // Desfazer transformação
    u = (u & 0x8000000000000000ULL) ? u ^ 0x8000000000000000ULL : ~u;
    double d;
    memcpy(&d, &u, sizeof(double));
    return d;
}

// Radix Sort para doubles
void radixSortDouble(double arr[], int n) {
    uint64_t *intView = (uint64_t*) malloc(n * sizeof(uint64_t));
    uint64_t *output = (uint64_t*) malloc(n * sizeof(uint64_t));
    int count[256];
    int i, byte;

    // Transformar doubles em inteiros ordenáveis
    for (i = 0; i < n; i++) {
        intView[i] = doubleToSortableUint64(arr[i]);
    }

    // Radix Sort por bytes (8 bytes em double)
    for (byte = 0; byte < 8; byte++) {
        // Zerando contador
        for (i = 0; i < 256; i++) count[i] = 0;

        // Contar ocorrências de cada byte
        for (i = 0; i < n; i++) {
            int byteVal = (int)((intView[i] >> (byte * 8)) & 0xFF);
            count[byteVal]++;
        }

        // Acumular contagem
        for (i = 1; i < 256; i++) count[i] += count[i - 1];

        // Construir saída ordenada
        for (i = n - 1; i >= 0; i--) {
            int byteVal = (int)((intView[i] >> (byte * 8)) & 0xFF);
            output[--count[byteVal]] = intView[i];
        }

        // Copiar de volta para a visualização inteira
        for (i = 0; i < n; i++) intView[i] = output[i];
    }

    // Converter de volta para double
    for (i = 0; i < n; i++) {
        arr[i] = sortableUint64ToDouble(intView[i]);
    }

    free(intView);
    free(output);
}

int main(int argc, char *argv[]) {
    FILE *file;
    double *arr;
    int n, i;

    // Verificar argumento
    if (argc < 2) {
        printf("Uso: %s <nome_do_arquivo_binario>\n", argv[0]);
        return 1;
    }

    // Abrir arquivo
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    // Ler quantidade de números
    fread(&n, sizeof(int), 1, file);
    printf("Tamanho do array: %d\n", n);

    // Alocar array
    arr = (double*) malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    // Ler números
    fread(arr, sizeof(double), n, file);
    fclose(file);

    // Ordenar com Radix Sort
    radixSortDouble(arr, n);

    // Mostrar array ordenado
    printf("Array ordenado:\n");
    for (i = 0; i < n; i++) {
        printf("%lf ", arr[i]);
    }
    printf("\n");

    // Liberar memória
    free(arr);
    return 0;
}
