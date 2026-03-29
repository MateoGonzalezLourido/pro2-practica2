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

/* Write your code here... */
#define MAX_COMITES 10
#define NULLC -1
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




