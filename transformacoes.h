#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H
#define TAM 4
#include "v3.h"
class transformacoes
{
public:
    transformacoes();
    void Identidade(float I[TAM][TAM]);
    void Escala(float E[TAM][TAM], float e[TAM-1]);
    void Translacao(float T[TAM][TAM], float t[TAM-1]);

    void MxM(float A[TAM][TAM],float B[TAM][TAM],float C[TAM][TAM]);
    void MxV(float M[TAM][TAM], Point *P);
    void Imp(float M[TAM][TAM]);

};

#endif // TRANSFORMACOES_H
