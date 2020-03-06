#include <stdlib.h>
#include <stdio.h>

void buildGraph();
void printGrades();

typedef struct student student_t;
typedef struct student{
  int friendNumber;
  int gradePrediction;
  int bestGrade;
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
  student_t *student;
  int i, j, grade, src, dest, tmp;

  scanf("%d,%d", &studentNumber, &friendshipNumber);
  graph = (student_t*) malloc(sizeof(student_t) * studentNumber);

  for(i = 0; i < studentNumber; i++){
    scanf("%d", &grade);
    graph[i].friendNumber = 0;
    graph[i].gradePrediction = grade;
    graph[i].bestGrade = grade;
    graph[i].friends = (student_t**) calloc(studentNumber, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    scanf("%d %d", &src, &dest);
    tmp = graph[src - 1].friendNumber;
    graph[src - 1].friends[tmp] = &graph[dest - 1];
    graph[src - 1].friendNumber++;

    if(graph[src - 1].bestGrade < graph[dest - 1].bestGrade){
      graph[src - 1].bestGrade = graph[dest - 1].bestGrade;
    }
  }

  for(i = studentNumber - 1; i >= 0; i--){
    for(j = 0; j < graph[i].friendNumber; j++){
      if(graph[i].friends[j] -> bestGrade > graph[i].bestGrade){
        graph[i].bestGrade = graph[i].friends[j] -> bestGrade;
      }
    }
  }

}

void printGrades(){
  int i;

  for(i = 0; i < studentNumber; i++){
    printf("%d\n", graph[i].bestGrade);
  }
}
