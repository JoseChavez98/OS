#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_HILOS 4


int step;

pthread_mutex_t mutex1;

struct Matrix {
    int rows;
    int cols;
    int **mat;
};

void initMatrix(struct Matrix *m){

    m->mat=malloc( m->rows * sizeof(int*));

    for(int i=0;i<m->rows;i++)
    {
        m->mat[i]=malloc(m->cols * sizeof(int));
    }

    for(int i=0 ; i< m->rows ;i++){
        for(int j=0; j< m->cols ; j++){
            m->mat[i][j]=0;
        }
    }

    srand (time(NULL));

    for(int i=0 ; i<m->rows ;i++){
        for(int j=0; j<m->cols ; j++){
            m->mat[i][j]+=rand() % 5 +1;
        }
    }

}

void initMatrix0(struct Matrix *m){

    m->mat=malloc( m->rows * sizeof(int*));

    for(int i=0;i<m->rows;i++)
    {
        m->mat[i]=malloc(m->cols * sizeof(int));
    }

    for(int i=0 ; i<m->rows ;i++){
        for(int j=0; j<m->cols ; j++){
            m->mat[i][j]=0;
        }
    }

}

void printMatrix(int **mat,int row,int col){
    for(int i=0 ; i<row ;i++){
        for(int j=0; j<col ; j++){
            printf("%i ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int **matrix(int row,int col){
    int **matrix;
    matrix=malloc( row * sizeof(int));

    for(int i=0;i<row;i++)
    {
        matrix[i]=malloc(col * sizeof(int));
    }

    for(int i=0 ; i<row ;i++){
        for(int j=0; j<col ; j++){
            matrix[i][j]=0;
        }
    }

    srand (time(NULL));

    for(int i=0 ; i<row ;i++){
        for(int j=0; j<col ; j++){
            matrix[i][j]=rand() % 5 +1;
        }
    }

    return matrix;

}

int **multiplyMatrixSecuencial(int **matrix1, int **matrix2,int row1,int col1,int row2, int col2){
    int **matrix_result;
     matrix_result=malloc(row1 * sizeof(int*));

    for(int i=0;i<row1;i++)
    {
        matrix_result[i]=malloc(col2 * sizeof(int));
    }


    for(int i=0 ; i<row1 ;i++){
        for(int j=0; j<col2 ; j++){
            matrix_result[i][j]=0;
        }
    }

    for(int i = 0; i < row1; ++i)
        for(int j = 0; j < col2; ++j)
            for(int k = 0; k < col1; ++k)
            {
                matrix_result[i][j] += matrix1[i][k] * matrix2[k][j];
            }

    return matrix_result;
}

void fillMatrix(int **matrix,int row,int col){
    for(int i=0 ; i<row ;i++){
        for(int j=0; j<col ; j++){
            matrix[i][j]=0;
        }
    }
}

void *multiplyMatrixParalel(void *arg){

    struct Matrix   *container = (struct Matrix *)arg;
    int core = step++;



    for(int i = core * container[0].rows/NUM_HILOS ; i < (core + 1) * container[0].rows/NUM_HILOS ; i++)
        for(int j = 0; j < container[1].cols; ++j)
            for(int k = 0; k < container[0].cols; ++k)
            {
                container[2].mat[i][j] += container[0].mat[i][k] * container[1].mat[k][j];
            }

}

int main(){

    struct timeval start;
    struct timeval finish;
    long compTime;
    double Time;


    int row1,col1,row2,col2;

    printf("numero filas matriz : ");
    scanf("%d",&row1);
    printf("numero columnas matriz : ");
    scanf("%d",&col1);
    printf("numero filas matriz : ");
    scanf("%d",&row2);
    printf("numero columnas matriz : ");
    scanf("%d",&col2);

    struct Matrix aS,bS,cS;

    aS.rows=row1;aS.cols=col1;
    bS.rows=row2;bS.cols=col2;
    cS.rows=row1;cS.cols=col2;

    initMatrix(&aS);
    //printMatrix(aS.mat,aS.rows,aS.cols);
    initMatrix(&bS);
    //printMatrix(bS.mat,bS.rows,bS.cols);
    initMatrix0(&cS);


    gettimeofday(&start, 0);
    cS.mat=multiplyMatrixSecuencial(aS.mat,bS.mat,row1,col1,row2,col2);
    gettimeofday(&finish, 0);


    compTime = (finish.tv_sec - start.tv_sec) * 1000000;
    compTime = compTime + (finish.tv_usec - start.tv_usec);
    Time = (double)compTime;

    //printMatrix(cS.mat,row1,col2);

    printf("Multiplicacion matricial secuencial: %f Secs\n",(double)Time/1000000.0);
    printf("");

    struct Matrix mat_vector[3];

    struct Matrix a;
    struct Matrix b;
    struct Matrix c;

    a.rows=row1;a.cols=col1;
    b.rows=row2;b.cols=col2;
    c.rows=a.rows;c.cols=b.cols;


    initMatrix(&a);
    initMatrix(&b);
    initMatrix0(&c);

//    printMatrix(a.mat,a.rows,a.cols);
//    printMatrix(b.mat,b.rows,b.cols);

    mat_vector[0]=a;
    mat_vector[1]=b;
    mat_vector[2]=c;



    pthread_t threads[NUM_HILOS];

    gettimeofday(&start, 0);

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&threads[i], NULL, multiplyMatrixParalel,(void *)(mat_vector) );
    }

    for (int i = 0; i < NUM_HILOS; i++)
        pthread_join(threads[i], NULL);

    gettimeofday(&finish, 0);

    compTime = (finish.tv_sec - start.tv_sec) * 1000000;
    compTime = compTime + (finish.tv_usec - start.tv_usec);
    Time = (double)compTime;

    printf("Multiplicacion matricial paralela con %d hilos : %f Secs\n",NUM_HILOS,(double)Time/1000000.0);

    //printMatrix(c.mat,c.rows,c.cols);




    return 0;
}