#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "menu.h"
int menu(){
    const char *msg[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Clean Show", "5. Dirty Show", "6. Reorganization"};
    const int msg_count = sizeof(msg) / sizeof(msg[0]);
    int n;
    for (int i = 0; i < msg_count; i++){
        printf("%s\n", msg[i]);
    }
    printf("Введите значение:\n");
    do{
        n = getInt();
        if (n < msg_count && n >= 0){
            return n;
        }
        printf("Введено некоректное число. Повторите попытку.\n");
    } while(n >= msg_count);
}
