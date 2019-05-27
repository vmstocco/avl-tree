#ifndef ARVOREAVL_H_INCLUDED
#define ARVOREAVL_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

struct INFO {
  int chave;
  int valor;
};

struct NO {
  struct INFO info;
  int fb; //fator de balanceamento
  struct NO *pai; //ponteiro para o pai
  struct NO *fesq; //ponteiro para o filho da esquerda
  struct NO *fdir; //ponteiro para o filho da direita
};

struct ARVORE_AVL {
  struct NO *raiz;
};

struct NO *rot_dir(struct NO *no);
struct NO *rot_esq(struct NO *no);
struct NO *rot_dir_esq(struct NO *no);
struct NO *rot_esq_dir(struct NO *no);

void criar_arvore_avl(struct ARVORE_AVL *arv);
void limpar_arvore_avl(struct ARVORE_AVL *arv);
void limpar_arvore_avl_aux(struct NO *raiz);
void preordem_aux(struct NO *raiz);
void preordem(struct ARVORE_AVL *arv);

void inserir_arvore_avl(struct ARVORE_AVL *arv, struct INFO info);

// lê os elementos de entrada
void leitura(int *tam, struct INFO **valores);

struct NO *balanceamento_esquerdo(struct NO *no, bool *h);
struct NO *balanceamento_direito(struct NO *no, bool *h);
struct NO *busca_remove(struct NO *no, struct NO *no_chave, bool h);

// realiza a remoção de um elemento
void remover_aux(struct ARVORE_AVL *arv,int info, bool *h);


#endif // ARVOREAVL_H_INCLUDED
