#ifndef __BOOKS_H__
#define __BOOKS_H__

#include <stdio.h>
#include <string.h>
#include <windows.h>
//#include "Login.h"
//#include "Page.h"

struct Books
{
    char AccountNumber[13];   //登录号
    char Name[30];    //书名
    char BookNumber[13];   //图书编号
    int Price;  //单价
    char Author[20];    //作者
    char Class[13]; //分类号
    char Publisher[30]; //出版单位
    char PublishingTime[15];    //出版时间
    int RemainingNumber;    //馆藏剩余数目
    struct Books *next;     //下一个成员地址
};

struct BooksList
{
    struct Books *head;     //图书链表头
    struct Books *rear;     //图书表尾
    int number;     //图书数量
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

int BooksLoad();        //图书信息加载
int BooksInput();       //图书录入
int SaveBL();           //保存更改过的图书信息
void ShowBooks();       //显示所有图书
void ShowBook(struct Books *Book);      //显示某一种图书的信息
void DeleteBooks();     //删除图书
int SearchByAN(char s[]);      //通过登录号搜索图书
int FreeResult();          //清除搜索结果
void ShowResult();      //显示搜索结果
void SorttingByName();      //按名字排序
void SorttingByClass();     //按分类号排序
void SorttingByAuthor();      //按作者排序
void SearchBook();      //搜索图书
void ChangeBook();      //修改图书信息
void GetString(char s[],int Size);

#endif // __BOOKS_H__
