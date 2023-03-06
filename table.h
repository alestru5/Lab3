#ifndef TABLE_H
#define TABLE_H
int count_rel(Table *board, char *key);
int Add(Table *board);
int Find(Table *board);
int Delete(Table *board);
int CleanShow(Table *board);
int DirtyShow(Table *board);
int Reorg(Table *board);
void clear(Table *board);
#endif
