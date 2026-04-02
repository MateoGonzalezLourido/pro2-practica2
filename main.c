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

  if (isEmptyListC(*lista)) {
    resultado.InfoComite = NULLC;
    resultado.InfoProyecto = NULLP;
    return resultado;
  }
  resultado.InfoComite = findItemC(comitteeName, *lista);
  if (resultado.InfoComite == NULLC) {
    resultado.InfoProyecto = NULLP;
    return resultado;
  }
  // TODO: REVISAR SI NECESITA PRECONDICION DE LISTA NO VACIA,

  resultado.InfoProyecto =
      findItemP(projectName, lista->data[resultado.InfoComite].projectList);

  return resultado;
}

/*
    funcion:añadir un proyecto nuevo
    parametros:el nombre del comite, total evaluadores, la lista donde añadir
*/
void Create(tListC *lista, char *comitteeName, char *totalEvaluators) {
  // TODO: REVISAR SI NECESITA PRECONDICION DE LISTA NO VACIA,

  if (findItemC(comitteeName, *lista) != NULLC) {
    printf("+ Error: Create not possible\n");
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
  printf("* Create: committee %s totalevaluators %d\n", item.committeeName,
         item.totalEvaluators);
}

/*
funcion:añadir un proyecto nuevo a un comite
parametros:el nombre del proyecto, categoria eco, la lista donde añadir
*/
void New(tListC *lista, char *comitteeName, char *projectName, char *category) {
  const tProyectoInfo resultado =
      Obtener_Indice_Lista_Proyecto(lista, comitteeName, projectName);
  if (resultado.InfoComite == NULLC || resultado.InfoProyecto == NULLP) {
    printf("+ Error: New not possible\n");
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

  printf("* New: committee %s project %s category %s\n", comitteeName,
         projectName, item.projectEco ? "eco" : "non-eco");
}
/*
    funcion:votar un proyecto
    parametros:lista comites,nombre comite,nombre del proyecto
*/
void vote(tListC *lista, char *comitteeName, char *projectName) {
  const tProyectoInfo resultado =
      Obtener_Indice_Lista_Proyecto(lista, comitteeName, projectName);
  if (resultado.InfoComite == NULLC) {
    printf("+ Error: Vote not possible\n");
    return;
  }
  if (resultado.InfoProyecto == NULLP) {
    printf("+ Error: Vote not possible. Project %s not found in committee %s\n",
           projectName, comitteeName);
    lista->data[resultado.InfoComite].nullVotes++;
    return;
  }

  // actualizar votos
  resultado.InfoProyecto->data.numVotes++;
  lista->data[resultado.InfoComite].validVotes++;
  updateItemP(resultado.InfoProyecto->data, resultado.InfoProyecto,
              &lista->data[resultado.InfoComite].projectList);

  printf("* Vote: committee %s project %s category %s numvotes %d\n",
         comitteeName, projectName,
         (resultado.InfoProyecto->data.projectEco) ? "eco" : "non-eco",
         resultado.InfoProyecto->data.numVotes);
}
/*
    funcion:descalificar/borrar un proyecto
    parametros:lista comites,nombre comite,nombre del proyecto
*/
void Disqualify(tListC *lista, char *projectName) {
  if (isEmptyListC(*lista)) {
    printf("+ Error: Disqualify not possible\n");
    return;
  }
  for (int i = 0; i <= lastC(*lista); i++) {
    tProyectoInfo resultado = Obtener_Indice_Lista_Proyecto(
        lista, lista->data[i].committeeName, projectName);
    if (resultado.InfoProyecto != NULLP)
      break;

    if (resultado.InfoComite == NULLC || resultado.InfoProyecto == NULLP) {
      printf("%sCommittee %s \nNo project \n%s disqualified\n",
             (i == 0) ? "" : "\n",
             lista->data[resultado.InfoComite].committeeName, projectName);
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

    printf("%sCommittee %s \nproject %s disqualified\n", (i == 0) ? "" : "\n",
           lista->data[resultado.InfoComite].committeeName, projectName);
  }
}

void Remove(tListC *lista) {
  if (isEmptyListC(*lista)) {
    printf("+ Error: Remove not possible\n");
    return;
  }
  const tPosC comites = lastC(*lista);
  bool removed = false;
  for (int i = 0; i <= comites; i++) {
    if (lista->data[i].validVotes == 0) {
      deleteAtPositionC(i, lista);
      printf("* Remove: committee %s\n", lista->data[i].committeeName);
      removed = true;
    }
  }
  if (!removed) {
    printf("+ Error: Remove not possible\n");
  }
}
/*
funcion:mostrar los datos de la votacion general
parametros:lista de comites
*/
void Stats(tListC *lista) {
  if (isEmptyListC(*lista)) {
    printf("+ Error: Stats not possible\n");
    return;
  }

  for (int i = 0; i <= lastC(*lista); i++) {
    tItemC comite = lista->data[i];
    printf("%sCommittee %s \n", (i == 0) ? "" : "\n", comite.committeeName);
    if (isEmptyListP(comite.projectList)) {
      printf("No projects\n Nullvotes %d\nParticipation: %d votes from %d "
             "evaluators (%.2f%%)\n",
             comite.nullVotes, comite.validVotes, comite.totalEvaluators,
             (comite.totalEvaluators > 0)
                 ? (comite.validVotes * 100.0 / comite.totalEvaluators)
                 : 0);
      continue;
    }
    tPosP proyecto = firstP(comite.projectList);
    tPosP ultimo = lastP(comite.projectList);
    do {
      printf("Project %s category %s numvotes %d (%d%%)\n",
             proyecto->data.projectName,
             (proyecto->data.projectEco) ? "eco" : "non-eco",
             proyecto->data.numVotes,
             (comite.validVotes > 0)
                 ? (proyecto->data.numVotes * 100 / comite.validVotes)
                 : 0);

      if (!strcmp(proyecto->data.projectName, ultimo->data.projectName))
        proyecto = nextP(proyecto, comite.projectList);

    } while (!strcmp(proyecto->data.projectName, ultimo->data.projectName));
  }
}
/*
funcion:mostrar proyecto ganador de cada comite de categoria eco y no eco
parametros:lista de comites
*/
void Winners(tListC *lista) {
  if (isEmptyListC(*lista)) {
    printf("+ Error: Winners not possible\n");
    return;
  }
  for (int i = 0; i <= lastC(*lista); i++) {
    tItemC comite = lista->data[i];
    if (isEmptyListP(comite.projectList) || comite.validVotes == 0) {
      printf("%sCommittee %s \n", (i == 0) ? "" : "\n", comite.committeeName);
      printf("Category eco: No winner\n");
      printf("Category non-eco: No winner\n");
      continue;
    }
    tPosP proyecto = firstP(comite.projectList);
    tPosP ultimo = lastP(comite.projectList);
    tPosP ganadorEco = NULL;
    tPosP ganadorNonEco = NULL;
    do {
      if (proyecto->data.projectEco) {
        if (ganadorEco == NULL ||
            proyecto->data.numVotes > ganadorEco->data.numVotes) {
          ganadorEco = proyecto;
        }
      } else {
        if (ganadorNonEco == NULL ||
            proyecto->data.numVotes > ganadorNonEco->data.numVotes) {
          ganadorNonEco = proyecto;
        }
      }

      if (!strcmp(proyecto->data.projectName, ultimo->data.projectName))
        proyecto = nextP(proyecto, comite.projectList);

    } while (!strcmp(proyecto->data.projectName, ultimo->data.projectName));

    // por si fallase algo
    if (proyecto == NULLP || ganadorEco == NULLP || ganadorNonEco == NULLP) {
      printf("+ Error: Winners not possible\n");
      continue;
    }

    printf("%sCommittee %s \n", (i == 0) ? "" : "\n", comite.committeeName);
    printf("Category eco: Project %s numvotes %d\n",
           ganadorEco->data.projectName, ganadorEco->data.numVotes);
    printf("Category non-eco: Project %s numvotes %d\n",
           ganadorNonEco ? ganadorNonEco->data.projectName : "No winner",
           ganadorNonEco ? ganadorNonEco->data.numVotes : 0);
  }
}

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, tListC *listCommittees) {
  printf("********************\n");

  switch (command) {
  case 'C':
    printf("%s %c: committee/project %s totalevaluators %s\n", commandNumber,
           command, param1, param2);
    Create(listCommittees, param1, param2);
    break;
  case 'N':
    printf("%s %c: committee/project %s totalevaluators %s category %s\n",
           commandNumber, command, param1, param2, param3);
    New(listCommittees, param1, param2, param3);
    break;
  case 'S':
    printf("%s %c\n", commandNumber, command);
    Stats(listCommittees);
    break;
  case 'V':
    printf("%s %c: committee/project %s totalevaluators %s\n", commandNumber,
           command, param1, param2);
    vote(listCommittees, param1, param2);
    break;
  case 'D':
    printf("%s %c: committee/project %s\n", commandNumber, command, param1);
    Disqualify(listCommittees, param1);
    break;
  case 'R':
    printf("%s %c\n", commandNumber, command);
    Remove(listCommittees);
    break;
  case 'W':
    printf("%s %c\n", commandNumber, command);
    Winners(listCommittees);
    break;
  default:
    printf("%s %c\n", commandNumber, command);
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
