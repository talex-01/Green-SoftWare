#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RADIX 256  // 256 possíveis caracteres ASCII

// Função para obter o dígito de uma posição específica em uma string
int getDigit(char *str, int place) {
    if (place < strlen(str)) {
        return str[place];  // Retorna o caractere em código ASCII
    }
    return 0;  // Retorna 0 para posições além do tamanho da string
}

// Função para ordenar as strings usando Radix Sort
void radixSortString(char *arr[], int n) {
    char **output = malloc(n * sizeof(char*));
    if (!output) {
        printf("Erro ao alocar memória para Radix Sort.\n");
        exit(1);
    }

    // Encontrar o tamanho da maior string
    int maxLength = strlen(arr[0]);
    for (int i = 1; i < n; i++) {
        if (strlen(arr[i]) > maxLength) {
            maxLength = strlen(arr[i]);
        }
    }

    // Ordenar cada caractere, de trás para frente
    for (int place = maxLength - 1; place >= 0; place--) {
        int count[RADIX] = {0};

        // Contagem de ocorrências dos dígitos (caracteres)
        for (int i = 0; i < n; i++) {
            int digit = getDigit(arr[i], place);
            count[digit]++;
        }

        // Modificar o vetor count para que ele contenha a posição final de cada elemento
        for (int i = 1; i < RADIX; i++) {
            count[i] += count[i - 1];
        }

        // Construir o vetor de saída
        for (int i = n - 1; i >= 0; i--) {
            int digit = getDigit(arr[i], place);
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // Copiar o vetor de saída de volta para o vetor original
        memcpy(arr, output, n * sizeof(char*));
    }

    free(output);
}

int main(int argc, char *argv[]) {
    FILE *file;
    char **arr;
    int n, i;

    // Verificar se o nome do arquivo foi passado
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
    printf("Tamanho do array: %d\n", n);

    // Alocar memória para o array de strings
    arr = malloc(n * sizeof(char*));
    if (arr == NULL) {
        printf("Erro ao alocar memória para array.\n");
        fclose(file);
        return 1;
    }

    // Ler as strings do arquivo
    for (i = 0; i < n; i++) {
        arr[i] = malloc(21 * sizeof(char));  // Assumindo que as strings têm até 20 caracteres
        fread(arr[i], sizeof(char), 20, file);
        arr[i][20] = '\0';  // Garantir que a string seja null-terminated
    }
    fclose(file);

    // Mostrar as strings antes da ordenação
    //printf("Antes da ordenação:\n");
    //for (i = 0; i < n; i++) {
    //    printf("%s\n", arr[i]);
    //}
    //printf("\n");

    // Ordenar as strings usando Radix Sort
    radixSortString(arr, n);

    // Mostrar as strings após a ordenação
    printf("Depois da ordenação:\n");
    for (i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    // Liberar a memória alocada
    for (i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
