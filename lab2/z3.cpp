#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int is_consonant(char c) {
    c = tolower(c);
    return isalpha(c) && !is_vowel(c);
}

char* process_string(const char* input) {
    int len = strlen(input);
    char* result = (char*)malloc((len * 3 + 1) * sizeof(char));
    if (!result) return NULL;

    int res_index = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '.' && i > 0 && i < len - 1 &&
            is_vowel(input[i - 1]) && is_consonant(input[i + 1])) {
            result[res_index++] = '.';
            result[res_index++] = '.';
            result[res_index++] = '.';
        } else if (input[i] != '.') {
            result[res_index++] = input[i];
        }
    }
    result[res_index] = '\0';
    return result;
}

int main() {
    FILE *fin, *fout;
    char *str = NULL;
    char ch;
    int size = 0;
    int capacity = 1;

    // Чтение из файла
    fin = fopen("file1.txt", "r");
    if (!fin) {
        printf("Cannot open file1.txt\n");
        return 1;
    }

    str = (char*)malloc(capacity * sizeof(char));
    if (!str) {
        fclose(fin);
        return 1;
    }

    while ((ch = fgetc(fin)) != EOF && ch != '\n') {
        if (size + 1 >= capacity) {
            capacity++;
            char *new_str = (char*)malloc(capacity * sizeof(char));
            if (!new_str) { free(str); fclose(fin); return 1; }
            for (int i = 0; i < size; i++) new_str[i] = str[i];
            free(str);
            str = new_str;
        }
        str[size++] = ch;
    }
    str[size] = '\0';
    fclose(fin);

    printf("Read from file: %s\n", str);

    // Обработка
    char* result = process_string(str);
    printf("Result: %s\n", result);

    // Запись в файл
    fout = fopen("file2.txt", "w");
    if (!fout) {
        printf("Cannot open file2.txt\n");
        free(str);
        free(result);
        return 1;
    }
    fprintf(fout, "%s", result);
    fclose(fout);

    printf("Result written to file2.txt\n");

    free(str);
    free(result);
    return 0;
}
