#include <stdio.h>
#include <stdlib.h>

int atoi(const char *nptr) {
    int result = 0;
    int sign = 1;
    int i = 0;
    

    while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n') {
        i++;
    }
    

    if (nptr[i] == '-') {
        sign = -1;
        i++;
    } else if (nptr[i] == '+') {
        i++;
    }
    

    while (nptr[i] >= '0' && nptr[i] <= '9') {
        result = result * 10 + (nptr[i] - '0');
        i++;
    }
    
    return sign * result;
}

int main() {
    char str[] = "AB373CD";
    int val = atoi(str);
    printf("The value of str is %d\n", val);
    return 0;
}
