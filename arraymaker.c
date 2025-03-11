#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_STRING_LEN 20 // Tamanho fixo para cada string

// Função para gerar strings aleatórias
void random_string(char *str, size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < length - 1; i++) {
        int key = rand() % (int)(sizeof charset - 1);
        str[i] = charset[key];
    }
    str[length - 1] = '\0';
}


// Função para gerar e guardar INTs
void generate_and_save_int_array(const char *filename, int size, int ordenado) {
    FILE *file = fopen(filename, "wb");  // Abrir arquivo binário para escrita
    if (!file) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    // Primeiro, escrevemos o número de elementos no arquivo
    fwrite(&size, sizeof(int), 1, file);

    // Alocar memória para o array de inteiros
    int *array = malloc(size * sizeof(int));
    if (!array) {
        perror("Erro de memória");
        exit(1);
    }

    // Preencher o array com valores aleatórios
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000000;
    }

    // Se o array for para ser ordenado
    if (ordenado) {
        // Ordenar o array (usando qsort)
        qsort(array, size, sizeof(int), (int (*)(const void*, const void*))strcmp);
    }

    // Escrever o conteúdo do array no arquivo
    fwrite(array, sizeof(int), size, file);
    
    // Fechar o arquivo e liberar memória
    fclose(file);
    free(array);
}

void generate_and_save_float_array(const char *filename, int size) {
    FILE *file = fopen(filename, "wb");
    if (!file) { perror("Erro ao abrir ficheiro"); exit(1); }

    // Escreve o tamanho no início do ficheiro
    fwrite(&size, sizeof(int), 1, file);

    float *array = malloc(size * sizeof(float));
    if (!array) { perror("Erro de memória"); exit(1); }

    for (int i = 0; i < size; i++) array[i] = ((float)rand() / RAND_MAX) * 10000000.0f;

    fwrite(array, sizeof(float), size, file);
    fclose(file);
    free(array);
}


void generate_and_save_double_array(const char *filename, int size) {
    FILE *file = fopen(filename, "wb");
    if (!file) { perror("Erro ao abrir ficheiro"); exit(1); }

    // Escreve o tamanho no início do ficheiro
    fwrite(&size, sizeof(int), 1, file);

    double *array = malloc(size * sizeof(double));
    if (!array) { perror("Erro de memória"); exit(1); }

    for (int i = 0; i < size; i++) array[i] = ((double)rand() / RAND_MAX) * 10000000.0;

    fwrite(array, sizeof(double), size, file);
    fclose(file);
    free(array);
}


void generate_and_save_string_array(const char *filename, int size) {
    FILE *file = fopen(filename, "wb");
    if (!file) { perror("Erro ao abrir ficheiro"); exit(1); }

    // Escreve o tamanho no início do ficheiro
    fwrite(&size, sizeof(int), 1, file);

    char str[MAX_STRING_LEN];
    for (int i = 0; i < size; i++) {
        random_string(str, MAX_STRING_LEN);
        fwrite(str, sizeof(char), MAX_STRING_LEN, file);
    }

    fclose(file);
}


int main() {
    char tipo[10];
    int tamanho, ordenado;
    char filename[100]; // Nome do ficheiro final

    printf("Digite o tipo do array (int, float, double, string): ");
    scanf("%9s", tipo);

    printf("Digite o tamanho do array: ");
    scanf("%d", &tamanho);

    // Perguntar ao usuário se o array deve ser ordenado (apenas para inteiros)
    if (strcmp(tipo, "int") == 0) {
        printf("Deseja o array de inteiros ordenado? (1 para sim, 0 para não): ");
        scanf("%d", &ordenado);
    } else {
        ordenado = 0; // Não aplica para tipos não inteiros
    }

    // Criar nome do ficheiro automaticamente com tipo e tamanho
    snprintf(filename, sizeof(filename), "array_%s_%d_sorted.bin", tipo, tamanho);

    srand(time(NULL)); // Inicializar gerador aleatório

    // Escolha do tipo e chamada da função correta
    if (strcmp(tipo, "int") == 0) {
        generate_and_save_int_array(filename, tamanho, ordenado);
        printf("Array de inteiros criado em '%s'\n", filename);
    } else if (strcmp(tipo, "float") == 0) {
        generate_and_save_float_array(filename, tamanho);
        printf("Array de floats criado em '%s'\n", filename);
    } else if (strcmp(tipo, "double") == 0) {
        generate_and_save_double_array(filename, tamanho);
        printf("Array de doubles criado em '%s'\n", filename);
    } else if (strcmp(tipo, "string") == 0) {
        generate_and_save_string_array(filename, tamanho);
        printf("Array de strings criado em '%s'\n", filename);
    } else {
        printf("Tipo desconhecido!\n");
    }

    return 0;
}
