#include <stdio.h>
#include <stdlib.h>

void bubbleSort(double arr[], int n) {
    int i, j;
    double temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca os elementos
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    double *arr;
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

    // Exibir o tamanho do array
    printf("Tamanho do array: %d\n", n);

    // Alocar memória para o array de doubles
    arr = (double*) malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    // Ler os números do arquivo
    fread(arr, sizeof(double), n, file);
    fclose(file);

    // Ordenar o array usando Bubble Sort
    bubbleSort(arr, n);

    // Mostrar os números após a ordenação
    printf("Depois da ordenação:\n");
    for (i = 0; i < n; i++) {
        printf("%lf ", arr[i]);
    }
    printf("\n");

    // Liberar a memória alocada
    free(arr);

    return 0;
}
