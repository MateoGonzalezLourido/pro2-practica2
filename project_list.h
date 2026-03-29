/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "types.h"

// variables
#define NULLP NULL

typedef struct {
  tProjectName projectName;
  tNumVotes numVotes;
  tProjectEco projectEco;
} tItemP;

typedef struct tNode {
  tItemP data;
  struct tNode *next;
} tNode;

typedef struct tNode *tPosP;
typedef tPosP tListP;

// funciones

// funciones del tipo tList
void createEmptyListP(tListP *L);          /*Crea una lista (vacia)
         recibe de entradas la memoria de la lista (ya inicializada)
         Salidas: L pasa a ser null
         No hay condiciones ni postcondiciones
         */
bool isEmptyListP(tListP L);               /*comprueba si la lista esta vacia
               recibe de entradas el valor de la lista
               salidas: TRUE:vacia, FALSE:no vacia
               no hay precondiciones ni postcondiciones
               */
tPosP firstP(tListP L);                    /*devolver primer nodo ocupado
                  recibe de entradas el valor de la lista
                  salida: p.memoria del primer nodo de la lista
                  precondicion:lista no vacia
                  postcondicion: no hay
                  */
tPosP lastP(tListP L);                     /*devolver ultimo nodo ocupado
                   recibe de entradas el valor de la lista
                   salida: p.memoria del primer nodo de la lista
                   precondicion:lista no vacia
                   postcondicion: no hay
                   */
tPosP nextP(tPosP p, tListP L);            /*devolver siguiente nodo ocupado;
        recibe de entradas el valor de la lista y el nodo al que buscaremos su siguiente
        salida: p.memoria del siguiente nodo de la lista / null
        precondicion:nodo recibido valido
        postcondicion: no hay
        */
tPosP previousP(tPosP p, tListP L);        /* devolver anterior nodo ocupado;
       recibe de entradas el valor de la lista y el nodo al que buscaremos su siguiente
       salida: p.memoria del nodo anterior de la lista / null
       precondicion:nodo recibido valido
       postcondicion: no hay
       */
bool insertItemPP(tItemP item, tListP *L); /* añadir elemento a la lista
 recibe de entradas la p.memoria de la lista y el nodo donde añadiremos el nuevo
 item, y el item que añadiremos salida: true/false segun saliese bien o no
 precondicion:nodo donde insertar recibido valido
 postcondicion: Las posiciones de los elementos de la lista posteriores a la del
 elemento insertado pueden haber variado
 */
tItemP getItemP(tPosP pos, tListP L); /*recuperar info proyecto de un nodo de la
lista recibe de entradas el valor de la lista y el nodo que obtendremos su info
salida: el objeto pedido
precondicion:nodo recibido valido
postcondicion: ho hay */
tListP updateItemP(tItemP newData, tPosP pos,
                   tListP *L);                  /*actualizar un nodo de
la lista recibe de entradas la nueva data que pondremos, el nodo de la lista y
el p.memoria de la lista salida: el valor de la lista precondicion:nodo recibido
valido postcondicion: El orden de los elementos de la lista no se ve modificado
*/
tPosP findItemP(tProjectName data, tListP L);   /*buscar indice proyecto;
recibe de entradas el nombre del proyecto y el valor de la lista
salida: la info del nodo / null
precondicion:ho hay
postcondicion: ho hay */
tListP deleteAtPositionP(tPosP pos, tListP *L); /*borrar proyecto
recibe de entradas el nodo a borrar y la p.memoria de la lista
salida: la lista cambiada
precondicion:La posición indicada es una posición válida en la lista
postcondicion: Las posiciones de los elementos de la lista posteriores a la de
la           posición eliminada pueden haber variado. */