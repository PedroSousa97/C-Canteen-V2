#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <time.h>
#include <string>
#include <locale.h>
#include "Functions.h"
#include "Entidade.h"
#include "Refeição.h"
#include "Mesa.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Portuguese");

	srand(time(NULL));

	string * primeirosnomes = new string[contaLinhas("primeiro_nome.txt")];
	preencheArray(primeirosnomes, "primeiro_nome.txt");
	string * ultimosnomes = new string[contaLinhas("ultimo_nome.txt")];
	preencheArray(ultimosnomes, "ultimo_nome.txt");
	string * cursos = new string[contaLinhas("cursos.txt")];						//Leitura, contagem de linhas e criação de arrays que irão conter os nomes e cursos
	preencheArray(cursos, "cursos.txt");
	int tamanhoy = contaLinhas("cursos.txt");

	int contaciclos = 0;
	int emerg;
	int ganhostotais = 0;
	int contaS = 0;
	string entrada;
	string pratoprincip;
	float custo;																		//Inicialização de variáveis e dos primeiros randoms
	int grupo;
	int elementosgrupo;
	int randomcargo;
	int randomciclos;
	int randomcourse;
	bool estatutoespecial;
	bool studentorstaff;
	string curso;
	int randomCriação = 40 + (std::rand() % (50 - 40 + 1));
	int randomCantina = 30 + (std::rand() % (50 - 30 + 1));
	int aremover;
	bool pessoaencontrada = false;
	bool dadosGuardados = false;
	int functions;

	Refeiçao* Atual = new Refeiçao;

	cout << "******************************* BEM VINDO À CANTINA EDA *******************************" << endl << endl;
	cout << "************************************ REFEIÇAO NOVA ************************************" << endl << endl;
	cout << "A cantina EDA necessita de uma nova refeição." << endl;
	cout << "   1.Introduza a entrada:" << endl;
	cin >> entrada;
	cout << "   2.Introduza o prato principal:" << endl;
	cin >> pratoprincip;
	cout << "   3.Introduza o custo:" << endl;
	cin >> custo;
	cout << endl << endl;

	Atual->entrada = entrada;
	Atual->pratoprincipal = pratoprincip;								//Preenchimento da Refeição Atual tendo em conta os dados introduzidos pelo utilizador
	Atual->custo = custo;

	


	BST* root = new BST;
	root = NULL;
	BST* ultmNome = new BST;							//Criação das raízes, embora nulas, das BST de entidades removidas, utentes ordenados por ultimo nome e mesas ordenadas por lugares ocupados
	ultmNome = NULL;
	BSTM* Mesas = new BSTM;
	Mesas = NULL;
	

	dupListLigada* Fila = new dupListLigada;			//Criação da Fila
	novaLista(Fila);

	while (randomCriação > 0) {
		int j = 0;
		grupo = 100 + (std::rand() % (500 - 100 + 1));
		elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
		randomcargo = 0 + (std::rand() % (2 - 0 + 1));								//Randoms simples para caracterizar aleatoriamente os novos utentes
		randomciclos = 2 + (std::rand() % (5 - 2 + 1));
		randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
		curso = cursos[randomcourse];

		if (randomcargo > 0) {
			studentorstaff = true;										//Definição de novas entidades como aluno ou staff
		}
		else if (randomcargo == 0) {
			studentorstaff = false;
		}
		while (j < elementosgrupo) {
			int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));				//Random para estatuto de 1 a 100
			if (randomestatuto <= 5) {											//Se o valor obtido for menor ou igual a 5 então é estudante estatuto especial 
				estatutoespecial = true;										//(ou seja 5 de 100 números dá uma probabilidade de 5% como pedido)
			}
			else if (randomestatuto > 5) {
				estatutoespecial = false;										//Enquanto j for menor que o núemro de elementos constituintes do grupo e não ultrapassar a capacidade da fila, cria entidades
			}
			criaEntidade(primeirosnomes, ultimosnomes, curso, Fila, grupo, estatutoespecial, studentorstaff, randomciclos, elementosgrupo);
			randomCriação--;
			j++;
		}
		j = 0;
	}
	
	

	dupListLigadaM* mesas = new dupListLigadaM;					//Criação da dupla lista ligada
	novaLista(*mesas);
	int lugaresdisponiveis = randomCantina;
	int v = 0;
	int numeromesa = 1;
	int numalunossentados = 0;
	int tamanhomesa;
	int vagasocupadas = 0;
	do {
		while (v <= randomCantina && lugaresdisponiveis > 0) {          //Enquanto houver cadeiras a colocar na cantina ele irá criar Mesas no vetor conjmesas
			tamanhomesa = 2 + (std::rand() % (5 - 2 + 1));				//Tamanho aleatório da mesa a criar
			if (tamanhomesa < lugaresdisponiveis) {
				tamanhomesa = tamanhomesa;
			}
			else if (tamanhomesa > lugaresdisponiveis) {				//Se o tamanho ultrapassar a disponibilidade, então o tamanho passa a ser a própria disponibilidade de colocção de cadeiras na cantina
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
	dupListLigadaM::Item* fimderefeiçao = mesas->apfim;
	dupListLigada::Item* fimderefeiçao2 = new dupListLigada::Item;
	dupListLigadaM::Item* emergencia = mesas->apfim;
	dupListLigada::Item* emergencia2 = new dupListLigada::Item;									//Interatores para percorres as listas em diferentes funções
	dupListLigada* FilaGravaçao = new dupListLigada;
	novaLista(FilaGravaçao);
	dupListLigadaM* MesasGravaçao = new dupListLigadaM;
	novaLista(*MesasGravaçao);
	Refeiçao* Gravaçao = new Refeiçao;
	BST* RemovidosGravaçao = new BST;
	RemovidosGravaçao = NULL;




	dupListLigada::Item * aux3 = Fila->apfim;
	
	while (aux3 != NULL) {
		if (aux3->pessoa->plafond < Atual->custo) {			//Verificação de alunos sem plafond
			int resposta;
			if (aux3->pessoa->estatuto == true) {
				cout << "**************************************** ATENÇÃO ****************************************" << endl;
				cout << "O aluno de estatuto especial " << aux3->pessoa->prim_nome << " com número mecanográfico " << aux3->pessoa->num_mec <<  " não tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
				cout << "   1.Remover entidade da fila;" << endl;     //Se for aluno de estatuto especial, não imprime a segunda opção tendo em conta que estes indivíduos não têm grupo
			}if (aux3->pessoa->estatuto == false) {
				cout << "**************************************** ATENÇÃO ****************************************" << endl;
				cout << "A entidade " << aux3->pessoa->prim_nome << " com número mecanográfico " << aux3->pessoa->num_mec << " grupo " << aux3->pessoa->num_grupo_dep << " não tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
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
				 if (aux3->previous == NULL) {								//Remoção de um só indivíduo
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
					if(auxdoaux->pessoa->num_grupo_dep == pesquisa){   //auxdoaux irá percorrer de novo a fila e remover todos os elementos com número de grupo igual á pessoa sem plafond detetada

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
	cout << "Entidades removidas por falta de plafond: " << endl << endl;		//Print para verificação do primeiro varrimento e deteção de entidades sem plafond e posterior remoção para a BST
	
	Print(root);


	cout << endl << endl;

	bool sair = false;
	char opcao;
	do
	{
		cout << "                                            Cantina EDA" << endl;
		cout << "(s)Seguinte   (e)Emergência   (g)Gravar   (c)Carregar Dados   (o)Opções   (0)Fechar Programa" << endl << endl;

		cout << "Refeição Actual:" << endl;
		cout << "      Entrada: " << Atual->entrada << endl;								//Impressão da Refeiçao
		cout << "      Prato: " << Atual->pratoprincipal << endl;
		cout << "      custo: " << Atual->custo << endl << endl;
		dupListLigadaM::Item * aux2 = mesas->apfim;
		while (aux2 != NULL) {
			cout << "Mesa " << aux2->mesa->numdemesa << " (CAPACIDADE " << aux2->mesa->tamanho <<") :" << endl;		//Impressão das mesaas e dos seus constituintes
			if (aux2->mesa->lugaresocupados == 0) {
				cout << "Não existem alunos sentados nesta mesa!" << endl << endl;			//Se a mesa tiver vazia:
			}
			else if (aux2->mesa->lugaresocupados > 0) {			//Impressão de todos os utentes sentados em cada mesa
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

		dupListLigada::Item * aux = Fila->apfim;				//Impressão da fila de espera
		while (aux != NULL) {
			cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Duração, "<<aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
			aux = aux->previous;

		}
		cout << endl << endl;
	
		cout << "Dinheiro cobrado até ao momento pela Cantina EDA: " << ganhostotais << "Euros!!" << endl;     //Print de uma variável criada para provar que a cobrança dos alunos removidos
		cin >> opcao;																						   //tanto por emergência como por ciclos está a ocorrer
		cout << endl << endl;
		if (opcao == 's') {
			contaS++;                                   //ContaS começa a 0
		}

		switch (opcao) {
		case 's':
			if (contaS == 1) {							//ContaS=1 significa que se refere ao primeiro ciclo, então popula só as mesas com os alunos da fila
				sentaPessoas(Fila, mesas);
			}
			else if (contaS > 1) {  
				while (descontaCiclos != NULL) {					//varrimento dos utentes sentados e a usufruir da refeição e subtração do tempo restante
					descontaCiclos2 = descontaCiclos->mesa->x->apfim;
					while (descontaCiclos2 != NULL) {
						descontaCiclos2->pessoa->ciclosrestantes = descontaCiclos2->pessoa->ciclosrestantes - 1;
						descontaCiclos2 = descontaCiclos2->previous;
					}
					descontaCiclos = descontaCiclos->previous;
				}
				descontaCiclos = mesas->apfim;

				while (fimderefeiçao != NULL) {							//Pesquisa de alunos que já tenham acabado a refeição e eliminação dos mesmos
					fimderefeiçao2 = fimderefeiçao->mesa->x->apfim;
					while (fimderefeiçao2 != NULL) {
						if (fimderefeiçao2->pessoa->ciclosrestantes == 0) {
							fimderefeiçao2->pessoa->plafond = fimderefeiçao2->pessoa->plafond - Atual->custo;   //cobra a refeição aos alunos
							fimderefeiçao->mesa->lugaresocupados = fimderefeiçao->mesa->lugaresocupados - 1;    //Volta a aumentar os lugares vagos
							if (fimderefeiçao2->next == NULL && fimderefeiçao2->previous == NULL) {
								fimderefeiçao->mesa->x->apfim->pessoa = NULL;
								fimderefeiçao->mesa->x->apfim->next = NULL;
								fimderefeiçao->mesa->x->apfim->previous = NULL;
							}
							if (fimderefeiçao2->next == NULL && fimderefeiçao2->previous != NULL && fimderefeiçao2->previous != fimderefeiçao->mesa->x->apinicio) {
								fimderefeiçao2->previous->next = NULL;
								fimderefeiçao->mesa->x->apfim = fimderefeiçao2->previous;
							}
							if (fimderefeiçao2->next == NULL && fimderefeiçao2->previous == fimderefeiçao->mesa->x->apinicio) {
								fimderefeiçao2->previous->next = NULL;
								fimderefeiçao->mesa->x->apfim = fimderefeiçao2->previous;
								fimderefeiçao->mesa->x->apinicio->pessoa = NULL;
								fimderefeiçao->mesa->x->apinicio->next = NULL;
								fimderefeiçao->mesa->x->apinicio->previous = NULL;
							}
							if (fimderefeiçao2->previous == NULL) {
								fimderefeiçao2->next->previous = NULL;
								fimderefeiçao->mesa->x->apinicio = fimderefeiçao2->next;
							}
							if (fimderefeiçao2->next != NULL && fimderefeiçao2->previous != NULL)
							{
								fimderefeiçao2->next->previous = fimderefeiçao2->previous;
								fimderefeiçao2->previous->next = fimderefeiçao2->next;

							}
							ganhostotais = ganhostotais + Atual->custo;					//Adiciona o custo da refeição aos ganhos da cantina toda vez que remove alguém com 0 cilcos restantes
						}

						fimderefeiçao2 = fimderefeiçao2->previous;
					}
					fimderefeiçao = fimderefeiçao->previous;
				}
				fimderefeiçao = mesas->apfim;

				randomCriação = 5 + (std::rand() % (15 - 5 + 1));  //Random entre 5 e 15 para que a cada ciclos cheguem à fila novos utentes, são assim criados sempre novas entidades e adicionados à fila
				while (randomCriação > 0) {
					int j = 0;
					grupo = 100 + (std::rand() % (500 - 100 + 1));
					elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
					randomcargo = 0 + (std::rand() % (2 - 0 + 1));								//Randoms
					randomciclos = 2 + (std::rand() % (5 - 2 + 1));
					randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
					curso = cursos[randomcourse];

					if (randomcargo > 0) {
						studentorstaff = true;										//Definição de novas entidades como aluno ou staff
					}
					else if (randomcargo == 0) {
						studentorstaff = false;
					}
					while (j < elementosgrupo) {
						int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));				//Random para estatuto de 1 a 100
						if (randomestatuto <= 5) {											//Se o valor obtido for menor ou igual a 5 então é estudante estatuto especial 
							estatutoespecial = true;										//(ou seja 5 de 100 números dá uma probabilidade de 5% como pedido)
						}
						else if (randomestatuto > 5) {
							estatutoespecial = false;										//Enquanto j for menor que o núemro de elementos constituintes do grupo e não ultrapassar a capacidade da fila, cria entidades
						}
						criaEntidade(primeirosnomes, ultimosnomes, curso, Fila, grupo, estatutoespecial, studentorstaff, randomciclos, elementosgrupo);
						randomCriação--;
						j++;
					}
					j = 0;
				}
				movimentaPessoas(Fila, mesas);     // Se houver vagas senta pessoas
				contaciclos++;
				if (contaciclos == 10) {													//A cada 10 ciclos a cantina necessita de uma nova refeição
					cout << "A cantina EDA necessita de uma nova refeição." << endl;
					cout << "   1.Introduza a entrada:" << endl;
					cin >> entrada;
					cout << "   2.Introduza o prato principal:" << endl;
					cin >> pratoprincip;
					cout << "   3.Introduza o custo:" << endl;
					cin >> custo;

					Atual->entrada = entrada;										//Atribuição da nova refeição
					Atual->pratoprincipal = pratoprincip;
					Atual->custo = custo;
					contaciclos = 0;																//Chegando aos 10 temos que inicializar de novo o contaciclos a 0
				}
				while (aux3 != NULL) {    //Nova verificação, com métodos iguais ao anterior para remoção de entidades sem plafond
					if (aux3->pessoa->plafond < Atual->custo) {
						int resposta;
						if (aux3->pessoa->estatuto == true) {
							cout << "**************************************** ATENÇÃO ****************************************" << endl;
							cout << "O aluno de estatuto especial " << aux3->pessoa->prim_nome << " com número mecanográfico " << aux3->pessoa->num_mec << " não tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
							cout << "   1.Remover entidade da fila;" << endl;
						}if (aux3->pessoa->estatuto == false) {
							cout << "**************************************** ATENÇÃO ****************************************" << endl;
							cout << "A entidade " << aux3->pessoa->prim_nome << " com número mecanográfico " << aux3->pessoa->num_mec << " grupo " << aux3->pessoa->num_grupo_dep << " não tem plafond suficiente. (Plafond " << aux3->pessoa->plafond << " Euros)" << endl;
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
			cout << "**************************************** EMERGÊNCIA ****************************************" << endl;   //Remoção de um utente ou grupo por emergência
			cout << "Situação de emergência:" << endl;
			cout << "   1.Remover entidade da cantina;" << endl;
			cout << "   2.Remover grupo/departamento da cantina;" << endl;
			cin >> emerg;
			if (emerg == 1) {
				cout << "Número mecanográfico da entidade:" << endl;
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
					cout << "Não existe de momento nenhuma entidade com número " << aremover << " a usufruir da cantina!" << endl << endl;
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
					cout << "Não existe de momento nenhuma entidade com número de Grupo/Departamento " << aremover << " a usufruir da cantina!" << endl << endl;
				}
				pessoaencontrada = false;
				emergencia = mesas->apfim;
			}
			movimentaPessoas(Fila, mesas);
			break;
		case 'g':

			FilaGravaçao->apfim = Fila->apfim;
			RemovidosGravaçao = root;
			MesasGravaçao->apfim = mesas->apfim;
			Gravaçao->custo = Atual->custo;
			Gravaçao->pratoprincipal = Atual->pratoprincipal;
			Gravaçao->entrada = Atual->entrada;
			dadosGuardados = true;
			break;
		case 'c':														//Infelizmente não foi possível utilizar gravação através de ficheiro txt, dava erro de gravação externo e não permitia realizar 
			if (dadosGuardados == false) {								//a alteração/escrita no ficheiro. Contudo consegue gravar enquanto se está a usufruir do executável, grava dados, sobrepondo cada
				cout << "************Não existem dados de Cantina gravados!**************" << endl;	//vez que é utilizado. Apenas as mesas é que não carregam os dados com sucesso
			}
			if (dadosGuardados == true) {
				Fila->apfim = FilaGravaçao->apfim;
				root = RemovidosGravaçao;
				mesas->apfim = MesasGravaçao->apfim;
				Atual->custo = Gravaçao->custo;
				Atual->pratoprincipal = Gravaçao->pratoprincipal;
				Atual->entrada = Gravaçao->entrada;
			}
			break;
		case 'o':
			cout << "******************************* OPÇÕES *******************************" << endl << endl;
			cout << "   1.Visualizar todos os utentes da cantina;" << endl;
			cout << "   2.Visualizar todos os utentes ordenados alfabeticamente pelo sobrenome;" << endl;
			cout << "   3.Mostrar todas as mesas;" << endl;
			cout << "   4.Mostrar todas as mesas ordanadas por número de lugares ocupados;" << endl;
			cout << "   5.Mostrar todos os indivíduos rejeitados por falta de plafond;" << endl;
			cout << "   6.Mostrar todos os indivíduos rejeitados por falta de plafond ordenados pelo primeiro nome;" << endl;
			cout << "   7.Aletar plafond de algum utente que ainda se encontre na fila;" << endl;
			cout << "   8.Procurar utentes por curso/departamento;" << endl;
			cout << "   9.Editar o tempo de refeição de um grupo/departamento;" << endl;
			cout << "  10.Pesquisa de informação relativa ao utente por número mecanográfico;" << endl;
			cout << "  11.Editar o nome de um indivíduo;" << endl;
			cin >> functions;
			cout << endl << endl;
			if (functions == 1) {						//Prints básicos idênticos aos anteriores para apresnetar todos os utentes da Cantina
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
			if (functions == 2) {  //É aqui  que se usa a BST organizada por último nome dos utentes para apresnetar todos os utentes que atualmente estam a usufruir da cantina
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
				cout << "Todos os utentes que estam atualmente a usufruir dos serviços da Cantina:" << endl << endl;
				Print(ultmNome);
				cout << endl << endl;
			}
			if (functions == 3)			//Impressão simples e igual à anterior para impressão das mesas e utentes sentados nas mesmas
				aux2 = mesas->apfim;
			while (aux2 != NULL) {
				cout << "Mesa " << aux2->mesa->numdemesa << " (CAPACIDADE " << aux2->mesa->tamanho << ") :" << endl;
				if (aux2->mesa->lugaresocupados == 0) {
					cout << "Não existem alunos sentados nesta mesa!" << endl << endl;
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
			if (functions == 4) {					//É aqui que se dá uso à BST de mesas para imprrimir as mesmas e os seus utentes por ordem crescente de número de lugares ocupados
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					Mesas = adicionaElemBSTM(Mesas, aux2->mesa);
					aux2 = aux2->previous;
				}
				cout << "Todos as mesas organizadas por número de lugares ocupados:" << endl << endl;
				Print(Mesas);
				cout << endl << endl;
			}
			if (functions == 5) {							
				cout << "************ Entidades removidas por falta de plafond: ************" << endl << endl;
				Print(root);
				cout << endl << endl;
			}
			if (functions == 6) {																				     //Não fazia sentido desorganizar a BST, então ambos os prints são iguais e de fácil
				cout << "Entidades removidas por falta de plafond ordenados por ordem alfabética:" << endl << endl;  //compreensão
				Print(root);
				cout << endl << endl;
			}
			if (functions == 7) {												//Alteração de plafond de uma entidade em questão
				cout << "***************************** Alterar Plafond de Utente *****************************" << endl;
				cout << "Indique o número mecanográfico da entidade em questão:" << endl;
				cout << "Número mecanográfico da entidade:" << endl;
				cin >> aremover;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_mec == aremover) {
						float novoplafond;												//Procura na fila a pessoa com número indicado pelo utilizador
						pessoaencontrada = true;
						cout << "Insira o novo Plafond:" << endl;
						cin >> novoplafond;
						aux->pessoa->plafond = novoplafond;
					}
					aux = aux->previous;

				}
				if (pessoaencontrada = false) {
					cout << "Não existe entidade com este número mecanográfico!" << endl;			//Se não existir o número em questão
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
					cout << endl << endl;     // Impressão de todos os utentes do curso em questão
					aux = Fila->apfim;
					while (aux != NULL) {
						if (aux->pessoa->course == curso) {
							cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Duração, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
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
					aux = Fila->apfim;         // Impressão de todos os utentes do departamento em questão
					while (aux != NULL) {
						if (aux->pessoa->num_grupo_dep == aremover) {
							pessoaencontrada = true;
							cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Duração, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
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
				cout << "Editar o tempo de refeição de um grupo/departamento:" << endl;
				cout << "Novo tempo de refeição que quer atribuir:" << endl;
				cin >> novotempo;
				cout << "Departamento/Grupo a alterar tempo de refeição:" << endl;
				cin >> aremover;
				cout << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_grupo_dep == aremover) {
						pessoaencontrada = true;							//Altera o tempo de refeição de todos os elemntos do grupo na fila
						aux->pessoa->ciclosrestantes = novotempo;
					}
					aux = aux->previous;
				}
				aux2 = mesas->apfim;
				while (aux2 != NULL) {
					dupListLigada::Item* auxiliarCadeiras = aux2->mesa->x->apfim;
					while (auxiliarCadeiras != NULL) {
						if (auxiliarCadeiras->pessoa->num_grupo_dep == aremover) {         //Altera o tempo de refeição de todos os elemntos do grupo nas mesas
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
				cout << "Informação relativa ao utente com número mecanográfico indicado pelo utilizador:" << endl; //Informção relativa a uma pessoa com nº mecanografico x
				cout << "Número Mecanográfico:" << endl;
				cin >> aremover;
				cout << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_mec == aremover) {
						cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Duração, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
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
				cout << "Número mecanográfico da entidade em questão:" << endl;
				cin >> aremover;
				cout << endl << endl;
				aux = Fila->apfim;
				while (aux != NULL) {
					if (aux->pessoa->num_mec == aremover) {
						cout << aux->pessoa->prim_nome << " " << aux->pessoa->seg_nome << ", " << aux->pessoa->num_mec << ", " << aux->pessoa->cargo << ", " << aux->pessoa->num_grupo_dep << ", " << aux->pessoa->course << ", Duração, " << aux->pessoa->ciclosrestantes << ", Plafond: " << aux->pessoa->plafond << " Euros" << endl;
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
			cout << "Escolheu a opção Sair!" << endl << endl;
			sair = true;
			break;
		default:
			cout << "Escolha uma opcao valida." << endl << endl;
			break;
		}
	} while (!sair);

	system("PAUSE");
	cin.sync();
	cin.get();
	return 0;
}
