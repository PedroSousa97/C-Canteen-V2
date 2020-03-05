#pragma once
#ifndef MESA_H
#define MESA_H
#include <string>
#include "Entidade.h"
using namespace std;

struct dupListLigada {
	struct Item {					//Dupla lista ligada para cria��o da fila de entidades
		Entidade* pessoa;
		Item* next;					//Apontador para pr�ximo e para anterior para ser mais f�cil trabalhar os nodos da lista. Al�m disso com dois apontadores torna-se mais dif�cil perder informa��o
		Item* previous;

	};
	Item* apinicio;					//Apontador para o in�cio da fila (�ltimo elemento a chegar)
	Item* apfim;					//Apontador para o fim da fila (neste caso o primeiro utente a chegar e o primeiro a ser servido)
};

struct Mesa {
	int tamanho;					//Tamanho da mesa
	int lugaresocupados;			//Lugares ocupados por alunos/staff sentado na mesa
	int numdemesa;					//N�mero da mesa
	dupListLigada* x;				//Dupla lista ligada com entidades
};


struct dupListLigadaM {					//dupla lista ligada para cria��o da lista de mesas
	struct Item {
		Mesa* mesa;						//apontador para o tipo de dados de Mesa
		Item* next;						//apontador para pr�ximo e anterior pelas mesmas raz�es que acima foram expostas
		Item* previous;

	};
	Item* apinicio;						//apontadores para o in�cio e fim da fila
	Item* apfim;
};

struct BST {
		Entidade* x;					//Estrutura simples e igual � lecionada para cria��o de um nodo de um �rvore de pesquisa bin�ria de entidades
		BST* left;
		BST* right;

};
struct BSTM {							//Estrutura simples e igual � lecionada para cria��o de um nodo de um �rvore de pesquisa bin�ria de Mesas
	Mesa* x;
	BSTM* left;
	BSTM* right;

};

#endif 