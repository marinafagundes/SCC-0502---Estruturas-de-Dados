#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    unsigned long long horas;
    unsigned long long minutos;
    unsigned long long segundos;
} Tempo;

Tempo somaTempos(Tempo t1, Tempo t2) {
    Tempo resultado;
    resultado.horas = t1.horas + t2.horas;
    resultado.minutos = t1.minutos + t2.minutos;
    resultado.segundos = t1.segundos + t2.segundos;

    if (resultado.segundos >= 60) {
        resultado.minutos += resultado.segundos / 60;
        resultado.segundos %= 60;
    }

    if (resultado.minutos >= 60) {
        resultado.horas += resultado.minutos / 60;
        resultado.minutos %= 60;
    }

    return resultado;
}

Tempo hanoi(unsigned long long n) {
    if (n == 1) {
        Tempo t;
        t.horas = 0;
        t.minutos = 0;
        t.segundos = 1;
        return t;
    }

    Tempo metade = hanoi(n - 1);
    Tempo tempoMovimento;
    tempoMovimento.horas = 0;
    tempoMovimento.minutos = 0;
    tempoMovimento.segundos = pow(2, n - 1);

    Tempo tempoTotal = somaTempos(metade, tempoMovimento);

    return tempoTotal;
}

int main() {
    unsigned long long numDiscos;
    scanf("%llu", &numDiscos);

    Tempo tempoFinal = hanoi(numDiscos);

    printf("%02llu:%02llu:%02llu\n", tempoFinal.horas, tempoFinal.minutos, tempoFinal.segundos);

    return 0;
}
