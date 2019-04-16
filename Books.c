#include "Books.h"

struct Books *BP;
struct BooksList BL;
int BLChange=0;
struct SearchResult Result;     //��������ı�ͷ

int BooksLoad()
{
    FILE *fp;

    if((fp=fopen("Books.bin","rb"))==NULL)        //��ͼ���ļ�
    {
        printf("��ͼ���ļ�ʧ�ܣ�\r\n");
    }

    fseek(fp,0L,SEEK_END);      //��ָ���ƶ����ļ���β

    if(ftell(fp)==0)
    {
        BL.head=NULL;
        BL.rear=NULL;
        BL.number=0;
        printf("û��ͼ�飡\r\n");       //�ж��ļ��Ĵ�С
        return -1;
    }
    else
    {
        rewind(fp);
        BP=BL.head=(struct Books*)malloc(sizeof(struct Books));   //׼����ȡ����

        while(fread(BP,sizeof(struct Books),1,fp)!=1);      //ֱ����������Ϊֹ����ֹ���ļ�ʱ�����������

        (*BP).next=NULL;      //ָ��ָ�������β
        BL.rear=BP;
        BL.number=1;        //������һ����
    }

    while(feof(fp)==0)
    {
        //fread(((*BP).next=(struct Books*)malloc(sizeof(struct Books))),sizeof(struct Books),1,fp);
        //feof((fp)==0);
        (*BP).next=(struct Books*)malloc(sizeof(struct Books));
        if(fread((*BP).next,sizeof(struct Books),1,fp)==1)      //��ȡ�ļ���ȷ������������������
        {
        BP=(*BP).next;        //BPָ����һ����
        (*BP).next=NULL;      //ָ������Ľ�β
        BL.rear=BP;
        BL.number++;
        }else
        {
            free((*BP).next);           //�����ͷŵ��ղŷ���Ŀռ�
            (*BP).next=NULL;             //(*BP).next����ָ�������β
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

        printf("��¼�ţ�");
        //scanf("%s",(*Book).AccountNumber);
        //getchar();
        GetString((*Book).AccountNumber,13);
        printf("������");
        //scanf("%s",(*Book).Name);
        //getchar();
        GetString((*Book).Name,30);
        printf("ͼ���ţ�");
        //scanf("%s",(*Book).BookNumber);
        //getchar();
        GetString((*Book).BookNumber,13);
        printf("���ۣ�");
        scanf("%d",&((*Book).Price));
        getchar();
        printf("���ߣ�");
       // scanf("%s",(*Book).Author);
        //getchar();
        GetString((*Book).Author,20);
        printf("����ţ�");
        //scanf("%s",(*Book).Class);
        //getchar();
        GetString((*Book).Class,13);
        printf("���浥λ��");
        //scanf("%s",(*Book).Publisher);
        //getchar();
        GetString((*Book).Publisher,30);
        printf("����ʱ�䣺");
        //scanf("%s",(*Book).PublishingTime);
        //getchar();
        GetString((*Book).PublishingTime,15);
        printf("�ݲ�ʣ����Ŀ��");
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
        (*(BL.rear)).next=Book;    //��������뵽ͼ�������β��
        BL.rear=Book;
        BL.number++;
        }
        BL.number++;
        printf("Y����¼�룬N����");
        scanf("%c",&flag);
        getchar();
        if(flag=='N')
        {
            BLChange=1;         //ͼ�������޸ı�־��λ
            return 0;
        }
    }
}

int SaveBL()
{
    FILE *fp;
    SorttingByName();       //�������ٱ���

    if(BLChange)
    {
         if((fp=fopen("Books.bin","wb"))==NULL)        //��ͼ���ļ�
            {
                printf("��ͼ���ļ�ʧ�ܣ�\r\n");
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
        printf("����ɹ���\r\n");
        printf("************************************************************************************************\r\n\r\n");
    }

    fclose(fp);
    return 0;
}

void ShowBooks()
{
    BP=BL.head;
    printf("%-15s%-20s%-20s%-20s%-8s%-8s\r\n","��¼��","����","����","������","�����","�ݲ�ʣ������");
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
    printf("%-15s%-20s%-20s%-20s%-8s%-8s\r\n","��¼��","����","����","������","�����","�ݲ�ʣ������");
    printf("%-15s%-20s%-20s%-20s%-8s%-8d\r\n",(*Book).AccountNumber,(*Book).Name,(*Book).Author,(*Book).Publisher,(*Book).Class,(*Book).RemainingNumber);
    printf("************************************************************************************************\r\n\r\n");
}

void DeleteBooks()          //�ú���Ҫ��SearchByAN()һͬʹ�òſ��ԣ���������
{
    struct SearchResult *RP;
    RP=Result.next;     //RPָ����һ���������
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
    printf("ɾ���ɹ���\r\n");
}

int SearchByAN(char s[])
{
    struct Books *BP1,*BP2;
    struct SearchResult *RP;
    BP1=BP2=BL.head;
    Result.next=(struct SearchResult*)malloc(sizeof(struct SearchResult));
    RP=Result.next;
    (*RP).next=NULL;     //���������ֻ�����������Եڶ�����next��ָ��������Ľ�β
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
            printf("û���Ȿ�顣\r\n");
            Result.Book=NULL;
            (*RP).Book=NULL;
            return 0;       //���������û���ҵ���˵�������ڣ��Ż�0
        }else
        {
            BP1=(*BP1).next;        //ָ��ͬʱ����ƶ�һλ
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

    printf("�������Ϊ��\r\n");
    printf("************************************************************************************************\r\n\r\n");
    printf("%-15s%-20s%-20s%-20s%-8s%-8s\r\n","��¼��","����","����","������","�����","�ݲ�ʣ������");
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
    BP2=BL.head;          //�����ǵ�������Ҫ����ָ����ܽ��в���
    BP3=(*BL.head).next;

    flag=1;
    while(flag)
    {
        BP2=BL.head;          //�����ǵ�������Ҫ����ָ����ܽ��в���
        BP3=(*BL.head).next;
        if((*BP1).next==NULL)
        {
            flag=0;
        }
        if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Name,-1,(*BP2).Name,-1)==1)
        {
            BP=(*BP1).next;     //��û�������ͷ��������
            BL.head=BP1;        //BP1���ӵ�ͷ
            (*BP1).next=BP2;    //ͷ�����ӻ�֮ǰ�ĺ�˳�������
            BP1=BP;         //BP1����ָ��δ�����ͷ
            continue;       //����һ����Ա
        }

        while(((*BP3).next!=NULL)&&(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Name,-1,(*BP3).Name,-1)!=1))     //�ҵ�BP1<BP3
        {
            BP2=(*BP2).next;
            BP3=(*BP3).next;
        }

        if((*BP3).next==NULL)
        {
            if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Name,-1,(*BP3).Name,-1)==3)
            {
                BP=(*BP1).next;
                (*BP3).next=BP1;            //BP1�����һ��Ԫ�ػ��򣬽ӵ������
                (*BP1).next=NULL;
                BL.rear=BP1;
                BP1=BP;
                continue;
            }
        }

        BP=(*BP1).next;
        (*BP2).next=BP1;       //���򣬽�BP1���ӵ�BP2��BP3֮��
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
    BP2=BL.head;          //�����ǵ�������Ҫ����ָ����ܽ��в���
    BP3=(*BL.head).next;

    flag=1;
    while(flag)
    {
        BP2=BL.head;          //�����ǵ�������Ҫ����ָ����ܽ��в���
        BP3=(*BL.head).next;
        if((*BP1).next==NULL)
        {
            flag=0;
        }
        if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Class,-1,(*BP2).Class,-1)==1)
        {
            BP=(*BP1).next;     //��û�������ͷ��������
            BL.head=BP1;        //BP1���ӵ�ͷ
            (*BP1).next=BP2;    //ͷ�����ӻ�֮ǰ�ĺ�˳�������
            BP1=BP;         //BP1����ָ��δ�����ͷ
            continue;       //����һ����Ա
        }

        while(((*BP3).next!=NULL)&&(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Class,-1,(*BP3).Class,-1)!=1))     //�ҵ�BP1<BP3
        {
            BP2=(*BP2).next;
            BP3=(*BP3).next;
        }

        if((*BP3).next==NULL)
        {
            if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Class,-1,(*BP3).Class,-1)==3)
            {
                BP=(*BP1).next;
                (*BP3).next=BP1;            //BP1�����һ��Ԫ�ػ��򣬽ӵ������
                (*BP1).next=NULL;
                BL.rear=BP1;
                BP1=BP;
                continue;
            }
        }

        BP=(*BP1).next;
        (*BP2).next=BP1;       //���򣬽�BP1���ӵ�BP2��BP3֮��
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
    BP2=BL.head;          //�����ǵ�������Ҫ����ָ����ܽ��в���
    BP3=(*BL.head).next;

    flag=1;
    while(flag)
    {
        BP2=BL.head;          //�����ǵ�������Ҫ����ָ����ܽ��в���
        BP3=(*BL.head).next;
        if((*BP1).next==NULL)
        {
            flag=0;
        }
        if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Author,-1,(*BP2).Author,-1)==1)
        {
            BP=(*BP1).next;     //��û�������ͷ��������
            BL.head=BP1;        //BP1���ӵ�ͷ
            (*BP1).next=BP2;    //ͷ�����ӻ�֮ǰ�ĺ�˳�������
            BP1=BP;         //BP1����ָ��δ�����ͷ
            continue;       //����һ����Ա
        }

        while(((*BP3).next!=NULL)&&(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Author,-1,(*BP3).Author,-1)!=1))     //�ҵ�BP1<BP3
        {
            BP2=(*BP2).next;
            BP3=(*BP3).next;
        }

        if((*BP3).next==NULL)
        {
            if(CompareString(LOCALE_SYSTEM_DEFAULT,0,(*BP1).Author,-1,(*BP3).Author,-1)==3)
            {
                BP=(*BP1).next;
                (*BP3).next=BP1;            //BP1�����һ��Ԫ�ػ��򣬽ӵ������
                (*BP1).next=NULL;
                BL.rear=BP1;
                BP1=BP;
                continue;
            }
        }

        BP=(*BP1).next;
        (*BP2).next=BP1;       //���򣬽�BP1���ӵ�BP2��BP3֮��
        (*BP1).next=BP3;
        BP1=BP;
    }
}

void SearchBook()
{
    int flag;
    char c;
    char s[30];
    struct SearchResult *RP,*RP1;   //RP1ָ����������Ľ�β

    while(1)
    {
    printf("��ѡ��������ʽ��\r\n1������������\r\n2��������������\r\n3�������������\r\n");
    scanf("%d",&flag);
    getchar();
    switch(flag)
    {
    case 1:
        printf("������");
        //scanf("%s",s);
        //getchar();
        GetString(s,30);
        BP=BL.head;
        while(((*BP).next!=NULL)&&strcmp(s,(*BP).Name))   //�����Ƿ����Ȿ�飬�к������������˳�
        {
            BP=(*BP).next;
        }
        if(strcmp(s,(*BP).Name)==0)   //������һ����
        {
            Result.Book=BP;
            Result.next=NULL;
            RP1=&Result;
        }else
        {
            printf("û���Ȿ�飡\r\n");
            break;
        }
        BP=(*BP).next;
        while(BP!=NULL)
        {
            if(strcmp(s,(*BP).Name)==0)
            {
                RP=(struct SearchResult*)malloc(sizeof(struct SearchResult));
                (*RP).Book=BP;
                (*RP).next=NULL;    //�����������
                (*RP1).next=RP;     //��������ӵ��������β��
                RP1=RP;             //ָ��β��
            }
            BP=(*BP).next;
        }
        ShowResult();
        FreeResult();
        break;
    case 2:
        printf("��������");
        //scanf("%s",s);
        //getchar();
        GetString(s,20);
        BP=BL.head;
        while(((*BP).next!=NULL)&&strcmp(s,(*BP).Author))   //�����Ƿ����Ȿ�飬�к������������˳�
        {
            BP=(*BP).next;
        }
        if(strcmp(s,(*BP).Author)==0)   //������һ����
        {
            Result.Book=BP;
            Result.next=NULL;
            RP1=&Result;
        }else
        {
            printf("û���Ȿ�飡\r\n");
            break;
        }
        BP=(*BP).next;
        while(BP!=NULL)
        {
            if(strcmp(s,(*BP).Author)==0)
            {
                RP=(struct SearchResult*)malloc(sizeof(struct SearchResult));
                (*RP).Book=BP;
                (*RP).next=NULL;    //�����������
                (*RP1).next=RP;     //��������ӵ��������β��
                RP1=RP;             //ָ��β��
            }
            BP=(*BP).next;
        }
        ShowResult();
        FreeResult();
        break;
    case 3:
        printf("����ţ�");
        //scanf("%s",s);
        //getchar();
        GetString(s,13);
        BP=BL.head;
        while(((*BP).next!=NULL)&&strcmp(s,(*BP).Class))   //�����Ƿ����Ȿ�飬�к������������˳�
        {
            BP=(*BP).next;
        }
        if(strcmp(s,(*BP).Class)==0)   //������һ����
        {
            Result.Book=BP;
            Result.next=NULL;
            RP1=&Result;
        }else
        {
            printf("û���Ȿ�飡\r\n");
            break;
        }
        BP=(*BP).next;
        while(BP!=NULL)
        {
            if(strcmp(s,(*BP).Class)==0)
            {
                RP=(struct SearchResult*)malloc(sizeof(struct SearchResult));
                (*RP).Book=BP;
                (*RP).next=NULL;    //�����������
                (*RP1).next=RP;     //��������ӵ��������β��
                RP1=RP;             //ָ��β��
            }
            BP=(*BP).next;
        }
        ShowResult();
        FreeResult();
        break;
    default :
        break;
    }
    printf("����Y������N�˳�\r\n");
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
        printf("������Ҫ�޸�ͼ��ĵ�¼��:");
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
            printf("û���Ȿ�飡\r\n");
        }else
        {
            printf("Ҫ�޸ĵ������Ϣ��\r\n\r\n");

            printf("************************************************************************************************\r\n\r\n");
            ShowBook(BP);
            printf("��¼�ţ�");
            //scanf("%s",(*BP).AccountNumber);
            //getchar();
            GetString((*BP).AccountNumber,13);
            printf("������");
            //scanf("%s",(*BP).Name);
            //getchar();
            GetString((*BP).Name,30);
            printf("ͼ���ţ�");
            //scanf("%s",(*BP).BookNumber);
           // getchar();
           GetString((*BP).BookNumber,13);
            printf("���ۣ�");
            scanf("%d",&((*BP).Price));
            getchar();
            printf("���ߣ�");
            //scanf("%s",(*BP).Author);
            //getchar();
            GetString((*BP).Author,20);
            printf("����ţ�");
            //scanf("%s",(*BP).Class);
            //getchar();
            GetString((*BP).Class,13);
            printf("���浥λ��");
            //scanf("%s",(*BP).Publisher);
            //getchar();
            GetString((*BP).Publisher,30);
            printf("����ʱ�䣺");
            //scanf("%s",(*BP).PublishingTime);
           // getchar();
            GetString((*BP).PublishingTime,15);
            printf("�ݲ�ʣ����Ŀ��");
            scanf("%d",&((*BP).RemainingNumber));
            getchar();
        }
        printf("�޸ĳɹ���\r\��Y�����޸ģ�N�˳�\r\n");
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
            printf("\r\n���볬�����޶��ַ��������������룡\r\n");
            i=0;
        }
    }
    s[i]='\0';
    putchar('\n');
}
