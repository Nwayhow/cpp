#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <valarray>

using namespace std;
class pageinfo
{
public:
    int page_id;//页面号
    int visit;//被访问标记
};

int Order[100];//指令地址数组
int pageNum[100];//每条指令对应的页面号
int numOfBlock;//分配的内存块数量
void formTable(){
    srand((int)time(0));
    Order[0] = 0;
    int opt;
    for (int i = 1; i < 100; i++) {
        opt = rand() % 10;
        if (opt <= 6 && opt >= 0) {
            Order[i] = Order[i - 1] + 1;
        }//70%按顺序去读取地址
        else if (opt <= 7) {//在前地址的情况
            if (Order[i - 1] == 0) { //处理边界情况
                i--;
                continue;
            }
            Order[i] = rand() % Order[i - 1];
        }
        else {
            if (Order[i - 1] > 98) { //处理边界情况
                i--;
                continue;//重新生成
            }
            Order[i] = (rand() % (99 - Order[i - 1])) + Order[i - 1] + 1;
        }
        if (Order[i] > 99) { //若有超过地址范围的指令，则重新生成
            i--;
        }
    }
}
void init(pageinfo block[])
{
    for (int i = 0; i < numOfBlock; i++) {
        block[i].page_id = -1;
        block[i].visit = -1;
    }

}
void LRU(pageinfo block[]) {

    int page_falut = 0; //缺页数
    bool is_find; //页面是否已在内存块中
    bool is_full; //内存块是否满
    for (int i = 0; i < 100; i++) {
        is_find = false;
        is_full = true;
        for (int j = 0; j < numOfBlock; j++) {
            if (block[j].page_id != -1) {
                block[j].visit++; //若该页已在内存块，则每次都要给一个累计增值
                if (block[j].page_id == pageNum[i]) {
                    is_find = true;
                    block[j].visit = -1; //若命中，直接清除累计
                }
            }
        }
        if (is_find == false) {//没有命中的情况下
            page_falut++;
            for (int j = 0; j < numOfBlock; j++) {
                if (block[j].page_id == -1) {
                    is_full = false;
                    block[j].page_id = pageNum[i];
                    block[j].visit = -1;//未被访问
                    break;
                }
            }
            if (is_full) {//已满的情况下
                int longest = -2;//记录最久未使用的页面
                int best_page;
                for (int j = 0; j < numOfBlock; j++) {
                    if (block[j].visit > longest) {
                        best_page = j;
                        longest = block[j].visit;
                    }
                }
                block[best_page].page_id = pageNum[i];
                block[best_page].visit = -1;
            }
        }
    }
    printf("LRU算法的缺页次数:%d,缺页率:%f\n",  page_falut, (page_falut / 100.0));
}
void optimal(pageinfo block[])
{

    int page_falut = 0; //缺页数
    bool is_find; //页面是否已在内存块中
    bool is_full; //内存块是否满
    int opt_value;//用于表示页面在之后的页面流里出现的先后顺序
    for (int i = 0; i < 100; i++) {
        is_find = false;
        is_full = true;
        for (int j = 0; j < numOfBlock; j++) {
            if (block[j].page_id == pageNum[i]) {
                is_find = true;
            }
        }
        if (is_find == false) {
            page_falut++;
            for (int j = 0; j < numOfBlock; j++) {
                if (block[j].page_id == -1) {
                    is_full = false;
                    block[j].page_id = pageNum[i];
                    break;
                }
            }
            if (is_full) {
                for (int j = 0; j < numOfBlock; j++) {
                    for (int k = i + 1; k < 100; k++) { //对之后的页面流遍历
                        if (block[j].page_id == pageNum[k]) {
                            block[j].visit = k;
                            break;
                        }
                    }
                }
                int max = 0;
                int best_page; // 最适合替换出的页面
                for (int j = 0; j < numOfBlock; j++) {
                    if (block[j].visit == -1) { //若该页面在之后都没出现过
                        best_page = j;
                        break;
                    }
                    else {
                        if (block[j].visit > max) {
                            max = block[j].visit;
                            best_page = j;
                        }
                    }
                }
                block[best_page].page_id = pageNum[i];
                for (int j = 0; j < numOfBlock; j++) { //重置block的访问标记
                    block[j].visit = -1;
                }
            }
        }
    }
    printf("optimal算法的缺页次数:%d,缺页率:%f\n", page_falut, (page_falut / 100.0));

}
void FIFO(pageinfo block[])
{

    int page_falut = 0; //缺页数
    bool is_find; //页面是否已在内存块中
    bool is_full; //内存块是否满
    for (int i = 0; i < 100; i++) {
        is_find = false;
        is_full = true;
        for (int j = 0; j < numOfBlock; j++) {
            if (block[j].page_id == pageNum[i]) {
                is_find = true;
            }
        }
        if (is_find == false) {
            page_falut++;
            for (int j = 0; j < numOfBlock; j++) {
                if (block[j].page_id == -1) {
                    is_full = false;
                    block[j].page_id = pageNum[i];
                    break;
                }
            }
            if (is_full) {
                for (int j = 1; j < numOfBlock; j++) {//将最先进的页面替换出去
                    block[j - 1].page_id = block[j].page_id;
                }
                block[numOfBlock - 1].page_id = pageNum[i];
            }
        }
    }
    printf("FIFO算法的缺页次数:%d,缺页率:%f\n", page_falut, (page_falut / 100.0));
}
int main() {
    formTable();//随机生成100个内存地址
    printf("访问序列为:\n");
    for (int i = 0; i < 100; i++) {//访问序列为
        printf("%d ", Order[i]);
        if ((i + 1) % 10 == 0) printf("\n");
        pageNum[i] = Order[i] / 10;//对应每一个页号,以页为单位去访问
    }
    for (int i = 2; i <= 12; i++) {//内存块大小
        numOfBlock = i;
        pageinfo block[i];//申请内存块大小数组
        printf("对大小为%d的内存块,各算法访问效率为:\n", i);
        init(block);
        optimal(block);
        init(block);
        LRU(block);
        init(block);
        FIFO(block);
        printf("\n");
    }
    return 0;
}

