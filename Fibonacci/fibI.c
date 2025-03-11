#include <stdio.h>
#include <stdlib.h>

long long fibonacci_iterativo(int n) {
    if (n <= 1)
        return n;
    
    long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {  // Verifica se foi passado um argumento
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Converte argumento para inteiro

    if (n < 0) {
        printf("Por favor, insira um número inteiro não negativo.\n");
        return 1;
    }

    printf("Fibonacci iterativo(%d) = %lld\n", n, fibonacci_iterativo(n));
    return 0;
}

