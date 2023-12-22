#include <stdio.h>
#include <stdbool.h>
#define q 22

int Text[100];
int Pattern[100];

bool compare(int s1[], int s2[], int m) {
    for (int i = 0; i < m; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

int Hash(int num) {
    return num % q;
}

int convertToNumber(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result = result * 10 + arr[i];
    }
    return result;
}

int main() {
    int textLength, patternLength;

    printf("Enter the length of the text: ");
    scanf("%d", &textLength);
    printf("Enter the text (digits separated by space): ");
    for (int i = 0; i < textLength; i++) {
        scanf("%d", &Text[i]);
    }

    printf("Enter the length of the pattern: ");
    scanf("%d", &patternLength);
    printf("Enter the pattern (digits separated by space): ");
    for (int i = 0; i < patternLength; i++) {
        scanf("%d", &Pattern[i]);
    }


    int pat = convertToNumber(Pattern, patternLength);
    int hashOfPattern = Hash(pat);
    int text = convertToNumber(Text, patternLength);
    int hashOfText = Hash(text);
    
    for (int i = 0; i <= textLength - patternLength; i++) {
        if (hashOfPattern == hashOfText) {
            int s1[patternLength];
            for (int j = 0; j < patternLength; j++) {
                s1[j] = Pattern[j];
            }
            int s2[patternLength];
            for (int j = 0; j < patternLength; j++) {
                s2[j] = Text[i + j];
            }
            if (compare(s1, s2, patternLength)) {
                printf("Pattern Occurs With Shift %d\n", i);
            }
        }
        if(i<textLength - patternLength){
            int temp[patternLength];
             for (int j = 0; j < patternLength; j++) {
                temp[j] = Text[i+1+ j];
            }
            int num=convertToNumber(temp,patternLength);
            hashOfText=Hash(num);
        }

        
    }
    return 0;
}
