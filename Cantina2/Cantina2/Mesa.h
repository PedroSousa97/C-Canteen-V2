#pragma once
#ifndef MESA_H
#define MESA_H
#include <string>
#include "Entidade.h"
using namespace std;

struct dupListLigada {
	struct Item {					//Dupla lista ligada para criação da fila de entidades
		Entidade* pessoa;
		Item* next;					//Apontador para próximo e para anterior para ser mais fácil trabalhar os nodos da lista. Além disso com dois apontadores torna-se mais difícil perder informação
		Item* previous;

	};
	Item* apinicio;					//Apontador para o início da fila (último elemento a chegar)
	Item* apfim;					//Apontador para o fim da fila (neste caso o primeiro utente a chegar e o primeiro a ser servido)
};

struct Mesa {
	int tamanho;					//Tamanho da mesa
	int lugaresocupados;			//Lugares ocupados por alunos/staff sentado na mesa
	int numdemesa;					//Número da mesa
	dupListLigada* x;				//Dupla lista ligada com entidades
};


struct dupListLigadaM {					//dupla lista ligada para criação da lista de mesas
	struct Item {
		Mesa* mesa;						//apontador para o tipo de dados de Mesa
		Item* next;						//apontador para próximo e anterior pelas mesmas razões que acima foram expostas
		Item* previous;

	};
	Item* apinicio;						//apontadores para o início e fim da fila
	Item* apfim;
};

struct BST {
		Entidade* x;					//Estrutura simples e igual à lecionada para criação de um nodo de um árvore de pesquisa binária de entidades
		BST* left;
		BST* right;

};
struct BSTM {							//Estrutura simples e igual à lecionada para criação de um nodo de um árvore de pesquisa binária de Mesas
	Mesa* x;
	BSTM* left;
	BSTM* right;

};

#endif 