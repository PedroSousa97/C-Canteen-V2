#pragma once
#ifndef FUNCITONS_H
#define FUNCTIONS_H
#include <string>
#include "Entidade.h"
#include "Mesa.h"

using namespace std;

void Print(BSTM * x);
BSTM* adicionaElemBSTM(BSTM* root, Mesa* pessoa);
BSTM* novoNodoBSTM(Mesa* dados);
BST* adicionaElemBSTUlt(BST* root, Entidade* pessoa);
int contaLinhas(string nomeFicheiro);
void preencheArray(string * vectorGuarda, string nomeFicheiro);
void novaLista(dupListLigada * x);
void adicionaElementos(dupListLigada * x, dupListLigada::Item * item);
void novaLista(dupListLigadaM & x);
void adicionaElementos(dupListLigadaM & x, dupListLigadaM::Item * item);
void criaEntidade(string *v, string *z, string curso, dupListLigada* x, int grupo, bool estatutoespecial, bool studentorstaff, int ciclos, int numconstgrup);
void criaMesa(int tamanho, int lugaresoc, int nummesa, dupListLigadaM* z);
BST* novoNodoBST(Entidade* dados);
BST* adicionaElemBST(BST* root, Entidade* pessoa);
void Print(BST * x);
void sentaPessoas(dupListLigada* y, dupListLigadaM* z);
void movimentaPessoas(dupListLigada* y, dupListLigadaM* z);

#endif 