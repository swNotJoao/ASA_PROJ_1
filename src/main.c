#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct student{
  unsigned int friendNumber;
  unsigned char gradePrediction;
  unsigned char visited; /*0 ou 1*/
  struct student **friends;
} student_t;

int dfs(student_t *student);

int studentNumber, friendshipNumber;
int i, j, k, src, dest, tmp;
student_t *graph;

int main(int argc, char **argv, char **envp) {
  if(scanf("%d,%d", &studentNumber, &friendshipNumber) != 2){};
  graph = (student_t*) calloc(studentNumber, sizeof(student_t));

  for(i = 0; i < studentNumber; i++){
    if(scanf("%hhu", &graph[i].gradePrediction) != 1){};
    graph[i].friends = (student_t**) calloc(32, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    if(scanf("%d %d", &src, &dest) != 2){};
    tmp = graph[src - 1].friendNumber;

    if(tmp % 32 == 0)
      graph[src - 1].friends = realloc(graph[src - 1].friends, sizeof(student_t*)*(tmp + 32));

    graph[src - 1].friends[tmp] = &graph[dest - 1];
    graph[src - 1].friendNumber++;

    /*if(graph[src - 1].gradePrediction < graph[dest - 1].gradePrediction)
      graph[src - 1].gradePrediction = graph[dest - 1].gradePrediction;*/
  }

  /*for(k = 0; k < 2; k++)
    for(i = studentNumber - 1; i >= 0; i--)
      for(j = 0; j < graph[i].friendNumber; j++)
        if(graph[i].friends[j] -> gradePrediction > graph[i].gradePrediction)
          graph[i].gradePrediction = graph[i].friends[j] -> gradePrediction;*/

  dfs(&graph[0]);

  for(i = 0; i < studentNumber; i++)
    printf("%d\n", graph[i].gradePrediction);

  return 0;
}

int dfs(student_t *student){
  int i, max = student -> gradePrediction;

  if (student -> friends[0] == NULL){
    student -> gradePrediction = max;
    return student -> gradePrediction;
  }

  for (i = 0; i < student -> friendNumber; i++)
    if (student -> friends[i] -> visited == 0){
      student -> friends[i] -> visited = 1;
      max = MAX(dfs(student -> friends[i]), max);
    }
  student -> gradePrediction = max;
  return max;
}
