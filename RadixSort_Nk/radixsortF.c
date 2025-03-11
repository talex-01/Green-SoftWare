#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Função auxiliar para manipular bits de floats
uint32_t floatToSortableUint32(float f) {
    uint32_t u;
    memcpy(&u, &f, sizeof(float));
    // Se o número for negativo, inverte todos os bits (complemento de 1)
    // Se for positivo, inverte apenas o bit do sinal
    return (u & 0x80000000U) ? ~u : u ^ 0x80000000U;
}

// Função inversa: de volta para float
float sortableUint32ToFloat(uint32_t u) {
    // Desfazer transformação
    u = (u & 0x80000000U) ? u ^ 0x80000000U : ~u;
    float f;
    memcpy(&f, &u, sizeof(float));
    return f;
}

// Radix Sort para floats
void radixSortFloat(float arr[], int n) {
    uint32_t *intView = (uint32_t*) malloc(n * sizeof(uint32_t));
    uint32_t *output = (uint32_t*) malloc(n * sizeof(uint32_t));
    int count[256];
    int i, byte;

    // Transformar floats em inteiros ordenáveis
    for (i = 0; i < n; i++) {
        intView[i] = floatToSortableUint32(arr[i]);
    }

    // Radix Sort por bytes (4 bytes em float)
    for (byte = 0; byte < 4; byte++) {
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

    // Converter de volta para float
    for (i = 0; i < n; i++) {
        arr[i] = sortableUint32ToFloat(intView[i]);
    }

    free(intView);
    free(output);
}

int main(int argc, char *argv[]) {
    FILE *file;
    float *arr;
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
    arr = (float*) malloc(n * sizeof(float));
    if (arr == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    // Ler números
    fread(arr, sizeof(float), n, file);
    fclose(file);

    // Ordenar com Radix Sort
    radixSortFloat(arr, n);

    // Mostrar array ordenado
    printf("Array ordenado:\n");
    for (i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");

    // Liberar memória
    free(arr);
    return 0;
}
