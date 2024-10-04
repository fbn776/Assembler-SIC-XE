#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct {
    char label[SIZE];
    char operator[SIZE];
    char operand[SIZE];
} Instruction;

void split_string_by_instruct(char *str, const char *delim, Instruction instructions[], int *size) {
    int i = 0;
    char *arr[100];
    const char *token = strtok(str, delim);

    while (token != NULL && i < 100) {
        arr[i] = (char *)malloc(strlen(token) + 1);
        if (arr[i] == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        strcpy(arr[i++], token);
        token = strtok(NULL, delim);
    }

    if(i > 3 || i == 0) {
        perror("Error: Invalid instruction format\n");
        exit(1);
    }

    strcpy(instructions[(*size)].label, i == 1 || i == 2 ? "" : arr[0]);
    strcpy(instructions[(*size)].operator, i == 1 || i == 2 ? arr[0] : arr[1]);
    strcpy(instructions[(*size)++].operand, i == 1 ? "" : i == 2 ? arr[1] : arr[2]);

    // Free allocated memory
    for (int j = 0; j < i; j++)
        free(arr[j]);
}

int main() {
    FILE *input_fp = fopen("inputs/input.txt", "r");

    if (input_fp == NULL) {
        perror("Error: File not found\n");
        return 1;
    }

    char *buffer = NULL;
    size_t bufsize = 0;
    Instruction instructions[SIZE];
    int size;

    while (getline(&buffer, &bufsize, input_fp) != -1)
        split_string_by_instruct(buffer, " ", instructions, &size);

    // for(int i = 0; i < size; i++) {
    //     printf("-----------------------------\n");
    //     printf("Label: %s\n", instructions[i].label);
    //     printf("Operator: %s\n", instructions[i].operator);
    //     printf("Operand: %s\n", instructions[i].operand);
    // }

    // Clean up
    free(buffer);
    fclose(input_fp);
    return 0;
}
