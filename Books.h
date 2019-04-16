#ifndef __BOOKS_H__
#define __BOOKS_H__

#include <stdio.h>
#include <string.h>
#include <windows.h>
//#include "Login.h"
//#include "Page.h"

struct Books
{
    char AccountNumber[13];   //��¼��
    char Name[30];    //����
    char BookNumber[13];   //ͼ����
    int Price;  //����
    char Author[20];    //����
    char Class[13]; //�����
    char Publisher[30]; //���浥λ
    char PublishingTime[15];    //����ʱ��
    int RemainingNumber;    //�ݲ�ʣ����Ŀ
    struct Books *next;     //��һ����Ա��ַ
};

struct BooksList
{
    struct Books *head;     //ͼ������ͷ
    struct Books *rear;     //ͼ���β
    int number;     //ͼ������
};

struct SearchResult
{
    struct Books *Book;
    struct SearchResult *next;
};

extern struct Books *BP;
extern struct BooksList BL;
extern int BLChange;
extern struct SearchResult Result;

int BooksLoad();        //ͼ����Ϣ����
int BooksInput();       //ͼ��¼��
int SaveBL();           //������Ĺ���ͼ����Ϣ
void ShowBooks();       //��ʾ����ͼ��
void ShowBook(struct Books *Book);      //��ʾĳһ��ͼ�����Ϣ
void DeleteBooks();     //ɾ��ͼ��
int SearchByAN(char s[]);      //ͨ����¼������ͼ��
int FreeResult();          //����������
void ShowResult();      //��ʾ�������
void SorttingByName();      //����������
void SorttingByClass();     //�����������
void SorttingByAuthor();      //����������
void SearchBook();      //����ͼ��
void ChangeBook();      //�޸�ͼ����Ϣ
void GetString(char s[],int Size);

#endif // __BOOKS_H__
