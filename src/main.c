#include <stdlib.h>
#include <stdio.h>

typedef struct student student_t;

void buildGraph();

typedef struct student{
  int friendNumber;
  int gradePrediction;
  student_t **friends;

} student_t;


int studentNumber, friendshipNumber;
student_t *graph;

int main(int argc, char **argv, char **envp) {

  buildGraph();

  return 0;
}

void buildGraph(){
  student_t *student;
  int i, grade, src, dest, tmp;

  scanf("%d,%d", &studentNumber, &friendshipNumber);
  printf("studentNumber = %d\n", studentNumber);
  graph = (student_t*) malloc(sizeof(student_t) * studentNumber);

  for(i = 0; i < studentNumber; i++){
    scanf("%d", &grade);
    graph[i].friendNumber = 0;
    graph[i].gradePrediction = grade;
    graph[i].friends = (student_t**) calloc(studentNumber, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    scanf("%d %d", &src, &dest);
    tmp = graph[src - 1].friendNumber;
    graph[src - 1].friends[tmp] = &graph[dest - 1];
    graph[src - 1].friendNumber++;
  }
}
