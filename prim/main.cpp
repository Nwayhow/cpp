#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
int n;
int lineNum;
int a[5001][5001];
int tem;
#define rep(i, a, b) for (int i = a; i <= b; ++i)
void startA(){
    for(int i=0;i<5001;i++){
        for(int i1=0;i1<5001;i1++){
            a[i][i1]=200001;
        }
    }

}

int prim(int start,bool *M){
    int tem;
    int min=200001;
    for(int i=0;i<n;i++){
        if(M[i]==false){
            if(min>a[start][i]){
                min=a[start][i];
                tem=i;
            }
        }
    }
    return tem;
}
int main()
{
    fstream fin("prim.in", ios::in), fout("prim.out", ios::out);
    fin >> n;
    tem=200000*n+1;
    fin>>lineNum;
    startA();
    int start,end;
    rep(i, 0, lineNum-1) {
        fin >> start;
        fin >> end;
        fin >> a[start-1][end-1];
        a[end-1][start-1]=a[start-1][end-1];
    }
    int N[n];
    N[0]=0;
    bool M[n];
    rep(i, 0, n-1){
        M[i]=false;
    }
    M[0]=true;
    int count=1;
    int total=0;
    int tem;
    while(count<n){
        int min=200001;
        rep(i, 0, count-1){
            int l=prim(N[i],M);
            if(min>a[i][l]){
                min=a[i][l];
                tem=l;
            };

        }
            total=total+min;
            M[tem]=true;
            N[count]=tem;
            count++;

    }
    fout<<total;


    return 0;

}