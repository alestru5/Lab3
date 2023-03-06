#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Item{
    unsigned int element;
}Item;
typedef struct KeySpace{
    Item *info;
    char *key;
    int busy;
    int release;

}KeySpace;
typedef struct Table{
    KeySpace *ks;
    int msize;
    int csize;
}Table;
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
int count_rel(Table *board, char *key){
    for (int i = board->csize-1; i >= 0; i--){
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy != 0){
            return board->ks[i].release;
        }
    }
    return -1;
}
int Add(Table *board){
    if (board->csize == board->msize) {
        printf("Ошибка: Переполнение. Попробуйте Reorganization.\n");
        return 1;
    }
    printf("Введите ключ:\n");
    char *key = getStr();
    int rel;
    rel = count_rel(board, key);
    board->ks = realloc(board->ks, sizeof(KeySpace) * (board->csize + 1));
    board->ks[board->csize].info = malloc(sizeof(Item));
    board->ks[board->csize].busy = 1;
    board->ks[board->csize].key = key;
    if (rel >= 0) {
        board->ks[board->csize].release = rel + 1;
    } else{
        board->ks[board->csize].release = 1;
    }
    printf("Введите значение по ключу:\n");
    int el = getInt();
    board->ks[board->csize].info->element = el;
    board->csize += 1;
    return 1;
}
int Find(Table *board){
    printf("Введите ключ, элементы которого хотите увидеть:\n");
    char *key = getStr();
    int f = 1;
    for (int i = 0; i < board->csize; i++){
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy != 0){
            printf("busy: %d key: %s release: %d element: %d\n", board->ks[i].busy, board->ks[i].key,
                   board->ks[i].release, board->ks[i].info->element);
            f = 0;
        }
    }
    if (f){
        printf("Такого ключа не существует.\n");
    }
    free(key);
    return 1;
}
int Delete(Table *board){
    printf("Введите ключ удаляемого элемента:\n");
    char *key = getStr();
    int rel = count_rel(board, key), n;
    if (rel == -1){
        printf("Ошибка: Такого элемента не существует.\n");
	free(key);
        return 1;
    }
    if (rel > 1){
        printf("Есть %d элемента с этим ключом. Что хотите удалить?\n", rel);
        for (int i = 0; i < board->csize; i++){
            if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy == 1) {
                printf("%d. %d (release: %d)\n", board->ks[i].release, board->ks[i].info->element, board->ks[i].release);
            }
        }
        printf("%d. ALL\n", rel + 1);
        do{
            n = getInt();
            if (n <= rel + 1 && n > 0){
                break;
            }
            printf("Введено некоректное число. Повторите попытку.\n");
        } while(n > rel + 1 || n <= 0);
    } else{
        n = 1;
    }
    for (int i = 0; i < board->csize; i++){
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy == 1) {
            if (board->ks[i].release == n) {
                board->ks[i].busy = 0;
            } else if (board->ks[i].release > n){
                board->ks[i].release -= 1;
            } else if(n == rel + 1){
                board->ks[i].busy = 0;
            }
        }
    }
    free(key);
    return 1;
}
int CleanShow(Table *board){
    int f = 1;
    if (board->csize == 0){
        printf("Таблица пустая.\n");
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
        if (board->ks[i].busy != 0) {
            f = 0;
            printf("busy: %d key: %s release: %d element: %d\n", board->ks[i].busy, board->ks[i].key,
                   board->ks[i].release, board->ks[i].info->element);
        }
    }
    if (f){
        printf("Таблица пустая.\n");
    }
    return 1;
}
int DirtyShow(Table *board){
    if (board->csize == 0){
        printf("Таблица пустая.\n");
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
            printf("busy: %d key: %s release: %d element: %d\n", board->ks[i].busy, board->ks[i].key,
                   board->ks[i].release, board->ks[i].info->element);
    }
    return 1;
}
int Reorg(Table *board){
    int i = 0;
    while (i < board->csize){
        if (board->ks[i].busy == 0) {
		free(board->ks[i].key);
            for (int j = i; j < board->csize - 1; j++) {
                board->ks[j].busy = board->ks[j + 1].busy;
                board->ks[j].key = board->ks[j + 1].key;
                board->ks[j].info->element = board->ks[j + 1].info->element;
                board->ks[j].release = board->ks[j + 1].release;
            }
            board->csize -= 1;
	    free(board->ks[board->csize].info);
            board->ks = realloc(board->ks, sizeof(KeySpace) * board->csize);
            i -= 1;
        }
        i += 1;
    }
    return 1;
}
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
void clear(Table *board){
    for (int i = 0; i < board->csize; i++){
        free(board->ks[i].info);
	free(board->ks[i].key);
    }
    free(board->ks);
}
int main() {
    Table board = {NULL, 5, 0};
    int num_func;
    int (*fptr[])(Table *) = {NULL, Add, Find, Delete, CleanShow, DirtyShow, Reorg};
    while(num_func = menu()){
        if (!fptr[num_func](&board)){
            break;
        }
    }
    clear(&board);
    printf("END");
    return 0;
}
