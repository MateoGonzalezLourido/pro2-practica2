/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: gonzález lourido, mateo LOGIN 1: m.glourido
 * GROUP: 3.3
 * DATE: 10/04/2026
 */

#include "project_list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void createEmptyListP(tListP *L) {
  // precd: ya esta inicializada
  *L = NULLP; // asi se define que esta vacia
}

bool isEmptyListP(const tListP L) { return L == NULLP; }

tPosP firstP(const tListP L) {
  return L; // por normas del TAD,tListP L ya representa el puntero al nodo1, y
            // cumple el TAD
}

tPosP lastP(tListP L) {
  tPosP p = L;                             // cd TAD
  while (p != NULLP && p->next != NULLP) { // buscar desde el primer nodo hasta
                                           // que sea null (ultimo nodo +1)
    p = p->next;
  }
  return p; // p apunta al ultimo nodo de la lista
}
tPosP nextP(tPosP p, const tListP L) {
  (void)L; // L no hace falta
  if (p == NULLP)
    return NULLP; // el rango es valido, pero podria ser una lista vacia
  return p->next;
}

tPosP previousP(const tPosP p, const tListP L) {
  if (p == NULLP || L == NULLP || L == p)
    return NULLP;

  tPosP q = L;                               // nodo anterior
  while (q->next != NULLP && q->next != p) { // desde el inicio hasta nodo dado
    q = q->next;                             // recorremos los nodos
  }
  return (q->next == p)
             ? q
             : NULLP; // esto es por si no encontramos p al recorrer nodos (por
                      // eso devolvemos NULLP , porque fallo)
}

bool insertItemP(const tItemP data, tListP *L) {
  tPosP newNode = malloc(sizeof(*newNode));
  if (newNode == NULL) return false;

  newNode->data = data;
  newNode->next = NULLP;

  // Caso 1: lista vacía, o el nuevo nodo va antes que el primero
  if (*L == NULLP || strcmp(data.projectName, (*L)->data.projectName) < 0) {
    newNode->next = *L;
    *L = newNode;
    return true;
  }

  // Caso 2: buscar posición correcta
  tPosP prev = *L;
  while (prev->next != NULLP && strcmp(prev->next->data.projectName, data.projectName) < 0)
    prev = prev->next;


  newNode->next = prev->next;
  prev->next = newNode;
  return true;
}

tItemP getItemP(tPosP pos, tListP L) {
  (void)L;
  return pos->data;
}

tListP updateItemP(const tItemP newData, tPosP pos, tListP *L) {
  // lista vacia (si L es null, pos puede ser null, sienmdo posición válida
  // aunque sea Null)
  if (pos != NULLP)
    pos->data = newData; // actualizar el contenido del nodo
  return *L;             // la lista no cambia de orden ni de estructura
}

tPosP findItemP(tProjectName data, const tListP L) {
  tPosP p = L; // empezamos en el priemr nodo

  while (p != NULLP) {
    if (strcmp(p->data.projectName, data) == 0) { // coincidencia
      return p;
    }
    p = p->next; // siguiente nodo
  }
  return NULLP; // no se encotro nodo
}
tListP deleteAtPositionP(tPosP pos, tListP *L) {
  if (*L == NULLP || pos == NULLP) { // lista vacia
    return *L;
  }
  // si se borra el primer nodo
  if (pos == *L) {
    tListP newHead = (*L)->next;
    free(*L);
    *L = newHead;
    return newHead;
  }
  // buscar nodo anterior
  tPosP prev = *L;
  while (prev->next != NULLP && prev->next != pos) {
    prev = prev->next;
  }

  // si encontramos el nodo
  if (prev->next == pos) {
    prev->next = pos->next;
    free(pos);
  }
  return *L;
}
