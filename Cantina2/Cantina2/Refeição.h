#pragma once
#ifndef REFEIÇÃO_H
#define REFEIÇÃO_H
#include <string>
using namespace std;

struct Refeiçao {
	string entrada;                 //Prato inserido pelo utilizador como entrada
	string pratoprincipal;			//Prato inserido pelo utilizador como prato principal
	float custo;					//Preço inserido pelo utilizador para a refeição
};


#endif 