#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)

class point{

public:
    int expect=1;
    double value;
};
void Quick_Sort(double a[], int begin, int end){
    if(begin >= end)//只有一个元素,递归完成
        return;
    double sign = a[end];
    int i = begin;
    int j = end;
    while(i != j){//对右边大和左边小的值进行调换
        while(a[i] <= sign && j > i)
            i++;
        while(a[j] >= sign && j > i)
            j--;
        if(j > i){
            double t = a[i];
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
    int i;
    fstream fin("huffman.in", ios::in), fout("huffman.out", ios::out);
    int n;
    double  tmp;
    fin >> n;
    double a[n];
    double expecting=0;
    rep(i, 0, n-1) {
        fin >> tmp;
        a[i]=tmp;
    }
    Quick_Sort(a,0,n-1);
    point p[n];
    rep(i, 0, n-1) {
        fin >> tmp;
        p[i].value=a[i];
    }
    for( i=2;i<n;i++){
        for(int i1=0;i1<i;i1++){
            p[i1].expect++;
        }
    }
    for( i=0;i<n;i++){
       expecting=expecting+p[i].expect*p[i].value;
    }
    fout<<expecting;

    return 0;

}