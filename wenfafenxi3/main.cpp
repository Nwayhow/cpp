#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<string.h>
using namespace std;
char LR0[50][50][100] = { {"null" ,"null" ,"null", "null" ,"S4"   ,"S5"   ,"null" ,"null" ,"1"    ,"2"    ,"3"   },///   0
                         {"S6"   ,"S7"   ,"null", "null" ,"null ","null" ,"null" ,"acc"  ,"null" ,"null" ,"null"},///   1
                         {"r3"   ,"r3"   ,"S8"  , "S9"   ,"null" ,"null" ,"r3"   ,"r3"   ,"null" ,"null" ,"null"},///   2
                         {"r6"   ,"r6"   ,"r6"  , "r6"   ,"null" ,"null" ,"r6"   ,"r6"   ,"null" ,"null" ,"null"},///   3
                         {"r8"   ,"r8"   ,"r8"  , "r8"   ,"null" ,"null" ,"r8"   ,"r8"   ,"null" ,"null" ,"null"},///   4
                         {"null" ,"null" ,"null", "null" ,"S4"   ,"S5"   ,"null" ,"null" ,"10"   ,"2"    ,"3"   },///   5
                         {"null" ,"null" ,"null", "null" ,"S4"   ,"S5"   ,"null" ,"null" ,"null" ,"11"   ,"3"   },///   6
                         {"null" ,"null" ,"null", "null" ,"S4"   ,"S5"   ,"null" ,"null" ,"null" ,"12"   ,"3"   },///   7
                         {"null" ,"null" ,"null", "null" ,"S4"   ,"S5"   ,"null" ,"null" ,"null" ,"null" ,"13"  },///   8
                         {"null" ,"null" ,"null", "null" ,"S4"   ,"S5"   ,"null" ,"null" ,"null" ,"null" ,"14"  },///   9
                         {"S6"   ,"S7"   ,"null", "null" ,"null" ,"null" ,"S15"  ,"null" ,"null" ,"null" ,"null"},///   10
                         {"r1"   ,"r1"   ,"S8"  , "S9"   ,"null" ,"null" ,"r1"   ,"r1"   ,"null" ,"null" ,"null"},///   11
                         {"r2"   ,"r2"   ,"S8"  , "S9"   ,"null" ,"null" ,"r2"   ,"r2"   ,"null" ,"null" ,"null"},///   12
                         {"r4"   ,"r4"   ,"r4"  , "r4"   ,"null" ,"null" ,"r4"   ,"r4"   ,"null" ,"null" ,"null"},///   13
                         {"r5"   ,"r5"   ,"r5"  , "r5"   ,"null" ,"null" ,"r5"   ,"r5"   ,"null" ,"null" ,"null"},///   14
                         {"r7"   ,"r7"   ,"r7"  , "r7"   ,"null" ,"null" ,"r7"   ,"r7"   ,"null" ,"null" ,"null"},///   15
};
char L[200] = "+-*/a()#ETF";    //��ͷ
int  del[10] = { 0,3,3,1,3,3,1,3,1 };//0-8��ÿһ�����ķ��̶�
char head[20] = { 'S','E','E','E','T','T','T','F','F' };
stack<int>con;
stack<char>cmp;
char cod[300] = "0";//״̬ջ
int cindex = 0;
char sti[300] = "#";//����ջ
int sindex = 0;//����ջ��
int calculate2(int l, char s[])
{
    int num = 0;
    for (int i = 0; i < l; i++)
    {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}
int changer2(int x, int y) {//������ǰ׺����
    int l=strlen(LR0[x][y]);
    int t= calculate2(l,LR0[x][y]);
    if (t < 10)
    {
        cindex++;
        cod[cindex] = LR0[x][y][0];//С��10,ֻ��һλ��,ֱ�Ӽ���״̬ջ
    }
    else
    {
        int k = 0;
        cindex++;
        cod[cindex] = '(';
        while (k < l)
        {
            cindex++;
            cod[cindex] = LR0[x][y][k];
            k++;
        }
        cindex++;
        cod[cindex] = ')';
    }
    return t;
}

int findL(char b)//ͨ��״̬ת�Ʊ�,Ѱ�Һ��״̬
{
    for (int i = 0; i <= 10; i++)
    {
        if (b == L[i])
        {
            return i;
        }
    }
    return -1;
}
int calculate(int l, char s[])
{
    int num = 0;
    for (int i = 1; i < l; i++)
    {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}
void changeS(int t,int x,int y,int l,char str[],int LR){
    con.push(t);//����ջ
    sindex++;
    sti[sindex] = str[LR];//����Ԫ��ѹ�����ջ��
    cmp.push(str[LR]);//����Ԫ��ѹ�����ջ��
    if (t < 10)
    {
        cindex++;
        cod[cindex] = LR0[x][y][1];//С��10,ֻ��һλ��,ֱ�Ӽ���״̬ջ
    }
    else
    {
        int k = 1;
        cindex++;
        cod[cindex] = '(';
        while (k < l)
        {
            cindex++;
            cod[cindex] = LR0[x][y][k];
            k++;
        }
        cindex++;
        cod[cindex] = ')';
    }
}
void changer1(int g){//ɾ����һ��״̬
    while (g > 0) {
        if (cod[cindex] == ')') {
            cod[cindex] = '\0';
            cindex--;
            for (;;) {
                if (cod[cindex] == '(') {
                    cod[cindex] = '\0';
                    cindex--;
                    break;
                } else {
                    cod[cindex] = '\0';
                    cindex--;
                }
            }
            g--;
        } else {
            cod[cindex] = '\0';
            cindex--;
            g--;
        }
    }
}
void analyze(char str[], int len)//???????????
{
    int cnt = 1;
    printf("����		״̬ջ		        ����ջ              ���봮              ACTION    GOTO\n");
    int LR = 0;
    while (LR <= len)
    {
        printf("(%d)		%-20s	%-20s", cnt, cod, sti);//�����ǰ״̬
        cnt++;
        for (int i = LR; i < len; i++)
        {
            printf("%c", str[i]);//�����ǰ�ַ���
        }
        for (int i = len - LR; i < 20; i++)printf(" ");

        int x = con.top();
        int y = findL(str[LR]);//�ұ�ͷ
        //��λ���״̬
        if (y == -1) {
            printf("\n����Ƿ��ַ�\n");
            break;
        }//�Ƿ�����
        if (strcmp(LR0[x][y], "null") != 0)//�ǿ�ת��
        {
            int l = strlen(LR0[x][y]);

            if (LR0[x][y][0] == 'a')//acc
            {
                printf("acc        \n");//�������,���accept
                return;
            }
            else if (LR0[x][y][0] == 'S')//����shift����
            {
                printf("%-10s \n", LR0[x][y]);//ACTION����
                int t = calculate(l, LR0[x][y]);//��ȡS���������
                changeS(t,x,y,l,str,LR);//�޸ĸ���ջ
                LR++;
            }
            else if (LR0[x][y][0] == 'r')//����return����
            {
                printf("%-10s", LR0[x][y]);//��ӡaction����
                int t = calculate(l, LR0[x][y]);//��ȡr�������
                int g = del[t];//���ķ��̶�
                while (g--)//�����Ҫreturn��ǰ��״̬
                {
                    con.pop();
                    cmp.pop();
                    sti[sindex] = '\0';
                    sindex--;
                }
                changer1(del[t]);//�޸�ջ
                cmp.push(head[t]);//�ѷǶ�Ӧ���ս��ѹ��ջ
                sindex++;
                sti[sindex] = head[t];
                x = con.top();
                y = findL(cmp.top());//�Һ��״̬
                t=changer2(x,y);//���µ�״̬����ջ
                con.push(t);
                printf("%-10d\n", t);
            }
        }
        else
        {
            printf("\n��%d��%c���ִ���!", x, L[y]);
            break;

        }
    }

}
int main()
{
    con.push(0);
    cmp.push('#');
    char str[200];
    cout << "�������ַ���" << endl;
    cin >> str;
    int len = strlen(str);
    str[len] = '#';//�ս����
    len = len + 1;//���ȼ�һ
    analyze(str, len);
    return 0;
}
