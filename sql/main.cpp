// 此示例演示如何通过ODBC方式获取GaussDB(for openGauss)中的数据。
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
    // 请环境句柄
    V_OD_erg = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&V_OD_Env);
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
    {
        printf("句柄错误\n");
        exit(0);
    }
    // 设置环境属性（版本信息）
    SQLSetEnvAttr(V_OD_Env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    //请连接句柄
    V_OD_erg = SQLAllocHandle(SQL_HANDLE_DBC, V_OD_Env, &V_OD_hdbc);
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
    {
        SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
        exit(0);
    }
    //置连接属性
    SQLSetConnectAttr(V_OD_hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0);
    // 连接数据源，这里的“userName”与“password”分别表示连接数据库的用户名和用户密码，请根据实际情况修改。
    // 如果odbc.ini文件中已经配置了用户名密码，那么这里可以留空（""）；但是不建议这么做，因为一旦odbc.ini权限管理不善，将导致数据库用户密码泄露。
    V_OD_erg = SQLConnect(V_OD_hdbc, (SQLCHAR*) "PostgreSQL35W", SQL_NTS,
                          (SQLCHAR*) "bupt2020211346", SQL_NTS,  (SQLCHAR*) "bupt@2022", SQL_NTS);
    if ((V_OD_erg != SQL_SUCCESS) && (V_OD_erg != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQL连接失败 %d\n",V_OD_erg);
        SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
        exit(0);
    }
    printf("连接成功 !\n");
    //设置语句属性
    SQLSetStmtAttr(V_OD_hstmt,SQL_ATTR_QUERY_TIMEOUT,(SQLPOINTER *)3,0);
    //申请语句句柄
    SQLAllocHandle(SQL_HANDLE_STMT, V_OD_hdbc, &V_OD_hstmt);
    // 直接执行SQL语句。
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "SET SEARCH_PATH TO bupt2020211346", SQL_NTS); //指定Schema
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "drop table IF EXISTS dorm", SQL_NTS);
    printf("创建表格dorm\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "CREATE TABLE dorm(people VARCHAR(32), number int8);", SQL_NTS);
    printf("开始插入数据\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('倪玮昊',2020211346)", SQL_NTS);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('马率峰',2020211344)", SQL_NTS);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('刘义红',2020211343)", SQL_NTS);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "insert into dorm values('缪奇志',2021211345)", SQL_NTS);
    printf("插入数据结束\n");
    // 执行准备好的语句
    SQLExecute(V_OD_hstmt);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "select * from dorm", SQL_NTS);
    // 绑定结果集
    SQLBindCol(V_OD_hstmt,1,SQL_C_SLONG, (SQLPOINTER)&V_OD_buffer,150,
               (SQLLEN *)&V_OD_err);
    //通过SQLFetch取结果集中数据
    V_OD_erg=SQLFetch(V_OD_hstmt);
    //通过SQLGetData获取并返回数据。
    printf("从数据库dorm中查询数据\n");
    printf("查询到的数据如下：\n");
    while(V_OD_erg != SQL_NO_DATA)
    {
        SQLGetData(V_OD_hstmt,1,SQL_C_DEFAULT,&V_OD_name,32,NULL);
        printf("姓名:%s\t",V_OD_name);
        SQLGetData(V_OD_hstmt,2,SQL_C_DEFAULT,&V_OD_number,32,NULL);
        printf("学号:%d\t",V_OD_number) ;
        printf("\n");
        V_OD_erg=SQLFetch(V_OD_hstmt);
    };
    //释 放 句 柄 资 源
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    //申请语 句 句柄
    SQLAllocHandle(SQL_HANDLE_STMT, V_OD_hdbc, &V_OD_hstmt);
    printf("\n");
    printf("数据查询结束，下面删除寝室成员“刘义红”\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "SET SEARCH_PATH TO bupt2020211346", SQL_NTS); //指定Schema
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "delete from dorm where people='刘义红'", SQL_NTS);
    printf("数据删除完毕\n");
    // 执行准备好的语句
    SQLExecute(V_OD_hstmt);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "select * from dorm", SQL_NTS);
    // 绑定结果集
    SQLBindCol(V_OD_hstmt,1,SQL_C_SLONG, (SQLPOINTER)&V_OD_buffer,150,
               (SQLLEN *)&V_OD_err);
    //通过SQLFetch取结果集中数据
    V_OD_erg=SQLFetch(V_OD_hstmt);
    //通过SQLGetData获取并返回数据。
    printf("从数据库dorm中查询数据\n");
    printf("查询到的数据如下：\n");
    while(V_OD_erg != SQL_NO_DATA)
    {
        SQLGetData(V_OD_hstmt,1,SQL_C_DEFAULT,&V_OD_name,32,NULL);
        printf("姓名:%s\t",V_OD_name);
        SQLGetData(V_OD_hstmt,2,SQL_C_DEFAULT,&V_OD_number,0,NULL);
        printf("学号:%d\t",V_OD_number) ;
        printf("\n");
        V_OD_erg=SQLFetch(V_OD_hstmt);
    };
    //释 放 句 柄 资 源
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    //申请语 句 句柄
    SQLAllocHandle(SQL_HANDLE_STMT, V_OD_hdbc, &V_OD_hstmt);
    printf("\n");
    printf("数据删除完毕，下面修改“缪奇志”的学号\n");
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "SET SEARCH_PATH TO bupt2020211346", SQL_NTS); //指定Schema
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "UPDATE dorm SET number='2020211345' where people='缪奇志'", SQL_NTS);
    printf("数据修改完毕\n");
    // 执行准备好的语句
    SQLExecute(V_OD_hstmt);
    SQLExecDirect(V_OD_hstmt, (SQLCHAR *) "select * from dorm", SQL_NTS);
    // 绑定结果集
    SQLBindCol(V_OD_hstmt,1,SQL_C_SLONG, (SQLPOINTER)&V_OD_buffer,150,
               (SQLLEN *)&V_OD_err);
    //通过SQLFetch取结果集中数据
    V_OD_erg=SQLFetch(V_OD_hstmt);
    //通过SQLGetData获取并返回数据。
    printf("从数据库dorm中查询数据\n");
    printf("查询到的数据如下：\n");
    while(V_OD_erg != SQL_NO_DATA)
    {
        SQLGetData(V_OD_hstmt,1,SQL_C_DEFAULT,&V_OD_name,32,NULL);
        printf("姓名:%s\t",V_OD_name);
        SQLGetData(V_OD_hstmt,2,SQL_C_DEFAULT,&V_OD_number,0,NULL);
        printf("学号为:%d\t",V_OD_number) ;
        printf("\n");
        V_OD_erg=SQLFetch(V_OD_hstmt);
    };
    printf("完成!\n");
    //释 放 句 柄 资 源
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    //断开数据源连接并释放句柄资源
    SQLFreeHandle(SQL_HANDLE_STMT,V_OD_hstmt);
    SQLDisconnect(V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC,V_OD_hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, V_OD_Env);
    return(0);
}

