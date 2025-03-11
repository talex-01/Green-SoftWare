#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Estrutura para armazenar resultados
typedef struct {
    char nome_arquivo[512];
    double media_package;
    double media_tempo;
    int valido; // 1 se dados válidos, 0 se não
} Resultado;

// Função para processar um CSV específico e armazenar o resultado
Resultado processar_csv(const char *caminho_arquivo, const char *nome_arquivo) {
    Resultado res;
    strcpy(res.nome_arquivo, nome_arquivo);
    res.media_package = 0.0;
    res.media_tempo = 0.0;
    res.valido = 0;

    FILE *file;
    char linha[1024];
    double soma_package = 0.0, soma_tempo = 0.0;
    int contador = 0;

    file = fopen(caminho_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s!\n", caminho_arquivo);
        return res;
    }

    // Ignorar cabeçalho
    fgets(linha, sizeof(linha), file);

    while (fgets(linha, sizeof(linha), file)) {
        char *token;
        int coluna = 0;
        double package = 0.0, time = 0.0;
        int campo_vazio_package = 1, campo_vazio_time = 1;

        // Quebra linha por vírgula
        token = strtok(linha, ",");

        while (token != NULL) {
            // Remover espaços iniciais
            while (*token == ' ') token++;

            if (coluna == 3) { // Package
                if (strlen(token) > 0) {
                    package = atof(token);
                    campo_vazio_package = 0;
                }
            } else if (coluna == 7) { // Time (ms)
                if (strlen(token) > 0) {
                    time = atof(token);
                    campo_vazio_time = 0;
                }
            }

            token = strtok(NULL, ",");
            coluna++;
        }

        // Se ambos os campos foram lidos corretamente
        if (!campo_vazio_package && !campo_vazio_time) {
            soma_package += package;
            soma_tempo += time;
            contador++;
        }
    }

    fclose(file);

    // Se houver dados válidos, calcular médias
    if (contador > 0) {
        res.media_package = soma_package / contador;
        res.media_tempo = soma_tempo / contador;
        res.valido = 1;
    }

    return res;
}

// Função de comparação para qsort (ordena por nome do arquivo)
int comparar_resultados(const void *a, const void *b) {
    const Resultado *ra = (const Resultado *)a;
    const Resultado *rb = (const Resultado *)b;
    return strcmp(ra->nome_arquivo, rb->nome_arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <diretorio>\n", argv[0]);
        return 1;
    }

    const char *diretorio = argv[1];
    struct dirent *entrada;
    DIR *dp = opendir(diretorio);

    if (dp == NULL) {
        printf("Erro ao abrir diretório %s\n", diretorio);
        return 1;
    }

    // Array para armazenar nomes de arquivos (suportando até 1000 arquivos CSV)
    Resultado resultados[1000];
    int total_arquivos = 0;

    // Buscar arquivos CSV
    while ((entrada = readdir(dp))) {
        if (strstr(entrada->d_name, ".csv")) {
            char caminho_arquivo[512];
            snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/%s", diretorio, entrada->d_name);

            // Processar e armazenar resultado
            Resultado res = processar_csv(caminho_arquivo, entrada->d_name);
            resultados[total_arquivos++] = res;
        }
    }

    closedir(dp);

    // Ordenar resultados por nome do ficheiro
    qsort(resultados, total_arquivos, sizeof(Resultado), comparar_resultados);

    // Escrever resultados no arquivo final
    FILE *saida = fopen("resultado_final.csv", "w");
    if (saida == NULL) {
        printf("Erro ao criar arquivo de saída!\n");
        return 1;
    }

    // Escrever cabeçalho
    fprintf(saida, "ficheiro;energia;tempo\n");

    // Escrever dados processados
    for (int i = 0; i < total_arquivos; i++) {
        if (resultados[i].valido) {
            fprintf(saida, "%s;%.2lf;%.2lf\n", resultados[i].nome_arquivo, resultados[i].media_package, resultados[i].media_tempo);
        } else {
            fprintf(saida, "%s;N/A;N/A\n", resultados[i].nome_arquivo);
        }
    }

    fclose(saida);
    printf("\nArquivo resultado_final.csv gerado com sucesso!\n");
    return 0;
}
