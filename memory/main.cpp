#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <valarray>

using namespace std;
class pageinfo
{
public:
    int page_id;//ҳ���
    int visit;//�����ʱ��
};

int Order[100];//ָ���ַ����
int pageNum[100];//ÿ��ָ���Ӧ��ҳ���
int numOfBlock;//������ڴ������
void formTable(){
    srand((int)time(0));
    Order[0] = 0;
    int opt;
    for (int i = 1; i < 100; i++) {
        opt = rand() % 10;
        if (opt <= 6 && opt >= 0) {
            Order[i] = Order[i - 1] + 1;
        }//70%��˳��ȥ��ȡ��ַ
        else if (opt <= 7) {//��ǰ��ַ�����
            if (Order[i - 1] == 0) { //����߽����
                i--;
                continue;
            }
            Order[i] = rand() % Order[i - 1];
        }
        else {
            if (Order[i - 1] > 98) { //����߽����
                i--;
                continue;//��������
            }
            Order[i] = (rand() % (99 - Order[i - 1])) + Order[i - 1] + 1;
        }
        if (Order[i] > 99) { //���г�����ַ��Χ��ָ�����������
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

    int page_falut = 0; //ȱҳ��
    bool is_find; //ҳ���Ƿ������ڴ����
    bool is_full; //�ڴ���Ƿ���
    for (int i = 0; i < 100; i++) {
        is_find = false;
        is_full = true;
        for (int j = 0; j < numOfBlock; j++) {
            if (block[j].page_id != -1) {
                block[j].visit++; //����ҳ�����ڴ�飬��ÿ�ζ�Ҫ��һ���ۼ���ֵ
                if (block[j].page_id == pageNum[i]) {
                    is_find = true;
                    block[j].visit = -1; //�����У�ֱ������ۼ�
                }
            }
        }
        if (is_find == false) {//û�����е������
            page_falut++;
            for (int j = 0; j < numOfBlock; j++) {
                if (block[j].page_id == -1) {
                    is_full = false;
                    block[j].page_id = pageNum[i];
                    block[j].visit = -1;//δ������
                    break;
                }
            }
            if (is_full) {//�����������
                int longest = -2;//��¼���δʹ�õ�ҳ��
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
    printf("LRU�㷨��ȱҳ����:%d,ȱҳ��:%f\n",  page_falut, (page_falut / 100.0));
}
void optimal(pageinfo block[])
{

    int page_falut = 0; //ȱҳ��
    bool is_find; //ҳ���Ƿ������ڴ����
    bool is_full; //�ڴ���Ƿ���
    int opt_value;//���ڱ�ʾҳ����֮���ҳ��������ֵ��Ⱥ�˳��
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
                    for (int k = i + 1; k < 100; k++) { //��֮���ҳ��������
                        if (block[j].page_id == pageNum[k]) {
                            block[j].visit = k;
                            break;
                        }
                    }
                }
                int max = 0;
                int best_page; // ���ʺ��滻����ҳ��
                for (int j = 0; j < numOfBlock; j++) {
                    if (block[j].visit == -1) { //����ҳ����֮��û���ֹ�
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
                for (int j = 0; j < numOfBlock; j++) { //����block�ķ��ʱ��
                    block[j].visit = -1;
                }
            }
        }
    }
    printf("optimal�㷨��ȱҳ����:%d,ȱҳ��:%f\n", page_falut, (page_falut / 100.0));

}
void FIFO(pageinfo block[])
{

    int page_falut = 0; //ȱҳ��
    bool is_find; //ҳ���Ƿ������ڴ����
    bool is_full; //�ڴ���Ƿ���
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
                for (int j = 1; j < numOfBlock; j++) {//�����Ƚ���ҳ���滻��ȥ
                    block[j - 1].page_id = block[j].page_id;
                }
                block[numOfBlock - 1].page_id = pageNum[i];
            }
        }
    }
    printf("FIFO�㷨��ȱҳ����:%d,ȱҳ��:%f\n", page_falut, (page_falut / 100.0));
}
int main() {
    formTable();//�������100���ڴ��ַ
    printf("��������Ϊ:\n");
    for (int i = 0; i < 100; i++) {//��������Ϊ
        printf("%d ", Order[i]);
        if ((i + 1) % 10 == 0) printf("\n");
        pageNum[i] = Order[i] / 10;//��Ӧÿһ��ҳ��,��ҳΪ��λȥ����
    }
    for (int i = 2; i <= 12; i++) {//�ڴ���С
        numOfBlock = i;
        pageinfo block[i];//�����ڴ���С����
        printf("�Դ�СΪ%d���ڴ��,���㷨����Ч��Ϊ:\n", i);
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

