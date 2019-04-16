#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <string.h>
#include <stdio.h>
#include "Books.h"

#define Max_BorrowingNumber 5

struct Administrators
{
    char AccountNumber[13];     //账号
    char AccountKeys[20];   //密码
    char Name[20];  //管理员姓名
    char Sex[3];    //性别
    unsigned char Jurisdiction;     //管理权限
    struct Administrators *next;    //管理员链表的下一个成员
};

struct Users
{
    char AccountNumber[13];     //账号
    char AccountKeys[20];       //密码
    char Name[20];      //用户姓名
    char Sex[3];    //性别
    char StudentNumber[13];     //学号
    unsigned char Leaguer;  //会员标志符
    struct Books Borrowing[Max_BorrowingNumber];      //所借的图书，最多同时借5本
    int BorrowingNumber;        //当前借的书的数目
    struct Users *next;     //用户链表的下一个成员
};

struct AdministratorsList
{
    struct Administrators *head;    //管理员链表头
    struct Administrators *rear;    //管理员表尾
    unsigned int number;     //管理员数目
};

struct UserList
{
    struct Users *head;    //用户链表头
    struct Users *rear;    //用户表尾
    unsigned int number;      //用户数量
};

struct OnlineUsers
{
    int UsersClass;       //在线用户类型标志 1：用户 0：管理员
    struct Administrators *OnlineA;         //当前用户指针
    struct Users *OnlineU;
};

extern struct AdministratorsList AL;
extern struct UserList UL;
extern struct Administrators *AP;     //当前访问管理员链表成员的指针
extern struct Users *UP;        //当前访问用户成员指针
extern struct OnlineUsers OU;       //在线用户记录结构体
extern int ULChange;            //用户更改标志
extern int ALChange;            //管理员更改标志

int AdministratorsLoad();      //管理员数据加载
int UsersLoad();       //用户数据加载
char *Encryption(char Keys[]);    //加密函数
int UsersLogin();       //用户登录函数
int AdministratorsLogin();      //管理员登录函数
int Is_A_Existence();           //判断管理员是否存在
int Is_U_Existence();           //判断用户是否存在
void ShowAdministrators();      //显示所有管理员信息
void ShowUsers();           //显示所有用户信息
void ShowOU();          //显示当前在线用户信息
void ShowOA();          //显示当前在线管理员信息
void ChangeMessage();   //修改个人信息
int SaveAL();       //保存管理员
int SaveUL();       //保存用户
int ShowBorrowing();  //显示借用的图书
int Borrowing();        //借书
int ReturnBook();       //还书
void ApplyForVIP();     //申请会员
void UserManagement();  //用户管理
void CancleVIP();       //注销会员
void DeleteUsers();     //删除用户
void UserRegistration();    //用户注册
void ADRegistration();      //管理员注册
void Auditing();        //申请审核
int AuditingVIP();     //会员审核
int AuditingAD();      //管理员注册审核
void GetKeys(char s[]);     //获取密码

#endif // __LOGIN_H__

