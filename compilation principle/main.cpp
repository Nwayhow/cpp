#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

//判断当前字符串是否为关键字
bool isKey(string s){
    //关键字数组
    string keyArray[] = {"int","char","string","bool","float","double","float","true","false","return",
                         "if","else","while","for","default","do","public","static","switch"};
    //与当前字符串一一对比
    for(int i=0;i<sizeof(keyArray);i++){
        if(keyArray[i] == s){
            return true;
        }
        else{
            return false;
        }
    }
}

//判断当前字符是否是运算符
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
//判断当前字符是否是分隔符
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
int wordnum;//记录文档中的单词总数
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
    int row=1;//记录行数
    int total=0;//字符总数
    string file = "code.txt";
    ifstream infile;
    //将文件流对象与文件连接起来
    infile.open(file.data());
    //若失败,则输出错误消息,并终止程序运行
    assert(infile.is_open());
    infile >> noskipws;
    //txt文本中读取空格符与换行符
    //读取文本中的一个字符
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
    while (!infile.eof()){//未读取到终结符号
        if(isalpha(ch) || '_'==ch){//可能是标识符或者关键字
            special.append(1,ch);//加入字符串
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
            if(isSeparator(ch) || isOperator(ch))//读入标识符号
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
                        cout<<"错误在 ";
                        cout<<row;
                        cout<<"行"<<endl;
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
                cout<<"错误在 ";
                cout<<row;
                cout<<"行"<<endl;
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
            //继续读入数字，组成常数
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
                cout<<"错误在 ";
                cout<<row;
                cout<<"行"<<endl;
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
            //判断是否存在<=、>=、!=
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
            //下一个读入符为字母、数字、分隔符，即正确
            if(isalpha(ch) || isdigit(ch) || isSeparator(ch)){
                cout<<"(4,\""+ special+"\")"<<endl;
                recording( special,4);
                special="";
                continue;
            }
            else{
                //将错误输入符一起读入，直到正确
                while(!isSeparator(ch) && !isalpha(ch) && !isdigit(ch)){
                    special.append(1,ch);
                    infile>>ch;
                    if(isMarkStart(special)){
                        cout<<"发现注释内容为:";
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
                        cout<<"发现注释内容为:";
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
                    cout << "错误在 ";
                    cout << row;
                    cout << "行" << endl;
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
            //出错处理
            special.append(1,ch);
            cout<<"(Error,\""+special+"\")   ";
            cout<<"错误在 ";
            cout<<row;
            cout<<"行"<<endl;
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
    cout<<"代码字符总数为: "<<total-1<<endl;
    cout<<"行数为: "<<row<<endl;
    for(int i=0;i<wordnum;i++){
        cout<<"该单词为: "<<words[i].name<<" 数量为: "<<words[i].count<<" 类型为 "<<words[i].kind<<endl;
    }
}