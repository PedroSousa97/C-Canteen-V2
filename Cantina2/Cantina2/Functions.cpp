#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "Entidade.h"
#include "Functions.h"
#include "Mesa.h"
using namespace std;



int contaLinhas(string nomeFicheiro) {

	fstream myFile;
	string line;
	int conta = 0;
	myFile.open(nomeFicheiro, ios::in);						//Função que abre um fecheiro de texto e retorna a quantidade de linhas que foram lidas
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			conta++;

		}
	}
	myFile.close();
	return conta;
}

void preencheArray(string * vectorGuarda, string nomeFicheiro) {
	fstream myFile;
	string line;
	int conta = 0;
	myFile.open(nomeFicheiro, ios::in);
	if (myFile.is_open()) {
		while (getline(myFile, line)) {					//Função que a cada linha de texto do ficheiro irá corresponder a uma posição de memória de um dado vetor
			vectorGuarda[conta] = line;
			conta++;
		}
	}
	myFile.close();
}

void novaLista(dupListLigada * x) {						//Função para criação de uma nova lista ligada
	x->apinicio = NULL;
	x->apfim = NULL;
}

void adicionaElementos(dupListLigada * x, dupListLigada::Item * item) {			//Função para preenchimento da nova dupla lista ligada
	if (x->apinicio == NULL && x->apfim == NULL) {

		x->apfim = item;
		item->previous = NULL;
		item->next = NULL;
	}
	else if (x->apinicio==NULL){
		
		item->next = x->apfim;
		x->apfim->previous = item;
		x->apinicio = item;

	}
	else {
		item->next = x->apinicio;
		item->previous = NULL;
		x->apinicio->previous = item;
		x->apinicio = item;
	}
}
void novaLista(dupListLigadaM & x) {						//Função para criação de uma nova lista ligada
	x.apinicio = NULL;
	x.apfim = NULL;
}

void adicionaElementos(dupListLigadaM & x, dupListLigadaM::Item * item) {			//Função para preenchimento da nova dupla lista ligada
	if (x.apinicio == NULL && x.apfim == NULL) {

		x.apfim = item;
		item->previous = NULL;
		item->next = NULL;
	}
	else if (x.apinicio == NULL) {

		item->next = x.apfim;
		x.apfim->previous = item;
		x.apinicio = item;

	}
	else {
		item->next = x.apinicio;
		item->previous = NULL;
		x.apinicio->previous = item;
		x.apinicio = item;
	}
}

void criaEntidade(string *v, string *z, string curso, dupListLigada* x, int grupo, bool estatutoespecial, bool studentorstaff, int ciclos, int numconstgrup) {
	int tamanhov = contaLinhas("primeiro_nome.txt");
	int tamanhoz = contaLinhas("ultimo_nome.txt");								//Inteiros utilizados para criar os randoms de 0 até ao tamanho do vetor que guarda as informações relativas aos momes e cursos
	int tamanhoy = contaLinhas("cursos.txt");
	int randomfirstname = 0 + (std::rand() % ((tamanhov - 1) - 0 + 1));
	int randomsecondname = 0 + (std::rand() % ((tamanhoz - 1) - 0 + 1));		//Randoms própriamente ditos entre 0 e tamanho do vetor que nos dará nomes e cursos aleatórios
	int randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
	int randomcargo = 0 + (std::rand() % (2 - 0 + 1));
	
	
		if (studentorstaff == true) {												//Se for aluno, que não seja de estatuto especial, a entidade será criada desta forma:
			Entidade *aluno = new Entidade;
			aluno->studentorstaff = true;
			aluno->estatuto = false;
			aluno->numcosntgrupo = numconstgrup;
			aluno->ciclosrestantes = ciclos;
			aluno->cargo = "Aluno";
			aluno->prim_nome = v[randomfirstname];
			aluno->seg_nome = z[randomsecondname];
			aluno->num_mec = 10000 + (std::rand() % (99999 - 10000 + 1));
			aluno->num_grupo_dep = grupo;
			aluno->course = curso;
			aluno->plafond = 1 + (std::rand() % (1 - 100 + 1));
			dupListLigada::Item* pessoa = new dupListLigada::Item;
			pessoa->pessoa = aluno;
			adicionaElementos(x, pessoa);

		} if (studentorstaff == false) {											//Se for staff, a entidade será criada desta forma:
			Entidade *staff = new Entidade;
			staff->studentorstaff = false;
			staff->estatuto = false;
			staff->numcosntgrupo = numconstgrup;
			staff->ciclosrestantes = ciclos;
			staff->cargo = "Staff";
			staff->prim_nome = v[randomfirstname];
			staff->seg_nome = z[randomsecondname];
			staff->num_mec = 10000 + (std::rand() % (99999 - 10000 + 1));
			staff->num_grupo_dep = grupo;
			staff->plafond = 1 + (std::rand() % (100 - 1 + 1));
			dupListLigada::Item* pessoa = new dupListLigada::Item;
			pessoa->pessoa = staff;
			adicionaElementos(x, pessoa);


		}if (studentorstaff == true && estatutoespecial == true) {					//Se for aluno, que seja de estatuto especial, a entidade será criada desta forma:
			Entidade *especial = new Entidade;
			especial->estatuto = true;
			especial->studentorstaff = true;
			especial->numcosntgrupo = 1;
			especial->ciclosrestantes = ciclos;
			especial->cargo = "Aluno Estatuto Especial";
			especial->prim_nome = v[randomfirstname];
			especial->seg_nome = z[randomsecondname];
			especial->num_mec = 10000 + (std::rand() % (99999 - 10000 + 1));
			especial->course = curso;
			especial->num_grupo_dep = 0;
			especial->plafond = 1 + (std::rand() % (1 - 100 + 1));
			dupListLigada::Item* pessoa = new dupListLigada::Item;				//Aqui no aluno de estatuto especial, em vez de usarmos a habitual função adicionaElemento
			pessoa->pessoa = especial;											//Tendo em conta que este tem prioridade e passa à frente dos restantes na fila bem como é o 1º a ser atendido
			pessoa->next = NULL;												//Já associamos a criação de estatuto especial como o novo apfim da nossa fila
			pessoa->previous = x->apfim;
			x->apfim->next = pessoa;
			x->apfim = pessoa;
			

		}
}
void criaMesa(int tamanho, int lugaresoc, int nummesa,dupListLigadaM* z) {				//Função simples para criação das mesas
	Mesa *mesa = new Mesa;
	mesa->tamanho = tamanho;
	mesa->lugaresocupados = lugaresoc;
	mesa->numdemesa = nummesa;
	mesa->x = new dupListLigada;
	mesa->x->apfim = NULL;
	mesa->x->apinicio = NULL;
	dupListLigadaM ::Item* table = new dupListLigadaM::Item;
	 table->mesa= mesa;
	 adicionaElementos(*z, table);
}

BST* novoNodoBST(Entidade* dados) {						//Função para criação de um novo nodo BST
	BST* novoNodo = new BST;
	novoNodo->x= dados;
	novoNodo->left = NULL;
	novoNodo->right = NULL;
	return novoNodo;
}

BST* adicionaElemBST(BST* root, Entidade* pessoa) {			//Função para preenchimento da BST por ordem do primeiro nome de cada entidade que a constitui
	if (root == NULL) {
		return novoNodoBST(pessoa);
	}
	if (pessoa->prim_nome <= root->x->prim_nome) {
		root->left = adicionaElemBST(root->left, pessoa);
	}
	else if (pessoa->prim_nome > root->x->prim_nome) {
			root->right = adicionaElemBST(root->right, pessoa);
	}
	return root;
}
BSTM* novoNodoBSTM(Mesa* dados) {						//Função para criação de um novo nodo BSTM
	BSTM* novoNodo = new BSTM;
	novoNodo->x = dados;
	novoNodo->left = NULL;
	novoNodo->right = NULL;
	return novoNodo;
}

BSTM* adicionaElemBSTM(BSTM* root, Mesa* pessoa) {			//Função para preenchimento da BSTM tendo em conta o nº de lugares ocupados de cada mesa
	if (root == NULL) {
		return novoNodoBSTM(pessoa);
	}
	if (pessoa->lugaresocupados <= root->x->lugaresocupados) {
		root->left = adicionaElemBSTM(root->left, pessoa);
	}
	else if (pessoa->lugaresocupados > root->x->lugaresocupados) {
		root->right = adicionaElemBSTM(root->right, pessoa);
	}
	return root;
}
void Print(BSTM * x)										//Função para impressão de uma arvore de pesquisa binária que contanha mesas. Foi criada para ser utilizada na funcionalidade 5.2.1
{															//A própria BSTM foi criada com o intuito de tornar mais fácil a organização e impressão das mesas por rdem crescente do nº de lugares ocupados
	if (x != NULL)
	{
		Print(x->left);
		cout << "MESA NÚMERO " << x->x->numdemesa <<":"<< endl;
		dupListLigada::Item * aux2 = x->x->x->apfim;
		while (aux2 != NULL) {
					cout << aux2->pessoa->prim_nome << " " << aux2->pessoa->seg_nome << ", " << aux2->pessoa->cargo << ", " << aux2->pessoa->course << ", Grupo " << aux2->pessoa->num_grupo_dep << ", " << aux2->pessoa->num_mec << " (ciclos restantes : " << aux2->pessoa->ciclosrestantes << ")" << endl;
			aux2 = aux2->previous;
		}
		cout << endl;
		Print(x->right);
	}

	return;
}
BST* adicionaElemBSTUlt(BST* root, Entidade* pessoa) {			//Função para preenchimento da BST por ordem do ultimo nome de cada entidade que a constitui
	if (root == NULL) {
		return novoNodoBST(pessoa);
	}
	if (pessoa->seg_nome <= root->x->seg_nome) {
		root->left = adicionaElemBST(root->left, pessoa);
	}
	else if (pessoa->seg_nome > root->x->seg_nome) {
		root->right = adicionaElemBST(root->right, pessoa);
	}
	return root;
}

void Print(BST * x)												//Função para impressão de uma BST de entidades
{
	if (x != NULL)
	{
		Print(x->left);
		cout << x->x->prim_nome << " " << x->x->seg_nome << ", " << x->x->cargo << ", " << x->x->num_grupo_dep << ", " << x->x->course << ", Plafond: " << x->x->plafond << " Euros" << endl;
		Print(x->right);
	}

	return;
}

void sentaPessoas(dupListLigada* y, dupListLigadaM* z) {      //Função inicial para colocação de pessoas das filas nas mesas, apenas é utilizada no primeiro ciclo ou na primeira vaga de clientes
	dupListLigadaM::Item * aux = z->apfim;
	while (aux != NULL) {
		if (aux->mesa->lugaresocupados == 0) {
			if (y->apfim->pessoa->studentorstaff == true) {		//Condição de colocação nas mesas para alunos
				int ciclos = y->apfim->pessoa->numcosntgrupo;
				int grupo = y->apfim->pessoa->num_grupo_dep;
				string curso = y->apfim->pessoa->course;
				bool cargo = y->apfim->pessoa->studentorstaff;
				string estatuto = y->apfim->pessoa->cargo;
				while (aux->mesa->lugaresocupados < aux->mesa->tamanho && y->apfim->pessoa->course == curso && y->apfim->pessoa->studentorstaff == cargo && y->apfim->pessoa->cargo == estatuto && y->apfim != NULL) {   
					dupListLigada::Item* auxiliar = y->apfim;						//Enquanto a mesa tiver cadeiras vagas e o proximo elemento da fila for do mesmo curso que as pessoas sentadas na mesma
					dupListLigada::Item* auxiliar2 = new dupListLigada::Item;		//continua a sentar entidades
					auxiliar2->pessoa = auxiliar->pessoa;
					if (aux->mesa->x->apfim == NULL && aux->mesa->x->apinicio == NULL) {
						aux->mesa->x->apfim = auxiliar2;
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apinicio == NULL) {								//Conjunto de ifs intuitivos e simples para mover as entidades da fila para a mesa e preencher a dupla lista ligada da mesma
						aux->mesa->x->apinicio = auxiliar2;								//Além disto move apontadores para eliminar as entidades que foram copiadas da fila
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = aux->mesa->x->apinicio;
						aux->mesa->x->apinicio->next = aux->mesa->x->apfim;
						aux->mesa->x->apinicio->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apfim != NULL && aux->mesa->x->apinicio != NULL) {
						aux->mesa->x->apinicio->previous = auxiliar2;
						aux->mesa->x->apinicio->previous->next = aux->mesa->x->apinicio;
						aux->mesa->x->apinicio = aux->mesa->x->apinicio->previous;
						aux->mesa->x->apinicio->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					ciclos--;
					aux->mesa->lugaresocupados = aux->mesa->lugaresocupados + 1;
				}
			}

			if (y->apfim->pessoa->studentorstaff == false) {			//Condição de colocação nas mesas para staff
				int ciclos = y->apfim->pessoa->numcosntgrupo;
				int grupo = y->apfim->pessoa->num_grupo_dep;
				string curso = y->apfim->pessoa->course;
				bool cargo = y->apfim->pessoa->studentorstaff;
				string estatuto = y->apfim->pessoa->cargo;
				while (aux->mesa->lugaresocupados < aux->mesa->tamanho && y->apfim->pessoa->num_grupo_dep == grupo && y->apfim->pessoa->studentorstaff == cargo && y->apfim->pessoa->cargo == estatuto && y->apfim != NULL) {
					dupListLigada::Item* auxiliar = y->apfim;								//Enquanto a mesa tiver cadeiras vagas e o proximo elemento da fila for do mesmo departamento que as pessoas sentadas na mesma
					dupListLigada::Item* auxiliar2 = new dupListLigada::Item;				//continua a sentar entidades
					auxiliar2->pessoa = auxiliar->pessoa;
					if (aux->mesa->x->apfim == NULL && aux->mesa->x->apinicio == NULL) {
						aux->mesa->x->apfim = auxiliar2;
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apinicio == NULL) {									//Conjunto de ifs intuitivos e simples para mover as entidades da fila para a mesa e preencher a dupla lista ligada da mesma
						aux->mesa->x->apinicio = auxiliar2;									//Além disto move apontadores para eliminar as entidades que foram copiadas da fila
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = aux->mesa->x->apinicio;
						aux->mesa->x->apinicio->next = aux->mesa->x->apfim;
						aux->mesa->x->apinicio->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apfim != NULL && aux->mesa->x->apinicio != NULL) {
						aux->mesa->x->apinicio->previous = auxiliar2;
						aux->mesa->x->apinicio->previous->next = aux->mesa->x->apinicio;
						aux->mesa->x->apinicio = aux->mesa->x->apinicio->previous;
						aux->mesa->x->apinicio->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					ciclos--;
					aux->mesa->lugaresocupados = aux->mesa->lugaresocupados + 1;
				}
			}
		}
		aux = aux->previous;
	}
}

void movimentaPessoas(dupListLigada* y, dupListLigadaM* z) {				//Função para colocação de pessoas nas mesmas nos restantes ciclos;
	dupListLigadaM::Item * aux = z->apfim;
	while (aux != NULL) {
		if (aux->mesa->lugaresocupados == 0) {								//Enquanto tiver lugares por ocupar chama sempre a próxima pessoa da fila
				while (aux->mesa->lugaresocupados < aux->mesa->tamanho && y->apfim != NULL) {
					dupListLigada::Item* auxiliar = y->apfim;
					dupListLigada::Item* auxiliar2 = new dupListLigada::Item;
					auxiliar2->pessoa = auxiliar->pessoa;
					if (aux->mesa->x->apfim->pessoa->ciclosrestantes <= 0) {
						aux->mesa->x->apfim = auxiliar2;
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apfim == NULL && aux->mesa->x->apinicio == NULL) {
						aux->mesa->x->apfim = auxiliar2;
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apinicio == NULL) {
						aux->mesa->x->apinicio = auxiliar2;
						aux->mesa->x->apfim->next = NULL;
						aux->mesa->x->apfim->previous = aux->mesa->x->apinicio;
						aux->mesa->x->apinicio->next = aux->mesa->x->apfim;
						aux->mesa->x->apinicio->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					if (aux->mesa->x->apfim != NULL && aux->mesa->x->apinicio != NULL) {
						aux->mesa->x->apinicio->previous = auxiliar2;
						aux->mesa->x->apinicio->previous->next = aux->mesa->x->apinicio;
						aux->mesa->x->apinicio = aux->mesa->x->apinicio->previous;
						aux->mesa->x->apinicio->previous = NULL;
						auxiliar->previous->next = NULL;
						y->apfim = auxiliar->previous;
					}
					
					aux->mesa->lugaresocupados = aux->mesa->lugaresocupados + 1;
				}
			}

			
		aux = aux->previous;
	}
}