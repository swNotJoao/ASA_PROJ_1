#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct student{
  unsigned int friendNumber;
  unsigned char gradePrediction;
  unsigned char visited;
  struct student **friends;
} student_t;

void propaga(student_t *student);
student_t* find_newMax(student_t *graph);

int studentNumber, friendshipNumber;
int i, j, k, src, dest, tmp, visitedN = 0;
char max = 0;
student_t *graph, *max_student;

int main(int argc, char **argv, char **envp) {
  if(scanf("%d,%d", &studentNumber, &friendshipNumber) != 2){};
  graph = (student_t*) calloc(studentNumber, sizeof(student_t));

  for(i = 0; i < studentNumber; i++){
    if(scanf("%hhu", &graph[i].gradePrediction) != 1){};

    /*if (graph[i].gradePrediction > max){
      max = graph[i].gradePrediction;
      max_student = &graph[i];
    } */

    graph[i].friends = (student_t**) calloc(32, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    if(scanf("%d %d", &src, &dest) != 2){};
    tmp = graph[dest - 1].friendNumber;

    if(tmp % 32 == 0)
      graph[dest - 1].friends = realloc(graph[dest - 1].friends, sizeof(student_t*)*(tmp + 32));

    graph[dest - 1].friends[tmp] = &graph[src - 1];
    graph[dest - 1].friendNumber++;
  }

  while(visitedN <= studentNumber) {
      max_student = find_newMax(graph);
      propaga(max_student);
  }

  for(i = 0; i < studentNumber; i++)
    printf("%d\n", graph[i].gradePrediction);

  return 0;
}

void propaga(student_t *student){
    student -> visited = 1;

    if (student -> friends[0] == NULL){
        student -> visited = 2;
        visitedN++;
    return;
  }

  for(i = 0; i < student -> friendNumber; i++){
      if (student -> friends[i] -> visited != 2) {
          student -> friends[i] -> gradePrediction = max;
      }
    if (student -> friends[i] -> visited == 0)
      propaga(student -> friends[i]);
  }

    student -> visited = 2;
    visitedN++;
    return;
}

student_t* find_newMax(student_t *graph){
    int new_Max = 0;
    student_t *newMaxStudent;
    for(i = 0; i < studentNumber; i++){
        if(graph[i].visited != 2){
            max = MAX(new_Max, graph[i].gradePrediction);
            newMaxStudent = &graph[i];
        }
    }
    return newMaxStudent;
}
