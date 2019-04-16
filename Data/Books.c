#include "Books.h"

struct Books *BP;
struct BooksList BL;
int BLChange=0;
struct SearchResult Result;     //搜索结果的表头

int BooksLoad()
{
    FILE *fp;

    if((fp=fopen("Books.bin","rb"))==NULL)        //打开图书文件
    {
        printf("打开图书文件失败！\r\n");
    }

    fseek(fp,0L,SEEK_END);      //将指针移动到文件结尾

    if(ftell(fp)==0)
    {
        BL.head=NULL;
        BL.rear=NULL;
        BL.number=0;
        printf("没有图书！\r\n");       //判断文件的大小
        return -1;
    }
    else
    {
        rewind(fp);
        BP=BL.head=(struct Books*)malloc(sizeof(struct Books));   //准备读取数据

        while(fread(BP,sizeof(struct Books),1,fp)!=1);      //直到读到数据为止，防止读文件时出错引起错误

        (*BP).next=NULL;      //指针指向链表结尾
        BL.rear=BP;
        BL.number=1;        //至少有一本书
    }

    while(feof(fp)==0)
    {
        //fread(((*BP).next=(struct Books*)malloc(sizeof(struct Books))),sizeof(struct Books),1,fp);
        //feof((fp)==0);
        (*BP).next=(struct Books*)malloc(sizeof(struct Books));
        if(fread((*BP).next,sizeof(struct Books),1,fp)==1)      //读取文件正确，将数据连接上链表
        {
        BP=(*BP).next;        //BP指向下一本书
        (*BP).next=NULL;      //指向链表的结尾
        BL.rear=BP;
        BL.number++;
        }else
        {
            free((*BP).next);           //否则，释放掉刚才分配的空间
            (*BP).next=NULL;             //(*BP).next重新指向链表结尾
        }
    }
    fp=fclose(fp);
    return 0;
}

int BooksInput()
{
    struct Books *Book;
    char flag;

    while(1)
    {
        Book=(struct Books*)malloc(sizeof(struct Books));

        printf("登录号：");
        //scanf("%s",(*Book).AccountNumber);
        //getchar();
        GetString((*Book).AccountNumber,13);
        printf("书名：");
        //scanf("%s",(*Book).Name);
        //getchar();
        GetString((*Book).Name,30);
        printf("图书编号：");
        //scanf("%s",(*Book).BookNumber);
        //getchar();
        GetString((*Book).BookNumber,13);
        printf("单价：");
        scanf("%d",&((*Book).Price));
        getchar();
        printf("作者：");
       // scanf("%s",(*Book).Author);
        //getchar();
        GetString((*Book).Author,20);
        printf("分类号：");
        //scanf("%s",(*Book).Class);
        //getchar();
        GetString((*Book).Class,13);
        printf("出版单位：");
        //scanf("%s",(*Book).Publisher);
        //getchar();
        GetString((*Book).Publisher,30);
        printf("出版时间：");
        //scanf("%s",(*Book).PublishingTime);
        //getchar();
        GetString((*Book).PublishingTime,15);
        printf("馆藏剩余数目：");
        scanf("%d",&((*Book).RemainingNumber));
        getchar();

        if(BL.number==0)
        {
            (*Book).next=NULL;
            BL.head=Book;
            BL.rear=Book;
            BL.number++;
        }else
        {
        (*Book).next=NULL;
        (*(BL.rear)).next=Book;    //将新书加入到图书链表的尾部
        BL.rear=Book;
        BL.number++;
        }
        BL.number++;
        printf("Y继续录入，N保存");
        scanf("%c",&flag);
        getchar();
        if(flag=='N')
        {
            BLChange=1;         //图书链表修改标志置位
            return 0;
        }
    }
}

int SaveBL()
{
    FILE *fp;
    SorttingByName();       //先排序再保存

    if(BLChange)
    {
         if((fp=fopen("Books.bin","wb"))==NULL)        //打开图书文件
            {
                printf("打开图书文件失败！\r\n");
            }
    }else
    {
        return 0;
    }

    if(BL.number==0)
    {
        fclose(fp);
        return 0;
    }else
    {
        BP=BL.head;
        while((*BP).next!=NULL)
            {
                while(fwrite(BP,sizeof(struct Books),1,fp)!=1);
                BP=(*BP).next;
            }
        while(fwrite(BP,sizeof(struct Books),1,fp)!=1);
        printf("保存成功！\r\n");
        printf("************************************************************************************************\r\n\r\n");
    }

    fclose(fp);
    return 0;
}

void ShowBooks()
{
    BP=BL.head;
    printf("%-15s%-20s%-20s%-20s%-8s%-8s\r\n","登录号","书名","作者","出版社","分类号","馆藏剩余数量");
    while((*BP).next!=NULL)
    {
        printf("%-15s%-20s%-20s%-20s%-8s%-8d\r\n",(*BP).AccountNumber,(*BP).Name,(*BP).Author,(*BP).Publisher,(*BP).Class,(*BP).RemainingNumber);
        BP=(*BP).next;
    }
    printf("%-15s%-20s%-20s%-20s%-8s%-8d\r\n",(*BP).AccountNumber,(*BP).Name,(*BP).Author,(*BP).Publisher,(*BP).Class,(*BP).RemainingNumber);
    printf("************************************************************************************************\r\n\r\n");
}

void ShowBook(struct Books *Book)
{
    printf("%-15s%-20s%-20s%-20s%-8s%-8s\r\n","登录号","书名","作者","出版社","分类号","馆藏剩余数量");
    printf("%-15s%-20s%-20s%-20s%-8s%-8d\r\n",(*Book).AccountNumber,(*Book).Name,(*Book).Author,(*Book).Publisher,(*Book).Class,(*Book).RemainingNumber);
    printf("************************************************************************************************\r\n\r\n");
}

void DeleteBooks()          //该函数要和SearchByAN()一同使用才可以，否则会出错；
{
    struct SearchResult *RP;
    RP=Result.next;     //RP指向下一个搜索结果
    if((*RP).Book==BL.rear)
    {
        free((*RP).Book);
        (*Result.Book).next=NULL;
    }else if((*RP).Book==BL.head)
    {
        BL.head=(*BL.head).next;
        free((*RP).Book);
    }else
    {
        (*Result.Book).next=(*(*RP).Book).next;
        free((*RP).Book);
    }
    BL.number--;
    printf("删除成功！\r\n");
}

int SearchByAN(char s[])
{
    struct Books *BP1,*BP2;
    struct SearchResult *RP;
    BP1=BP2=BL.head;
    Result.next=(struct SearchResult*)malloc(sizeof(struct SearchResult));
    RP=Result.next;
    (*RP).next=NULL;     //搜索结果就只有两个，所以第二个的next就指向了链表的结尾
    if(strcmp((*BP2).AccountNumber,s)==0)
    {
        Result.Book=BP1;
        (*RP).Book=BP2;
        return 1;
    }else
    {
        BP2=(*BP2).next;
    }
    while(strcmp((*BP2).AccountNumber,s)!=0)
    {
        if((*BP2).next==NULL)
        {
            printf("没有这本书。\r\n");
            Result.Book=NULL;
            (*RP).Book=NULL;
            return 0;       //搜索到最后都没有找到，说明不存在，放回0
        }else
        {
            BP1=(*BP1).next;        //指针同时向后移动一位
            BP2=(*BP2).next;
        }
    }

    Result.Book=BP1;
    (*RP).Book=BP2;
    return 1;
}

int FreeResult()
{
    struct SearchResult *RP1,*RP2;
    RP1=Result.next;
    RP2=Result.next;
    if(RP1==NULL)
    {
        return 0;
    }
    if((*RP1).next==NULL)
    {
        free(RP1);
        return 0;
    }else
    {
        RP1=(*RP1).next;
    }

    while((*RP1).next!=NULL)
    {
        free(RP2);
        RP2=RP1;
        RP1=(*RP1).next;
    }

    free(RP1);
    free(RP2);
    Result.next=NULL;
    return 0;
}

void ShowResult()
{
    struct SearchResult *RP;
    struct Books *BP3;
    RP=&Result;

    printf("搜索结果为：\r\n");
    printf("************************************************************************************************\r\n\r\n");
    printf("%-15s%-20s%-20s%-20s%-8s%-8s\r\n","登录号","书名","作者","出版社","分类号","馆藏剩余数量");
    //printf("%-15s%-15s%-10s%-15s%-8s%-8d\r\n",(*Book).AccountNumber,(*Book).Name,(*Book).Author,(*Book).Publisher,(*Book).Class,(*Book).RemainingNumber);
    while((*RP).next!=NULL)
    {
        BP3=(*RP).Book;
        printf("%-15s%-20s%-20s%-20s%-8s%-8d\r\n",(*BP3).AccountNumber,(*BP3).Name,(*BP3).Author,(*BP3).Publisher,(*BP3).Class,(*BP3).RemainingNumber);
        RP=(*RP).next;
    }
     BP3=(*RP).Book;
     printf("%-15s%-20s%-20s%-20s%-8s%-8d\r\n",(*BP3).AccountNumber,(*BP3).Name,(*BP3).Author,(*BP3).Publisher,(*BP3).Class,(*BP3).RemainingNumber);
    printf("************************************************************************************************\r\n\r\n");
}

void SorttingByName()
{
    int flag;
    struct Books *BP1,*BP2,*BP3;
    BP1=(*BL.head).next;
    flag=CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BL.head).Name,-1,(*BP1).Name,-1);
    if(flag==3)
    {
        BP=(*BP1).next;
        (*BP1).next=BL.head;
        (*BL.head).next=NULL;
        BL.rear=BL.head;
        BL.head=BP1;
        BP1=(*BP1).next;
    }
    else
    {
        BP=(*BP1).next;
        (*BP1).next=NULL;
        BL.rear=BP1;
        BP1=BP;
    }
    BP2=BL.head;          //由于是单向链表，要两个指针才能进行插入
    BP3=(*BL.head).next;

    flag=1;
    while(flag)
    {
        BP2=BL.head;          //由于是单向链表，要两个指针才能进行插入
        BP3=(*BL.head).next;
        if((*BP1).next==NULL)
        {
            flag=0;
        }
        if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Name,-1,(*BP2).Name,-1)==1)
        {
            BP=(*BP1).next;     //将没有排序的头保存起来
            BL.head=BP1;        //BP1连接到头
            (*BP1).next=BP2;    //头在连接会之前拍好顺序的链表
            BP1=BP;         //BP1重新指向未排序的头
            continue;       //排下一个成员
        }

        while(((*BP3).next!=NULL)&&(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Name,-1,(*BP3).Name,-1)!=1))     //找到BP1<BP3
        {
            BP2=(*BP2).next;
            BP3=(*BP3).next;
        }

        if((*BP3).next==NULL)
        {
            if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Name,-1,(*BP3).Name,-1)==3)
            {
                BP=(*BP1).next;
                (*BP3).next=BP1;            //BP1比最后一个元素还打，接到最后面
                (*BP1).next=NULL;
                BL.rear=BP1;
                BP1=BP;
                continue;
            }
        }

        BP=(*BP1).next;
        (*BP2).next=BP1;       //否则，将BP1连接到BP2与BP3之间
        (*BP1).next=BP3;
        BP1=BP;
    }
    //BLChange=1;
}

void SorttingByClass()
{
    int flag;
    struct Books *BP1,*BP2,*BP3;
    BP1=(*BL.head).next;
    flag=CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BL.head).Class,-1,(*BP1).Class,-1);
    if(flag==3)
    {
        BP=(*BP1).next;
        (*BP1).next=BL.head;
        (*BL.head).next=NULL;
        BL.rear=BL.head;
        BL.head=BP1;
        BP1=(*BP1).next;
    }
    else
    {
        BP=(*BP1).next;
        (*BP1).next=NULL;
        BL.rear=BP1;
        BP1=BP;
    }
    BP2=BL.head;          //由于是单向链表，要两个指针才能进行插入
    BP3=(*BL.head).next;

    flag=1;
    while(flag)
    {
        BP2=BL.head;          //由于是单向链表，要两个指针才能进行插入
        BP3=(*BL.head).next;
        if((*BP1).next==NULL)
        {
            flag=0;
        }
        if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Class,-1,(*BP2).Class,-1)==1)
        {
            BP=(*BP1).next;     //将没有排序的头保存起来
            BL.head=BP1;        //BP1连接到头
            (*BP1).next=BP2;    //头在连接会之前拍好顺序的链表
            BP1=BP;         //BP1重新指向未排序的头
            continue;       //排下一个成员
        }

        while(((*BP3).next!=NULL)&&(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Class,-1,(*BP3).Class,-1)!=1))     //找到BP1<BP3
        {
            BP2=(*BP2).next;
            BP3=(*BP3).next;
        }

        if((*BP3).next==NULL)
        {
            if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Class,-1,(*BP3).Class,-1)==3)
            {
                BP=(*BP1).next;
                (*BP3).next=BP1;            //BP1比最后一个元素还打，接到最后面
                (*BP1).next=NULL;
                BL.rear=BP1;
                BP1=BP;
                continue;
            }
        }

        BP=(*BP1).next;
        (*BP2).next=BP1;       //否则，将BP1连接到BP2与BP3之间
        (*BP1).next=BP3;
        BP1=BP;
    }
}

void SorttingByAuthor()
{
    int flag;
    struct Books *BP1,*BP2,*BP3;
    BP1=(*BL.head).next;
    flag=CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BL.head).Author,-1,(*BP1).Author,-1);
    if(flag==3)
    {
        BP=(*BP1).next;
        (*BP1).next=BL.head;
        (*BL.head).next=NULL;
        BL.rear=BL.head;
        BL.head=BP1;
        BP1=(*BP1).next;
    }
    else
    {
        BP=(*BP1).next;
        (*BP1).next=NULL;
        BL.rear=BP1;
        BP1=BP;
    }
    BP2=BL.head;          //由于是单向链表，要两个指针才能进行插入
    BP3=(*BL.head).next;

    flag=1;
    while(flag)
    {
        BP2=BL.head;          //由于是单向链表，要两个指针才能进行插入
        BP3=(*BL.head).next;
        if((*BP1).next==NULL)
        {
            flag=0;
        }
        if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Author,-1,(*BP2).Author,-1)==1)
        {
            BP=(*BP1).next;     //将没有排序的头保存起来
            BL.head=BP1;        //BP1连接到头
            (*BP1).next=BP2;    //头在连接会之前拍好顺序的链表
            BP1=BP;         //BP1重新指向未排序的头
            continue;       //排下一个成员
        }

        while(((*BP3).next!=NULL)&&(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Author,-1,(*BP3).Author,-1)!=1))     //找到BP1<BP3
        {
            BP2=(*BP2).next;
            BP3=(*BP3).next;
        }

        if((*BP3).next==NULL)
        {
            if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Author,-1,(*BP3).Author,-1)==3)
            {
                BP=(*BP1).next;
                (*BP3).next=BP1;            //BP1比最后一个元素还打，接到最后面
                (*BP1).next=NULL;
                BL.rear=BP1;
                BP1=BP;
                continue;
            }
        }

        BP=(*BP1).next;
        (*BP2).next=BP1;       //否则，将BP1连接到BP2与BP3之间
        (*BP1).next=BP3;
        BP1=BP;
    }
}

void SearchBook()
{
    int flag;
    char c;
    char s[30];
    struct SearchResult *RP,*RP1;   //RP1指向搜索结果的结尾

    while(1)
    {
    printf("请选择搜索方式：\r\n1、按书名搜索\r\n2、按作者名搜索\r\n3、按分类号搜索\r\n");
    scanf("%d",&flag);
    getchar();
    switch(flag)
    {
    case 1:
        printf("书名：");
        //scanf("%s",s);
        //getchar();
        GetString(s,30);
        BP=BL.head;
        while(((*BP).next!=NULL)&&strcmp(s,(*BP).Name))   //搜索是否有这本书，有后搜索到最后就退出
        {
            BP=(*BP).next;
        }
        if(strcmp(s,(*BP).Name)==0)   //至少有一本书
        {
            Result.Book=BP;
            Result.next=NULL;
            RP1=&Result;
        }else
        {
            printf("没有这本书！\r\n");
            break;
        }
        BP=(*BP).next;
        while(BP!=NULL)
        {
            if(strcmp(s,(*BP).Name)==0)
            {
                RP=(struct SearchResult*)malloc(sizeof(struct SearchResult));
                (*RP).Book=BP;
                (*RP).next=NULL;    //创建搜索结果
                (*RP1).next=RP;     //将结果连接到结果链表尾部
                RP1=RP;             //指向尾部
            }
            BP=(*BP).next;
        }
        ShowResult();
        FreeResult();
        break;
    case 2:
        printf("作者名：");
        //scanf("%s",s);
        //getchar();
        GetString(s,20);
        BP=BL.head;
        while(((*BP).next!=NULL)&&strcmp(s,(*BP).Author))   //搜索是否有这本书，有后搜索到最后就退出
        {
            BP=(*BP).next;
        }
        if(strcmp(s,(*BP).Author)==0)   //至少有一本书
        {
            Result.Book=BP;
            Result.next=NULL;
            RP1=&Result;
        }else
        {
            printf("没有这本书！\r\n");
            break;
        }
        BP=(*BP).next;
        while(BP!=NULL)
        {
            if(strcmp(s,(*BP).Author)==0)
            {
                RP=(struct SearchResult*)malloc(sizeof(struct SearchResult));
                (*RP).Book=BP;
                (*RP).next=NULL;    //创建搜索结果
                (*RP1).next=RP;     //将结果连接到结果链表尾部
                RP1=RP;             //指向尾部
            }
            BP=(*BP).next;
        }
        ShowResult();
        FreeResult();
        break;
    case 3:
        printf("分类号：");
        //scanf("%s",s);
        //getchar();
        GetString(s,13);
        BP=BL.head;
        while(((*BP).next!=NULL)&&strcmp(s,(*BP).Class))   //搜索是否有这本书，有后搜索到最后就退出
        {
            BP=(*BP).next;
        }
        if(strcmp(s,(*BP).Class)==0)   //至少有一本书
        {
            Result.Book=BP;
            Result.next=NULL;
            RP1=&Result;
        }else
        {
            printf("没有这本书！\r\n");
            break;
        }
        BP=(*BP).next;
        while(BP!=NULL)
        {
            if(strcmp(s,(*BP).Class)==0)
            {
                RP=(struct SearchResult*)malloc(sizeof(struct SearchResult));
                (*RP).Book=BP;
                (*RP).next=NULL;    //创建搜索结果
                (*RP1).next=RP;     //将结果连接到结果链表尾部
                RP1=RP;             //指向尾部
            }
            BP=(*BP).next;
        }
        ShowResult();
        FreeResult();
        break;
    default :
        break;
    }
    printf("输入Y继续，N退出\r\n");
    scanf("%c",&c);
    getchar();
    if(c=='N')
    {
        break;
    }
    }
}

void ChangeBook()
{
    char c,s[13];
    while(1)
    {
        printf("请输入要修改图书的登录号:");
        //scanf("%s",s);
        //getchar();
        GetString(s,13);
        BP=BL.head;
        while((BP!=NULL)&&strcmp(s,(*BP).AccountNumber)!=0)
        {
            BP=(*BP).next;
        }
        if(BP==NULL)
        {
            printf("没有这本书！\r\n");
        }else
        {
            printf("要修改的书的信息：\r\n\r\n");

            printf("************************************************************************************************\r\n\r\n");
            ShowBook(BP);
            printf("登录号：");
            //scanf("%s",(*BP).AccountNumber);
            //getchar();
            GetString((*BP).AccountNumber,13);
            printf("书名：");
            //scanf("%s",(*BP).Name);
            //getchar();
            GetString((*BP).Name,30);
            printf("图书编号：");
            //scanf("%s",(*BP).BookNumber);
           // getchar();
           GetString((*BP).BookNumber,13);
            printf("单价：");
            scanf("%d",&((*BP).Price));
            getchar();
            printf("作者：");
            //scanf("%s",(*BP).Author);
            //getchar();
            GetString((*BP).Author,20);
            printf("分类号：");
            //scanf("%s",(*BP).Class);
            //getchar();
            GetString((*BP).Class,13);
            printf("出版单位：");
            //scanf("%s",(*BP).Publisher);
            //getchar();
            GetString((*BP).Publisher,30);
            printf("出版时间：");
            //scanf("%s",(*BP).PublishingTime);
           // getchar();
            GetString((*BP).PublishingTime,15);
            printf("馆藏剩余数目：");
            scanf("%d",&((*BP).RemainingNumber));
            getchar();
        }
        printf("修改成功！\r\按Y继续修改，N退出\r\n");
        scanf("%c",&c);
        getchar();
        if(c=='N')
        {
            break;
        }
    }
    BLChange=1;
    SaveBL();
}

void GetString(char s[],int Size)
{
    char c;
    int i=0;
    while((c=getch())!='\r')
    {
        if(i<Size)
        {
            s[i]=c;
            i++;
            putchar(c);
        }else
        {
            printf("\r\n输入超过了限定字符数，请重新输入！\r\n");
            i=0;
        }
    }
    s[i]='\0';
    putchar('\n');
}
