#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
float determinant(float [][50],float);
void cofactor(float [][50],float);
void inverse(float [][50],float [][50],float);
void multiplication();
void transpose();
void square();

int f;

int main()
{
    char line[1000];
    FILE * fpointer = fopen("Cpackage.txt", "a+");

    printf("\n\n\t\t\t\t\tCALCULATIONS WITH MATRICES\n\n\n\n");
    float a[50][50],n,d;
    int i,j;
    L1:printf("Enter the stated numbers:\n");
    printf("\t1: To find inverse of a sq matrix.\n");
    printf("\t2: To find determinant of a sq matrix.\n");
    printf("\t3: To find CoFactor of a sq matrix.\n");
    printf("\t4: To find trace of a sq matrix.\n");
    printf("\t5: To find transpose of a matrix.\n");
    printf("\t6: To add 2 matrices.\n");
    printf("\t7: To subtract 2 matrices.\n");
    printf("\t8: To multiply 2 matrices.\n");
    printf("\t9: To find square of a matrix.\n");
    printf("\t10:To print the file which contains addition, subtraction and trace.\n");

    printf("\nPlease enter the corresponding number: ");
    scanf("%d",&f);
    if(f>0 && f<=10)
    {

        /*Checking for the number*/

        if(f<=4 && f>=1)
        {
            printf("Enter the order of the Matrix: ");
            scanf("%f",&n);
            if(n>0)
            {
                /*Asking user to enter the values of elements in the matrix*/

                printf("Enter the elements of (%.0f X %.0f) square Matrix row wise:\n",n,n);
                for(i=0;i<n;i++)
                {
                    for(j=0;j<n;j++)
                    {
                        scanf("%f",&a[i][j]);
                    }
                }

                /*Displaying the matrix*/

                printf("\nYour matrix is: \n");
                for (i = 0; i < n; ++i)
                {
                    for (j = 0; j < n; ++j)
                    {
                        printf("\t%f  ", a[i][j]);
                    }
                    printf("\n");
                }

                if(f==1)
                {
                    d = determinant(a,n);
                    if(d==0)
                    {
                        printf("\nInverse of the above matrix does not exist as determinant=0.\n");
                    }
                    else
                    {
                        cofactor(a,n);
                    }
                }
                else if(f==2)
                {
                    d = determinant(a,n);
                    printf("\nDeterminant of the above square matrix = %f\n",d);
                }
                else if(f==3)
                {
                    cofactor(a,n);
                }
                else if(f==4)
                {
                    /*To find trace of a matrix*/

                    float sum=0;
                    int i;
                    for(i=0;i<n;i++)
                    {
                        sum+=a[i][i];
                    }
                    printf("\n The trace of the matrix = %f\n",sum);
                }
            }
            else
            {
                printf("\nOrder of a matrix should be > 0. Invalid order entered.\n");
            }
        }
        else if(f==5)
        {
            transpose();
        }
        else if(f==6 || f==7)

        /*To add or subtract 2 matrices*/

        {
            int r,c,i,j,a[100][100],b[100][100],sum[100][100],diff[100][100];
            printf("\nEnter the number of rows : ");
            scanf("%d",&r);
            printf("\nEnter the number of columns : ");
            scanf("%d",&c);
            printf("\nEnter the elements of the first matrix : ");
            for(i = 0; i < r; i++)
            {
                for(j = 0; j < c; j++)
                {
                    printf("\nEnter element a%d%d :",i + 1,j + 1);
                    scanf("%d",&a[i][j]);
                }
            }
            printf("\nEnter elements for second matrix");
            for(i = 0; i < r; i++)
            {
                for(j =0 ; j <c; j++)
                {
                    printf("\nEnter the element a%d%d :",i + 1,j + 1);
                    scanf("%d",&b[i][j]);
                }
            }
            if(f==6)
            {
                for(i = 0 ; i < r ; i++)
                {
                    for(j = 0 ; j < c ; j++)
                    {
                        sum[i][j] = a[i][j] + b[i][j];
                    }
                }
                printf("\nSum of both matrices equal to:\n\n");
                fprintf(fpointer,"\nSum of both matrices equal to:\n\n");
                for(i = 0 ; i < r ; i++)
                {
                    for(j = 0; j < c; j++)
                    {
                        printf("\t%d ",sum[i][j]);
                        fprintf(fpointer,"\t%d ",sum[i][j]);
                        if(j == c - 1)
                        {
                            printf("\n\n");
                            fprintf(fpointer,"\n\n");
                        }
                    }
                }
            }
            else
            {
                for(i = 0 ; i < r ; i++)
                {
                    for(j = 0 ; j < c ; j++)
                    {
                        diff[i][j] = a[i][j] - b[i][j];
                    }
                }
                printf("\nDifference of second  matrix from first  matrix is  equal to: \n");
                fprintf(fpointer,"\nDifference of second  matrix from first  matrix is  equal to: \n");
                for(i = 0 ; i < r ; i++)
                {
                    for(j = 0; j < c; j++)
                    {
                        printf("\t%d ",diff[i][j]);
                        fprintf(fpointer,"\t%d ",diff[i][j]);
                        if(j == c - 1)
                        {
                            printf("\n\n");
                            fprintf(fpointer,"\n\n");
                        }
                    }
                }
            }
        }

        /*To multiply 2 matrices*/

        else if(f==8)
        {
            multiplication();
        }
        else if(f==9)
        {
            square();
        }
        else if(f==10)
        {
            printf("\n\nContents in file which contains calculations in addition, subtraction and trace:\n\n");
            char c;
            while(c!=EOF)
            {
                c=fgetc(fpointer);
                printf("%c",c);
            }
        }
    }
    else
    {
        printf("\nPlease enter correct input.\n\n");
        goto L1;
    }
    fclose(fpointer);
}

/*To Find Determinant of the matrix*/

float determinant(float a[50][50],float k)
{
    float s=1, det, b[50][50];
    int m, n, i, j, c;

    if(k==1)
    {
        return (a[0][0]);
        /*For 1 x 1 matrix*/
    }
    else
    {
        det = 0;
        for (c = 0; c<k; c++)
        {
            m = 0;
            n = 0;
            for(i = 0; i<k; i++)
            {
                for (j = 0 ; j<k; j++)
                {
                    b[i][j] = 0;
                    if(i!=0 && j!=c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                        {
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
          det += s*(a[0][c]*determinant(b,k-1));
          s = -s;
        }
    }
    return(det);
}

/*To find cofactor of a matrix*/

void cofactor(float num[50][50], float F)
{
    float b[50][50], Cmat[50][50];
    int p, q, m, n, i, j;

    for (q=0; q<F; q++)
    {
        for (p=0; p<F; p++)
        {
            m = 0;
            n = 0;
            for(i=0; i<F; i++)
            {
                for (j=0; j<F; j++)
                {
                    if(i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if(n<(F - 2))
                        {
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            Cmat[q][p] = pow(-1, q + p) * determinant(b, F - 1);
        }
    }

    /*To find inverse*/

    if(f==1)
    {
        inverse(num, Cmat, F);
    }

    /*To print Cofactor matrix*/

    else if(f==3)
    {
        for(i=0; i<F; i++)
        {
            for(j=0; j<F; j++)
            {
                printf("\t%f", Cmat[i][j]);
            }
            printf("\n");
        }
    }
}

/*To find inverse of matrix*/

void inverse(float num[50][50], float Cmat[50][50], float p)
{
    int i, j;
    float b[50][50], inverse[50][50], det;

    /*Transposing to find adjoint*/

    for (i = 0;i < p; i++)
    {
        for (j = 0;j < p; j++)
        {
            b[i][j] = Cmat[j][i];
        }
    }

    /*Dividing by determinant to find inverse*/

    det = determinant(num, p);
    for (i = 0;i < p; i++)
    {
        for (j = 0;j < p; j++)
        {
            inverse[i][j]=(b[i][j])/det;
        }
    }

    /*Displaying the inverse matrix*/

    printf("\nThe inverse of matrix is : \n");
    for (i = 0;i < p; i++)
    {
        for (j = 0;j < p; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
        printf("\n\n");
    }
}

/*To find product of two matrices*/

void multiplication()
{
        int r1,c1,r2,c2,i,j,k,sum=0,a[100][100],b[100][100],product[100][100];
        printf("enter the number of rows of first matrix: ");
        scanf("%d",&r1);
        printf("\nEnter the number of columns of first matrix: ");
        scanf("%d",&c1);
        printf("\nEnter the number of rows of second matrix: ");
        scanf("%d",&r2);
        printf("\nEnter the number of columns of first matrix: ");
        scanf("%d",&c2);

        printf("\nEnter elements of first matrix:");
        for(i=0;i<r1;i++)
        {
            for(j=0;j<c1;j++)
            {
                printf("\nEnter element a%d%d : ",i+1,j+1);
                scanf("%d",&a[i][j]);
            }
        }

        printf("\nEnter the elements of second matrix:");
        for(i=0;i<r2;i++)
        {
            for(j=0;j<c2;j++)
            {
                printf("\nEnter element b%d%d : ",i+1,j+1);
                scanf("%d",&b[i][j]);
            }
        }

        if(c1!=r2)
        {
            printf("\nMatrices with entered order cannot be multiplied");
        }
        else
        {
            for(i=0;i<r1;i++)
            {
                for(j=0;j<c2;j++)
                {
                    for(k=0;k<r2;k++)
                    {
                        sum+=a[i][k]*b[k][j];
                    }
                    product[i][j]=sum;
                    sum=0;
                }
            }
        }

        printf("\nThe product of given matrices :\n");
        for(i=0;i<r1;i++)
        {
            for(j=0;j<c2;j++)
            {
                printf("\t%d ",product[i][j]);
                if(j == c2 -1)
                {
                    printf("\n\n");
               }
          }
     }
}

/*To find transpose*/

void transpose()
{
    int MAT[50][50],trans[50][50],r,c,i,j,m,n;
    printf("\nPlease enter the number of rows of your matrix: ");
    scanf("%d",&r);
    printf("\nPlease enter the number of columns of your matrix: ");
    scanf("%d",&c);

    /*Receiving the elements to the matrix from user*/

    printf("\nEnter the matrix elements:\n");
    for (i = 0; i < r; ++i)
    {
        for (j = 0; j < c; ++j)
        {
            printf("Enter element A%d%d: ", i + 1, j + 1);
            scanf("%d", &MAT[i][j]);
        }
    }

    // Displaying the matrix A[][]

    printf("\nYour matrix is: \n");
    for (i = 0; i < r; ++i)
    {
        for (j = 0; j < c; ++j)
        {
            printf("%d  ", MAT[i][j]);
            if (j == c - 1)
            {
                printf("\n");
            }
        }
    }

    /*Calculating the transpose*/

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
                trans[j][i]=MAT[i][j];
        }
    }

    /*Printing the transpose*/

    printf("\nTranspose of the matrix:\n");
    for (i = 0; i < c; ++i)
    {
        for (j = 0; j < r; ++j)
        {
            printf("%d  ", trans[i][j]);
            if (j == r - 1)
            {
                printf("\n");
            }
        }
    }
}

/*To find square of a matrix*/

void square()
{
    int a[100][100],square[100][100],N,i,j,k,sum=0;
    printf("\nEnter the order of the matrix: ");
    scanf("%d",&N);
    printf("\nEnter the element of the matrix:");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("\nEnter element a%d%d: ",i+1,j+1);
            scanf("%d",&a[i][j]);
        }
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            for(k=0;k<N;k++)
            {
                sum += (a[i][k])*(a[k][j]);
            }
            square[i][j] = sum;
            sum = 0;
        }
    }
    printf("\nThe square of the  matrix is :\n\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d\t ",square[i][j]);
            if(j==N-1)
            {
                printf("\n\n");
            }
        }
    }
}
