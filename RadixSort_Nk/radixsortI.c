#include <stdio.h>
#include <stdlib.h>

void radixSortInt(int arr[], int n) {
    int output[n];
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    for (int exp = 1; max/exp > 0; exp *= 10) {
        int count[10] = {0};
        for (int i = 0; i < n; i++) count[(arr[i]/exp)%10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i-1];
        for (int i = n - 1; i >= 0; i--) output[--count[(arr[i]/exp)%10]] = arr[i];
        for (int i = 0; i < n; i++) arr[i] = output[i];
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    int *arr;
    int n, i;

    // Verificar se o nome do arquivo foi passado como argumento
    if (argc < 2) {
        printf("Uso: %s <nome_do_arquivo_binario>\n", argv[0]);
        return 1;
    }

    // Abrir o arquivo binário passado como argumento
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    // Ler a quantidade de números no arquivo
    fread(&n, sizeof(int), 1, file);
    printf("Tamanho do array: %d\n", n);

    // Alocar memória para o array de inteiros
    arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    // Ler os números do arquivo
    fread(arr, sizeof(int), n, file);
    fclose(file);

    // Ordenar o array usando Radix Sort
    radixSortInt(arr, n);

    // Mostrar os números após a ordenação
    printf("Array ordenado:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Liberar a memória alocada
    free(arr);

    return 0;
}
