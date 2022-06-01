/*
* Autor: Raquel
* Email: a23999@alunos.ipca.pt
* Date:2022
* Desc: Listas Ligadas 
* ???
*/
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include "Dados.h"

#pragma region inserir 
/*
		* @brief cria uma operação, insere o inteiro recebido na estrutura operação e retorna a mesma
		* @param[in] op		Codigo da operação a inserir
		* @param[in] j		job onde vai ser inserida a operação
		* @return    estrutura job onde inserida a nova operaçao
*/

job* CriaOperacao(int op, job*j) 
{
	operacao* newoperacao = (operacao*)malloc(sizeof(operacao));
	if (newoperacao == NULL) return NULL; // verificar se a memoria
	newoperacao->op = op;
	newoperacao->maquina = NULL;
	newoperacao->next = NULL;
	return InserirOperacao( newoperacao, j);
}
/*
* @brief cria um job, insere o inteiro recebido na estrutura job e retorna a mesma
* @param[in] codigo		Codigo do job a inserir
* @return    estrutura job onde inserido o novo job
*/
job* CriaJob(int codigo, job* h)
{
	job* newjob = (job*)malloc(sizeof(job));
	if (newjob == NULL)return NULL;
	newjob->codigo = codigo;
	newjob->operacao = NULL;
	newjob->next = NULL;
	return InserirJob (newjob,h);
}

/*
* @brief cria uma maquina, insere os inteiros, maquina e tempo, recebidos na estrutura operação e retorna a mesma
* @param[in] op		Codigo da operação a inserir
* @param[in] maq    nova maquina a criar
* @param[in] tp     tp da nova maquina
*  @return    estrutura operaçao onde foi inserido a maquina e o tempo
*/

operacao* CriaMaquina(int maq, int tp, operacao*op)
{
	maquina* newMaq = (maquina*)malloc(sizeof(maquina));
	if (newMaq == NULL) return NULL;
	newMaq->maq = maq;
	newMaq->tp = tp;
	newMaq->next = NULL;
	return inserirMaq (newMaq,op);
}
/** 
 *@brief Cria uma maquina,uma operação e um job e insere tudo dentro do job
 * @param[in] codigo	codigo do job
 * @param[in] op	codigo da operação
 * @param[in] maq  código da maquina
 * @param[in] tp  tempo da máquina
 * @param[in] h lista onde vai ser inserido o job
 * @return	ob com tudo inserido
*/

job* insereAll(int codigo, int op, int maq, int tp, job* h)
{
	h = CriaJob(codigo, h);
	h = CriaOperacao(op, h);
	h->operacao = CriaMaquina(maq, tp, h->operacao);

	return h;
}

/*
* @brief Insere um novo job no início da estrutura
* @param[in] h    Inicio da Lista
* @param[in] novo   Novo job a inserir
* @return    Lista de jobs
*/
job* InserirJob(job* h, job* novo)
{
	if (novo == NULL) return h; // verifico se  os apontadores sao validos
	if (h == NULL)return novo;
	// ver se existe o job
	if (Existejob(h, novo->codigo)) return h; // se existir nao insere
	novo->next = h;
	h = novo;
	return h;
}

/*	
* @brief		Insere uma operaçao dentro de um job
* @param[in]	processo Lista de jobs onde vai ser inserida a operaçao
* @param[in]	oper	  Operaçao a inserir
* @return		Estrutura job onde foi inserida a operação
*
*/
job* InserirOperacao(job* processo, operacao* oper)
{
	if (processo == NULL) return NULL;

	if (oper == NULL) return NULL;
	if (!processo->operacao)		//se não existir nenhuma operaçao no job,insere a operaçao recebida
	{
		processo->operacao = oper;
		return processo;
	}
	if (Existeoperacao(processo->operacao, oper->op)) return processo; //se ja existir a operaçao no job, nao insere

	oper->next = processo->operacao;
	processo->operacao = oper;			//insere no inicio da lista a nova operaçao

	return processo;
}

/*
* @brief		Insere uma maquina dentro de uma operação
* @param[in]	h Lista de operações onde vai ser inserida a maquina
* @param[in]	m		 maquina a inserir
* @return		Estrutura job onde foi inserida a operação
*/

operacao* inserirMaq(operacao* op, maquina* m)
{
	if (op == NULL) return NULL;
	if (m == NULL) return op;
	if (!op->maquina)			//se não existir nenhuma maquina na operaçao,insere a maquina e respetivo tempo
	{
		op->maquina = m;
		return op;
	}

	if (ExisteMaq(op->maquina, m->maq) )return op; //se já existir a maquina na operçao, nao insere

	m->next = op->maquina;
	op->maquina = m;
	return op;
}


#pragma endregion
#pragma region Remove

/*
* @brief		remove a lista de jobs toda lista
* @param[in]	work  lista a ser removida
*/

void removeAllJob(job* work)
{
	job* aux = work;
	while (aux != NULL)
	{
		job* aux2 = aux;
		aux = aux2->next;
		removeJob(aux2);
	}
}

/*
* @brief		funçao auxiliar de remover jobs
* @param[in]	work  job a ser removido
* @return		lista sem o job a ser removido
*/

job* removeJob(job* work)
{
	operacao* aux = work->operacao;
	job* toDelete = work;
	work = toDelete->next;
	while (aux != NULL)
	{
		operacao* aux2 = aux;
		aux->next = aux2->next;
		removeOp(aux2);

	}
	free(toDelete);

	return work;

}

/*
* @brief		função auxiliar de remoçao de operações
* @param[in]	op  operação a ser removida
* @return		lista sem a operação a ser removida
*/
operacao* removeOp(operacao* op)
{
	maquina* aux = op->maquina;
	operacao* toDelete = op;
	op = toDelete->next;
	while (aux != NULL)
	{
		maquina* aux2 = aux;
		aux->next = aux2->next;
		removeMaq(aux2);

	}
	free(toDelete);

	return op;
}

/*
* @brief		funçao auxiliar de remoçao de maquinas
* @param[in]	m maquina a ser removida 
* @return		lista sem maquina a ser removida
*/
maquina* removeMaq(maquina* m)
{
	maquina* toDelete = m;
	m = toDelete->next;
	free(toDelete);

	return m;
}

#pragma endregion
#pragma region procura e altera 

/**
* @brief  Verifica se operacao existe. Se existir devolve endereço operacao!
* @param [in] h		Inicio da Lista
* @param [in] op	código da operacao a procurar
* @return	Apontador para a operacao encontrada
*/

operacao* ProcuraOperacao(operacao* h, int op)
{
	if (h == NULL)return NULL;
	else
	{
		operacao* aux = h;
		while (aux != NULL)
		{
			if (aux->op == op)
			{
				return (aux);
			}
			aux = aux->next;
		}
		return NULL;
	}
}

/**
* @brief Verifica se maquina existe. Se existir devolve endereço maquina!
* @param [in] h		Inicio da Lista
* @param [in] maq	código da maquina a procurar
* @return	Apontador para a maquina encontrada
*/

  maquina* ProcuraMaq(maquina* h, int maq)
{
	if (h == NULL)return NULL;
	else
	{
		maquina* aux = h;
		while (aux != NULL)
		{
			if (aux-> maq == maq)
			{
		
				return (aux);
			}
			aux = aux->next;
		}
		return NULL;
	}
}
  /**
* @brief Verifica se o job existe. Se existir devolve o codigo do job!
* @param [in] h		Inicio da Lista
* @param [in] codigo	código da maquina a procurar
* @return	Apontador para o job a encontrada
*/
  job* ProcuraJob(job* h, int codigo)
  {
	  if (h == NULL)return NULL;
	  else
	  {
		  job* aux = h;
		  while (aux != NULL)
		  {
			  if (aux->codigo == codigo)
			  {

				  return (aux);
			  }
			  aux = aux->next;
		  }
		  return NULL;
	  }
  }


  /**
* @brief Altera operacao da lista de jobs
* @param [in]	h	Apontador para inicio da Lista
* @param [in]	op  Codigo da operacao a alterar
* @param [in]	novaop	nova operacao
* @return	lista de jobs com o codigo da operaçao alterada
*/
 job* AterarOperacao(job* h, int op, int novaop)
{
	 operacao* aux;

	 if (!h) return NULL;

	 aux = ProcuraOperacao(h->operacao, op);
	 aux->op = novaop;

	 return h;
}

/**
* @brief Altera maquina
* @param [in]	h	Apontador para inicio da Lista
* @param [in]	op  Codigo da operacao a a encontrar
* @param [in]   m   codigo de maquina a alterar
* @param [in]	novamaq	nova maquina
* @param [in    novotp  novo tempo
* @return	Apontador para Lista
*/

job* AterarMaq(job* h, int op, int m , int novamaq,int novotp)
{
	maquina* aux;
	operacao* aux2;
	if (!h)return NULL;
	aux2 = ProcuraOperacao(h->operacao, op);
	aux = ProcuraMaq(aux2->maquina, m);


	if (aux)
	{
		aux->maq = novamaq;
		aux->tp = novotp;
	}
	return h;
}

#pragma endregion
#pragma region Existe

/**
* @brief  Verifica se job existe. Se existir devolve Bool!
* @param [in] h		Inicio da Lista
* @param [in] codigo	código do job a procurar
* @return	True/False
*/

bool Existejob(job* h, int codigo)
{
	job* aux = h;
	if (h == NULL) return false;
	while (aux != NULL)
	{
		if (aux->codigo == codigo)
			return true;
		else
		{
			aux = aux->next;
		}
	}
	return false;
}

/**
* @brief Verifica se operacao existe. Se existir devolve Bool!
* @param [in] h		Inicio da Lista
* @param [in] op	código da operacao a procurar
* @return	True/False
*/
bool Existeoperacao(operacao* h, int op)
{
	operacao* aux = h;
	if (h == NULL) return false;
	while (aux != NULL)
	{
		if (aux->op == op)
			return true;
		else
		{
			aux = aux->next;
		}
	}
	return false;
}

/**
* @brief Verifica se maquina existe. Se existir devolve Bool!
* @param [in] h		Inicio da Lista
* @param [in] maq	código da maquina a procurar
* @return	True/False
*/

bool ExisteMaq(maquina* h, int maq)
{
	maquina* aux = h;
	if (h == NULL) return false;
	while (aux != NULL)
	{
		if (aux->maq == maq)
			return true;
		else
		{
			aux = aux->next;
		}
	}
	return false;
}
#pragma endregion
#pragma region Tempos

/**
* @brief Tempo Min
* @param [in]	h	Apontador para inicio da Lista
* @return	aux  o menor valor 
*/

maquina* TempoMin(operacao* h)
{
	if (!h) return NULL;
	if (!h->maquina)
	{
		return NULL;
	}
	maquina* aux = h->maquina;
	maquina* aux2 = h->maquina->next;
	while (aux2)
	{
		if (aux->tp > aux2->tp) // se for menor aux fica com esse valor 
		{
			aux = aux2;
		}
		aux2 = aux2->next;
	}
	return aux; // retorna o menor
}

/**
* @brief Tempo Max
* @param [in]	h	Apontador para inicio da Lista
* @return	aux  o maior valor
*/

maquina*TempoMax(operacao* h)
{
	if (!h) return NULL;
	if (!h->maquina)
	{
		return NULL;
	}
	maquina* aux = h->maquina;
	maquina* aux2 = h->maquina->next;
	while (h->maquina->next)
	{
		if (aux->tp < aux2->tp) // se for maior aux fica com esse valor 
		{
			aux = aux2;
		}
		aux2 = aux2->next;
	}
	return aux; // retorna o maior
}

/**
* @brief Tempo Max
* @param [in]	h	Apontador para inicio da Lista
* @return	valor da media 
*/

int Media(operacao* h)
{
	float media = 0, x = 0;
	if (!h) return 0;
	while (h->maquina)
	{
		media += h->maquina->tp;
		h->maquina = h->maquina->next;
		x++;
	}
	media = media / x;
	return media;
}

/**
* @brief minimo
* @param [in]	processo	Apontador para inicio da Lista
* @return	soma   minimo tempo para fazer todas as operacoes
*/

int minimo(job* processo)
{
	maquina* aux;
	job* aux2 = processo;
	int soma = 0;
	if (!processo) return 0;
	while (aux2->operacao)
	{
		aux = TempoMin(aux2->operacao);	//determina a maquina que demora o menor tempo 
		if (aux)
		{
			//MostraMaq(aux, aux2->operacao->op);		//escreve a operaçao em causa e a maquina que demora o menor tempo a efetuar a operaçao	
			soma += aux->tp;
		}
		aux2->operacao = aux2->operacao->next;  // vai para a proxima
	}
	return soma;
}

/**
* @brief maximo
* @param [in]	processo	Apontador para inicio da Lista
* @return	soma   maximo tempo para fazer todas as operacoes
*/

int maximo(job* processo)
{
	maquina* aux;
	job* aux2 = processo;
	int soma = 0;
	if (!processo)return 0;
	while (aux2->operacao)
	{
		aux = TempoMax(aux2->operacao);//determina a maquina que demora o menor tempo 
		if (aux)
		{
			//MostraMaq(aux, aux2->operacao->op);		//escreve a operaçao em causa e a maquina que demora o menor tempo a efetuar a operaçao
				
			soma += aux->tp;
		}
		aux2->operacao = aux2->operacao->next;
	}
	return soma;
}

#pragma endregion
#pragma region File
/**
*@brief escreve a lista de jobs num ficheiro .txt
* @param[in]	processo	lista de tipo job
*/
void escreveFile(job* processo)
{
	FILE* fj;
	fj = fopen("Job.txt", "w");
	while (processo)
	{
		while (processo->operacao)
		{
			while (processo->operacao->maquina)
			{
				fprintf(fj, "%d;%d;%d;%d\n", processo->codigo, processo->operacao->op, processo->operacao->maquina->maq, processo->operacao->maquina->tp);
				processo->operacao->maquina = processo->operacao->maquina->next;
			}
			processo->operacao = processo->operacao->next;
		}
		processo = processo->next;
	}

	fclose(fj);
}
/// <summary>
/// Lê ficheiro .txt com as listas guardadas
/// </summary>
/// <returns>lista de jobs</returns>
job* lerFile()
{
	FILE* fj;
	int jobCod, opCod, m, tem;
	job* processo = NULL;
	fj = fopen("Job.txt", "r");

	if (fj)
	{
		do
		{
			fscanf(fj, "%d;%d;%d;%d", &jobCod, &opCod, &m, &tem);
			processo = insereAll(jobCod, opCod, m, tem, processo);
			if (feof(fj))
			{
				break;
			}
		} while (1);
	}
	



//	if (fj)
//	{
//		do
//		{
//			if (!processo)
//			{
//				fscanf(fj, "%d;%d;%d;%d", &jobCod, &opCod, &m, &tem);
//				processo = CriaJob(jobCod);
//				processo->operacao = CriaOperacao(opCod);
//				processo->operacao->maquina = CriaMaquina(m, tem);
//			}
//			else	
//			{
//				fscanf(fj, "%d;%d;%d;%d", &jobCod, &opCod, &m, &tem);
//				aux = CriaJob(jobCod);
//				aux->operacao = CriaOperacao(opCod);
//				aux->operacao->maquina = CriaMaquina(m, tem);
//				processo = InserirJob(processo, aux);
//				processo = InserirOperacao(processo, aux->operacao);
//				processo->operacao = inserirMaq(processo->operacao, aux->operacao->maquina);		
//			}
//			if (feof(fj))//quando chegar ao final do ficheiro para de ler
//			{
//				break;
//			}
//		} while (1);	
//		fclose(fj);
//	}
//	return processo;
}




 
//bool gravarjobs(char* file, job* h)
//{
//	FILE* fp;
//	if (h == NULL) return false;
//	if ((fp = fopen(file, "wb")) == NULL)return false;
//	 gravar resgistos
//	job* aux = h;
//	File auxjob;
//	while (aux)
//	{
//		auxjob.codigo = aux->codigo;
//		fwrite(&auxjob, sizeof(File), 1, fp);
//		aux = aux->next;
//	}
//	fclose(fp);
//	return true;
//}
//
//bool gravaroperacao(char* file, operacao* h)
//{
//	FILE* fo;
//	if (h == NULL) return false;
//	if ((fo = fopen(file, "wb")) == NULL)return false;
//	 gravar resgistos
//	operacao* aux = h;
//	File auxoperacao;
//	while (aux)
//	{
//		auxoperacao.op = aux->op;
//		fwrite(&auxoperacao, sizeof(File), 1,fo);
//		aux = aux->next;
//	}
//	fclose(fo);
//	return true;
//}
//
// File* lerFile(char* file)
//{
//	FILE* fp;
//	File* h = NULL;
//	File* aux;
//	
//
//	if ((fp = fopen(file, "rb")) == NULL)return NULL;
//	 le registos no ficheiro
//	File  auxjob;
//	File auxoperacao;
//	while (fread(&auxjob, &auxoperacao, sizeof(File), 8, fp))
//	{
//		aux = CriaJob(auxjob.codigo);
//		h = InserirJob(h, aux);
//		aux = CriaOperacao(auxoperacao.op);
//		h = InserirOperacao(h, aux);
//	}
//	fclose(fp);
//	return h;
//}
//
//void MostraLista(job* h)
//{
//	job* aux = h;
//	while (aux)
//	{
//		Mostrajob(aux);
//		aux = aux->next;
//	}
//}
//void Mostrajob(job* nodo)
//{
//	if (nodo != NULL)
//	{
//		printf("Job= %d\n", nodo->codigo);
//	}
//}
//void Mostralistaop(operacao* h)
//{
//	operacao* aux = h;
//	while (aux)
//	{
//		Mostraoperacao(aux);
//		aux = aux->next;
//	}
//}
//void Mostraoperacao(operacao* nodo)
//{
//	if (nodo != NULL)
//	{
//		printf("operacao= %d\n", nodo->op);
//	}
//}
//void MostraMaq(maquina* m, int op)
//{
//	if (m)
//	{
//		printf("Operacao: %d\t", op);
//		printf("Maquina: %d\t", m->maq);
//		printf("Tempo: %d\n", m->tp);
//	}
//}

//
//void Showlist(job* j) {
//	if (j == NULL) {
//		return(NULL);
//	}
//	else {
//		while (j != NULL) {
//			j = j->next;
//		}
//	}
//	return(j);
//}

#pragma endregion
