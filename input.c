#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
char *getStr(){
    char *ans = malloc(sizeof(char));
    char n;
    int len = 0;
    n = getchar();
    while(n != EOF && n != '\n'){
        ans = realloc(ans, sizeof(char) * (len + 2));
        ans[len] = n;
        len += 1;
        n = getchar();
    }
    ans[len] = '\0';
    return ans;
}
int getInt(){
    int n, a;
    do{
        n = scanf("%d", &a);
        if (n < 0){
            return 0;
        }
        if (n == 0 || a < 0){
            printf("Введен некоректный символ, повторите попытку:\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }while(n == 0 || a < 0);
    scanf("%*[^\n]");
    scanf("%*c");
    return a;
}
