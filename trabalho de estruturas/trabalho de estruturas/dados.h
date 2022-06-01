/*
* Autor: Raquel
* Email: a23999@alunos.ipca.pt
* Date:2022
* Desc: Defenicao de structs e fun�oes
* ???
*/
#ifndef DADOS
#define DADOS

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS


# pragma region structs

typedef struct maquina
{
	int maq;
	int tp;
	struct maquina* next;
}maquina;

typedef struct operacao
{
	int op;
	struct maquina *maquina;
	struct opracao* next;
	
}operacao;

typedef struct job
{
	int codigo;
	struct job* next;
	struct operacao *operacao;
}job;

#pragma endregion

#pragma region Existe
/*@brief Verifica se maquina existe. Se existir devolve Bool!*/
bool ExisteMaq(maquina* h, int maq);
/*@brief Verifica se operacao existe. Se existir devolve Bool!*/
bool Existeoperacao(operacao* h, int op);
/*@brief  Verifica se job existe. Se existir devolve Bool!*/
bool Existejob(job* h, int codigo);
#pragma endregion
#pragma region Criar
/** @brief cria um job, insere o inteiro recebido na estrutura job e retorna a mesma*/
job* CriaJob(int codigo, job* h);
/* @brief cria uma opera��o, insere o inteiro recebido na estrutura opera��o e retorna a mesma*/
job* CriaOperacao(int op, job* j);
/* @brief cria uma maquina, insere os inteiros, maquina e tempo, recebidos na estrutura opera��o e retorna a mesma*/
operacao* CriaMaquina(int maq, int tp, operacao* op);
#pragma endregion
#pragma region Inserir
/*@brief Cria uma maquina,uma opera��o e um job e insere tudo dentro do job*/
job* insereAll(int codigo, int op, int maq, int tp, job* h);
/* @brief Insere um novo job no in�cio da estrutura*/
job* InserirJob(job* h, job* novo);
/* @brief Insere uma opera�ao dentro de um job*/
job* InserirOperacao(job* processo, operacao* h);
/* @brief Insere uma maquina dentro de uma opera��o*/
operacao* inserirMaq(operacao* h, maquina* m);
#pragma endregion 
#pragma region Remove 
/* @brief remove a lista de jobs toda lista*/
void removeAllJob(job* work);
/* @brief fun�ao auxiliar de remover jobs*/
job* removeJob(job* work);
/*@brief fun��o auxiliar de remo�ao de opera��es*/
operacao* removeOp(operacao* op);
/** @brief fun�ao auxiliar de remo�ao de maquinas*/
maquina* removeMaq(maquina* m);
#pragma endregion
#pragma region Procura e altera
/*@brief  Verifica se operacao existe. Se existir devolve endere�o operacao!*/
operacao* ProcuraOperacao(operacao* h, int op);
/*@brief Verifica se maquina existe. Se existir devolve endere�o maquina!*/
maquina* ProcuraMaq(maquina* h, int maq);
/*@brief Verifica se o job existe. Se existir devolve o codigo do job!*/
job* ProcuraJob(job* h, int codigo);
/*@brief Altera operacao da lista de jobs*/
job* AterarOperacao(job* h, int op, int novaop);
/*@brief Altera maquina*/
job* AterarMaq(job* h, int op, int m, int novamaq, int novotp);
#pragma endregion 
#pragma region file
/*@brief escreve a lista de jobs num ficheiro .txt*/
void escreveFile(job* processo);
/*L� ficheiro .txt com as listas guardadas*/
job* lerFile();
#pragma endregion 
#pragma region Tempo
/** @brief Tempo Min*/
maquina* TempoMin(operacao* h);
/* @brief Tempo Max*/
maquina* TempoMax(operacao* h);
/* @brief Tempo Max*/
int Media(operacao* h);
/*@brief minimo*/
int minimo(job* processo);
/*@brief maximo*/
int maximo(job* processo);
#pragma endregion
//bool gravarjobs(char* jobs, job* h);
//job* lerjob(char* jobs);
//void MostraLista(job* h);
//void Mostrajob(job* nodo);
//void MostraMaq(maquina* m, int codigo);
//
//bool gravaroperacao(char* operacoes, operacao* h);
//void Mostralistaop(operacao* h);
//void Mostraoperacao(operacao* nodo);
#endif;