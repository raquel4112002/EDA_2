#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

job** iniciaHash(job* ht[])
{
	int i;
	for (i = 0; i < Max; i++)
	{
		ht[i] = NULL;
		ht[i] = (job*)malloc(sizeof(job));
		ht[i]->next = NULL;
	} 
	return *ht;
}

int hashval(int val)
{
	if (val > 0)
		return(val % Max);
	return 0;
}

job** InsertcodHash(int* cod, job** ht) {

	//Cria nova celula para a lista
	job* j = (struct job*)malloc(sizeof(struct job));
	j->codigo = cod;
	j->next = NULL;
	*ht = InsertHashInicio(cod, ht);
	return *ht;
}


job** InsertHashInicio(job* h, job* ht[])
	{
		int pos = hashval(h->codigo);
		h->next = ht[pos];
		ht[pos] = h;
		return *ht;
	}

job* jobHashProcura(int codigo, job* ht[])
{
	if (!ht)return NULL;
	int pos = hashval(codigo);
	if (ht[pos] == NULL) return NULL;
		return(ProcuraJob);
}

job** removeAll(job* ht[])
{
	if (!ht) return NULL;

	job* head, t;
	for (int i = 0; i < Max; i++)
		if (ht[i] != NULL)
		{
			head = ht[i];
			removeAllJob(head);
			ht[i] = NULL;
		}
	return *ht;
}

job** removeHashJob(job* ht[], int codigo)
{
	if (!ht) return NULL;

	job* aux = jobHashProcura(ht, codigo);
	if (aux == NULL) return *ht;
	ht = removeJob(aux);
	return *ht;
}

job** alterarHashOp(job* ht[], int op, int novoop, int codigo)
{
	if (!ht) return NULL;
	job* aux = jobHashProcura(ht, codigo);
	ht = AterarOperacao(aux, op, novoop);
	return *ht;
}

//void ShowHash(job* ht[])
//{
//	for (int i = 0; i < Max; i++) {
//		if (ht[i] != NULL)
//		{
//			printf("Index: %d \t", i);
//			MostraLista(ht[i]);
//		}
//	}
//}
void escreveHashFicheiro(job* ht[])
{
	FILE* fj;

	fj = fopen("Job.txt", "w");

	for (int i = 0; i < Max; i++)
	{
		escreveFile(ht[i]);
	}
	fclose(fj);
}

job** lerHashFile(job* ht[])
{
	FILE* fj;
	int codigo = 0, op = 0, maq = 0, tp = 0;

	ht = iniciaHash(ht);

	fj = fopen("Job.txt", "r");

	if (fj)
	{
		do
		{
			fscanf("%d,%d,%d,%d", codigo, op, maq, tp);
			int pos = hashval(codigo);
			ht[pos] = insereAll(codigo, op, maq, tp, ht[pos]);

			if (feof(fj))
			{
				break;
			}

		} while (1);
		fclose(fj);
	}
	return *ht;
}
