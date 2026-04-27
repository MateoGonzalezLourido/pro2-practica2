/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: gonzález lourido, mateo LOGIN 1: m.glourido
 * GROUP: 3.3
 * DATE: 10/04/2026
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

typedef struct {
  tItemC data[MAX_COMITES];
  int last;
} Lista;

typedef int tPosC;
typedef Lista tListC;

// funciones

// funciones del tipo tList

void createEmptyListC(tListC *L);         /*Crea una lista (vacia)
        recibe de entradas la memoria de la lista (ya inicializada)
        Salidas: L pasa a ser null
        No hay condiciones ni postcondiciones
        */
bool isEmptyListC(tListC L);              /*comprueba si la lista esta vacia
              recibe de entradas el valor de la lista
              salidas: TRUE:vacia, FALSE:no vacia
              no hay precondiciones ni postcondiciones
              */
tPosC firstC(tListC L);                   /*devolver primer nodo ocupado
                 recibe de entradas el valor de la lista
                 salida: indice del primer elemento de la lista
                 precondicion: lista no vacia
                 postcondicion: no hay
                 */
tPosC lastC(tListC L);                    /*devolver ultimo nodo ocupado
                  recibe de entradas el valor de la lista
                  salida: indice del ultimo elemento de la lista
                  precondicion: lista no vacia
                  postcondicion: no hay
                  */
tPosC nextC(tPosC indice, tListC L);      /*devolver siguiente nodo ocupado;
       recibe de entradas el valor de la lista y el indice al que buscaremos su
       siguiente      salida: indice del siguiente elemento de la lista / null
       precondicion: indice recibido valido
       postcondicion: no hay
       */
tPosC previousC(tPosC indice, tListC L);  /*devolver anterior nodo ocupado;
      recibe de entradas el valor de la lista y el indice al que buscaremos su
      anterior  salida: indice del elemento anterior de la lista / null
      precondicion: indice recibido valido
      postcondicion: no hay
      */
bool insertItemC(tItemC data, tListC *L); /*añadir elemento a la lista
recibe de entradas la p.memoria de la lista y el item que añadiremos
salida: true/false segun saliese bien o no
precondicion: indice donde insertar recibido valido
postcondicion: Las posiciones de los elementos de la lista posteriores a la del
elemento insertado pueden haber variado
*/
void deleteAtPositionC(tPosC indice, tListC *L); /*borrar proyecto
recibe de entradas el indice a borrar y la p.memoria de la lista
salida: la lista cambiada
precondicion: La posicion indicada es una posicion valida en la lista
postcondicion: Las posiciones de los elementos de la lista posteriores a la de
la            posicion eliminada pueden haber variado.
*/
tItemC getItemC(tPosC indice, tListC L); /*recuperar info proyecto de un nodo de
la lista recibe de entradas el valor de la lista y el indice del que obtendremos
su info salida: el objeto pedido precondicion: indice recibido valido
postcondicion: no hay
*/
void updateItemC(tItemC data, tPosC indice, tListC *L); /*actualizar un nodo de
la lista recibe de entradas la nueva data que pondremos, el indice de la lista y
la p.memoria de la lista
salida: void
precondicion: indice recibido valido
postcondicion: El orden de los elementos de la lista no se ve modificado
*/
tPosC findItemC(tProjectName data, tListC L); /*buscar indice proyecto;
recibe de entradas el nombre del proyecto y el valor de la lista
salida: el indice del nodo / null
precondicion: no hay
postcondicion: no hay
*/
