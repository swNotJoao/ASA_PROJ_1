#include <stdlib.h>
#include <stdio.h>

void buildGraph();
void printGrades();

typedef struct student student_t;
typedef struct student{
  int friendNumber;
  char gradePrediction;
  student_t **friends;

} student_t;

int studentNumber, friendshipNumber;
student_t *graph;

int main(int argc, char **argv, char **envp) {
  buildGraph();
  printGrades();

  return 0;
}

void buildGraph(){
  int i, j, grade, src, dest, tmp;

  if(scanf("%d,%d", &studentNumber, &friendshipNumber) != 2){};
  graph = (student_t*) malloc(sizeof(student_t) * studentNumber);

  for(i = 0; i < studentNumber; i++){
    if(scanf("%d", &grade) != 1){};
    graph[i].friendNumber = 0;
    graph[i].gradePrediction = grade;
    graph[i].friends = (student_t**) calloc(32, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    if(scanf("%d %d", &src, &dest) != 2){};
    tmp = graph[src - 1].friendNumber;

    if(tmp % 32 == 0){
      graph[src - 1].friends = realloc(graph[src - 1].friends, sizeof(student_t*)*(tmp + 32));
    }

    graph[src - 1].friends[tmp] = &graph[dest - 1];
    graph[src - 1].friendNumber++;

    if(graph[src - 1].gradePrediction < graph[dest - 1].gradePrediction){
      graph[src - 1].gradePrediction = graph[dest - 1].gradePrediction;
    }
  }

  for(i = studentNumber - 1; i >= 0; i--){
    for(j = 0; j < graph[i].friendNumber; j++){
      if(graph[i].friends[j] -> gradePrediction > graph[i].gradePrediction){
        graph[i].gradePrediction = graph[i].friends[j] -> gradePrediction;
      }
    }
  }
}

void printGrades(){
  int i;

  for(i = 0; i < studentNumber; i++){
    printf("%d\n", graph[i].gradePrediction);
  }
}
