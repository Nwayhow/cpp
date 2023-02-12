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
char L[200] = "+-*/a()#ETF";    //表头
int  del[10] = { 0,3,3,1,3,3,1,3,1 };//0-8号每一个的文法程度
char head[20] = { 'S','E','E','E','T','T','T','F','F' };
stack<int>con;
stack<char>cmp;
char cod[300] = "0";//状态栈
int cindex = 0;
char sti[300] = "#";//符号栈
int sindex = 0;//符号栈顶
int calculate2(int l, char s[])
{
    int num = 0;
    for (int i = 0; i < l; i++)
    {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}
int changer2(int x, int y) {//处理无前缀整数
    int l=strlen(LR0[x][y]);
    int t= calculate2(l,LR0[x][y]);
    if (t < 10)
    {
        cindex++;
        cod[cindex] = LR0[x][y][0];//小于10,只有一位数,直接加入状态栈
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

int findL(char b)//通过状态转移表,寻找后继状态
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
    con.push(t);//进入栈
    sindex++;
    sti[sindex] = str[LR];//把新元素压入符号栈中
    cmp.push(str[LR]);//把新元素压入符号栈中
    if (t < 10)
    {
        cindex++;
        cod[cindex] = LR0[x][y][1];//小于10,只有一位数,直接加入状态栈
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
void changer1(int g){//删除上一个状态
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
    printf("步骤		状态栈		        符号栈              输入串              ACTION    GOTO\n");
    int LR = 0;
    while (LR <= len)
    {
        printf("(%d)		%-20s	%-20s", cnt, cod, sti);//输出当前状态
        cnt++;
        for (int i = LR; i < len; i++)
        {
            printf("%c", str[i]);//输出当前字符串
        }
        for (int i = len - LR; i < 20; i++)printf(" ");

        int x = con.top();
        int y = findL(str[LR]);//找表头
        //定位后继状态
        if (y == -1) {
            printf("\n输入非法字符\n");
            break;
        }//非法输入
        if (strcmp(LR0[x][y], "null") != 0)//非空转换
        {
            int l = strlen(LR0[x][y]);

            if (LR0[x][y][0] == 'a')//acc
            {
                printf("acc        \n");//分析完成,输出accept
                return;
            }
            else if (LR0[x][y][0] == 'S')//进行shift操作
            {
                printf("%-10s \n", LR0[x][y]);//ACTION类型
                int t = calculate(l, LR0[x][y]);//读取S后面的数字
                changeS(t,x,y,l,str,LR);//修改各种栈
                LR++;
            }
            else if (LR0[x][y][0] == 'r')//进行return操作
            {
                printf("%-10s", LR0[x][y]);//打印action类型
                int t = calculate(l, LR0[x][y]);//读取r后的数字
                int g = del[t];//找文法程度
                while (g--)//清除需要return的前继状态
                {
                    con.pop();
                    cmp.pop();
                    sti[sindex] = '\0';
                    sindex--;
                }
                changer1(del[t]);//修改栈
                cmp.push(head[t]);//把非对应非终结符压入栈
                sindex++;
                sti[sindex] = head[t];
                x = con.top();
                y = findL(cmp.top());//找后继状态
                t=changer2(x,y);//将新的状态加入栈
                con.push(t);
                printf("%-10d\n", t);
            }
        }
        else
        {
            printf("\n第%d行%c出现错误!", x, L[y]);
            break;

        }
    }

}
int main()
{
    con.push(0);
    cmp.push('#');
    char str[200];
    cout << "请输入字符串" << endl;
    cin >> str;
    int len = strlen(str);
    str[len] = '#';//终结符号
    len = len + 1;//长度加一
    analyze(str, len);
    return 0;
}
