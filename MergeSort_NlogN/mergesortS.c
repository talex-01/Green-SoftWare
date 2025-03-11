#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(char arr[][20], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    char (*L)[20] = (char(*)[20])malloc(n1 * sizeof(char[20]));
    char (*R)[20] = (char(*)[20])malloc(n2 * sizeof(char[20]));

    for (int i = 0; i < n1; i++)
        strcpy(L[i], arr[l + i]);
    for (int i = 0; i < n2; i++)
        strcpy(R[i], arr[m + 1 + i]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(arr[k], L[i]);
            i++;
        } else {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(char arr[][20], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    char (*arr)[20];
    int n;

    if (argc < 2) {
        printf("Uso: %s <nome_do_arquivo_binario>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    fread(&n, sizeof(int), 1, file);  // Lê o número de elementos
    arr = (char(*)[20])malloc(n * sizeof(char[20]));

    fread(arr, sizeof(char[20]), n, file);  // Lê os elementos do array
    fclose(file);

    printf("Antes da ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, 0, n - 1);

    printf("Depois da ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
