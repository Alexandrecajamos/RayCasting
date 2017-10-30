#include "operacoes.h"

Operacoes::Operacoes()
{

}

float** Operacoes::mult(int M, int N, int P, float **A, float **B)
{
    float **C;

    C = (float **)malloc(sizeof(float)*M);
    for (int i = 0; i < M; i++)
        C[i] = (float *)malloc(sizeof(float)*P);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
               //printf("\ni = %d; j=%d; C[i][j] = %f", i,j, matC[i][j]);
        }
    return C;
}
float** Operacoes::Identidade(int N)
{
    float **mat;
    mat = (float **)malloc(sizeof(float)*N);
    for (int i = 0; i < N; i++)
        mat[i] = (float *)malloc(sizeof(float)*N);

    for(int i =0; i< N;i++)
        for(int j =0; j < N; j++){
            if(i==j){
                mat[i][j]=1;
            }else{
                mat[i][j]=0;
            }

        }



    return mat;
}

float** Operacoes::TrocaColuna (int M,int N, int P, int C1, int C2, float **matA){
    float** Id, **Result;
    Id = Identidade(N);
    Id[C1][C1] = 0;
    Id[C1][C2] = 1;
    Id[C2][C2] = 0;
    Id[C2][C1] = 1;
    Result = mult(M,N,P,matA,Id);
    return Result;
}
float** Operacoes::VetorColuna(Point P){
    float** v;
    v = (float**)malloc(sizeof(float)*(4));
    for (int i = 0; i < 4; i++)
        v[i] = (float *)malloc(sizeof(float));
    v[0][0]=P.x;
    v[1][0]=P.y;
    v[2][0]=P.z;
    v[3][0]=1;

    return v;
}
float* Operacoes::Gauss (int N, float **matA, float *vet2){
    float* vet1 = (float *)malloc(sizeof(float)*N);
    int* vetAux = (int *)malloc(sizeof(int)*N);
    for(int k=0;k<N;k++){
        vetAux[k] = k;
    }
    int i,j;
    float alfa;
     for(j=0;j<=(N-2);j++){
        for(i=(j+1);i < N;i++){
            if(matA[i][j]!=0){
                if(matA[j][j]==0){ //Pivotação
                    float MJ = 0;
                    int aux=0;

                    for(int k=j+1; k<N;k++){
                        if(matA[j][k]>MJ){
                            MJ = matA[j][k];
                            aux = k;
                            }
                    }
                    int NC = aux; //Nova Coluna
                    matA = TrocaColuna(N,N,N,j,NC,matA);
                    //imp(N,N,matA);
                    vetAux[j]=NC;
                    vetAux[NC]=j;
                }
                alfa = (-matA[i][j])/matA[j][j];
                matA[i][j] = 0;
                for(int k=(j+1); k < N; k++){
                    matA[i][k] = matA[i][k] + (matA[j][k]*alfa);
                }

                vet2[i] = vet2[i] + (vet2[j]*alfa);
                }
        }
    }

    for(i = (N-1); i >=0; i--){
        float soma = 0;
        for(int k = i+1; k < N; k++)
            soma += matA[i][k] * vet2[k];
        vet2[i] = (vet2[i]-soma)/matA[i][i];

    }

    for(int k=0;k<N;k++){
        vet1[k]=vet2[vetAux[k]];
    }

    return vet1;
}
float* Operacoes::Vetor(Point P){
    float* v=(float*)malloc(sizeof(float)*4);
    v[0]=P.x;
    v[1]=P.y;
    v[2]=P.z;
    v[3]=0;
    return v;
}
Point Operacoes::normal(Point a, Point b)
{
    Point p1;
    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);
    return p1;
}
