#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; ++i)
class object{
public:
    int size;
    int value;
};
object thing[2500];
void find(int i, int j, int* record,int **m)
{
    if (i > 0)
    {
        if (m[i][j] == m[i - 1][j])
        {
            record[i - 1] = 0;
            find(i - 1, j,
                 record,m);
        }
        else if (j - thing[i].size >= 0 && m[i][j] == m[i - 1][j - thing[i].size] + thing[i].value)
        {
            record[i - 1] = 1;
            find(i - 1, j - thing[i].size,
                 record,m);
        }
    }
}
int main() {
    int totalSize;
    int totalNum;
    fstream fin("bag.in", ios::in), fout("bag.out", ios::out);
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

        int x ;
    int y;
    for (x = 1; x <= totalNum; x++) {
        for (y = 1; y <= totalSize; y++) {
            if (y < thing[x].size)
                m[x][y] = m[x - 1][y];
            else
                m[x][y] = max(m[x - 1][y], m[x - 1][y - thing[x].size] + thing[x].value);
        }
    }
    int* record;
    record = (int*)malloc(sizeof(int) * totalNum);
    find(totalNum, totalSize, record,m);

    for (int i = 0; i < totalNum; i++)
    {
        if(record[i]==1)
            fout << i+1 << " ";
    }
    return 0;
}
