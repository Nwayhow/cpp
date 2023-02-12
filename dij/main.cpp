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
            a[i][i1]=tem;
        }
    }

}
int findmin(int D[],int S[]) {
    int min = 10000;
    int minnum = -1;
    for (int count = 0; count < n; count++) {
        if (D[count] < min && D[count]!=0 && S[count]!=1) {
            min = D[count];
            minnum = count;
        }
    }
    return minnum;
}
int Dijkstra(int startpoint, int endpoint){
    int S[n];
    int D[n];
    int P[n];
    for (int con = 0; con < n; con++) {
        P[con] = startpoint;
        S[con] = 0;
    }
    P[startpoint] = -1;
    for (int count = 0; count < n; count++) {
        D[count] = a[startpoint][count];
    }
    S[startpoint] = 1;
    for (int count = 0; count < n; count++) {
        int minnum=findmin(D,S);
        if (minnum >= 0) S[minnum] = 1;
        for (int con1 = 0; con1 < n; con1++) {
            if (S[con1] == 0 && D[con1] > D[minnum] + a[minnum][con1]) {
                D[con1] = D[minnum] + a[minnum][con1];
                P[con1] = minnum;
            }
        }
    }
    int way[n];
    int con2 = 0;
    int pre = P[endpoint];
    while (pre != -1) {
        way[con2] = pre;
        con2++;
        pre = P[pre];
    }
    int total=0;
    int con3;
    for (con3 = con2 - 2; con3 >= 0; con3--) {

        if(a[way[con3 + 1]][way[con3]]==tem) return -1;
        else total= a[way[con3 + 1]][way[con3]]+total;

    }
    if(a[way[con3 + 1]][endpoint]==tem) return -1;
    else total= a[way[con3 + 1]][endpoint]+total;
    return total;


}
int main()
{
    fstream fin("dijkstra.in", ios::in), fout("dijkstra.out", ios::out);
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
    int distance=Dijkstra(0,n-1);
    fout<<distance;
    return 0;

}