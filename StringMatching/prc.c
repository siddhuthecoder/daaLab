#include <stdio.h>

int main() {
    char character = '9';
    int numericValue = (int)character - '0';
    printf("The numeric value of '%c' is %d\n", character, numericValue);
    
    return 0;
}
