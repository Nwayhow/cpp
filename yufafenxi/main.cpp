#include<iostream>
#include<algorithm>
#include<string>
#include <cstring>

using namespace std;

char input_data[1024];//储存txt文本中的数据
int ptr = 0;          //指针
void E();
void T();
void F();
void show_remain();  //展示剩下未分析的字符串

int main() {
    cout << "请输入字符串" << endl;
    cin >> input_data;
    int i = strlen(input_data);
    input_data[i] = '$';//结束符号
    E();
    if (input_data[ptr] == '$') {
        cout << "分析完成" << endl;
    }
    else {
        cout << "分析错误" << endl;
    }
}

void show_remain() {//显示剩余的字符串
    int i = ptr;
    for (i = ptr; input_data[i] != '$'; i++) {
        cout << input_data[i];
    }
    cout << input_data[i] << '\n';
}

void E() {//非终结符号
    T();
    cout << "E->T" << endl;
    if (input_data[ptr] == '+') {
        cout << "	读入  +  " << endl;
        ptr++;
        E();
        cout << "E->E+T 当前剩余字符串";
        show_remain();
    }
    else if (input_data[ptr] == '-') {
        cout << "	读入  -  " << endl;
        ptr++;
        E();
        cout << "E->E-T	当前剩余字符串";
        show_remain();
    }
}

void T() {
    F();
    cout << "T->F" << endl;
    if (input_data[ptr] == '*') {
        cout << "	读入  *  " << endl;
        ptr++;
        T();
        cout << "T->T*F	当前剩余字符串";
        show_remain();
    }
    else if (input_data[ptr] == '/') {
        cout << "	读入  /  " << endl;
        ptr++;
        T();
        cout << "T->T/F	当前剩余字符串";
        show_remain();
    }
}

void F() {
    int i = 0;
    if (input_data[ptr] == '(') {
        cout << "	读入 (" << endl;
        ptr++;
        E();
        if (input_data[ptr] == ')') {
            cout << "	读入 )" << endl;
            ptr++;
            cout << "F->(E)	当前剩余字符串";
            show_remain();
        }
    }//读取不定长的整数的过程
    else if (input_data[ptr] >= '0' && input_data[ptr] <= '9') {
        int flag = 0;
        while (input_data[ptr] >= '0' && input_data[ptr] <= '9') {
            flag = 1;
            ptr++;
        }
        if (input_data[ptr] == '.' && flag == 1) {//考虑非整数的情况
            ptr++;
            while (input_data[ptr] >= '0' && input_data[ptr] <= '9') {
                ptr++;
            }
            flag = 0;
        }
        cout << "	读入 num" << endl;
        cout << "F->num	当前剩余字符串";
        show_remain();
    }
    else {
        cout << "错误" << endl;
        exit(1);
    }
}
