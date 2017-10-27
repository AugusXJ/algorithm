#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iomanip>
using namespace std;


double A[3][3]= {{0,1,0},{1,0,1},{0,1,0}};
int row=0;
int col=0;
double max1=0;
double m1=0,m2=0;


double Y[3]={1,1,1};
double X[3]={0,0,0};

void mult()
{
    X[0]=0;X[1]=0;X[2]=0;
    for(row=0;row<3;row++)
    {
        for(col=0;col<3;col++)
            X[row] +=A[row][col]*Y[col];
    }
}

void to1()
{
    long double tmp=fabs(X[0]);
    for(int i=1;i<3;i++)
    {
        if(fabs(X[i])>tmp)
            tmp=fabs(X[i]);
    }
    for(int i=0;i<3;i++)
    {
        Y[i]=X[i]/tmp;
    }
    m2=tmp;
}
int main()
{
    double ago=max1+100.0;
    int k=1;
    while(fabs(max1-ago)>0.000001|| k<3)
    {
          ago=max1;
          m1 = m2;
          mult();
          to1();
        cout<<"k= "<<k<<"\t";
        cout<<"X["<<k<<"]=";
        for(int i=0;i<3;i++)
            cout<<X[i]<<" ";
        cout<<"\tY["<<k<<"]=";
        for(int i=0;i<3;i++)
            cout<<Y[i]<<" ";
        cout<<endl;
        max1 = sqrt(m1*m2);
        k++;
    }
    cout<<endl<<"totally run "<<k-1<<" times"<<endl;
    cout<<endl<<"the matrix eigenvalue is "<<max1<<endl;
    system("pause");


}
