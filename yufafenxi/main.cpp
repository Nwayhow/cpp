#include<iostream>
#include<algorithm>
#include<string>
#include <cstring>

using namespace std;

char input_data[1024];//����txt�ı��е�����
int ptr = 0;          //ָ��
void E();
void T();
void F();
void show_remain();  //չʾʣ��δ�������ַ���

int main() {
    cout << "�������ַ���" << endl;
    cin >> input_data;
    int i = strlen(input_data);
    input_data[i] = '$';//��������
    E();
    if (input_data[ptr] == '$') {
        cout << "�������" << endl;
    }
    else {
        cout << "��������" << endl;
    }
}

void show_remain() {//��ʾʣ����ַ���
    int i = ptr;
    for (i = ptr; input_data[i] != '$'; i++) {
        cout << input_data[i];
    }
    cout << input_data[i] << '\n';
}

void E() {//���ս����
    T();
    cout << "E->T" << endl;
    if (input_data[ptr] == '+') {
        cout << "	����  +  " << endl;
        ptr++;
        E();
        cout << "E->E+T ��ǰʣ���ַ���";
        show_remain();
    }
    else if (input_data[ptr] == '-') {
        cout << "	����  -  " << endl;
        ptr++;
        E();
        cout << "E->E-T	��ǰʣ���ַ���";
        show_remain();
    }
}

void T() {
    F();
    cout << "T->F" << endl;
    if (input_data[ptr] == '*') {
        cout << "	����  *  " << endl;
        ptr++;
        T();
        cout << "T->T*F	��ǰʣ���ַ���";
        show_remain();
    }
    else if (input_data[ptr] == '/') {
        cout << "	����  /  " << endl;
        ptr++;
        T();
        cout << "T->T/F	��ǰʣ���ַ���";
        show_remain();
    }
}

void F() {
    int i = 0;
    if (input_data[ptr] == '(') {
        cout << "	���� (" << endl;
        ptr++;
        E();
        if (input_data[ptr] == ')') {
            cout << "	���� )" << endl;
            ptr++;
            cout << "F->(E)	��ǰʣ���ַ���";
            show_remain();
        }
    }//��ȡ�������������Ĺ���
    else if (input_data[ptr] >= '0' && input_data[ptr] <= '9') {
        int flag = 0;
        while (input_data[ptr] >= '0' && input_data[ptr] <= '9') {
            flag = 1;
            ptr++;
        }
        if (input_data[ptr] == '.' && flag == 1) {//���Ƿ����������
            ptr++;
            while (input_data[ptr] >= '0' && input_data[ptr] <= '9') {
                ptr++;
            }
            flag = 0;
        }
        cout << "	���� num" << endl;
        cout << "F->num	��ǰʣ���ַ���";
        show_remain();
    }
    else {
        cout << "����" << endl;
        exit(1);
    }
}
