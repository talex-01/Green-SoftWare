#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(char *arr[], int n) {
    int i, j;
    char *temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
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
    char **arr;
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

    // Ler a quantidade de strings no arquivo
    fread(&n, sizeof(int), 1, file);

    // Exibir o tamanho do array
    printf("Tamanho do array: %d\n", n);

    // Alocar memória para o array de ponteiros para strings
    arr = (char**) malloc(n * sizeof(char*));
    if (arr == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    // Ler as strings do arquivo
    for (i = 0; i < n; i++) {
        arr[i] = (char*) malloc(100 * sizeof(char));  // Aloca memória para cada string (tamanho máximo de 100 caracteres)
        fread(arr[i], sizeof(char), 100, file);  // Ler 100 caracteres por string
    }
    fclose(file);

    // Ordenar o array usando Bubble Sort
    bubbleSort(arr, n);

    // Mostrar as strings após a ordenação
    printf("Depois da ordenação:\n");
    for (i = 0; i < n; i++) {
        printf("%s ", arr[i]);  // Imprimir a string
    }
    printf("\n");

    // Liberar a memória alocada
    for (i = 0; i < n; i++) {
        free(arr[i]);  // Liberar cada string
    }
    free(arr);  // Liberar o array de ponteiros

    return 0;
}
