// ��ʾ����ʾ���ͨ��ODBC��ʽ��ȡGaussDB(for openGauss)�е����ݡ�
// DBtest.c (compile with: libodbc.so)
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlext.h>
#ifdef WIN32
#endif
SQLHENV       V_OD_Env;        // Handle ODBC environment
SQLHSTMT      V_OD_hstmt;      // Handle statement
SQLHDBC       V_OD_hdbc;       // Handle connection
SQLINTEGER    value = 100;
SQLINTEGER    V_OD_erg,V_OD_buffer,V_OD_err,V_OD_name[32],V_OD_number;
int main(int argc,char *argv[])
{
    // �뻷�����
    V_OD_erg = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&V_OD_Env);
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
    {
        printf("�������\n");
        exit(0);
    }
    // ���û������ԣ��汾��Ϣ��
    SQLSetEnvAttr(V_OD_Env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    //�����Ӿ��
    V_OD_erg = SQLAllocHandle(SQL_HANDLE_DBC, V_OD_Env, &V_OD_hdbc);
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
    {
        SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
        exit(0);
    }
    //����������
    SQLSetConnectAttr(V_OD_hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0);
    // ��������Դ������ġ�userName���롰password���ֱ��ʾ�������ݿ���û������û����룬�����ʵ������޸ġ�
    // ���odbc.ini�ļ����Ѿ��������û������룬��ô����������գ�""�������ǲ�������ô������Ϊһ��odbc.iniȨ�޹����ƣ����������ݿ��û�����й¶��
    V_OD_erg = SQLConnect(V_OD_hdbc, (SQLCHAR*) "PostgreSQL35W", SQL_NTS,
                          (SQLCHAR*) "bupt2020211346", SQL_NTS,  (SQLCHAR*) "bupt@2022", SQL_NTS);
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQL����ʧ�� %d\n",V_OD_erg);
        SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
        exit(0);
    }
    printf("���ӳɹ� !\n");
    //�����������
    SQLSetStmtAttr(V_OD_hstmt,SQL_ATTR_QUERY_TIMEOUT,(SQLPOINTER *)3,0);
    //���������
    SQLAllocHandle(SQL_HANDLE_STMT, V_OD_hdbc, &V_OD_hstmt);
    // ֱ��ִ��SQL��䡣
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "SET SEARCH_PATH TO bupt2020211346", SQL_NTS); //ָ��Schema
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "drop table IF EXISTS dorm", SQL_NTS);
    printf("�������dorm\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "CREATE TABLE dorm(people VARCHAR(32), number int8);", SQL_NTS);
    printf("��ʼ��������\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('�����',2020211346)", SQL_NTS);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('���ʷ�',2020211344)", SQL_NTS);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('�����',2020211343)", SQL_NTS);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('����־',2021211345)", SQL_NTS);
    printf("�������ݽ���\n");
    // ִ��׼���õ����
    SQLExecute(V_OD_hstmt);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "select * from dorm", SQL_NTS);
    // �󶨽����
    SQLBindCol(V_OD_hstmt,1,SQL_C_SLONG, (SQLPOINTER)&V_OD_buffer,150,
               (SQLLEN *)&V_OD_err);
    //ͨ��SQLFetchȡ�����������
    V_OD_erg=SQLFetch(V_OD_hstmt);
    //ͨ��SQLGetData��ȡ���������ݡ�
    printf("�����ݿ�dorm�в�ѯ����\n");
    printf("��ѯ�����������£�\n");
    while(V_OD_erg != SQL_NO_DATA)
    {
        SQLGetData(V_OD_hstmt,1,SQL_C_DEFAULT,&V_OD_name,32,NULL);
        printf("����:%s\t",V_OD_name);
        SQLGetData(V_OD_hstmt,2,SQL_C_DEFAULT,&V_OD_number,32,NULL);
        printf("ѧ��:%d\t",V_OD_number) ;
        printf("\n");
        V_OD_erg=SQLFetch(V_OD_hstmt);
    };
    //�� �� �� �� �� Դ
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    //������ �� ���
    SQLAllocHandle(SQL_HANDLE_STMT, V_OD_hdbc, &V_OD_hstmt);
    printf("\n");
    printf("���ݲ�ѯ����������ɾ�����ҳ�Ա������족\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "SET SEARCH_PATH TO bupt2020211346", SQL_NTS); //ָ��Schema
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "delete from dorm where people='�����'", SQL_NTS);
    printf("����ɾ�����\n");
    // ִ��׼���õ����
    SQLExecute(V_OD_hstmt);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "select * from dorm", SQL_NTS);
    // �󶨽����
    SQLBindCol(V_OD_hstmt,1,SQL_C_SLONG, (SQLPOINTER)&V_OD_buffer,150,
               (SQLLEN *)&V_OD_err);
    //ͨ��SQLFetchȡ�����������
    V_OD_erg=SQLFetch(V_OD_hstmt);
    //ͨ��SQLGetData��ȡ���������ݡ�
    printf("�����ݿ�dorm�в�ѯ����\n");
    printf("��ѯ�����������£�\n");
    while(V_OD_erg != SQL_NO_DATA)
    {
        SQLGetData(V_OD_hstmt,1,SQL_C_DEFAULT,&V_OD_name,32,NULL);
        printf("����:%s\t",V_OD_name);
        SQLGetData(V_OD_hstmt,2,SQL_C_DEFAULT,&V_OD_number,0,NULL);
        printf("ѧ��:%d\t",V_OD_number) ;
        printf("\n");
        V_OD_erg=SQLFetch(V_OD_hstmt);
    };
    //�� �� �� �� �� Դ
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    //������ �� ���
    SQLAllocHandle(SQL_HANDLE_STMT, V_OD_hdbc, &V_OD_hstmt);
    printf("\n");
    printf("����ɾ����ϣ������޸ġ�����־����ѧ��\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "SET SEARCH_PATH TO bupt2020211346", SQL_NTS); //ָ��Schema
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "UPDATE dorm SET number='2020211345' where people='����־'", SQL_NTS);
    printf("�����޸����\n");
    // ִ��׼���õ����
    SQLExecute(V_OD_hstmt);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "select * from dorm", SQL_NTS);
    // �󶨽����
    SQLBindCol(V_OD_hstmt,1,SQL_C_SLONG, (SQLPOINTER)&V_OD_buffer,150,
               (SQLLEN *)&V_OD_err);
    //ͨ��SQLFetchȡ�����������
    V_OD_erg=SQLFetch(V_OD_hstmt);
    //ͨ��SQLGetData��ȡ���������ݡ�
    printf("�����ݿ�dorm�в�ѯ����\n");
    printf("��ѯ�����������£�\n");
    while(V_OD_erg != SQL_NO_DATA)
    {
        SQLGetData(V_OD_hstmt,1,SQL_C_DEFAULT,&V_OD_name,32,NULL);
        printf("����:%s\t",V_OD_name);
        SQLGetData(V_OD_hstmt,2,SQL_C_DEFAULT,&V_OD_number,0,NULL);
        printf("ѧ��Ϊ:%d\t",V_OD_number) ;
        printf("\n");
        V_OD_erg=SQLFetch(V_OD_hstmt);
    };
    printf("���!\n");
    //�� �� �� �� �� Դ
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    //�Ͽ�����Դ���Ӳ��ͷž����Դ
    SQLFreeHandle(SQL_HANDLE_STMT,V_OD_hstmt);
    SQLDisconnect(V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    return(0);
}

