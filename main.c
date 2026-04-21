/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: gonzález lourido, mateo LOGIN 1: m.glourido
 * AUTHOR 2: muradas santa maría, pablo LOGIN 2: pablo.muradas
 * GROUP: 3.3
 * DATE: 10/04/2026
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

  tItemC item = getItemC(resultado.InfoComite, *lista);
  resultado.InfoProyecto = findItemP(projectName, item.projectList);

  return resultado;
}

/*
    funcion:añadir un proyecto nuevo
    parametros:el nombre del comite, total evaluadores, la lista donde añadir
*/
void Create(tListC *lista, char *comitteeName, char *totalEvaluators) {

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
  insertItemC(item, lista);
  printf("* Create: committee %s totalevaluators %d\n", item.committeeName,
         item.totalEvaluators);
}

/*
funcion:añadir un proyecto nuevo a un comite
parametros:el nombre del proyecto, categoria eco, la lista donde añadir
*/
void New(tListC *lista, char *comitteeName, char *projectName, char *category) {
  tProyectoInfo resultado =
      Obtener_Indice_Lista_Proyecto(lista, comitteeName, projectName);
  if (resultado.InfoComite == NULLC || resultado.InfoProyecto != NULLP) {
    printf("+ Error: New not possible\n");
    return;
  }

  // crear info
  tItemP item;
  strcpy(item.projectName, projectName);
  item.projectEco = (strcmp(category, "eco") == 0);
  item.numVotes = 0;

  // insertar al final
  tItemC comite = getItemC(resultado.InfoComite, *lista);
  if (!insertItemP(item, &comite.projectList)) {
    printf("+ Error: New not possible\n");
    return;
  }
  updateItemC(comite, resultado.InfoComite, lista);

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
    printf("+ Error: Vote not possible. Project %s not found in committee %s. "
           "NULLVOTE\n",
           projectName, comitteeName);
    lista->data[resultado.InfoComite].nullVotes++;
    return;
  }

  // actualizar votos
  tItemC comite = getItemC(resultado.InfoComite, *lista);
  tItemP proyecto = getItemP(resultado.InfoProyecto, comite.projectList);

  proyecto.numVotes++;
  updateItemP(proyecto, resultado.InfoProyecto, &comite.projectList);

  comite.validVotes++;
  updateItemC(comite, resultado.InfoComite, lista);

  printf("* Vote: committee %s project %s category %s numvotes %d\n",
          comitteeName, projectName,
          (proyecto.projectEco) ? "eco" : "non-eco",
          proyecto.numVotes);
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
  bool first = true;
  for (tPosC pC = firstC(*lista); pC != NULLC; pC = nextC(pC, *lista)) {
    tItemC comite = getItemC(pC, *lista);
    tPosP pP = findItemP(projectName, comite.projectList);

    printf("%sCommittee %s\n", first ? "" : "\n", comite.committeeName);
    first = false;

    if (pP == NULLP) {
      printf("No project\n%s disqualified\n", projectName);
      continue;
    }
    tItemP proyecto = getItemP(pP, comite.projectList);
    comite.nullVotes += proyecto.numVotes;
    comite.validVotes -= proyecto.numVotes;
    deleteAtPositionP(pP, &comite.projectList);
    updateItemC(comite, pC, lista);
    printf("Project %s disqualified\n", projectName);
  }
}

void Remove(tListC *lista) {
  if (isEmptyListC(*lista)) {
    printf("+ Error: Remove not possible\n");
    return;
  }
  bool removed = false;
  tPosC pC = firstC(*lista);
  while (pC != NULLC) {
    tItemC comite = getItemC(pC, *lista);
    if (comite.validVotes == 0) {
      printf("* Remove: committee %s\n", comite.committeeName);
      deleteAtPositionC(pC, lista);
      removed = true;
      // Al borrar en una lista con arrays, la posición actual pC pasa a apuntar al siguiente elemento
      // No incrementamos pC.
    } else {
      pC = nextC(pC, *lista);
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
  for (tPosC pC = firstC(*lista); pC != NULLC; pC = nextC(pC, *lista)) {
    tItemC comite = getItemC(pC, *lista);
    bool isLast = (nextC(pC, *lista) == NULLC);

    printf("Committee %s\n", comite.committeeName);
    if (isEmptyListP(comite.projectList)) {
      printf("No projects\nNullvotes %d\nParticipation: %d votes from %d "
             "evaluators (%.2f%%)\n%s",
             comite.nullVotes, comite.validVotes + comite.nullVotes,
             comite.totalEvaluators,
             (comite.totalEvaluators > 0)
                 ? ((comite.validVotes + comite.nullVotes) * 100.0 /
                    comite.totalEvaluators)
                 : 0.0,
             isLast ? "" : "\n");
      continue;
    }

    for (tPosP pP = firstP(comite.projectList); pP != NULLP; pP = nextP(pP, comite.projectList)) {
      tItemP proyecto = getItemP(pP, comite.projectList);
      printf("Project %s category %s numvotes %d (%.2f%%)\n",
             proyecto.projectName,
             proyecto.projectEco ? "eco" : "non-eco",
             proyecto.numVotes,
             (comite.validVotes > 0)
                 ? (proyecto.numVotes * 100.0 / comite.validVotes)
                 : 0.0);
    }

    printf(
        "Nullvotes %d\nParticipation: %d votes from %d evaluators (%.2f%%)\n%s",
        comite.nullVotes, comite.validVotes + comite.nullVotes,
        comite.totalEvaluators,
        (comite.totalEvaluators > 0) ? ((comite.validVotes + comite.nullVotes) *
                                        100.0 / comite.totalEvaluators)
                                     : 0.0,
        isLast ? "" : "\n");
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
  for (tPosC pC = firstC(*lista); pC != NULLC; pC = nextC(pC, *lista)) {
    tItemC comite = getItemC(pC, *lista);
    printf("%sCommittee %s \n", (pC == firstC(*lista)) ? "" : "\n", comite.committeeName);

    if (isEmptyListP(comite.projectList) || comite.validVotes == 0) {
      printf("Category eco: No winner\n");
      printf("Category non-eco: No winner\n");
      continue;
    }

    tPosP ganadorEco = NULLP;
    tPosP ganadorNonEco = NULLP;
    tNumVotes maxVotesEco = -1;
    tNumVotes maxVotesNonEco = -1;

    for (tPosP pP = firstP(comite.projectList); pP != NULLP; pP = nextP(pP, comite.projectList)) {
      tItemP itemP = getItemP(pP, comite.projectList);
      if (itemP.projectEco) {
        if (itemP.numVotes > maxVotesEco) {
          maxVotesEco = itemP.numVotes;
          ganadorEco = pP;
        }
      } else {
        if (itemP.numVotes > maxVotesNonEco) {
          maxVotesNonEco = itemP.numVotes;
          ganadorNonEco = pP;
        }
      }
    }

    if (ganadorEco != NULLP) {
      tItemP itemG = getItemP(ganadorEco, comite.projectList);
      printf("Category eco: Project %s numvotes %d\n", itemG.projectName, itemG.numVotes);
    } else {
      printf("Category eco: No winner\n");
    }

    if (ganadorNonEco != NULLP) {
      tItemP itemG = getItemP(ganadorNonEco, comite.projectList);
      printf("Category non-eco: Project %s numvotes %d\n", itemG.projectName, itemG.numVotes);
    } else {
      printf("Category non-eco: No winner\n");
    }
  }
}

void processCommand(char *commandNumber, char command, char *param1,
                    char *param2, char *param3, tListC *listCommittees) {
  printf("********************\n");

  switch (command) {
  case 'C':
    printf("%s %c: committee %s totalevaluators %s\n", commandNumber, command,
           param1, param2);
    Create(listCommittees, param1, param2);
    break;
  case 'N':
    printf("%s %c: committee %s project %s category %s\n", commandNumber,
           command, param1, param2, param3);
    New(listCommittees, param1, param2, param3);
    break;
  case 'S':
    printf("%s %c:\n", commandNumber, command);
    Stats(listCommittees);
    break;
  case 'V':
    printf("%s %c: committee %s project %s\n", commandNumber, command, param1,
           param2);
    vote(listCommittees, param1, param2);
    break;
  case 'D':
    printf("%s %c: project %s\n", commandNumber, command, param1);
    Disqualify(listCommittees, param1);
    break;
  case 'R':
    printf("%s %c:\n", commandNumber, command);
    Remove(listCommittees);
    break;
  case 'W':
    printf("%s %c:\n", commandNumber, command);
    Winners(listCommittees);
    break;
  default:
    printf("%s %c:\n", commandNumber, command);
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
