/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "committee_list.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 255

// Buscador de comite y de proyectos de ese comite, devuelve un struct con la
// info de ambos / NULL si no se encuentra esa info
typedef struct {
  tPosP InfoProyecto;
  tPosC InfoComite;
} tProyectoInfo;

tProyectoInfo Obtener_Indice_Lista_Proyecto(tListC *lista, char *comitteeName,
                                            char *projectName) {
  tProyectoInfo resultado;
  resultado.InfoComite = findItemC(comitteeName, *lista);
  if (resultado.InfoComite == NULLC) {
    resultado.InfoProyecto = NULLP;
    return resultado;
  }

  resultado.InfoProyecto =
      findItemP(projectName, lista->data[resultado.InfoComite].projectList);

  return resultado;
}

/*
    funcion:añadir un proyecto nuevo
    parametros:el nombre del comite, total evaluadores, la lista donde añadir
*/
void Create(tListC *lista, char *comitteeName, char *totalEvaluators) {
  if (findItemC(comitteeName, *lista) != NULLC) {
    printf("+ Error: New not possible\n");
    return;
  }

  tItemC item;
  // Limitar a 25 caracteres máximo
  strncpy(item.committeeName, comitteeName, NAME_LENGTH_LIMIT - 1);
  item.committeeName[NAME_LENGTH_LIMIT - 1] = '\0'; // Asegurar terminación nula
  item.totalEvaluators = atoi(totalEvaluators);
  item.validVotes = 0;
  item.nullVotes = 0;
  createEmptyListP(&item.projectList);
  insertItemC(item, lastC(*lista) + 1, lista);
  printf();
}

/*
funcion:añadir un proyecto nuevo a un comite
parametros:el nombre del proyecto, categoria eco, la lista donde añadir
*/
void New(tListC *lista, char *comitteeName, char *projectName, char *category) {
  const tProyectoInfo resultado =
      Obtener_Indice_Lista_Proyecto(lista, comitteeName, projectName);
  if (resultado.InfoComite == NULLC || resultado.InfoProyecto == NULLP) {
    printf("+ Error: Committee not found\n");
    return;
  }

  // crear info
  tItemP item;
  strcpy(item.projectName, projectName);
  item.projectEco = (strcmp(category, "eco") == 0);
  item.numVotes = 0;

  // insertar al final
  if (!insertItemP(item, &lista->data[resultado.InfoComite].projectList)) {
    printf("+ Error: New not possible\n");
    return;
  }

  printf("* New: project %s category %s\n", projectName,
         item.projectEco ? "eco" : "non-eco");
}
/*
    funcion:votar un proyecto
    parametros:lista comites,nombre comite,nombre del proyecto
*/
void vote(tListC *lista, char *comitteeName, char *projectName) {
  const tProyectoInfo resultado =
      Obtener_Indice_Lista_Proyecto(lista, comitteeName, projectName);
  if (resultado.InfoComite == NULLC) {
    printf("+ Error: Committee not found\n");
    return;
  }
  if (resultado.InfoProyecto == NULLP) {
    printf("+ Error: Project not found\n");
    lista->data[resultado.InfoComite].nullVotes++;
    return;
  }

  // actualizar votos
  resultado.InfoProyecto->data.numVotes++;
  lista->data[resultado.InfoComite].validVotes++;
  updateItemP(resultado.InfoProyecto->data, resultado.InfoProyecto,
              &lista->data[resultado.InfoComite].projectList);

  printf();
}
/*
    funcion:descalificar/borrar un proyecto
    parametros:lista comites,nombre comite,nombre del proyecto
*/
void Disqualify(tListC *lista, char *comitteeName, char *projectName) {
  const tProyectoInfo resultado =
      Obtener_Indice_Lista_Proyecto(lista, comitteeName, projectName);
  if (resultado.InfoComite == NULLC || resultado.InfoProyecto == NULLP) {
    printf("+ Error: Committee not found\n");
    return;
  }

  lista->data[resultado.InfoComite].validVotes -=
      resultado.InfoProyecto->data.numVotes;
  lista->data[resultado.InfoComite].nullVotes +=
      resultado.InfoProyecto->data.numVotes;
  deleteAtPositionP(
      resultado.InfoProyecto,
      &lista->data[resultado.InfoComite]
           .projectList); // deleteAtPositionP ya actualiza la lista, no hace
                          // falta actualizarla después

  printf();
}

void Remove(tListC *lista) {
  const tPosC comites = lastC(*lista);
  for (int i = 0; i <= comites; i++) {
    if (lista->data[i].validVotes == 0) {
      deleteAtPositionC(i, lista);
    }
  }
}

void Stats() {}
void Winners() {}

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, tListC *listCommittees) {
  printf("********************\n");

  switch (command) {
  case 'C':
    printf();
    Create(listCommittees, param1, param2);
    break;
  case 'N':
    printf();
    New(listCommittees, param1, param2, param3);
    break;
  case 'S':
    printf();
    Stats();
    break;
  case 'V':
    printf();
    vote(listCommittees, param1, param2);
    break;
  case 'D':
    printf();
    Disqualify(listCommittees, param1, param2);
    break;
  case 'R':
    printf();
    Remove(listCommittees);
    break;
  case 'W':
    printf();
    Winners();
    break;
  default:
    printf();
    break;
  }
}

void readTasks(char *filename, tListC *listCommittees) {
  FILE *f = NULL;
  char *commandNumber, *command, *param1, *param2, *param3;
  const char delimiters[] = " \n\r";
  char buffer[MAX_BUFFER];

  f = fopen(filename, "r");

  if (f != NULL) {

    while (fgets(buffer, MAX_BUFFER, f)) {
      commandNumber = strtok(buffer, delimiters);
      command = strtok(NULL, delimiters);
      param1 = strtok(NULL, delimiters);
      param2 = strtok(NULL, delimiters);
      param3 = strtok(NULL, delimiters);

      processCommand(commandNumber, command[0], param1, param2, param3,
                     listCommittees);
    }

    fclose(f);

  } else {
    printf("Cannot open file %s.\n", filename);
  }
}

int main(int nargs, char **args) {
  tListC listCommittees;
  createEmptyListC(&listCommittees);
  char *file_name = "create.txt";

  if (nargs > 1) {
    file_name = args[1];
  } else {
#ifdef INPUT_FILE
    file_name = INPUT_FILE;
#endif
  }

  readTasks(file_name, &listCommittees);

  return 0;
}
