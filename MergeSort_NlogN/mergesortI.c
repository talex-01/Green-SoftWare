#include <stdio.h>
#include <stdlib.h>

// Função para mesclar dois subarrays em ordem crescente
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1; // Tamanho do subarray esquerdo
    int n2 = r - m;     // Tamanho do subarray direito

    // Arrays temporários para armazenar os subarrays
    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    // Copia os dados para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    // Mescla os arrays temporários de volta no array original
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar memória alocada
    free(L);
    free(R);
}

// Função recursiva do Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Encontra o ponto médio do array
        int m = l + (r - l) / 2;

        // Ordena as duas metades
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Mescla as duas metades
        merge(arr, l, m, r);
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

    // Exibir o tamanho do array
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

    // Mostrar os números antes da ordenação
    printf("Antes da ordenação:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Ordenar o array usando Merge Sort
    mergeSort(arr, 0, n - 1);

    // Mostrar os números após a ordenação
    printf("Depois da ordenação:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Liberar a memória alocada
    free(arr);

    return 0;
}
