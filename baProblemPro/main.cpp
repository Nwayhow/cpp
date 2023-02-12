#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; ++i)
class object{
public:
    int size;
    int value;
};
object thing[2500];
void find(int maxSize, int maxValue,int totalNum,int *qn,int q[][100][2]) {
    fstream fout("bag.out", ios::out);
    for (int i = 2; i <= totalNum+1; i++) {
        for (int j = 0; j < qn[i]; j++) {
            if (q[i][j][0] == maxSize && q[i][j][1] == maxValue) {
                fout << i-1 << " " ;
                maxSize = maxSize - thing[i - 1].size;
                maxValue = maxValue - thing[i - 1].value;}
        }
    }
}
void change(int totalNum,int totalSize,int *qn,int *pn,int q[][100][2],int p[][100][2]) {
    int maxValue = 0;
    int maxSize = 0;
    int temp;
    int x;
    for (int a = totalNum - 1; a > 0; a--) {
        for (x = 0, qn[a + 1] = 0; x < pn[a + 1]; x++) {
            if (p[a + 1][x][0] != -1) {
                temp = p[a + 1][x][0] + thing[a].size;
          if (temp <= totalSize) {
                    //把数据计入Q表格中
                    q[a + 1][qn[a + 1]][0] = temp;
                    q[a + 1][qn[a + 1]][1] = p[a + 1][x][1] + thing[a].value;qn[a + 1]++;
                }
            }
        }
        for (int i = 0; i < qn[i + 1]; i++) {
            for (int j = 0; j < pn[i + 1]; j++) {
                if (q[a + 1][i][0] >= p[a + 1][j][0] && q[a + 1][i][1] < p[a + 1][j][1]) {
                    q[a + 1][i][0] = -1;
                    q[a + 1][i][1] = -1;
                } else if (q[a + 1][i][0] <= p[a + 1][j][0] && q[a + 1][i][1] > p[a + 1][j][1]) {
                    p[a + 1][j][0] = -1;
                    p[a + 1][j][1] = -1;
                }
            }
        }
        //???????p
        for (int i = 0; i < pn[a + 1]; i++) {
            if (p[a + 1][i][0] != 0) {
                p[a][pn[a]][0] = p[a + 1][i][0];
                p[a][pn[a]][1] = p[a + 1][i][1];
                pn[a]++;
            }
        }
        for (int i = 0; i < qn[a + 1]; i++) {
            if (q[a + 1][i][0] != -1) {
                p[a][pn[a]][0] = q[a + 1][i][0];
                p[a][pn[a]][1] = q[a + 1][i][1];
                pn[a]++;
            }
        }
    }
    for (int i = 0; i < pn[1]; i++) {
        if (p[1][i][1] > maxValue) {
            maxValue = p[1][i][1];
            maxSize = p[1][i][0];
        }
    }
    find(maxSize, maxValue, totalNum,qn,q);
}
void start(int totalNum,int q[][100][2],int p[][100][2]){
    q[totalNum + 1][0][0] = thing[totalNum].size;
    q[totalNum + 1][0][1] = thing[totalNum].value;
    p[totalNum][0][0] = 0;
    p[totalNum][0][1] = 0;
    p[totalNum][1][0] = thing[totalNum].size;
    p[totalNum][1][1] = thing[totalNum].value;
}
int main() {
    int totalSize;
    int totalNum;
    int pn[100] = { 0 };//存储p[i]里的元素个数
    int qn[100] = { 0 };//存储p[i]里的元素个数
    int p[100][100][2] = { -1 };
    int q[100][100][2] = { -1 };
    fstream fin("bag.in", ios::in);
    fin >> totalSize;
    fin>>totalNum;
    rep(i, 1, totalNum) {
        fin>>thing[i].size;
        fin>>thing[i].value;
    }
    int **m = new int*[2500];
    for (int i = 0; i < 2500; i++){
        m[i] = new int[2500];
    }
    for (int x = 1; x <= totalNum; x++) {
        for (int y = 1; y <= totalSize; y++) {
            if (y < thing[x].size)
                m[x][y] = m[x - 1][y];
            else
                m[x][y] = max(m[x - 1][y], m[x - 1][y - thing[x].size] + thing[x].value);
        }
    }
    start(totalNum,q, p);
    pn[totalNum] = 2;
    qn[totalNum + 1] = 1;
    change(totalNum,totalSize,qn,pn,p,q);


}