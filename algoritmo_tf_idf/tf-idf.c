/*
    ALUMNOS:
    * Alata Gutierrez, Jose Rodolfo
    * Rivera Inche, Erly Toribio
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_DOCUMENTS 10
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordInfo;

void calculateTFIDF(float tfidf[MAX_DOCUMENTS][MAX_WORDS], int wordCount[MAX_DOCUMENTS][MAX_WORDS], int numDocuments, int numWords) {
    int i, j;
    int docFrequency[MAX_WORDS] = {0};

    // Calcula la frecuencia del documento para cada palabra
    for (i = 0; i < numDocuments; i++) {
        for (j = 0; j < numWords; j++) {
            if (wordCount[i][j] > 0) {
                docFrequency[j]++;
            }
        }
    }

    // Calcula la puntuación TF-IDF para cada palabra en cada documento
    for (i = 0; i < numDocuments; i++) {
        for (j = 0; j < numWords; j++) {
            float tf = (float) wordCount[i][j] / (float) numWords;
            float idf = log((float) numDocuments / (float) docFrequency[j]);
            tfidf[i][j] = tf * idf;
        }
    }
}

// Función para buscar una palabra en un arreglo
int findWord(char words[MAX_WORDS][MAX_WORD_LENGTH], int count, char* word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int numDocuments = 3;
    
    char filenames[3][15] = {"sample1.txt", "sample2.txt", "sample3.txt"};
    FILE* file;
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    
    for(int i=0; i<MAX_WORDS; i++){
        strcpy(words[i], "-1");
    }
    
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

        char word[MAX_WORD_LENGTH];
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


    int numWords = 0;
    
    for(int i=0; i<MAX_WORDS; i++){
        if(strcmp(words[i], "-1") != 0){
            numWords++;
        }
    }


    float tfidf[MAX_DOCUMENTS][MAX_WORDS];

    calculateTFIDF(tfidf, counts, numDocuments, numWords);

    // Imprime la puntuación TF-IDF para cada palabra en cada documento
    int i, j;
    for (i = 0; i < numDocuments; i++) {
        printf("Documento %d:\n", i + 1);
        for (j = 0; j < numWords; j++) {
            printf("Palabra %d - %s: %f\n", j+1, words[j], tfidf[i][j]);
        }
        printf("\n");
    }

    return 0;
}


