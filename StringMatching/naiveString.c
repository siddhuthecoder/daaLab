#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool compare(char s1[], char s2[], int m) {
    for (int i = 0; i < m; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

void NAIVE_STRING_MATCHER(char T[], char P[]) {
    int n = 0, m = 0;
    while (T[n] != '\0') {
        n++;
    }
    while (P[m] != '\0') {
        m++;
    }

    for (int i = 0; i <= n - m; i++) {
        char s1[m];
        for (int j = 0; j < m; j++) {
            s1[j] = P[j];
        }
        char s2[m];
        for (int j = 0; j < m; j++) {
            s2[j] = T[i + j];
        }
        if (compare(s1, s2, m)) {
            printf("Pattern Occurs With Shift %d\n", i);
        }
    }
}

int main() {
    char text[100];
    char pattern[50];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    
    int i = 0;
    while (text[i] != '\0') {
        if (text[i] == '\n') {
            text[i] = '\0';
            break;
        }
        i++;
    }

    i = 0;
    while (pattern[i] != '\0') {
        if (pattern[i] == '\n') {
            pattern[i] = '\0';
            break;
        }
        i++;
    }

    NAIVE_STRING_MATCHER(text, pattern);

    return 0;
}
