#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct {
    char label[SIZE];
    char operator[SIZE];
    char operand[SIZE];
} Instruction;

typedef struct {
    char key[SIZE];
    char value[SIZE];
} Symbol;

void split_string_by_instruct(char *str, const char *delim, Instruction instructions[], int *size) {
    int i = 0;
    char *arr[100];
    const char *token = strtok(str, delim);

    while (token != NULL && i < 100) {
        arr[i] = (char *) malloc(strlen(token) + 1);
        if (arr[i] == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        strcpy(arr[i++], token);
        token = strtok(NULL, delim);
    }

    if (i > 3 || i == 0) {
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

void search_opcode(FILE *fp, char *operator) {

}

void assemble_code(Instruction instructions[], int size, Symbol symbols[], int *symbol_size) {
    int LOCCTR = 0;
    int PGM_LENGTH = 0;
    int START_ADDR = LOCCTR;

    for (int i = 0; i < size; i++) {
        if (strcmp(instructions[i].operator, "START") == 0) {
            START_ADDR = atoi(instructions[i].operand);
            LOCCTR = START_ADDR;
        } else if (strcmp(instructions[i].operator, "END") == 0) {
            PGM_LENGTH = LOCCTR - START_ADDR;
            break;
        }
        // else {
        //     if (strcmp(instructions[i].label, "") != 0) {
        //         strcpy(symbols[(*symbol_size)].key, instructions[i].label);
        //         sprintf(symbols[(*symbol_size)++].value, "%d", LOCCTR);
        //     }
        //     LOCCTR += 3;
        // }
    }
}

void create_opcode(char *str, const char *delim, Symbol symtab[], int *size) {
    int i = 0;
    char *arr[100];
    const char *token = strtok(str, delim);

    while (token != NULL && i < 100) {
        arr[i] = (char *) malloc(strlen(token) + 1);
        if (arr[i] == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        strcpy(arr[i++], token);
        token = strtok(NULL, delim);
    }

    if (i > 2 || i == 0) {
        perror("Error: Invalid instruction format\n");
        exit(1);
    }


    // strcpy(instructions[(*size)].label, i == 1 || i == 2 ? "" : arr[0]);
    // strcpy(instructions[(*size)].operator, i == 1 || i == 2 ? arr[0] : arr[1]);
    // strcpy(instructions[(*size)++].operand, i == 1 ? "" : i == 2 ? arr[1] : arr[2]);

    // Free allocated memory
    for (int j = 0; j < i; j++)
        free(arr[j]);
}

int main() {
    FILE *input_fp = fopen("inputs/input.txt", "r");
    FILE *optab_fp = fopen("inputs/optab.txt", "r");

    if (input_fp == NULL) {
        perror("Error: File not found\n");
        return 1;
    }

    char *buffer = NULL;
    size_t bufsize = 0;

    Instruction instructions[SIZE];
    int size;

    Symbol symtab[SIZE], optab[SIZE];
    int symtab_size = 0, optab_size = 0;

    while (getline(&buffer, &bufsize, input_fp) != -1)
        split_string_by_instruct(buffer, " ", instructions, &size);

    create_optab(optab_fp, optab, &optab_size);
    assemble_code(instructions, size, symtab, &symtab_size);

    for(int i = 0; i < optab_size; i++) {
        printf("%s[%d] = %s\n", optab[i].key, i, optab[i].value);
    }

    // Clean up
    free(buffer);
    fclose(input_fp);
    fclose(optab_fp);

    return 0;
}
