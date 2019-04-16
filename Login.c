#include "Login.h"

struct AdministratorsList AL;
struct UserList UL;
struct Administrators *AP;
struct Users *UP;
struct OnlineUsers OU;
int ULChange=0;
int ALChange=0;

int AdministratorsLoad()
{
    FILE *fp;

    if((fp=fopen("Administrators.bin","rb"))==NULL)        //打开管理员文件
    {
        printf("打开管理员文件失败！\r\n");
    }

    fseek(fp,0L,SEEK_END);      //将指针移动到文件结尾

    if(ftell(fp)==0)
    {
        AL.head=NULL;
        AL.rear=NULL;
        AL.number=0;
        printf("没有管理员！\r\n");       //判断文件的大小
        return -1;
    }
    else
    {
        rewind(fp);
        AP=AL.head=(struct Administrators*)malloc(sizeof(struct Administrators));

        while(fread(AP,sizeof(struct Administrators),1,fp)!=1);

        (*AP).next=NULL;      //指针指向链表结尾
        AL.rear=AP;
        AL.number=1;        //至少有一个管理员
    }

    while(feof(fp)==0)
    {
        (*AP).next=(struct Administrators*)malloc(sizeof(struct Administrators));

        if(fread((*AP).next,sizeof(struct Administrators),1,fp)==1)         //读取下一个管理员数据
            {
            AP=(*AP).next;        //AP指向下一个管理员
            (*AP).next=NULL;      //指向链表的结尾
            AL.rear=AP;
            AL.number++;
            }else
            {
                free((*AP).next);
                (*AP).next=NULL;
            }
    }

    fp=fclose(fp);
    return 0;
}

int UsersLoad()
{
    FILE *fp;

    if((fp=fopen("Users.bin","rb"))==NULL)
    {
        printf("打开用户文件失败！\r\n");
    }
    fseek(fp,0L,SEEK_END);          //将文件指针移动到文件的结尾

    if(ftell(fp)==0)
    {
        UL.head=NULL;
        UL.rear=NULL;
        UL.number=0;
        printf("没有用户！\r\n");        //判断文件的大小，如果为0则没有用户，马上退出用户数据的加载
        return -1;
    }
    else
    {
        rewind(fp);
        UP=UL.head=(struct Users*)malloc(sizeof(struct Users));

        while(fread(UP,sizeof(struct Users),1,fp)!=1);

        (*UP).next=NULL;      //指针指向链表结尾
        UL.rear=UP;
        UL.number=1;        //至少有一个用户员
    }

    while(feof(fp)==0)
    {
        (*UP).next=(struct Users*)malloc(sizeof(struct Users));

        if(fread((*UP).next,sizeof(struct Users),1,fp)==1)         //读取下一个管理员数据
            {
            UP=(*UP).next;        //UP指向下一个用户
            (*UP).next=NULL;      //指向链表的结尾
            UL.rear=UP;
            UL.number++;
            }else
            {
                free((*UP).next);
                (*UP).next=NULL;
            }
    }

    fp=fclose(fp);
    return 0;
}

char *Encryption(char Keys[])
{
    int i=0;
    while(Keys[i+1]!='\0')
    {
        Keys[i]=Keys[i]+Keys[i+1];         //当前字符与后一字符值相加作为当前的字符
        i++;
    }
    Keys[i]=Keys[i]+Keys[i];
    return Keys;         //返回字符指针
}

int AdministratorsLogin()
{
    char AccountNumber[13];     //账号
    char AccountKeys[20];   //密码
    int times=0;

    while(times<3)
    {
    printf("管理员账号：");
    //scanf("%s",AccountNumber);
    //getchar();          //将输入的回车号读走
     GetString(AccountNumber,13);
    printf("密码：");
    //scanf("%s",AccountKeys);
    //getchar();          //将输入的回车号读走
    GetKeys(AccountKeys);
    if(Is_A_Existence(AccountNumber,AccountKeys,&times))
    {
        printf("欢迎来到管理员界面！\r\n");
        return 1;
    }
    printf("剩余登录次数为%d\r\n\r\n",3-times);
    }

    printf("登录次数用完！\r\n");
    return 0;
    printf("************************************************************************************************\r\n\r\n");
    return 0;
}

int Is_A_Existence(char AN[],char AK[],int *times)
{
    AP=AL.head;
    while(strcmp((*AP).AccountNumber,AN)!=0)        //从链表头开始搜索账号存不存在
    {
        if((*AP).next==NULL)
        {
            printf("账号不存在！");           //直到链表尾都没有找到账号，给出提示后直接退出程序
            *times=*times+1;
            return 0;
        }else
        {
            AP=(*AP).next;
        }
    }

    if(!strcmp(Encryption(AK),(*AP).AccountKeys))       //比较密码是不是正确
    {
        printf("登录成功！\r\n");
        OU.UsersClass=0;
        OU.OnlineA=AP;
        printf("************************************************************************************************\r\n\r\n");
        return 1;
    }else
    {
        printf("密码错误，请重新登录\r\n");           //密码错误，登录错误计数变量自动加一后退出函数
        *times=*times+1;
        return 0;
    }
}

int UsersLogin()
{
    char AccountNumber[13];     //账号
    char AccountKeys[20];   //密码
    int times=0;

    while(times<3)
    {
    printf("用户账号：");
    //scanf("%s",AccountNumber);
    //getchar();          //将输入的回车号读走
     GetString(AccountNumber,13);
    printf("密码：");
    //scanf("%s",AccountKeys);
    //getchar();          //将输入的回车号读走
    GetKeys(AccountKeys);
    if(Is_U_Existence(AccountNumber,AccountKeys,&times))
    {
        printf("欢迎来到用户界面！\r\n");
        return 1;
    }
    printf("剩余登录次数为%d\r\n\r\n",3-times);
    }

    printf("登录次数用完！\r\n");
    return 0;
}

int Is_U_Existence(char UN[],char UK[],int *times)
{
    UP=UL.head;
    while(strcmp((*UP).AccountNumber,UN)!=0)
    {
        if((*UP).next==NULL)
        {
            printf("账号不存在！\r\n");
            *times=*times+1;
            return 0;
        }else
        {
            UP=(*UP).next;
        }
    }

    if(!strcmp(Encryption(UK),(*UP).AccountKeys))
    {
        printf("登录成功！\r\n");
        OU.UsersClass=1;
        OU.OnlineU=UP;
        printf("************************************************************************************************\r\n\r\n");
        return 1;
    }else
    {
        printf("密码错误，请重新登录\r\n");
        *times=*times+1;
        return 0;
    }
}

void ShowAdministrators()
{
    AP=AL.head;
    printf("%-15s%-15s%-10s%-8s%-4s\r\n","账号","密码","姓名","性别","管理权");
    while((*AP).next!=NULL)
    {
        printf("%-15s%-15s%-10s%-8s%-4d\r\n",(*AP).AccountNumber,(*AP).AccountKeys,(*AP).Name,(*AP).Sex,(*AP).Jurisdiction);
        AP=(*AP).next;
    }
    printf("%-15s%-15s%-10s%-8s%-4d\r\n",(*AP).AccountNumber,(*AP).AccountKeys,(*AP).Name,(*AP).Sex,(*AP).Jurisdiction);
    printf("************************************************************************************************\r\n\r\n");
}
void ShowUsers()
{
    UP=UL.head;
    printf("%-15s%-15s%-10s%-8s%-10s%-15s\r\n","账号","密码","姓名","性别","会员","借用图书数目");
    while((*UP).next!=NULL)
    {
        printf("%-15s%-15s%-10s%-8s%-10d%-15d\r\n",(* UP).AccountNumber,(*UP).AccountKeys,(*UP).Name,(*UP).Sex,(*UP).Leaguer,(*UP).BorrowingNumber);
        UP=(*UP).next;
    }
   printf("%-15s%-15s%-10s%-8s%-10d%-15d\r\n",(* UP).AccountNumber,(*UP).AccountKeys,(*UP).Name,(*UP).Sex,(*UP).Leaguer,(*UP).BorrowingNumber);
   printf("************************************************************************************************\r\n\r\n");
}

void ShowOU()
{
    if(OU.UsersClass!=1)
    {
        printf("出错了！\r\n");
        return -1;
    }
    printf("%-15s%-15s%-10s%-8s%-10s%-15s\r\n","账号","学号","姓名","性别","会员","借用图书数目");
    printf("%-15s%-15s%-10s%-8s%-10d%-15d\r\n",(* (OU.OnlineU)).AccountNumber,(*(OU.OnlineU)).StudentNumber,(*(OU.OnlineU)).Name,(*(OU.OnlineU)).Sex,(*OU.OnlineU).Leaguer,(*OU.OnlineU).BorrowingNumber);
    printf("************************************************************************************************\r\n\r\n");
}

void ShowOA()
{
    if(OU.UsersClass!=0)
    {
        printf("出错了！\r\n");
        return -1;
    }
    printf("%-15s%-15s%-10s%-8s%-10s\r\n","账号","密码","姓名","性别","管理权限");
    printf("%-15s%-15s%-10s%-8s%-10d\r\n",(* (OU.OnlineA)).AccountNumber,(*(OU.OnlineA)).AccountKeys,(*(OU.OnlineA)).Name,(*(OU.OnlineA)).Sex,(*OU.OnlineA).Jurisdiction);
    printf("************************************************************************************************\r\n\r\n");
}

void ChangeMessage()
{
    if(OU.UsersClass==0)
    {
        printf("请输入修改的信息：\r\n");
        printf("密码：");
        //scanf("%s",(*OU.OnlineA).AccountKeys);
       // getchar();
        GetKeys((*OU.OnlineA).AccountKeys);
        Encryption((*OU.OnlineA).AccountKeys);
        printf("姓名：");
        //scanf("%s",(*OU.OnlineA).Name);
        //getchar();
        GetString((*OU.OnlineA).Name,20);
        printf("性别：");
        //scanf("%s",(*OU.OnlineA).Sex);
        //getchar();
        GetString((*OU.OnlineA).Sex,3);
        printf("修改成功！\r\n");
        ALChange=1;
        SaveAL();
    }else if(OU.UsersClass==1)
    {
        printf("请输入修改的信息：\r\n");
        printf("密码：");
        //scanf("%s",(*OU.OnlineU).AccountKeys);
        //getchar();
        GetKeys((*OU.OnlineU).AccountKeys);
        Encryption((*OU.OnlineU).AccountKeys);
        printf("姓名：");
        //scanf("%s",(*OU.OnlineU).Name);
        //getchar();
        GetString((*OU.OnlineU).Name,20);
        printf("性别：");
        //scanf("%s",(*OU.OnlineU).Sex);
        //getchar();
        GetString((*OU.OnlineU).Sex,3);
        printf("学号：");
        //scanf("%s",(*OU.OnlineU).StudentNumber);
        //getchar();
        GetString((*OU.OnlineU).StudentNumber,13);
        printf("修改成功！\r\n");
        ULChange=1;
        SaveUL();
    }else
    {
        printf("出错了！\r\n");
    }
}

int SaveAL()
{
    FILE *fp;

    if(ALChange)
    {
         if((fp=fopen("Administrators.bin","wb"))==NULL)        //打开管理员文件
            {
                printf("打开管理员文件失败！\r\n");
            }
    }else
    {
        return 0;
    }

    if(AL.number==0)
    {
        fclose(fp);
        return 0;
    }else
    {
        AP=AL.head;
        while((*AP).next!=NULL)
            {
                while(fwrite(AP,sizeof(struct Administrators),1,fp)!=1);
                AP=(*AP).next;
            }
        while(fwrite(AP,sizeof(struct Administrators),1,fp)!=1);
        fclose(fp);
        printf("保存成功！\r\n");
        printf("************************************************************************************************\r\n\r\n");
    }

    return 0;
}

int SaveUL()
{
    FILE *fp;

    if(ULChange)
    {
         if((fp=fopen("Users.bin","wb"))==NULL)        //打开用户文件
            {
                printf("打开用户文件失败！\r\n");
            }
    }else
    {
        return 0;
    }

    if(UL.number==0)
    {
        fclose(fp);
        return 0;
    }else
    {
        UP=UL.head;
        while((*UP).next!=NULL)
            {
                while(fwrite(UP,sizeof(struct Users),1,fp)!=1);
                UP=(*UP).next;
            }
        while(fwrite(UP,sizeof(struct Users),1,fp)!=1);
        fclose(fp);
        printf("保存成功！\r\n");
        printf("************************************************************************************************\r\n\r\n");
    }

    return 0;
}

int ShowBorrowing()
{
    int i;
    struct Users *UP1;
    UP1=OU.OnlineU;
    if((*OU.OnlineU).BorrowingNumber==0)
    {
        printf("当前没有借用图书！\r\n");
        printf("************************************************************************************************\r\n\r\n");
        return 0;
    }

    printf("借用的书为\r\n");
    printf("************************************************************************************************\r\n\r\n");
    printf("%-15s%-15s%-10s%-15s%-8s%-8s\r\n","登录号","书名","作者","出版社","分类号","馆藏剩余数量");
    for(i=0;i<(*OU.OnlineU).BorrowingNumber;i++)
    {
        printf("%-15s%-15s%-10s%-15s%-8s%-8d\r\n",(*UP1).Borrowing[i].AccountNumber,(*UP1).Borrowing[i].Name,(*UP1).Borrowing[i].Author,(*UP1).Borrowing[i].Publisher,(*UP1).Borrowing[i].Class,(*UP1).Borrowing[i].RemainingNumber);
    }
    printf("************************************************************************************************\r\n\r\n");
}

int Borrowing()
{
    char c,s[13];
    int i;
    if((*OU.OnlineU).Leaguer!=1)
    {
        printf("你还不是会员，无法借书！\r\n");
        printf("************************************************************************************************\r\n\r\n");
        return 0;
    }
    while(1)
    {
        printf("请输入要借的书的登录号：");
        //scanf("%s",s);
        //getchar();
        GetString(s,13);
        BP=BL.head;
        while((BP!=NULL)&&(strcmp((*BP).AccountNumber,s)!=0))
        {
                BP=(*BP).next;
        }
        if(BP==NULL)
        {
            printf("没有这本书！\r\n");
        }else if(((*OU.OnlineU).BorrowingNumber)>=5)
        {
            printf("你已经达到借书上限，不能再借书");
            return 0;
        }else if((*BP).RemainingNumber==0)
        {
            printf("这本书的剩余数量为0，不能再借了！\r\n");
        }
        else
        {
            printf("要借的书信息为：\r\n");
            ShowBook(BP);
            i=(*OU.OnlineU).BorrowingNumber;
            ((*OU.OnlineU).BorrowingNumber)++;
            strcpy((*OU.OnlineU).Borrowing[i].AccountNumber,(*BP).AccountNumber);
            strcpy((*OU.OnlineU).Borrowing[i].Name,(*BP).Name);
            strcpy((*OU.OnlineU).Borrowing[i].BookNumber,(*BP).BookNumber);
            strcpy((*OU.OnlineU).Borrowing[i].Author,(*BP).Author);
            strcpy((*OU.OnlineU).Borrowing[i].Class,(*BP).Class);
            strcpy((*OU.OnlineU).Borrowing[i].Publisher,(*BP).Publisher);
            strcpy((*OU.OnlineU).Borrowing[i].PublishingTime,(*BP).PublishingTime);
            (*OU.OnlineU).Borrowing[i].Price=(*BP).Price;
            (*BP).RemainingNumber--;
            (*OU.OnlineU).Borrowing[i].RemainingNumber=(*BP).RemainingNumber;
            ULChange=1;
            BLChange=1;
            printf("借书成功！\r\n");
        }
        printf("输入Y继续借书，N退出\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("出错了！\r\n");
            return -1;
        }
    }
    SaveBL();
    SaveUL();
    return 0;
}

int ReturnBook()
{
    char c,s[13];
    int i;
    if(((*OU.OnlineU).BorrowingNumber)==0)
    {
        printf("你当前没有借阅的图书！\r\n");
        return 0;
    }

    //printf("你借阅的书为：\r\n");
    ShowBorrowing();

    while(1)
    {
        printf("请输入要还的书的登录号：");
        //scanf("%s",s);
        //getchar();
        GetString(s,13);
        for(i=0;i<(*OU.OnlineU).BorrowingNumber;++i)
        {
            if( strcmp((*OU.OnlineU).Borrowing[i].AccountNumber,s)==0)
            {
                (*OU.OnlineU).BorrowingNumber--;
                ULChange=1;
                BP=BL.head;
                while((BP!=NULL)&&(strcmp((*BP).AccountNumber,s)!=0))
                {
                    BP=(*BP).next;                      //默认图书馆有这本书
                }
                if((strcmp((*BP).AccountNumber,s)==0))
                {
                    ((*BP).RemainingNumber)++;
                    BLChange=1;
                }
            }else
            {
                if((i+1)==(*OU.OnlineU).BorrowingNumber)
                {
                    printf("你没有借用这本书！\r\n");
                }
            }
        }
        printf("按Y继续，N退出\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("出错了！\r\n");
            return -1;
        }
    }

    SaveBL();
    SaveUL();
    return 0;
}

void ApplyForVIP()
{
    char c;
    FILE *fp;
    printf("按Y申请会员，N不申请会员\r\n");
    c=getch();
    if(c=='Y')
    {
        if((fp=fopen("ApplyForVIP.bin","ab"))==NULL)
        {
            printf("打开会员申请文件失败，注册失败！\r\n");
            return -1;
        }
        while(fwrite((*OU.OnlineU).AccountNumber,13,1,fp)!=1);
        printf("申请成功，等待通过！\r\n");
        fclose(fp);
    }else if(c=='N')
    {
        return 0;
    }else
    {
        printf("输入出错！\r\n");
        return -1;
    }
}

void UserManagement()
{
    int flag,flag1;
    flag1=1;
    while(flag1)
    {
        printf("1、显示所有用户\r\n2、注销会员\r\n3、删除用户\r\n4、退出\r\n");
        scanf("%d",&flag);
        getchar();
        switch(flag)
        {
        case 1:
            ShowUsers();
            break;
        case 2:
            CancleVIP();
            break;
        case 3:
            DeleteUsers();
            break;
        case 4:
            flag1=0;
            break;
        }
    }
}

void CancleVIP()
{
    char c,s[13];
    while(1)
    {
        printf("要注销会员的用户账号：");
        //scanf("%s",s);
        //getchar();
         GetString(s,13);
        UP=UL.head;
        while((UP!=NULL)&&(strcmp((*UP).AccountNumber,s)!=0))       //遍历用户链表
        {
            UP=(*UP).next;
        }
        if(UP==NULL)
        {
            printf("没有此会员！\r\n");
        }else
        {
            (*UP).Leaguer=0;                    //修改会员标志
            ULChange=1;
            printf("注销成功！\r\n");
        }
        printf("按Y继续，N退出\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("出错了！\r\n");
            return -1;
        }
    }
    SaveUL();           //有修改用户表就保存，在函数里会判断有没有修改用户表
}

void DeleteUsers()
{
    char c,s[13];
    struct Users *UP1,*UP2;
    while(1)
    {
        printf("请输入要删除用户的账号：");
        //scanf("%s",s);
        //getchar();
         GetString(s,13);
        UP1=UP2=UL.head;
        if(strcmp((*UP2).AccountNumber,s)==0)
        {
            UP=UL.head;
            UL.head=(*UP).next;
            UL.number--;
            free(UP);
            printf("删除成功！\r\n");
            ULChange=1;
        }else
        {
            UP2=(*UP2).next;
            while((UP2!=NULL)&&(strcmp((*UP2).AccountNumber,s)!=0))
            {
                UP1=(*UP1).next;
                UP2=(*UP2).next;
            }

            if(UP2==NULL)
            {
                if(strcmp((*UP2).AccountNumber,s)==0)
                {
                    (*UP1).next=NULL;
                    BL.rear=UP1;
                    BL.number--;
                    free(UP2);
                    printf("删除成功！\r\n");
                    ULChange=1;
                }else
                {
                    printf("没有这本书！\r\n");
                }
            }else
            {
                (*UP1).next=(*UP2).next;
                free(UP2);
                BL.number--;
                printf("删除成功！\r\n");
                ULChange=1;
            }
        }
        printf("按Y继续，N退出\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("出错了！\r\n");
            return -1;
        }
    }
    SaveUL();
}

void UserRegistration()
{
    struct Users *UP1;
    UP1=(struct Users*)malloc(sizeof(struct Users));
    printf("账号：");
    //scanf("%s",(*UP1).AccountNumber);
    //getchar();
     GetString((*UP1).AccountNumber,13);
    printf("密码：");
    //scanf("%s",(*UP1).AccountKeys);
    GetKeys((*UP1).AccountKeys);
    Encryption((*UP1).AccountKeys);
    //getchar();
    printf("姓名：");
    //scanf("%s",(*UP1).Name);
   // getchar();
    GetString((*UP1).Name,20);
    printf("性别：");
    //scanf("%s",(*UP1).Sex);
    //getchar();
    GetString((*UP1).Sex,3);
    printf("学号：");
    //scanf("%s",(*UP1).StudentNumber);
    //getchar();
    GetString((*UP1).StudentNumber,13);
    (*UP1).Leaguer=0;
    (*UP1).BorrowingNumber=0;
    (*UP1).next=NULL;
    (*UL.rear).next=UP1;
    UL.rear=UP1;
    UL.number++;
    ULChange=1;
    SaveUL();
    printf("注册成功！\r\n");
    printf("************************************************************************************************\r\n\r\n");
}

void ADRegistration()
{
    struct Administrators *AP1;
    FILE *fp;
    AP1=(struct Administrators*)malloc(sizeof(struct Administrators));
    printf("账号：");
    //scanf("%s",(*AP1).AccountNumber);
    //getchar();
     GetString((*AP1).AccountNumber,13);
    printf("密码：");
    //scanf("%s",(*AP1).AccountKeys);
    GetKeys((*AP1).AccountKeys);
    Encryption((*AP1).AccountKeys);
    //getchar();
    printf("姓名：");
    //scanf("%s",(*AP1).Name);
    //getchar();
    GetString((*AP1).Name,20);
    printf("性别：");
    //scanf("%s",(*AP1).Sex);
    //getchar();
    GetString((*AP1).Sex,3);
    (*AP1).Jurisdiction=0;

    if((fp=fopen("ADRegistration.bin","ab"))==NULL)
    {
        printf("打开管理员注册文件失败，注册失败！\r\n");
        return -1;
    }

    while(fwrite(AP1,sizeof(struct Administrators),1,fp)!=1);
    printf("注册成功，等待通过！\r\n");
    printf("************************************************************************************************\r\n\r\n");
    fclose(fp);
    return 0;
}

void Auditing()
{
    int flag;
    int flag1=1;
    while(flag1)
    {
        printf("1、会员申请审核\r\n2、管理员注册审核\r\n3、退出\r\n");
        scanf("%d",&flag);
        getchar();
        switch(flag)
        {
        case 1:
            AuditingVIP();
            break;
        case 2:
            AuditingAD();
            break;
        case 3:
            flag1=0;
            break;
        default :
            break;
        }
    }
}

int AuditingVIP()
{
    FILE *fp;
    char c,s[13];
    if((fp=fopen("ApplyForVIP.bin","rb"))==NULL)
    {
        printf("打开会员申请文件失败！\r\n");
        return -1;
    }

    while(feof(fp)==0)
    {
        if(fread(s,13,1,fp)==1)      //读取文件正确
        {
            UP=UL.head;
            while((UP!=NULL)&&(strcmp((*UP).AccountNumber,s)!=0))   //寻找该用户资料
            {
                UP=(*UP).next;
            }

            if(UP==NULL)
            {
                printf("出错了！\r\n");
                continue;
            }else
            {
                printf("要申请会员的用户资料：\r\n");
                printf("************************************************************************************************\r\n\r\n");
                printf("%-15s%-15s%-10s%-8s%-10s%-15s\r\n","账号","密码","姓名","性别","会员","借用图书数目");
                printf("%-15s%-15s%-10s%-8s%-10d%-15d\r\n",(* UP).AccountNumber,(*UP).AccountKeys,(*UP).Name,(*UP).Sex,(*UP).Leaguer,(*UP).BorrowingNumber);
                printf("************************************************************************************************\r\n\r\n");
                printf("按Y通过申请，N不通过\r\n");

                while(1)
                {
                    c=getch();
                    if(c=='Y')
                    {
                        (*UP).Leaguer=1;
                        ULChange=1;
                        break;
                    }else if(c=='N')
                    {
                        continue;
                        break;
                    }else
                    {
                        printf("输入错误,请再输入！\r\n");
                        continue;
                    }
                }
            }
        }
    }
    SaveUL();
    printf("已经没有要申请会员的用户了！\r\n");
    fclose(fp);

    if((fp=fopen("ApplyForVIP.bin","wb"))==NULL)
    {
        printf("打开会员申请文件失败！\r\n");
        return -1;
    }
    fclose(fp);
    return 0;
}
int AuditingAD()
{
    FILE *fp;
    char c;
    struct Administrators *AP1;
    if((fp=fopen("ADRegistration.bin","rb"))==NULL)
    {
        printf("打开管理员注册文件失败，注册失败！\r\n");
        return -1;
    }
    while(feof(fp)==0)
    {
        AP1=(struct Administrators*)malloc(sizeof(struct Administrators));
        if(fread(AP1,sizeof(struct Administrators),1,fp)==1)
        {
            printf("要申请管理员的用户信息：\r\n");
            printf("************************************************************************************************\r\n\r\n");
            printf("%-15s%-15s%-10s%-8s%-4s\r\n","账号","密码","姓名","性别","管理权");
            printf("%-15s%-15s%-10s%-8s%-4d\r\n",(*AP1).AccountNumber,(*AP1).AccountKeys,(*AP1).Name,(*AP1).Sex,(*AP1).Jurisdiction);
            printf("************************************************************************************************\r\n\r\n");
            printf("按Y通过，N不通过\r\n");
            while(1)
            {
                c=getch();
                if(c=='Y')
                {
                    (*AP1).next=NULL;
                    AL.number++;
                    (*AL.rear).next=AP1;
                    AL.rear=AP1;
                    ALChange=1;
                    break;
                }else if(c=='N')
                {
                    break;
                }else
                {
                    printf("输入出错，请从新输入！\r\n");
                }
            }
        }else
        {
            free(AP1);
        }
    }
    fclose(fp);
    if((fp=fopen("ADRegistration.bin","wb"))==NULL)
    {
        printf("打开管理员注册文件失败，注册失败！\r\n");    //清空文件
        return -1;
    }
    fclose(fp);
    printf("已经没有用户申请管理员了！\r\n");
    SaveAL();
    return 0;
}

void GetKeys(char s[])
{
    char c;
    int i=0;
    while((c=getch())!='\r')
    {
        if(i<13)
        {
            putchar('*');
            s[i]=c;
            i++;
        }else
        {
            printf("\r\n输入超过了密码限定的字符数，请重新输入！\r\n");
            i=0;
        }
    }
    s[i]='\0';
    putchar('\n');
}
