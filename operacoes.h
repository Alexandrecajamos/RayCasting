#ifndef OPERACOES_H
#define OPERACOES_H
#include <stdio.h>
#include <stdlib.h>
#include <point.h>

class Operacoes
{
public:
    Operacoes();
    float** Identidade(int M);
    float** mult(int M, int N, int P, float **A, float **B);
    float** TrocaColuna (int M,int N, int P, int C1, int C2, float **matA);
    float** VetorColuna(Point P);
    float* Gauss(int N, float **A, float *b);
    float* Vetor(Point P);
    Point normal(Point a, Point b);

};

#endif // OPERACOES_H
