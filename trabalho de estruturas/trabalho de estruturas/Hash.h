#include <stdio.h>
#include <stdbool.h>
#include "dados.h"

#ifndef HASH
#define HASH
#define Max 31 

typedef struct HashTable {
	struct job* tabela[Max];
}HashTable;

static struct job* hashTable[Max];

job** iniciaHash(job* ht[]);
int hashval(int val);
job** InsertHashInicio(job* val, job* ht[]);
job** InsertcodHash(int* cod, job** ht);

job* jobHashProcura(int codigo, job* ht[]);
job** removeHashJob(job* ht[], int codigo);
job** alterarHashOp(job* ht[], int op, int novoop, int codigo);

void escreveHashFicheiro(job* ht[]);
job** lerHashFile(job* ht[]);


job** removeAll(job* ht[]);


#endif // !HASH