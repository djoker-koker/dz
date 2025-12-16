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

// Функция обработки строки (для тестов)
char* process_string_calloc(const char* input) {
    int len = strlen(input);
    char* result = (char*)calloc(len * 3 + 1, sizeof(char));
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
    char *str = NULL;
    char ch;
    int size = 0;
    int capacity = 5;

    str = (char*)calloc(capacity, sizeof(char));
    if (!str) return 1;

    printf("Enter string (end with newline):\n");

    while ((ch = getchar()) != '\n') {
        if (size + 1 >= capacity) {
            capacity += 5;
            char *new_str = (char*)realloc(str, capacity * sizeof(char));
            if (!new_str) { free(str); return 1; }
            str = new_str;
        }
        str[size++] = ch;
    }
    str[size] = '\0';

    char* result = process_string_calloc(str);
    printf("Original: %s\n", str);
    printf("Result: %s\n", result);

    free(str);
    free(result);
    return 0;
}
