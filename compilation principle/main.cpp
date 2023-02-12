#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

//�жϵ�ǰ�ַ����Ƿ�Ϊ�ؼ���
bool isKey(string s){
    //�ؼ�������
    string keyArray[] = {"int","char","string","bool","float","double","float","true","false","return",
                         "if","else","while","for","default","do","public","static","switch"};
    //�뵱ǰ�ַ���һһ�Ա�
    for(int i=0;i<sizeof(keyArray);i++){
        if(keyArray[i] == s){
            return true;
        }
        else{
            return false;
        }
    }
}

//�жϵ�ǰ�ַ��Ƿ��������
bool isOperator(char ch){
    if('+'==ch || '-'==ch || '*'==ch || '/'==ch || '^'==ch || '='==ch || '<'==ch || '>'==ch || '!'==ch)
        return true;
    else
        return false;
}
bool isMarkStart(string s){
    int len=s.length();
    if(len<2) return false;

    if(s.at(len-1)=='*' && s.at(len-2)=='/'){
        return true;
    }
    else return false;

}
bool isMarkrow(string s){
    int len=s.length();
    if(len<2) return false;

    if(s.at(len-1)=='/' && s.at(len-2)=='/'){
        return true;
    }
    else return false;

}
//�жϵ�ǰ�ַ��Ƿ��Ƿָ���
bool isSeparator(char ch){
    if(','==ch || ';'==ch || '{'==ch || '}'==ch || '('==ch || ')'==ch)
        return true;
    else
        return false;
}//
class word{

public:
int count;
     string name;
     int kind;
};
int wordnum;//��¼�ĵ��еĵ�������
class word words[10000];
void recording(string special,int kind){
    for(int i=0;i<wordnum;i++){
        if(words[i].name.compare(special)==0){
            words[i].count++;
            return;
        }
    }
    words[wordnum].kind=kind;
    words[wordnum].name=special;
    words[wordnum].count++;
    wordnum++;
}
int main(){
    char ch;
    int row=1;//��¼����
    int total=0;//�ַ�����
    string file = "code.txt";
    ifstream infile;
    //���ļ����������ļ���������
    infile.open(file.data());
    //��ʧ��,�����������Ϣ,����ֹ��������
    assert(infile.is_open());
    infile >> noskipws;
    //txt�ı��ж�ȡ�ո���뻻�з�
    //��ȡ�ı��е�һ���ַ�
    infile>>ch;
    if(ch=='\n') {
        row++;
        infile>>ch;
    }
    else if (ch==' '){
        while(ch==' '){
            infile>>ch;
        }
    }
    else{
        total++;
    }
    string special;
    while (!infile.eof()){//δ��ȡ���ս����
        if(isalpha(ch) || '_'==ch){//�����Ǳ�ʶ�����߹ؼ���
            special.append(1,ch);//�����ַ���
            infile>>ch;
            if(ch=='\n') {
                row++;
                infile>>ch;
            }
            else if (ch==' '){
                while(ch==' '){
                    infile>>ch;
                }
            }
            else{
                total++;
            }

            while(isalpha(ch) || isdigit(ch) || '_'==ch){
                special.append(1,ch);
                infile>>ch;
                if(ch=='\n') {
                    row++;
                    infile>>ch;
                }
                else if (ch==' '){
                    while(ch==' '){
                        infile>>ch;
                    }
                }
                else{
                    total++;
                }
                if(isKey(special)){
                    cout<<("(1,\""+special+"\")")<<endl;
                    recording(special,1);
                    special="";
                }
            }
            if(isSeparator(ch) || isOperator(ch))//�����ʶ����
            {
                if(isKey(special)){
                    cout<<("(1,\""+special+"\")")<<endl;
                    recording(special,1);
                    special="";
                    continue;
                }
                else{
                    if(isdigit(special.at(0))){
                        cout<<"(Error,\""+special+"\")  ";
                        cout<<"������ ";
                        cout<<row;
                        cout<<"��"<<endl;
                        recording(special,6);
                    }else{
                        cout<<"(2,\""+special+"\")"<<endl;
                        recording(special,2);
                    }
                    special="";
                    continue;
                }

            }

            else{
                special.append(1,ch);
                infile>>ch;
                if(ch=='\n') {
                    row++;
                    infile>>ch;
                }
                else if (ch==' '){
                    while(ch==' '){
                        infile>>ch;
                    }
                }
                else{
                    total++;
                }
                while(!isSeparator(ch) && !isOperator(ch)){
                    special.append(1,ch);
                    infile>>ch;
                    while(ch=='\n' || ch==' ') {
                        if (ch == '\n') {
                            row++;
                            infile >> ch;
                        } else if (ch == ' ') {

                            infile >> ch;

                        }
                    }
                    if(ch!='\n' && ch!=' '){
                        total++;
                    }
                }
                cout<<"(Error,\""+special+"\"+"") ";
                cout<<"������ ";
                cout<<row;
                cout<<"��"<<endl;
                recording(special,6);
                special="";
                continue;

            }


        }
        else if(isdigit(ch)){
            special.append(1,ch);
            infile>>ch;
            while(ch=='\n' || ch==' ') {
                if (ch == '\n') {
                    row++;
                    infile >> ch;
                } else if (ch == ' ') {

                    infile >> ch;

                }
            }
            if(ch!='\n' && ch!=' '){
                total++;
            }
            //�����������֣���ɳ���
            while(isdigit(ch)){
                special.append(1,ch);
                infile>>ch;
                while(ch=='\n' || ch==' ') {
                    if (ch == '\n') {
                        row++;
                        infile >> ch;
                    } else if (ch == ' ') {

                        infile >> ch;

                    }
                }
                if(ch!='\n' && ch!=' '){
                    total++;
                }
            }
            if(isOperator(ch) || isSeparator(ch)){
                cout<<"(3,\""+special+"\")"<<endl;
                recording(special,3);
                special="";
                continue;
            }
            else{
                special.append(1,ch);
                infile>>ch;
                while(ch=='\n' || ch==' ') {
                    if (ch == '\n') {
                        row++;
                        infile >> ch;
                    } else if (ch == ' ') {

                        infile >> ch;

                    }
                }
                if(ch!='\n' && ch!=' '){
                    total++;
                }
                if(ch=='\n') row++;

                while(!isSeparator(ch) && !isOperator(ch)){
                    special.append(1,ch);
                    infile>>ch;
                    while(ch=='\n' || ch==' ') {
                        if (ch == '\n') {
                            row++;
                            infile >> ch;
                        } else if (ch == ' ') {

                            infile >> ch;

                        }
                    }
                    if(ch!='\n' && ch!=' '){
                        total++;
                    }

                }
                cout<<"(Error,\""+special+"\")  ";
                cout<<"������ ";
                cout<<row;
                cout<<"��"<<endl;
                recording(special,6);
                special="";
                continue;
            }

        }
        else if(isOperator(ch)){
            special.append(1,ch);
            infile>>ch;
            while(ch=='\n' || ch==' ') {
                if (ch == '\n') {
                    row++;
                    infile >> ch;
                } else if (ch == ' ') {
                    infile >> ch;

                }
            }
            if(ch!='\n' && ch!=' '){
                total++;
            }
            //�ж��Ƿ����<=��>=��!=
            if("<"== special || ">"== special || "!"== special){
                if('='==ch){
                    special.append(1,ch);
                    infile>>ch;
                    while(ch=='\n' || ch==' ') {
                        if (ch == '\n') {
                            row++;
                            infile >> ch;
                        } else if (ch == ' ') {

                            infile >> ch;

                        }
                    }
                    if(ch!='\n' && ch!=' '){
                        total++;
                    }
                }
            }
            //��һ�������Ϊ��ĸ�����֡��ָ���������ȷ
            if(isalpha(ch) || isdigit(ch) || isSeparator(ch)){
                cout<<"(4,\""+ special+"\")"<<endl;
                recording( special,4);
                special="";
                continue;
            }
            else{
                //�����������һ����룬ֱ����ȷ
                while(!isSeparator(ch) && !isalpha(ch) && !isdigit(ch)){
                    special.append(1,ch);
                    infile>>ch;
                    if(isMarkStart(special)){
                        cout<<"����ע������Ϊ:";
                        while( !infile.eof()) {
                            while (ch != '*' && !infile.eof()) {
                                infile >> ch;
                                if(ch=='\n') row++;
                                if(ch != '*')cout<<ch;
                            }
                            infile >> ch;
                            if(ch=='\n') row++;
                            if(ch=='/'){
                                cout<<endl;
                                special="";
                                infile >> ch;
                                if(ch=='\n') row++;
                                break;
                            }
                            else {cout<<ch;infile >> ch; if(ch=='\n') row++;
                                cout<<ch;}
                        }
                    }
                    else if(isMarkrow(special)){
                        cout<<"����ע������Ϊ:";
                        while(ch!='\n' && !infile.eof()){
                            infile>>ch;
                            cout<<ch;
                        }
                        special="";
                    }
                    while(ch=='\n' || ch==' ') {
                        if (ch == '\n') {
                            row++;
                            infile >> ch;
                        } else if (ch == ' ') {

                            infile >> ch;

                        }
                    }
                    if(ch!='\n' && ch!=' '){
                        total++;
                    }
                }
                if(special!="") {

                    cout << "(Error,\"" + special + "\")";
                    cout << "������ ";
                    cout << row;
                    cout << "��" << endl;
                    recording(special, 6);
                    special = "";
                }
                continue;
            }

        }
        else if(isSeparator(ch)){
            special.append(1,ch);
            cout<<"(5,\""+ special+"\")"<<endl;
            recording( special,5);
            special="";
            infile>>ch;
            while(ch=='\n' || ch==' ') {
                if (ch == '\n') {
                    row++;
                    infile >> ch;
                } else if (ch == ' ') {

                    infile >> ch;

                }
            }
            if(ch!='\n' && ch!=' '){
                total++;
            }
        }
        else{
            //������
            special.append(1,ch);
            cout<<"(Error,\""+special+"\")   ";
            cout<<"������ ";
            cout<<row;
            cout<<"��"<<endl;
            recording( special,6);
            special="";
            infile>>ch;
            while(ch=='\n' || ch==' ') {
                if (ch == '\n') {
                    row++;
                    infile >> ch;
                } else if (ch == ' ') {

                        infile >> ch;

                }
            }
            if(ch!='\n' && ch!=' '){
                total++;
            }

        }

    }
    infile.close();
    cout<<"�����ַ�����Ϊ: "<<total-1<<endl;
    cout<<"����Ϊ: "<<row<<endl;
    for(int i=0;i<wordnum;i++){
        cout<<"�õ���Ϊ: "<<words[i].name<<" ����Ϊ: "<<words[i].count<<" ����Ϊ "<<words[i].kind<<endl;
    }
}