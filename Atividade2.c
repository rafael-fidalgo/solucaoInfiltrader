#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int menor_distancia(int arr1[], int arr2[], int tamanho1, int tamanho2) {
    int menor = INT_MAX;
    for (int i = 0; i < tamanho1; i++) {
        for (int j = 0; j < tamanho2; j++) {
            int distancia = abs(arr1[i] - arr2[j]);
            if (distancia < menor) {
                menor = distancia;
            }
        }
    }
    return menor;
}

int main() {
    int array1[] = {-1, 5, 8, 10, 15, 20, 25, 30, 35, 40};
    int array2[] = {26, 6, 9, 12, 18, 22, 27, 32, 37, 42};
    int tamanho1 = sizeof(array1) / sizeof(array1[0]);
    int tamanho2 = sizeof(array2) / sizeof(array2[0]);

    printf("Menor distancia: %d\n", menor_distancia(array1, array2, tamanho1, tamanho2));

    return 0;
}
