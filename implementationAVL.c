#include "headerAVL.h"

#include <stdlib.h>
#include <stdio.h>

void criar_arvore_avl(struct ARVORE_AVL *arv) {
  arv->raiz = NULL;
}

void limpar_arvore_avl_aux(struct NO *raiz) {
  if (raiz != NULL) {
    limpar_arvore_avl_aux(raiz->fesq);
    limpar_arvore_avl_aux(raiz->fdir);
    free(raiz);
  }
}

void limpar_arvore_avl(struct ARVORE_AVL *arv) {
  limpar_arvore_avl_aux(arv->raiz);
  arv->raiz = NULL;
}

void preordem_aux(struct NO *raiz) {
  if (raiz != NULL) {
    printf("%d\n", raiz->info.chave);
    preordem_aux(raiz->fesq);
    preordem_aux(raiz->fdir);
  } else {
    printf("NULL\n");
  }
}

void preordem(struct ARVORE_AVL *arv) {
  preordem_aux(arv->raiz);
  printf("-----------\n");
}

struct NO *rot_dir(struct NO *no) {
  struct NO *aux = no->fesq;

  if (no->pai) { //verifica se no não é a raiz
    if (no->pai->fesq == no)
      no->pai->fesq = aux;
    else
      no->pai->fdir = aux;
  }

  aux->pai = no->pai;
  no->fesq = aux->fdir;
  if (no->fesq) no->fesq->pai = no;
  aux->fdir = no;
  no->pai = aux;

  return(aux);
}

struct NO *rot_esq(struct NO *no) {
  struct NO *aux = no->fdir;

  if (no->pai) { //verifica se no não é a raiz
    if (no->pai->fesq == no)
      no->pai->fesq = aux;
    else
      no->pai->fdir = aux;
  }

  aux->pai = no->pai;
  no->fdir = aux->fesq;
  if (no->fdir) no->fdir->pai = no;
  aux->fesq = no;
  no->pai = aux;

  return(aux);
}

struct NO *rot_esq_dir(struct NO *no) {
  rot_esq(no->fesq);
  return(rot_dir(no));
}

struct NO *rot_dir_esq(struct NO *no) {
  rot_dir(no->fdir);
  return(rot_esq(no));
}

struct NO *inserir_arvore_avl_aux(struct NO *raiz, struct INFO info, int *atual_fb) {
  if (raiz == NULL) {
    raiz = (struct NO *) malloc(sizeof(struct NO));
    raiz->fesq = raiz->fdir = raiz->pai = NULL;
    raiz->info = info;
    raiz->fb = 0;
    *atual_fb = 1;
  } else {
    if (raiz->info.chave > info.chave) { //desce pela esquerda
      raiz->fesq = inserir_arvore_avl_aux(raiz->fesq, info, atual_fb);
      raiz->fesq->pai = raiz;

      if (*atual_fb) {
          switch(raiz->fb) {
              case -1: {
                raiz->fb = 0;
                *atual_fb = 0;
                break;
              }
              case 0: {
                raiz->fb = 1;
                break;
              }
              case 1: {
                  if (raiz->fesq->fb == 1) {
                      raiz = rot_dir(raiz);
                      raiz->fb = 0;
                      raiz->fdir->fb = 0;
                      *atual_fb = 0;
                  }
                  else {
                      raiz = rot_esq_dir(raiz);

                      if (raiz->fb == 1) {
                          raiz->fesq->fb = 0;
                          raiz->fb = -1;
                      }
                      else {
                          raiz->fesq->fb = 1;
                          raiz->fdir->fb = 0;
                      }
                      raiz->fb = 0;
                      *atual_fb = 0;
                  }
                break;
              }
          }
      }

    } else { //desce pela direita
      raiz->fdir = inserir_arvore_avl_aux(raiz->fdir, info, atual_fb);
      raiz->fdir->pai = raiz;

      if (*atual_fb) {
          switch(raiz->fb) {
              case 1: {
                raiz->fb = 0;
                *atual_fb = 0;
                break;
              }
              case 0: {
                raiz->fb = -1;
                break;
              }
              case -1: {
                  if (raiz->fdir->fb == -1) {
                      raiz = rot_esq(raiz);
                      raiz->fb = 0;
                      raiz->fesq->fb = 0;
                      *atual_fb = 0;
                  }
                  else {
                      raiz = rot_dir_esq(raiz);

                      if (raiz->fb == -1) {
                          raiz->fdir->fb = 0;
                          raiz->fb = 1;
                      }
                      else {
                          raiz->fdir->fb = -1;
                          raiz->fesq->fb = 0;
                      }
                      raiz->fb = 0;
                      *atual_fb = 0;
                  }
                break;
              }
            }
        }
    }
  }
  return(raiz);
}

void inserir_arvore_avl(struct ARVORE_AVL *arv, struct INFO info) {
    int atual_fb = 0;
    arv->raiz = inserir_arvore_avl_aux(arv->raiz, info,&atual_fb);
}

void leitura(int *tam,struct INFO **valores) {
  int i;

  printf ("Numero de elementos que serao inseridos: ");
  scanf ("%d", tam);
  *valores = (struct INFO *)malloc((*tam)*sizeof(struct INFO));

  for (i=0; i < *tam; i++) {
      printf ("Chave: ");
      scanf ("%d", &(*valores)[i].chave);
      printf ("Valor: ");
      scanf ("%d", &(*valores)[i].valor);
  }
}

// atualização do FB e balanceamento para a raiz esquerda
struct NO *balanceamento_esq(struct NO *no, bool h) {
    struct NO *fdir;
    int fbdir;

    switch (no->fb) {
        case 1:
            no->fb = 0;
            break;
        case 0:
            no->fb = -1;
            h = false;
            break;
        case -1:
                fdir = no->fdir;
                fbdir = fdir->fb;
                if (fbdir <= 0) {
                    fdir = rot_esq(no);

                    if (fbdir == 0) {
                        no->fb = -1;
                        fdir->fb = 1;
                        h = false;
                    }
                    else {
                        no->fb = 0;
                        fdir->fb = 0;
                    }
                    no = fdir;
                }
                else {
                    no = rot_dir_esq(no);
                    no->fb = 0;
                }
    }
    return(no);
}

// atualização do FB e balanceamento para a raiz direita
struct NO *balanceamento_dir(struct NO *no, bool h) {
    struct NO *fesq;
    int fbesq;

    switch (no->fb) {
        case -1:
            no->fb = 0;
            break;
        case 0:
            no->fb = 1;
            h = false;
            break;
        case 1:
            fesq = no->fesq;
            fbesq = fesq->fb;
            if (fbesq >= 0) {
                fesq = rot_dir(no);

                if (fbesq == 0) {
                    no->fb = 1;
                    fesq->fb = -1;
                    h = false;
                }
                else {
                    no->fb = 0;
                    fesq->fb = 0;
                }
                no = fesq;
            }
            else {
                no = rot_esq_dir(no);
                no->fb = 0;
            }
    }
    return(no);
}

// busca nó substituto e realiza a remoção (busca o mais à direita do nó esquerdo)
struct NO *busca_remove(struct NO *no, struct NO *no_chave, bool h) {
    struct NO *no_removido;

    if (no->fdir != NULL) {
        no->fdir = busca_remove(no->fdir, no_chave, h);

        if (h) no = balanceamento_dir(no, h);
    }
    else {
        no_chave->info = no->info;
        no_removido = no;
        no = no->fesq;

        if (no != NULL)
            no->pai = no_removido->pai;
            h = true;     //expande a atualização dos FB
            free(no_removido);
    }
    return(no);
}

// remoção da árvore
struct NO *remover(struct NO *raiz, int info, bool h) {
    if (raiz == NULL) {
        printf("Chave nao encontrada.");
        h = false;
    }
    else {
        if (raiz->info.chave > info) { //desce pela sub-árvore esquerda
            raiz->fesq = remover(raiz->fesq, info, h);

            if (h) raiz = balanceamento_esq(raiz, h);
        }
        else
            if (raiz->info.chave < info) { //desce pela sub-árvore direita
                raiz->fdir = remover(raiz->fdir, info, h);

                if (h) raiz = balanceamento_dir(raiz,h);
            }
            else { //encontrou o elemento que será removido
                if (raiz->fdir == NULL) {
                    if (raiz->fesq != NULL) //escolhe o nó à esquerda como substituto
                        raiz->fesq->pai = raiz->pai;
                        raiz = raiz->fesq;
                        h = true;
                    }
                    else
                    if (raiz->fesq == NULL) {
                        if (raiz->fdir != NULL) //escolhe o nó à direita como substituto
                            raiz->fdir->pai = raiz->pai;
                            raiz = raiz->fdir;
                            h = true;
                        }
                        else { // busca o elemento mais à direita do nó esquerdo
                            raiz->fesq = busca_remove(raiz->fesq, raiz, h);
                            //se necessário efetua balanceamento esquerdo, pois a função busca_remove foi para o nó esquerdo
                            if (h) raiz = balanceamento_esq(raiz, h);
                    }
            }
    }
    return(raiz);
}

void remover_aux(struct ARVORE_AVL *arv,int info, bool *h) {
    arv->raiz = remover(arv->raiz, info, h);
};

