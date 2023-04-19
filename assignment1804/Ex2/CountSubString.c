#include <stdio.h>
#include <string.h>

int countSubstr(char* str, char* substr) {
    int count = 0;
    int len_str = strlen(str); //21
    int len_substr = strlen(substr); //2
    if (len_str < len_substr) {
        return 0;
    }
    // len_str - len_substr = 19
    for (int i = 0; i <= len_str - len_substr; i++) {
        if (strncmp(str + i, substr, len_substr) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "This is a test string";
    char substr[] = "is";
    int count = countSubstr(str, substr);
    printf("The substring '%s' occurs %d times in the string '%s'.\n", substr, count, str);
    return 0;
}
