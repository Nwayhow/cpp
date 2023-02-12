#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)

#define MAXSIZE 10
void compare(int a[],int b[],int c[],int len){
    int lena=len;
    int lenb=len;
    int ap=0;
    int bp=0;
    for(;ap<lena && bp<lenb;){//比大小
        if(a[ap]<b[bp]){
            c[ap+bp]=a[ap];
            ap++;
        }
        else{
            c[ap+bp]=b[bp];
            bp++;
        }
    }
    int lenc=bp+ap;
    if(ap<lena){//没有排序完的数依次放入c数组
        for(int i=ap;ap<lena;ap++){
            c[lenc]=a[ap];
            lenc++;
        }
    }
    else if(bp<lenb){
        for(int i=bp;bp<lenb;bp++){
            c[lenc]=b[bp];

            lenc++;
        }
    }

}
void cuts(int con,int t,int k[]){
    int a[t];
    int b[t];
    int c[2*t];//将k中需要排序的数写入a,b
    for(int i=0;i<t;i++){
        a[i]=k[con*2+i];

    }
    for(int i=0;i<t;i++){
        b[i]=k[con*2+t+i];
    }
    compare(a,b,c,t);
    int lenc=sizeof(c) / sizeof(c[0]);
    for(int i=0;i<lenc;i++){//c的内容拷贝回k
        k[con*2+i]=c[i];

    }
}
void MergeSort(int k[],int n)
{
//对k操作,初始跨度为1
int len=1;
    for(;len<n*2;len=len*2);
    len=len/2;

    for(int t=1;t<=len;t=t*2){
        for(int con=0;con<len/(t*2);con++){
            cuts(con,t,k);//
        }

    }

}

int main()
{
	int i;
    fstream fin("mergesort.in", ios::in), fout("mergesort.out", ios::out);
    int n, tmp;//输入输出流读取文件
    deque<int> q;
    fin >> n;
    int len=1;
    for(;len<n*2;len=len*2);
    int a[len];
    int count=0;
    rep(i, 1, n) {
        fin >> tmp;
        a[count]=tmp;
        count++;
        q.push_back(tmp);
    }

	MergeSort(a,n);

	printf("排序后的结果是:");
	for(i=0; i<n; i++)
	{
        fout<<a[i]<<" ";
		printf(" %d ",a[i]);
	}
	return 0;

}

