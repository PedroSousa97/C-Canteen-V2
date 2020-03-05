#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <time.h>
#include <string>
#include <locale.h>
#include "Functions.h"
#include "Entidade.h"
#include "Refei��o.h"
#include "Mesa.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Portuguese");

	srand(time(NULL));

	string * primeirosnomes = new string[contaLinhas("primeiro_nome.txt")];
	preencheArray(primeirosnomes, "primeiro_nome.txt");
	string * ultimosnomes = new string[contaLinhas("ultimo_nome.txt")];
	preencheArray(ultimosnomes, "ultimo_nome.txt");
	string * cursos = new string[contaLinhas("cursos.txt")];						//Leitura, contagem de linhas e cria��o de arrays que ir�o conter os nomes e cursos
	preencheArray(cursos, "cursos.txt");
	int tamanhoy = contaLinhas("cursos.txt");

	int contaciclos = 0;
	int emerg;
	int ganhostotais = 0;
	int contaS = 0;
	string entrada;
	string pratoprincip;
	float custo;																		//Inicializa��o de vari�veis e dos primeiros randoms
	int grupo;
	int elementosgrupo;
	int randomcargo;
	int randomciclos;
	int randomcourse;
	bool estatutoespecial;
	bool studentorstaff;
	string curso;
	int randomCria��o = 40 + (std::rand() % (50 - 40 + 1));
	int randomCantina = 30 + (std::rand() % (50 - 30 + 1));
	int aremover;
	bool pessoaencontrada = false;
	bool dadosGuardados = false;
	int functions;

	Refei�ao* Atual = new Refei�ao;

	cout << "******************************* BEM VINDO � CANTINA EDA *******************************" << endl << endl;
	cout << "************************************ REFEI�AO NOVA ************************************" << endl << endl;
	cout << "A cantina EDA necessita de uma nova refei��o." << endl;
	cout << "   1.Introduza a entrada:" << endl;
	cin >> entrada;
	cout << "   2.Introduza o prato principal:" << endl;
	cin >> pratoprincip;
	cout << "   3.Introduza o custo:" << endl;
	cin >> custo;
	cout << endl << endl;

	Atual->entrada = entrada;
	Atual->pratoprincipal = pratoprincip;								//Preenchimento da Refei��o Atual tendo em conta os dados introduzidos pelo utilizador
	Atual->custo = custo;

	


	BST* root = new BST;
	root = NULL;
	BST* ultmNome = new BST;							//Cria��o das ra�zes, embora nulas, das BST de entidades removidas, utentes ordenados por ultimo nome e mesas ordenadas por lugares ocupados
	ultmNome = NULL;
	BSTM* Mesas = new BSTM;
	Mesas = NULL;
	

	dupListLigada* Fila = new dupListLigada;			//Cria��o da Fila
	novaLista(Fila);

	while (randomCria��o > 0) {
		int j = 0;
		grupo = 100 + (std::rand() % (500 - 100 + 1));
		elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
		randomcargo = 0 + (std::rand() % (2 - 0 + 1));								//Randoms simples para caracterizar aleatoriamente os novos utentes
		randomciclos = 2 + (std::rand() % (5 - 2 + 1));
		randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
		curso = cursos[randomcourse];

		if (randomcargo > 0) {
			studentorstaff = true;										//Defini��o de novas entidades como aluno ou staff
		}
		else if (randomcargo == 0) {
			studentorstaff = false;
		}
		while (j < elementosgrupo) {
			int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));				//Random para estatuto de 1 a 100
			if (randomestatuto <= 5) {											//Se o valor obtido for menor ou igual a 5 ent�o � estudante estatuto especial 
				estatutoespecial = true;										//(ou seja 5 de 100 n�meros d� uma probabilidade de 5% como pedido)
			}
			else if (randomestatuto > 5) {
				estatutoespecial = false;										//Enquanto j for menor que o n�emro de elementos constituintes do grupo e n�o ultrapassar a capacidade da fila, cria entidades
			}
			criaEntidade(primeirosnomes, ultimosnomes, curso, Fila, grupo, estatutoespecial, studentorstaff, randomciclos, elementosgrupo);
			randomCria��o--;
			j++;
		}
		j = 0;
	}
	
	

	dupListLigadaM* mesas = new dupListLigadaM;					//Cria��o da dupla lista ligada
	novaLista(*mesas);
	int lugaresdisponiveis = randomCantina;
	int v = 0;
	int numeromesa = 1;
	int numalunossentados = 0;
	int tamanhomesa;
	int vagasocupadas = 0;
	do {
		while (v <= randomCantina && lugaresdisponiveis > 0) {          //Enquanto houver cadeiras a colocar na cantina ele ir� criar Mesas no vetor conjmesas
			tamanhomesa = 2 + (std::rand() % (5 - 2 + 1));				//Tamanho aleat�rio da mesa a criar
			if (tamanhomesa < lugaresdisponiveis) {
				tamanhomesa = tamanhomesa;
			}
			else if (tamanhomesa > lugaresdisponiveis) {				//Se o tamanho ultrapassar a disponibilidade, ent�o o tamanho passa a ser a pr�pria disponibilidade de coloc��o de cadeiras na cantina
				tamanhomesa = lugaresdisponiveis;
			}
			criaMesa(tamanhomesa, numalunossentados, numeromesa,mesas);
			lugaresdisponiveis = lugaresdisponiveis - tamanhomesa;
			numeromesa++;
			v++;
		}break;
	} while (lugaresdisponiveis >= 0);

	
	dupListLigadaM::Item* descontaCiclos = mesas->apfim;				
	dupListLigada::Item* descontaCiclos2 = new dupListLigada::Item;
	dupListLigadaM::Item* fimderefei�ao = mesas->apfim;
	dupListLigada::Item* fimderefei�ao2 = new dupListLigada::Item;
	dupListLigadaM::Item* emergencia = mesas->apfim;
	dupListLigada::Item* emergencia2 = new dupListLigada::Item;									//Interatores para percorres as listas em diferentes fun��es
	dupListLigada* FilaGrava�ao = new dupListLigada;
	novaLista(FilaGrava�ao);
	dupListLigadaM* MesasGrava�ao = new dupListLigadaM;
	novaLista(*MesasGrava�ao);
	Refei�ao* Grava�ao = new Refei�ao;
	BST* RemovidosGrava�ao = new BST;
	RemovidosGrava�ao = NULL;




	dupListLigada::Item * aux3 = Fila->apfim;
	
	while (aux3 != NULL) {
		if (aux3->pessoa->plafond < Atual->custo) {			//Verifica��o de alunos sem plafond
			int resposta;
			if (aux3->pessoa->estatuto == true) {
				cout << "**************************************** ATEN��O ****************************************" << endl;
				cout << "O aluno de estatuto especial " << aux3->pessoa->prim_nome << " com n�mero mecanogr�fico " << aux3->pessoa->num_mec <<  " n�o tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
				cout << "   1.Remover entidade da fila;" << endl;     //Se for aluno de estatuto especial, n�o imprime a segunda op��o tendo em conta que estes indiv�duos n�o t�m grupo
			}if (aux3->pessoa->estatuto == false) {
				cout << "**************************************** ATEN��O ****************************************" << endl;
				cout << "A entidade " << aux3->pessoa->prim_nome << " com n�mero mecanogr�fico " << aux3->pessoa->num_mec << " grupo " << aux3->pessoa->num_grupo_dep << " n�o tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
				cout << "   1.Remover entidade da fila;" << endl;
				cout << "   2.Remover grupo/departamento da fila;" << endl;
			}
			cin >> resposta;
			if (resposta == 1) {
				
				if (aux3->next == NULL) {
					aux3->previous->next = NULL;
					Fila->apfim = aux3->previous;
					root=adicionaElemBST(root, aux3->pessoa);
				}
				 if (aux3->previous == NULL) {								//Remo��o de um s� indiv�duo
					aux3->next->previous = NULL;
					Fila->apinicio = aux3->next;
					root = adicionaElemBST(root, aux3->pessoa);
				 }
				 else if (aux3->next != NULL && aux3->previous != NULL)
				 {
					 aux3->next->previous = aux3->previous;
					 aux3->previous->next = aux3->next;
					 root = adicionaElemBST(root, aux3->pessoa);
				 }
				
			}
			if (resposta == 2) {
				dupListLigada::Item * auxdoaux = Fila->apfim;
				int pesquisa = aux3->pessoa->num_grupo_dep;
				while (auxdoaux != NULL) {
					if(auxdoaux->pessoa->num_grupo_dep == pesquisa){   //auxdoaux ir� percorrer de novo a fila e remover todos os elementos com n�mero de grupo igual � pessoa sem plafond detetada

						if (auxdoaux->next == NULL) {
							auxdoaux->previous->next = NULL;
							Fila->apfim = auxdoaux->previous;
							root = adicionaElemBST(root, auxdoaux->pessoa);
							
						}
						if (auxdoaux->previous == NULL) {
							auxdoaux->next->previous = NULL;
							Fila->apinicio = auxdoaux->next;
							root = adicionaElemBST(root, auxdoaux->pessoa);
							
						}
						else if (auxdoaux->next != NULL && auxdoaux->previous != NULL) {
							auxdoaux->next->previous = auxdoaux->previous;
							auxdoaux->previous->next = auxdoaux->next;
							root = adicionaElemBST(root, auxdoaux->pessoa);
							
						}
						
					}
					auxdoaux = auxdoaux->previous;
				}
				
				}

			}
		aux3 = aux3->previous;
		}
	aux3 = Fila->apfim;
	
	cout << endl;
	cout << "Entidades removidas por falta de plafond: " << endl << endl;		//Print para verifica��o do primeiro varrimento e dete��o de entidades sem plafond e posterior remo��o para a BST
	
	Print(root);


	cout << endl << endl;

	bool sair = false;
	char opcao;
	do
	{
		cout << "                                            Cantina EDA" << endl;
		cout << "(s)Seguinte   (e)Emerg�ncia   (g)Gravar   (c)Carregar Dados   (o)Op��es   (0)Fechar Programa" << endl << endl;

		cout << "Refei��o Actual:" << endl;
		cout << "      Entrada: " << Atual->entrada << endl;								//Impress�o da Refei�ao
		cout << "      Prato: " << Atual->pratoprincipal << endl;
		cout << "      custo: " << Atual->custo << endl << endl;
		dupListLigadaM::Item * aux2 = mesas->apfim;
		while (aux2 != NULL) {
			cout << "Mesa " << aux2->mesa->numdemesa << " (CAPACIDADE " << aux2->mesa->tamanho <<") :" << endl;		//Impress�o das mesaas e dos seus constituintes
			if (aux2->mesa->lugaresocupados == 0) {
				cout << "N�o existem alunos sentados nesta mesa!" << endl << endl;			//Se a mesa tiver vazia:
			}
			else if (aux2->mesa->lugaresocupados > 0) {			//Impress�o de todos os utentes sentados em cada mesa
				dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
				while (auxiliarCadeiras != NULL) {
					cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << " (ciclos restantes : "<< auxiliarCadeiras->pessoa->ciclosrestantes << ")" << endl;
					auxiliarCadeiras = auxiliarCadeiras->previous;

				}
				cout << endl;
			}
			aux2 = aux2->previous;
		}
		cout << endl << endl;
		cout << "FILA DE ESPERA:" << endl << endl;

		dupListLigada::Item * aux = Fila->apfim;				//Impress�o da fila de espera
		while (aux != NULL) {
			cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Dura��o, "<<aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
			aux = aux->previous;

		}
		cout << endl << endl;
	
		cout << "Dinheiro cobrado at� ao momento pela Cantina EDA: " << ganhostotais << "Euros!!" << endl;     //Print de uma vari�vel criada para provar que a cobran�a dos alunos removidos
		cin >> opcao;																						   //tanto por emerg�ncia como por ciclos est� a ocorrer
		cout << endl << endl;
		if (opcao == 's') {
			contaS++;                                   //ContaS come�a a 0
		}

		switch (opcao) {
		case 's':
			if (contaS == 1) {							//ContaS=1 significa que se refere ao primeiro ciclo, ent�o popula s� as mesas com os alunos da fila
				sentaPessoas(Fila, mesas);
			}
			else if (contaS > 1) {  
				while (descontaCiclos != NULL) {					//varrimento dos utentes sentados e a usufruir da refei��o e subtra��o do tempo restante
					descontaCiclos2 = descontaCiclos->mesa->x->apfim;
					while (descontaCiclos2 != NULL) {
						descontaCiclos2->pessoa->ciclosrestantes = descontaCiclos2->pessoa->ciclosrestantes - 1;
						descontaCiclos2 = descontaCiclos2->previous;
					}
					descontaCiclos = descontaCiclos->previous;
				}
				descontaCiclos = mesas->apfim;

				while (fimderefei�ao != NULL) {							//Pesquisa de alunos que j� tenham acabado a refei��o e elimina��o dos mesmos
					fimderefei�ao2 = fimderefei�ao->mesa->x->apfim;
					while (fimderefei�ao2 != NULL) {
						if (fimderefei�ao2->pessoa->ciclosrestantes == 0) {
							fimderefei�ao2->pessoa->plafond = fimderefei�ao2->pessoa->plafond - Atual->custo;   //cobra a refei��o aos alunos
							fimderefei�ao->mesa->lugaresocupados = fimderefei�ao->mesa->lugaresocupados - 1;    //Volta a aumentar os lugares vagos
							if (fimderefei�ao2->next == NULL && fimderefei�ao2->previous == NULL) {
								fimderefei�ao->mesa->x->apfim->pessoa = NULL;
								fimderefei�ao->mesa->x->apfim->next = NULL;
								fimderefei�ao->mesa->x->apfim->previous = NULL;
							}
							if (fimderefei�ao2->next == NULL && fimderefei�ao2->previous != NULL && fimderefei�ao2->previous != fimderefei�ao->mesa->x->apinicio) {
								fimderefei�ao2->previous->next = NULL;
								fimderefei�ao->mesa->x->apfim = fimderefei�ao2->previous;
							}
							if (fimderefei�ao2->next == NULL && fimderefei�ao2->previous == fimderefei�ao->mesa->x->apinicio) {
								fimderefei�ao2->previous->next = NULL;
								fimderefei�ao->mesa->x->apfim = fimderefei�ao2->previous;
								fimderefei�ao->mesa->x->apinicio->pessoa = NULL;
								fimderefei�ao->mesa->x->apinicio->next = NULL;
								fimderefei�ao->mesa->x->apinicio->previous = NULL;
							}
							if (fimderefei�ao2->previous == NULL) {
								fimderefei�ao2->next->previous = NULL;
								fimderefei�ao->mesa->x->apinicio = fimderefei�ao2->next;
							}
							if (fimderefei�ao2->next != NULL && fimderefei�ao2->previous != NULL)
							{
								fimderefei�ao2->next->previous = fimderefei�ao2->previous;
								fimderefei�ao2->previous->next = fimderefei�ao2->next;

							}
							ganhostotais = ganhostotais + Atual->custo;					//Adiciona o custo da refei��o aos ganhos da cantina toda vez que remove algu�m com 0 cilcos restantes
						}

						fimderefei�ao2 = fimderefei�ao2->previous;
					}
					fimderefei�ao = fimderefei�ao->previous;
				}
				fimderefei�ao = mesas->apfim;

				randomCria��o = 5 + (std::rand() % (15 - 5 + 1));  //Random entre 5 e 15 para que a cada ciclos cheguem � fila novos utentes, s�o assim criados sempre novas entidades e adicionados � fila
				while (randomCria��o > 0) {
					int j = 0;
					grupo = 100 + (std::rand() % (500 - 100 + 1));
					elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
					randomcargo = 0 + (std::rand() % (2 - 0 + 1));								//Randoms
					randomciclos = 2 + (std::rand() % (5 - 2 + 1));
					randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
					curso = cursos[randomcourse];

					if (randomcargo > 0) {
						studentorstaff = true;										//Defini��o de novas entidades como aluno ou staff
					}
					else if (randomcargo == 0) {
						studentorstaff = false;
					}
					while (j < elementosgrupo) {
						int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));				//Random para estatuto de 1 a 100
						if (randomestatuto <= 5) {											//Se o valor obtido for menor ou igual a 5 ent�o � estudante estatuto especial 
							estatutoespecial = true;										//(ou seja 5 de 100 n�meros d� uma probabilidade de 5% como pedido)
						}
						else if (randomestatuto > 5) {
							estatutoespecial = false;										//Enquanto j for menor que o n�emro de elementos constituintes do grupo e n�o ultrapassar a capacidade da fila, cria entidades
						}
						criaEntidade(primeirosnomes, ultimosnomes, curso, Fila, grupo, estatutoespecial, studentorstaff, randomciclos, elementosgrupo);
						randomCria��o--;
						j++;
					}
					j = 0;
				}
				movimentaPessoas(Fila, mesas);     // Se houver vagas senta pessoas
				contaciclos++;
				if (contaciclos == 10) {													//A cada 10 ciclos a cantina necessita de uma nova refei��o
					cout << "A cantina EDA necessita de uma nova refei��o." << endl;
					cout << "   1.Introduza a entrada:" << endl;
					cin >> entrada;
					cout << "   2.Introduza o prato principal:" << endl;
					cin >> pratoprincip;
					cout << "   3.Introduza o custo:" << endl;
					cin >> custo;

					Atual->entrada = entrada;										//Atribui��o da nova refei��o
					Atual->pratoprincipal = pratoprincip;
					Atual->custo = custo;
					contaciclos = 0;																//Chegando aos 10 temos que inicializar de novo o contaciclos a 0
				}
				while (aux3 != NULL) {    //Nova verifica��o, com m�todos iguais ao anterior para remo��o de entidades sem plafond
					if (aux3->pessoa->plafond < Atual->custo) {
						int resposta;
						if (aux3->pessoa->estatuto == true) {
							cout << "**************************************** ATEN��O ****************************************" << endl;
							cout << "O aluno de estatuto especial " << aux3->pessoa->prim_nome << " com n�mero mecanogr�fico " << aux3->pessoa->num_mec << " n�o tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
							cout << "   1.Remover entidade da fila;" << endl;
						}if (aux3->pessoa->estatuto == false) {
							cout << "**************************************** ATEN��O ****************************************" << endl;
							cout << "A entidade " << aux3->pessoa->prim_nome << " com n�mero mecanogr�fico " << aux3->pessoa->num_mec << " grupo " << aux3->pessoa->num_grupo_dep << " n�o tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
							cout << "   1.Remover entidade da fila;" << endl;
							cout << "   2.Remover grupo/departamento da fila;" << endl;
						}
						cin >> resposta;
						if (resposta == 1) {

							if (aux3->next == NULL) {
								aux3->previous->next = NULL;
								Fila->apfim = aux3->previous;
								root = adicionaElemBST(root, aux3->pessoa);
							}
							if (aux3->previous == NULL) {
								aux3->next->previous = NULL;
								Fila->apinicio = aux3->next;
								root = adicionaElemBST(root, aux3->pessoa);
							}
							else if (aux3->next != NULL && aux3->previous != NULL)
							{
								aux3->next->previous = aux3->previous;
								aux3->previous->next = aux3->next;
								root = adicionaElemBST(root, aux3->pessoa);
							}

						}
						if (resposta == 2) {
							dupListLigada::Item * auxdoaux = Fila->apfim;
							int pesquisa = aux3->pessoa->num_grupo_dep;
							while (auxdoaux != NULL) {
								if (auxdoaux->pessoa->num_grupo_dep == pesquisa) {

									if (auxdoaux->next == NULL) {
										auxdoaux->previous->next = NULL;
										Fila->apfim = auxdoaux->previous;
										root = adicionaElemBST(root, auxdoaux->pessoa);

									}
									if (auxdoaux->previous == NULL) {
										auxdoaux->next->previous = NULL;
										Fila->apinicio = auxdoaux->next;
										root = adicionaElemBST(root, auxdoaux->pessoa);

									}
									else if (auxdoaux->next != NULL && auxdoaux->previous != NULL) {
										auxdoaux->next->previous = auxdoaux->previous;
										auxdoaux->previous->next = auxdoaux->next;
										root = adicionaElemBST(root, auxdoaux->pessoa);

									}

								}
								auxdoaux = auxdoaux->previous;
							}

						}

					}
					aux3 = aux3->previous;
				}
				aux3 = Fila->apfim;
			}

			break;
		case 'e':
			cout << "**************************************** EMERG�NCIA ****************************************" << endl;   //Remo��o de um utente ou grupo por emerg�ncia
			cout << "Situa��o de emerg�ncia:" << endl;
			cout << "   1.Remover entidade da cantina;" << endl;
			cout << "   2.Remover grupo/departamento da cantina;" << endl;
			cin >> emerg;
			if (emerg == 1) {
				cout << "N�mero mecanogr�fico da entidade:" << endl;
				cin >> aremover;
				cout << endl;
				while (emergencia != NULL) {
					emergencia2 = emergencia->mesa->x->apfim;
					while (emergencia2 != NULL) {
						if (emergencia2->pessoa->num_mec == aremover) {
							pessoaencontrada = true;
							emergencia2->pessoa->plafond = emergencia2->pessoa->plafond - Atual->custo;
							emergencia->mesa->lugaresocupados = emergencia->mesa->lugaresocupados - 1;
							if (emergencia2->next == NULL && emergencia2->previous == NULL) {
								emergencia->mesa->x->apfim->pessoa = NULL;
								emergencia->mesa->x->apfim->next = NULL;
								emergencia->mesa->x->apfim->previous = NULL;
							}
							if (emergencia2->next == NULL) {
								emergencia2->previous->next = NULL;
								emergencia->mesa->x->apfim = emergencia2->previous;
							}
							if (emergencia->previous == NULL) {
								emergencia2->next->previous = NULL;
								emergencia->mesa->x->apinicio = emergencia2->next;

							}
							if (emergencia2->next != NULL && emergencia2->previous != NULL)
							{
								emergencia2->next->previous = emergencia2->previous;
								emergencia2->previous->next = emergencia2->next;
							}
							ganhostotais = ganhostotais + Atual->custo;
						}

						emergencia2 = emergencia2->previous;
					}

					emergencia = emergencia->previous;
				}
				if (pessoaencontrada == false) {
					cout << "N�o existe de momento nenhuma entidade com n�mero " << aremover << " a usufruir da cantina!" << endl << endl;
				}
				pessoaencontrada = false;
				emergencia = mesas->apfim;
			}
			if (emerg == 2) {
				cout << "Grupo/Departamento da entidade:" << endl;
				cin >> aremover;
				cout << endl;
				while (emergencia != NULL) {
					emergencia2 = emergencia->mesa->x->apfim;
					while (emergencia2 != NULL) {
						if (emergencia2->pessoa->num_grupo_dep == aremover) {
							pessoaencontrada = true;
							emergencia2->pessoa->plafond = emergencia2->pessoa->plafond - Atual->custo;
							emergencia->mesa->lugaresocupados = emergencia->mesa->lugaresocupados - 1;
							if (emergencia2->next == NULL && emergencia2->previous == NULL) {
								emergencia->mesa->x->apfim->pessoa = NULL;
								emergencia->mesa->x->apfim->next = NULL;
								emergencia->mesa->x->apfim->previous = NULL;
								emergencia->mesa->x->apinicio->pessoa = NULL;
								emergencia->mesa->x->apinicio->next = NULL;
								emergencia->mesa->x->apinicio->previous = NULL;
							}
							if (emergencia2->next == NULL) {
								emergencia2->previous->next = NULL;
								emergencia->mesa->x->apfim = emergencia2->previous;
							}
							if (emergencia->previous == NULL) {
								emergencia2->next->previous = NULL;
								emergencia->mesa->x->apinicio = emergencia2->next;

							}
							if (emergencia2->next != NULL && emergencia2->previous != NULL)
							{
								emergencia2->next->previous = emergencia2->previous;
								emergencia2->previous->next = emergencia2->next;
							}
							ganhostotais = ganhostotais + Atual->custo;
						}

						emergencia2 = emergencia2->previous;
					}

					emergencia = emergencia->previous;
				}
				if (pessoaencontrada == false) {
					cout << "N�o existe de momento nenhuma entidade com n�mero de Grupo/Departamento " << aremover << " a usufruir da cantina!" << endl << endl;
				}
				pessoaencontrada = false;
				emergencia = mesas->apfim;
			}
			movimentaPessoas(Fila, mesas);
			break;
		case 'g':

			FilaGrava�ao->apfim = Fila->apfim;
			RemovidosGrava�ao = root;
			MesasGrava�ao->apfim = mesas->apfim;
			Grava�ao->custo = Atual->custo;
			Grava�ao->pratoprincipal = Atual->pratoprincipal;
			Grava�ao->entrada = Atual->entrada;
			dadosGuardados = true;
			break;
		case 'c':														//Infelizmente n�o foi poss�vel utilizar grava��o atrav�s de ficheiro txt, dava erro de grava��o externo e n�o permitia realizar 
			if (dadosGuardados == false) {								//a altera��o/escrita no ficheiro. Contudo consegue gravar enquanto se est� a usufruir do execut�vel, grava dados, sobrepondo cada
				cout << "************N�o existem dados de Cantina gravados!**************" << endl;	//vez que � utilizado. Apenas as mesas � que n�o carregam os dados com sucesso
			}
			if (dadosGuardados == true) {
				Fila->apfim = FilaGrava�ao->apfim;
				root = RemovidosGrava�ao;
				mesas->apfim = MesasGrava�ao->apfim;
				Atual->custo = Grava�ao->custo;
				Atual->pratoprincipal = Grava�ao->pratoprincipal;
				Atual->entrada = Grava�ao->entrada;
			}
			break;
		case 'o':
			cout << "******************************* OP��ES *******************************" << endl << endl;
			cout << "   1.Visualizar todos os utentes da cantina;" << endl;
			cout << "   2.Visualizar todos os utentes ordenados alfabeticamente pelo sobrenome;" << endl;
			cout << "   3.Mostrar todas as mesas;" << endl;
			cout << "   4.Mostrar todas as mesas ordanadas por n�mero de lugares ocupados;" << endl;
			cout << "   5.Mostrar todos os indiv�duos rejeitados por falta de plafond;" << endl;
			cout << "   6.Mostrar todos os indiv�duos rejeitados por falta de plafond ordenados pelo primeiro nome;" << endl;
			cout << "   7.Aletar plafond de algum utente que ainda se encontre na fila;" << endl;
			cout << "   8.Procurar utentes por curso/departamento;" << endl;
			cout << "   9.Editar o tempo de refei��o de um grupo/departamento;" << endl;
			cout << "  10.Pesquisa de informa��o relativa ao utente por n�mero mecanogr�fico;" << endl;
			cout << "  11.Editar o nome de um indiv�duo;" << endl;
			cin >> functions;
			cout << endl << endl;
			if (functions == 1) {						//Prints b�sicos id�nticos aos anteriores para apresnetar todos os utentes da Cantina
				cout << "********************* Utentes na Fila: *********************" << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->cargo << ", Grupo" << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
					aux = aux->previous;

				}
				cout << endl << endl;
				cout << "********************* Utentes nas Mesas: *******************" << endl << endl;
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << ", Plafond: " << auxiliarCadeiras->pessoa->plafond << " Euros" << endl;
						auxiliarCadeiras = auxiliarCadeiras->previous;
					}
					aux2 = aux2->previous;
				}
				cout << endl << endl;
				cout << "********* Utentes Removidos por falta de Plafond: ***********" << endl << endl;
				Print(root);
				cout << endl << endl;
			}
			if (functions == 2) {  //� aqui  que se usa a BST organizada por �ltimo nome dos utentes para apresnetar todos os utentes que atualmente estam a usufruir da cantina
				aux = Fila->apfim;
				while (aux != NULL) {
					ultmNome = adicionaElemBSTUlt(ultmNome, aux->pessoa);
					aux = aux->previous;

				}
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						ultmNome = adicionaElemBSTUlt(ultmNome, auxiliarCadeiras->pessoa);
						auxiliarCadeiras = auxiliarCadeiras->previous;
					}
					aux2 = aux2->previous;
				}
				cout << "Todos os utentes que estam atualmente a usufruir dos servi�os da Cantina:" << endl << endl;
				Print(ultmNome);
				cout << endl << endl;
			}
			if (functions == 3)			//Impress�o simples e igual � anterior para impress�o das mesas e utentes sentados nas mesmas
				aux2 = mesas->apfim;
			while (aux2 != NULL) {
				cout << "Mesa " << aux2->mesa->numdemesa << " (CAPACIDADE " << aux2->mesa->tamanho << ") :" << endl;
				if (aux2->mesa->lugaresocupados == 0) {
					cout << "N�o existem alunos sentados nesta mesa!" << endl << endl;
				}
				else if (aux2->mesa->lugaresocupados > 0) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << " (ciclos restantes : " << auxiliarCadeiras->pessoa->ciclosrestantes << ")" << endl;
						auxiliarCadeiras = auxiliarCadeiras->previous;

					}
					cout << endl;
				}
				aux2 = aux2->previous;
			}
			cout << endl << endl;
			if (functions == 4) {					//� aqui que se d� uso � BST de mesas para imprrimir as mesmas e os seus utentes por ordem crescente de n�mero de lugares ocupados
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					Mesas = adicionaElemBSTM(Mesas, aux2->mesa);
					aux2 = aux2->previous;
				}
				cout << "Todos as mesas organizadas por n�mero de lugares ocupados:" << endl << endl;
				Print(Mesas);
				cout << endl << endl;
			}
			if (functions == 5) {							
				cout << "************ Entidades removidas por falta de plafond: ************" << endl << endl;
				Print(root);
				cout << endl << endl;
			}
			if (functions == 6) {																				     //N�o fazia sentido desorganizar a BST, ent�o ambos os prints s�o iguais e de f�cil
				cout << "Entidades removidas por falta de plafond ordenados por ordem alfab�tica:" << endl << endl;  //compreens�o
				Print(root);
				cout << endl << endl;
			}
			if (functions == 7) {												//Altera��o de plafond de uma entidade em quest�o
				cout << "***************************** Alterar Plafond de Utente *****************************" << endl;
				cout << "Indique o n�mero mecanogr�fico da entidade em quest�o:" << endl;
				cout << "N�mero mecanogr�fico da entidade:" << endl;
				cin >> aremover;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_mec == aremover) {
						float novoplafond;												//Procura na fila a pessoa com n�mero indicado pelo utilizador
						pessoaencontrada = true;
						cout << "Insira o novo Plafond:" << endl;
						cin >> novoplafond;
						aux->pessoa->plafond = novoplafond;
					}
					aux = aux->previous;

				}
				if (pessoaencontrada = false) {
					cout << "N�o existe entidade com este n�mero mecanogr�fico!" << endl;			//Se n�o existir o n�mero em quest�o
				}
				pessoaencontrada = false;
			}
			if (functions == 8) {

				cout << "******************** Apresentar utentes de um curso/departamento ********************" << endl;
				cout << "Caso se trate de staff, utilize o departamento. Caso seja aluno utilize o curso para pesquisar." << endl;
				cout << "Indique se que pesquisar por curso/departamento:" << endl;
				cout << "1.Curso;" << endl;
				cout << "2.Departamento;" << endl;
				cin >> aremover;
				if (aremover == 1) {
					string curso;
					cout << "Qual o curso a pesquisar?" << endl;
					cin >> curso;
					cout << endl << endl;     // Impress�o de todos os utentes do curso em quest�o
					aux = Fila->apfim;
					while (aux != NULL) {
						if (aux->pessoa->course == curso) {
							cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Dura��o, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
						}
						aux = aux->previous;
					}
					aux2 = mesas->apfim;
					while (aux2 != NULL) {
						dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
						while (auxiliarCadeiras != NULL) {
							if (auxiliarCadeiras->pessoa->course == curso) {
								cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << " (ciclos restantes : " << auxiliarCadeiras->pessoa->ciclosrestantes << ")" << endl;
							}
							auxiliarCadeiras = auxiliarCadeiras->previous;

						}
						aux2 = aux2->previous;
					}

				}
				if (aremover == 2) {
					cout << "Qual o departamento a pesquisar?" << endl;
					cin >> aremover;
					cout << endl << endl;
					aux = Fila->apfim;         // Impress�o de todos os utentes do departamento em quest�o
					while (aux != NULL) {
						if (aux->pessoa->num_grupo_dep == aremover) {
							pessoaencontrada = true;
							cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Dura��o, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
						}
						aux = aux->previous;
					}
					aux2 = mesas->apfim;
					while (aux2 != NULL) {
						dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
						while (auxiliarCadeiras != NULL) {
							if (auxiliarCadeiras->pessoa->num_grupo_dep == aremover) {
								pessoaencontrada = true;
								cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << " (ciclos restantes : " << auxiliarCadeiras->pessoa->ciclosrestantes << ")" << endl;
							}
							auxiliarCadeiras = auxiliarCadeiras->previous;

						}
						aux2 = aux2->previous;
					}

				}
				
				cout << endl << endl;

			}
			if (functions == 9) {
				int novotempo;
				cout << "Editar o tempo de refei��o de um grupo/departamento:" << endl;
				cout << "Novo tempo de refei��o que quer atribuir:" << endl;
				cin >> novotempo;
				cout << "Departamento/Grupo a alterar tempo de refei��o:" << endl;
				cin >> aremover;
				cout << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_grupo_dep == aremover) {
						pessoaencontrada = true;							//Altera o tempo de refei��o de todos os elemntos do grupo na fila
						aux->pessoa->ciclosrestantes = novotempo;
					}
					aux = aux->previous;
				}
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						if (auxiliarCadeiras->pessoa->num_grupo_dep == aremover) {         //Altera o tempo de refei��o de todos os elemntos do grupo nas mesas
							pessoaencontrada = true;
							auxiliarCadeiras->pessoa->ciclosrestantes = novotempo;
						}
						auxiliarCadeiras = auxiliarCadeiras->previous;

					}
					aux2 = aux2->previous;
				}
			
				cout << endl << endl;
			}
			if (functions == 10) {
				cout << "Informa��o relativa ao utente com n�mero mecanogr�fico indicado pelo utilizador:" << endl; //Inform��o relativa a uma pessoa com n� mecanografico x
				cout << "N�mero Mecanogr�fico:" << endl;
				cin >> aremover;
				cout << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_mec == aremover) {
						cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Dura��o, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
					}
					aux = aux->previous;
				}
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						if (auxiliarCadeiras->pessoa->num_mec == aremover) {
							cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << " (ciclos restantes : " << auxiliarCadeiras->pessoa->ciclosrestantes << ")" << endl;
						}
						auxiliarCadeiras = auxiliarCadeiras->previous;

					}
					aux2 = aux2->previous;
				}
			
			cout << endl << endl;
			}
			if (functions == 11) {						//Alterar nome e sobrenome
				string novonome;
				string novosobrenome;
				cout << "Alterar o nome de um utente:" << endl;
				cout << "N�mero mecanogr�fico da entidade em quest�o:" << endl;
				cin >> aremover;
				cout << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_mec == aremover) {
						cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Dura��o, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
						cout << "Qual o novo primeiro nome?" << endl;
						cin >> novonome;
						cout << "Novo sobrenome?" << endl;
						cin >> novosobrenome;
						aux->pessoa->prim_nome = novonome;
						aux->pessoa->seg_nome = novosobrenome;
					}
					aux = aux->previous;
				}
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						if (auxiliarCadeiras->pessoa->num_mec == aremover) {
							cout << auxiliarCadeiras->pessoa->prim_nome << " " << auxiliarCadeiras->pessoa->seg_nome << ", " << auxiliarCadeiras->pessoa->cargo << ", " << auxiliarCadeiras->pessoa->course << ", Grupo " << auxiliarCadeiras->pessoa->num_grupo_dep << ", " << auxiliarCadeiras->pessoa->num_mec << " (ciclos restantes : " << auxiliarCadeiras->pessoa->ciclosrestantes << ")" << endl;
							cout << "Qual o novo primeiro nome?" << endl;
							cin >> novonome;
							cout << "Novo sobrenome?" << endl;
							cin >> novosobrenome;
							auxiliarCadeiras->pessoa->prim_nome = novonome;
							auxiliarCadeiras->pessoa->seg_nome = novosobrenome;
						}
						auxiliarCadeiras = auxiliarCadeiras->previous;

					}
					aux2 = aux2->previous;
				}

				cout << endl << endl;
			}
			
			break;

		case '0':
			cout << "Escolheu a op��o Sair!" << endl << endl;
			sair = true;
			break;
		default:
			cout << "Escolha uma opcao valida." << endl << endl;
			break;
		}
	} while (!sair);

	system("PAUSE");
	return 0;
	cin.sync();
	cin.get();
}