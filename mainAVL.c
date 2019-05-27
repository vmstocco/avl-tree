#include <stdio.h>
#include <stdlib.h>

#include "headerAVL.h"
#include "implementationAVL.c"

/*
Implementation of an AVL tree. Did it on my second semester at University of S�o Paulo.
*/

/*
Trabalho 3 - Remo��o em AVL - Algoritmos e Estruturas de dados - Professor: Fernando Vieira Paulovich

Vin�cius Marques Stocco n�USP 6427233
*/

int main() {
  struct ARVORE_AVL arv;
  criar_arvore_avl(&arv);

  int tam; //n�mero de elemento que ser�o inseridos na �rvore
  int i;
  int chave; //vari�vel que armazena a chave do elemento quer ser� removido
  int teste = 0; //vari�vel que verifica se o usu�rio quer continuar removendo
  bool bol;
  struct INFO *valores;

  //l� os elementos que ser�o inseridos na �rvore
  leitura(&tam,&valores);

  //insere e efetua o balanceamento dos elementos
  for (i=0; i < tam; i++) inserir_arvore_avl(&arv, valores[i]);

  //exibe em pr�-ordem
  preordem(&arv);

  if (tam > 0) {
    printf ("Digite 1 se deseja remover: ");
    scanf ("%d", &teste);

    while ((tam > 0) && (teste == 1)) { //verifica se h� pelo menos um elemento na �rvore para ser removido
        printf ("Chave do elemento: ");
        scanf ("%d", &chave);
        remover_aux(&arv,chave,&bol);
        printf ("\n");
        preordem(&arv);
        printf ("\nDigite 1 se deseja continuar removendo: ");
        scanf ("%d", &teste);
        tam--;
    }
  }
  else if (tam == 0) printf ("\nArvore vazia.\n\n");
  else printf ("\nValor invalido.\n\n");

  limpar_arvore_avl(&arv);

  return 0;
};
