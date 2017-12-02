#include "transformacoes.h"

transformacoes::transformacoes()
{

}

void transformacoes::Identidade(float I[TAM][TAM]){
    for(int i=0; i<TAM;i++){
        for(int j=0;j<TAM;j++){
            if(i==j)
                I[i][j]=1;
            else
                I[i][j]=0;
        }
    }
}

void transformacoes::Translacao(float T[TAM][TAM], float t[TAM]){
    this->Identidade(T);
    for(int i=0;i<(TAM-1);i++)
        T[i][TAM-1]=t[i];

}

void transformacoes::Escala(float E[TAM][TAM], float e[TAM]){
    this->Identidade(E);
    for(int i=0;i<(TAM-1);i++)
        E[i][i]=e[i];
}

void transformacoes::MxM(float A[TAM][TAM], float B[TAM][TAM], float C[TAM][TAM]){
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++) {
            C[i][j] = 0;
            for (int k = 0; k < TAM; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

}

void transformacoes::MxV(float M[TAM][TAM], Point *P){
    float vP[TAM]={P->x, P->y, P->z,1};
    float vPt[TAM]={0,0,0,0};
    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM;j++)
        vPt[i]+=M[i][j]*vP[j];
    }
    P->x=vPt[0];
    P->y=vPt[1];
    P->z=vPt[2];
}

void transformacoes::Imp(float M[TAM][TAM]){
    std::cout << "\n Matriz M["<<TAM<<"]["<<TAM<<"]: ";
    for(int i=0; i<TAM;i++){
        std::cout << "\n";
        for(int j=0;j<TAM;j++)
            std::cout << M[i][j] << " | ";
    }
}
