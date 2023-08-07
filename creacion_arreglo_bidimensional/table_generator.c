#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 50

// Función para buscar una palabra en un arreglo
int findWord(char words[MAX_WORDS][MAX_LENGTH], int count, char* word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    char filenames[3][15] = {"archivo1.txt", "archivo2.txt", "archivo3.txt"};
    FILE* file;
    char words[MAX_WORDS][MAX_LENGTH];
    int counts[3][MAX_WORDS] = {0};
    int totalCounts[MAX_WORDS] = {0};
    int totalWords = 0;

    // Leer los archivos y contar las palabras
    for (int i = 0; i < 3; i++) {
        file = fopen(filenames[i], "r");
        if (file == NULL) {
            printf("No se pudo abrir el archivo: %s\n", filenames[i]);
            return 1;
        }

        char word[MAX_LENGTH];
        while (fscanf(file, "%s", word) == 1) {
            int index = findWord(words, totalWords, word);
            if (index == -1) {
                strcpy(words[totalWords], word);
                counts[i][totalWords]++;
                totalCounts[totalWords]++;
                totalWords++;
            } else {
                counts[i][index]++;
                totalCounts[index]++;
            }
        }

        fclose(file);
    }

    // Imprimir la matriz
    for (int i = 0; i < totalWords; i++) {
        printf("%s\t", words[i]);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < totalWords; j++) {
            printf("%d\t", counts[i][j]);
        }
        printf("\n");
    }

    return 0;
}
