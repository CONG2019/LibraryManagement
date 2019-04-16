#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <string.h>
#include <stdio.h>
#include "Books.h"

#define Max_BorrowingNumber 5

struct Administrators
{
    char AccountNumber[13];     //�˺�
    char AccountKeys[20];   //����
    char Name[20];  //����Ա����
    char Sex[3];    //�Ա�
    unsigned char Jurisdiction;     //����Ȩ��
    struct Administrators *next;    //����Ա�������һ����Ա
};

struct Users
{
    char AccountNumber[13];     //�˺�
    char AccountKeys[20];       //����
    char Name[20];      //�û�����
    char Sex[3];    //�Ա�
    char StudentNumber[13];     //ѧ��
    unsigned char Leaguer;  //��Ա��־��
    struct Books Borrowing[Max_BorrowingNumber];      //�����ͼ�飬���ͬʱ��5��
    int BorrowingNumber;        //��ǰ��������Ŀ
    struct Users *next;     //�û��������һ����Ա
};

struct AdministratorsList
{
    struct Administrators *head;    //����Ա����ͷ
    struct Administrators *rear;    //����Ա��β
    unsigned int number;     //����Ա��Ŀ
};

struct UserList
{
    struct Users *head;    //�û�����ͷ
    struct Users *rear;    //�û���β
    unsigned int number;      //�û�����
};

struct OnlineUsers
{
    int UsersClass;       //�����û����ͱ�־ 1���û� 0������Ա
    struct Administrators *OnlineA;         //��ǰ�û�ָ��
    struct Users *OnlineU;
};

extern struct AdministratorsList AL;
extern struct UserList UL;
extern struct Administrators *AP;     //��ǰ���ʹ���Ա�����Ա��ָ��
extern struct Users *UP;        //��ǰ�����û���Աָ��
extern struct OnlineUsers OU;       //�����û���¼�ṹ��
extern int ULChange;            //�û����ı�־
extern int ALChange;            //����Ա���ı�־

int AdministratorsLoad();      //����Ա���ݼ���
int UsersLoad();       //�û����ݼ���
char *Encryption(char Keys[]);    //���ܺ���
int UsersLogin();       //�û���¼����
int AdministratorsLogin();      //����Ա��¼����
int Is_A_Existence();           //�жϹ���Ա�Ƿ����
int Is_U_Existence();           //�ж��û��Ƿ����
void ShowAdministrators();      //��ʾ���й���Ա��Ϣ
void ShowUsers();           //��ʾ�����û���Ϣ
void ShowOU();          //��ʾ��ǰ�����û���Ϣ
void ShowOA();          //��ʾ��ǰ���߹���Ա��Ϣ
void ChangeMessage();   //�޸ĸ�����Ϣ
int SaveAL();       //�������Ա
int SaveUL();       //�����û�
int ShowBorrowing();  //��ʾ���õ�ͼ��
int Borrowing();        //����
int ReturnBook();       //����
void ApplyForVIP();     //�����Ա
void UserManagement();  //�û�����
void CancleVIP();       //ע����Ա
void DeleteUsers();     //ɾ���û�
void UserRegistration();    //�û�ע��
void ADRegistration();      //����Աע��
void Auditing();        //�������
int AuditingVIP();     //��Ա���
int AuditingAD();      //����Աע�����
void GetKeys(char s[]);     //��ȡ����

#endif // __LOGIN_H__

