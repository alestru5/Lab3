#ifndef TYPE_H
#define TYPE_H
typedef struct Item{
    unsigned int  element;
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
#endif
