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

int studentNumber, friendshipNumber;
int i, j, k, src, dest, tmp, max = 0;
student_t *graph, max_student;

int main(int argc, char **argv, char **envp) {
  if(scanf("%d,%d", &studentNumber, &friendshipNumber) != 2){};
  graph = (student_t*) calloc(studentNumber, sizeof(student_t));

  for(i = 0; i < studentNumber; i++){
    if(scanf("%hhu", &graph[i].gradePrediction) != 1){};

    if (graph[i].gradePrediction > max){
      max = graph[i].gradePrediction;
      max_student = graph[i];
    }

    graph[i].friends = (student_t**) calloc(32, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    if(scanf("%d %d", &src, &dest) != 2){};
    tmp = graph[dest - 1].friendNumber;

    if(tmp % 32 == 0)
      graph[dest - 1].friends = realloc(graph[dest - 1].friends, sizeof(student_t*)*(tmp + 32));

    graph[dest - 1].friends[tmp] = &graph[src - 1];
    graph[dest - 1].friendNumber++;

    /*if(graph[src - 1].gradePrediction < graph[dest - 1].gradePrediction)
      graph[src - 1].gradePrediction = graph[dest - 1].gradePrediction;*/
  }
  /*
  for(k = 0; k < 2; k++)
    for(i = studentNumber - 1; i >= 0; i--)
      for(j = 0; j < graph[i].friendNumber; j++)
        if(graph[i].friends[j] -> gradePrediction > graph[i].gradePrediction)
          graph[i].gradePrediction = graph[i].friends[j] -> gradePrediction;
  */

  /*for(i = 0; i < max_student.friendNumber; i++){
    max_student.friends[i] -> gradePrediction = max;
    max_student.friends[i] -> visited = 1;
  }*/

  propaga(&max_student);

  for(i = 0; i < studentNumber; i++)
    printf("%d\n", graph[i].gradePrediction);

  return 0;
}

void propaga(student_t *student){
  if (student -> friends[0] == NULL){
    return;
  }

  for(i = 0; i < student -> friendNumber; i++){
    student -> friends[i] -> gradePrediction = max;
    student -> friends[i] -> visited = 1;
    if (student -> friends[i] -> visited == 0)
      propaga(student -> friends[i]);
  }
  return;
}
