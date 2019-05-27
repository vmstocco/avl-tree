#include <stdio.h>
#include <stdlib.h>

#include "headerAVL.h"
#include "implementationAVL.c"

/*
Implementation of an AVL tree. Did it on my second semester at University of São Paulo.
*/

/*
Trabalho 3 - Remoção em AVL - Algoritmos e Estruturas de dados - Professor: Fernando Vieira Paulovich

Vinícius Marques Stocco nºUSP 6427233
*/

int main() {
  struct ARVORE_AVL arv;
  criar_arvore_avl(&arv);

  int tam; //número de elemento que serão inseridos na árvore
  int i;
  int chave; //variável que armazena a chave do elemento quer será removido
  int teste = 0; //variável que verifica se o usuário quer continuar removendo
  bool bol;
  struct INFO *valores;

  //lê os elementos que serão inseridos na árvore
  leitura(&tam,&valores);

  //insere e efetua o balanceamento dos elementos
  for (i=0; i < tam; i++) inserir_arvore_avl(&arv, valores[i]);

  //exibe em pré-ordem
  preordem(&arv);

  if (tam > 0) {
    printf ("Digite 1 se deseja remover: ");
    scanf ("%d", &teste);

    while ((tam > 0) && (teste == 1)) { //verifica se há pelo menos um elemento na árvore para ser removido
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
