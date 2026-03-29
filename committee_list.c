/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "committee_list.h"
#include "string.h"
#include <stdbool.h>
#include <string.h>

/* Write your code here... */

void createEmptyList(tListC *L) {
  L->last = NULLC; // asi se define que esta vacia
}

bool isEmptyList(tListC L) {
  return L.last == NULLC; // vacio?
}

tPosC first(tListC L) {
    (void)L;
  return 0; // como los datos al borrar se mueven para abajo podemos asumir que
            // si la lista no esta vacia es 0, si fuese vacia sería null(-1)
            // pero ya es precondición
}

tPosC last(tListC L) { // ultimo indice ocupado(se guarda en la lista)
  return L.last;
}

tPosC next(const tPosC indice, const tListC L) {
  if (indice < 0 || indice >= L.last)
    return NULLC; // fuera de rango
  return (tPosC)indice + 1;
}
tPosC previous(const tPosC indice, const tListC L) {
  if (indice <= 0)
    return NULLC; // estaria fuera de rango
  return (tPosC)indice - 1;
}
bool insertItem(const tItemC data, const tPosC indice,
                tListC *L) { // el indice ya es valido
  if (L->last == MAX_COMITES - 1)
    return false; // lista ya llena
  const tPosC indice2 = (indice == NULLC)
                            ? L->last + 1
                            : indice; // para que funcione si last = -1
  for (int i = L->last; i >= indice2;
       i--) { // mover para arriba los datos (excepto si es lista vacia)
    L->data[i + 1] = L->data[i];
  }
  L->data[indice2] = data;
  L->last++;
  return true;
}
void deleteAtPosition(const tPosC indice, tListC *L) {
  if (indice != MAX_COMITES - 1) { // hay que mover los posteriores para abajo
    for (int i = indice; i < L->last;
         i++) { // mover para abajo los datos (esto cambia los indices)
      L->data[i] = L->data[i + 1];
    }
  } // si el indice es el ultimo, ya no se borra (no hay datos posteriores que
    // bajar)
  L->last--; // actualizamos ultimo espacio ocupado
}

tItemC getItem(const tPosC indice, const tListC L) { return L.data[indice]; }

void updateItem(const tItemC data, const tPosC indice, tListC *L) {
  L->data[indice] = data;
}

tPosC findItem(tProjectName data, const tListC L) {
  for (int i = 0; i <= L.last; i++) {
    // validaciones (comparar datos; mala escabilidad)
    if (strcmp(L.data[i].committeeName, data) == 0) {
      return i;
    }
  }
  return NULLC; // no existe/ no hay datos
}