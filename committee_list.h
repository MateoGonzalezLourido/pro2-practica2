/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "project_list.h"
#include "types.h"

// estructuras
#define MAX_COMITES 10
#define NULLC (-1)
typedef struct {
  tCommitteeName committeeName;
  tNumVotes totalEvaluators;
  tNumVotes validVotes;
  tNumVotes nullVotes;
  tListP projectList;
} tItemC;

struct Lista {
  tItemC data[MAX_COMITES];
  int last;
};

typedef int tPosC;
typedef tPosC tListC;

// funciones

// funciones del tipo tList
void createEmptyListC(tListC *L); // crear lista (devuelve un tList), (void)
                                  // indica "no recibe argumentos"
bool isEmptyListC(tListC L);      // vacia?; recibe la lista
tPosC firstC(tListC L); // devolver primer indice ocupado;recibe la lista
tPosC lastC(tListC L);  // devolver ultimo indice ocupado; recibe la lista
tPosC nextC(
    tPosC indice,
    tListC L); // devolver siguiente indice ocupado;recibe indice y lista
tPosC previousC(
    tPosC indice,
    tListC L); // devolver anterior indice ocupado; recibe indice y lista
bool insertItemC(tItemC data, tPosC indice,
                 tListC *L); // añadir elemento;recibe info insertar, indice
                             // donde se cambia, lista usar
void deleteAtPositionC(tPosC indice,
                       tListC *L); // borrar proyecto; recibe indice donde
                                   // borrar y la lista donde borrar
tItemC getItemC(tPosC indice, tListC L); // recuperar info proyecto
void updateItemC(tItemC data, tPosC indice,
                 tListC *L); // modificar lista; recibe cambiar, indice lista
                             // actualizar, lista usar
tPosC findItemC(
    tProjectName data,
    tListC L); // buscar indice proyecto; recibe info proyecto, lista usar
