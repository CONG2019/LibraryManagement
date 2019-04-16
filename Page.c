#include "Page.h"

void Homepage()
{
    int flag;
    int flag1=1;
    while(flag1)
    {
    printf("欢迎使用图书管信息管理系统！\r\n");
    printf("请先登录！\r\n");
    printf("1、用户登录\r\n2、管理员登录\r\n3、用户注册\r\n4、管理员注册\r\n5、退出\r\n");
    printf("************************************************************************************************\r\n\r\n");
    scanf("%d",&flag);
    switch(flag)
    {
    case 1:
        if(UsersLogin())
        {
            UsersPage();
            printf("成功\r\n");
        }else
        {
            flag1=0;
        }
        break;
    case 2:
        if(AdministratorsLogin())
        {
            AdministratorsPage();
            printf("成功\r\n");
        }else
        {
            flag1=0;
        }
        break;
    case 3:
        UserRegistration();
        break;
    case 4:
        ADRegistration();
        break;
    case 5:
        flag1=0;
        break;
    default :
        break;
    }
    }
}

void UsersPage()
{
    int flag;
    while(1)
    {
    printf("1、显示个人信息\r\n2、修改个人信息\r\n3、显示借用的图书\r\n4、借书\r\n5、还书\r\n6、申请会员\r\n7、显示所有图书\r\n8、搜索图书\r\n9、退出\r\n");
    scanf("%d",&flag);
    getchar();
    printf("************************************************************************************************\r\n\r\n");
    switch(flag)
    {
        case 1:
            ShowOU();
            break;
        case 2:
            ChangeMessage();
            break;
        case 3:
            ShowBorrowing();
            break;
        case 4:
            Borrowing();
            break;
        case 5:
            ReturnBook();
            break;
        case 6:
            ApplyForVIP();
            break;
        case 7:
            ShowBooks();
            break;
        case 8:
            SearchBook();
            break;
        case 9:
            return 0;
            break;
        default :
            break;
    }
    }
}

void AdministratorsPage()
{
    int flag;
    while(1)
    {
        printf("1、显示个人信息\r\n2、修改个人信息\r\n3、显示所有图书\r\n4、图书录入\r\n5、图书删除\r\n6、图书信息修改\r\n7、图书搜索\r\n8、排序\r\n9、用户管理\r\n10、申请审核\r\n11、退出\r\n");
        scanf("%d",&flag);
        getchar();
        printf("************************************************************************************************\r\n\r\n");
        switch(flag)
        {
            case 1:
                ShowOA();
                break;
            case 2:
                ChangeMessage();
                break;
            case 3:
                ShowBooks();
                break;
            case 4:
                BooksInput();
                if(BLChange==1)
                {
                    SaveBL();
                    BLChange=0;
                }
                break;
            case 5:
                DeletPage();
                break;
            case 6:
                ChangeBook();
                break;
            case 7:
                SearchBook();
                break;
            case 8:
                SortPage();
                break;
            case 9:
                UserManagement();
                break;
            case 10:
                Auditing();
                break;
            case 11:
                return 0;
                break;
            default :
                break;

        }
    }
}

void DeletPage()
{
    char flag;
    char s[13];
    while(1)
    {
        printf("请输入要删除书本的登录号：");
        //scanf("%s",s);
        //getchar();
         GetString(s,13);
        if(SearchByAN(s))
        {
            //ShowResult();
            printf("要删除的书的信息是：\r\n");
            ShowBook((*Result.next).Book);
            printf("输入Y删除，N不删除\r\n");
            //scanf("%c",&flag);
            //getchar();
            flag=getch();
            if(flag=='Y')
            {
                DeleteBooks();
                FreeResult();
                BLChange=1;
            }else if(flag=='N')
            {
                ;
            }else
            {
                printf("输入出错,不删除！\r\n");
            }
        }
        printf("继续删除按Y，退出按N\r\n");
        //scanf("%c",&flag);
        //getchar();
        flag=getch();
        if(flag=='N')
        {
            break;
        }
    }
    SaveBL();
}

void SortPage()
{
    char flag;
    int flag1=1;
    printf("请选择排序方式：\r\n1、按名字排序\r\n2、按分类号排序\r\n3、按作者排序\r\n");
    while(flag1)
    {
        scanf("%c",&flag);
        getchar();
        switch(flag)
        {
        case '1':
            SorttingByName();
            printf("排序结果为：\r\n");
            printf("************************************************************************************************\r\n\r\n");
            ShowBooks();
            flag1=0;     //输入正确，回到主界面
            break;
        case '2':
            SorttingByClass();
            printf("排序结果为：\r\n");
            printf("************************************************************************************************\r\n\r\n");
            ShowBooks();
            flag1=0;     //输入正确，回到主界面
            break;
        case '3':
            SorttingByAuthor();
            printf("排序结果为：\r\n");
            printf("************************************************************************************************\r\n\r\n");
            ShowBooks();
            flag1=0;     //输入正确，回到主界面
            break;
        default :
            break;
        }
    }
}
