#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
int n;
int lineNum;
int a[5001][5001];
class line{
public:
    int start;
    int end;
    int value=0;
};
line l[5001];
#define rep(i, a, b) for (int i = a; i <= b; ++i)
int findmin(int D[],int S[]) {
    int min = 2000001;
    int minnum = -1;
    for (int count = 0; count < n; count++) {
        if (D[count] < min && D[count]!=0 && S[count]!=1) {
            min = D[count];
            minnum = count;
        }
    }
    return minnum;
}
void startA(){
    for(int i=0;i<5001;i++){
        for(int i1=0;i1<5001;i1++){
            a[i][i1]=200000*n+1;
        }
    }

}
int kruskal(int startpoint, int endpoint, int tem){
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

    }if(a[way[con3 + 1]][endpoint]==tem) return -1;
    else total= a[way[con3 + 1]][endpoint]+total;
    return total;


}
void Quick_Sort(line a[], int begin, int end){
    if(begin >= end)//只有一个元素,递归完成
        return;
    line sign = a[end];
    int i = begin;
    int j = end;
    while(i != j){//对右边大和左边小的值进行调换
        while(a[i].value <= sign.value && j > i)
            i++;
        while(a[j].value >= sign.value && j > i)
            j--;
        if(j > i){
            line t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[end] = a[j];//与末尾调换
    a[j] = sign;
    Quick_Sort(a, begin, i-1);//重复过程
    Quick_Sort(a, i+1, end);
}
int main()
{
    fstream fin("kruskal.in", ios::in), fout("kruskal.out", ios::out);
    fin >> n;
    fin>>lineNum;
    startA();
    int start,end;
    rep(i, 0, lineNum-1) {
        fin >> start;
        l[i].start=start;
        fin >> end;
        l[i].end=end;
        fin >>  l[i].value;
    }
    int count=0;
    int length=0;
    Quick_Sort(l,0,lineNum-1);
    for(int i=0;i<lineNum && count<n-1;i++){
        int tem=a[l[i].start][l[i].end];
        a[l[i].start][l[i].end]=l[i].value;
        a[l[i].end][l[i].start]=l[i].value;
        if(kruskal(l[i].start, l[i].start, tem) == -1){
            count++;
            length=length+l[i].value;
        }
        else{
            a[l[i].start][l[i].end]=tem;
        };

    }
    fout<<length;


    return 0;

}