#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
int findmin(int D[],int S[]) {
    int min = 200001;
    int minnum = -1;
    for (int count = 0; count < n; count++) {
        if (D[count] < min && D[count]!=0 && S[count]!=1) {
            min = D[count];
            minnum = count;
        }
    }
    return minnum;
}

void Quick_Sort(int a[], int begin, int end){
    if(begin >= end)//只有一个元素,递归完成
        return;
    int sign = a[end];
    int i = begin;
    int j = end;
    while(i != j){//对右边大和左边小的值进行调换
        while(a[i] <= sign && j > i)
            i++;
        while(a[j] >= sign && j > i)
            j--;
        if(j > i){
            int t = a[i];
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
    fstream fin("quicksort.in", ios::in), fout("quicksort.out", ios::out);
    int n, tmp;
    deque<int> q;
    fin >> n;
    int a[n];
    int count=0;
    rep(i, 1, n) {
        fin >> tmp;
        a[count]=tmp;
        count++;
        q.push_back(tmp);
    }

    Quick_Sort(a,0,n-1);

    printf("排序后的结果是:");
    for(i=0; i<n; i++)
    {
        fout<<a[i]<<" ";
        printf(" %d ",a[i]);
    }
    return 0;

}

