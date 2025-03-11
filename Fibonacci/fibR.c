#include <stdio.h>
#include <stdlib.h>

// Implementação recursiva (ineficiente)
long long fibonacci_rec(int n) {
    if (n <= 1)
        return n;
    return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0) {
        printf("Número deve ser não negativo!\n");
        return 1;
    }

    printf("Fibonacci recursivo(%d) = %lld\n", n, fibonacci_rec(n));

    return 0;
}
