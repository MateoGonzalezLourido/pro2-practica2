/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: gonzález lourido, mateo LOGIN 1: m.glourido
 * AUTHOR 2: muradas santa maría, pablo LOGIN 2: pablo.muradas
 * GROUP: 3.3
 * DATE: 10/04/2026
 */

#include "committee_list.h"
#include "string.h"
#include <stdbool.h>
#include <string.h>

/* Write your code here... */

void createEmptyListC(tListC *L) {
    L->last = NULLC; // asi se define que esta vacia
}

bool isEmptyListC(tListC L) {
    return L.last == NULLC; // vacio?
}

tPosC firstC(tListC L) {
    (void) L;
    return 0; // como los datos al borrar se mueven para abajo podemos asumir que
    // si la lista no esta vacia es 0, si fuese vacia sería null(-1)
    // pero ya es precondición
}

tPosC lastC(tListC L) {
    // ultimo indice ocupado(se guarda en la lista)
    return L.last;
}

tPosC nextC(const tPosC indice, const tListC L) {
    if (indice < 0 || indice >= L.last)
        return NULLC; // fuera de rango
    return (tPosC) indice + 1;
}

tPosC previousC(const tPosC indice, const tListC L) {
    (void) L;
    if (indice <= 0)
        return NULLC; // estaria fuera de rango
    return (tPosC) indice - 1;
}

bool insertItemC(const tItemC data,tListC *L) {
    // el indice ya es valido
    if (L->last == MAX_COMITES - 1)
        return false; // lista ya llena
    const tPosC ultimo =lastC(*L);
     tPosC indice=0;
    while (indice<=ultimo && strcmp(L->data[indice].committeeName, data.committeeName) < 0) indice++;

    for (int i = L->last; i >= indice;i--) {
        // mover para arriba los datos (excepto si es lista vacia)
        L->data[i+1] = L->data[i];
    }
    L->data[indice] = data;
    L->last++;
    return true;
}

void deleteAtPositionC(const tPosC indice, tListC *L) {
    if (indice != MAX_COMITES - 1) {
        // hay que mover los posteriores para abajo
        for (int i = indice; i < L->last;
             i++) {
            // mover para abajo los datos (esto cambia los indices)
            L->data[i] = L->data[i + 1];
        }
    } // si el indice es el ultimo, ya no se borra (no hay datos posteriores que
    // bajar)
    L->last--; // actualizamos ultimo espacio ocupado
}

tItemC getItemC(const tPosC indice, const tListC L) { return L.data[indice]; }

void updateItemC(const tItemC data, const tPosC indice, tListC *L) {
    L->data[indice] = data;
}

tPosC findItemC(tProjectName data, const tListC L) {
    for (int i = 0; i <= L.last; i++) {
        // validaciones (comparar datos; mala escabilidad)
        if (strcmp(L.data[i].committeeName, data) == 0) {
            return i;
        }
    }
    return NULLC; // no existe/ no hay datos
}
