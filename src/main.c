#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct student{
    unsigned int friendNumber;
    unsigned char gradePrediction;
    unsigned char visited; /*0 ou 1*/
    struct student **friends;
} student_t;

void dfs_visit(student_t* student, int* count, int* newGrade);
student_t* find_newMax(student_t *graph);

int studentNumber, friendshipNumber;
int i, j, k, src, dest, tmp, nVisited  = 0;
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
        tmp = graph[dest - 1].friendNumber;

        if(tmp % 32 == 0)
            graph[src - 1].friends = realloc(graph[src - 1].friends, sizeof(student_t*)*(tmp + 32));

        graph[dest - 1].friends[tmp] = &graph[src - 1];
        graph[dest - 1].friendNumber++;
    }

    for (i = 0; i < studentNumber; i++){
        graph[i].visited = 0;
    }

    while(nVisited < studentNumber){
        student_t* origin = find_newMax(&graph[0]);
        int max = origin -> gradePrediction;
        if (origin -> visited == 0){
            dfs_visit(origin, &nVisited, &max);
        }
    }

    for(i = 0; i < studentNumber; i++)
        printf("%d\n", graph[i].gradePrediction);

    return 0;
}

void dfs_visit(student_t* student, int* count, int* newGrade) {
    int nEdges = student -> friendNumber;
    student -> visited = ++(*count);
    student -> gradePrediction = *newGrade;
    nVisited++;
    for (i = 0; i < nEdges; i++){
        if(student -> friends[i] -> visited == 0){
            dfs_visit(student -> friends[i], count, newGrade);
        }
    }
}

student_t* find_newMax(student_t *graph){
    unsigned char new_Max = 0;
    student_t *newMaxStudent = NULL;
    for(i = 0; i < studentNumber; i++){
        if(graph[i].visited == 0){
            if(graph[i].gradePrediction > new_Max) {
                new_Max = graph[i].gradePrediction;
                newMaxStudent = &graph[i];
            }
        }
    }
    return newMaxStudent;
}
