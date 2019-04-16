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

    if((fp=fopen("Administrators.bin","rb"))==NULL)        //�򿪹���Ա�ļ�
    {
        printf("�򿪹���Ա�ļ�ʧ�ܣ�\r\n");
    }

    fseek(fp,0L,SEEK_END);      //��ָ���ƶ����ļ���β

    if(ftell(fp)==0)
    {
        AL.head=NULL;
        AL.rear=NULL;
        AL.number=0;
        printf("û�й���Ա��\r\n");       //�ж��ļ��Ĵ�С
        return -1;
    }
    else
    {
        rewind(fp);
        AP=AL.head=(struct Administrators*)malloc(sizeof(struct Administrators));

        while(fread(AP,sizeof(struct Administrators),1,fp)!=1);

        (*AP).next=NULL;      //ָ��ָ�������β
        AL.rear=AP;
        AL.number=1;        //������һ������Ա
    }

    while(feof(fp)==0)
    {
        (*AP).next=(struct Administrators*)malloc(sizeof(struct Administrators));

        if(fread((*AP).next,sizeof(struct Administrators),1,fp)==1)         //��ȡ��һ������Ա����
            {
            AP=(*AP).next;        //APָ����һ������Ա
            (*AP).next=NULL;      //ָ������Ľ�β
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
        printf("���û��ļ�ʧ�ܣ�\r\n");
    }
    fseek(fp,0L,SEEK_END);          //���ļ�ָ���ƶ����ļ��Ľ�β

    if(ftell(fp)==0)
    {
        UL.head=NULL;
        UL.rear=NULL;
        UL.number=0;
        printf("û���û���\r\n");        //�ж��ļ��Ĵ�С�����Ϊ0��û���û��������˳��û����ݵļ���
        return -1;
    }
    else
    {
        rewind(fp);
        UP=UL.head=(struct Users*)malloc(sizeof(struct Users));

        while(fread(UP,sizeof(struct Users),1,fp)!=1);

        (*UP).next=NULL;      //ָ��ָ�������β
        UL.rear=UP;
        UL.number=1;        //������һ���û�Ա
    }

    while(feof(fp)==0)
    {
        (*UP).next=(struct Users*)malloc(sizeof(struct Users));

        if(fread((*UP).next,sizeof(struct Users),1,fp)==1)         //��ȡ��һ������Ա����
            {
            UP=(*UP).next;        //UPָ����һ���û�
            (*UP).next=NULL;      //ָ������Ľ�β
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
        Keys[i]=Keys[i]+Keys[i+1];         //��ǰ�ַ����һ�ַ�ֵ�����Ϊ��ǰ���ַ�
        i++;
    }
    Keys[i]=Keys[i]+Keys[i];
    return Keys;         //�����ַ�ָ��
}

int AdministratorsLogin()
{
    char AccountNumber[13];     //�˺�
    char AccountKeys[20];   //����
    int times=0;

    while(times<3)
    {
    printf("����Ա�˺ţ�");
    //scanf("%s",AccountNumber);
    //getchar();          //������Ļس��Ŷ���
     GetString(AccountNumber,13);
    printf("���룺");
    //scanf("%s",AccountKeys);
    //getchar();          //������Ļس��Ŷ���
    GetKeys(AccountKeys);
    if(Is_A_Existence(AccountNumber,AccountKeys,&times))
    {
        printf("��ӭ��������Ա���棡\r\n");
        return 1;
    }
    printf("ʣ���¼����Ϊ%d\r\n\r\n",3-times);
    }

    printf("��¼�������꣡\r\n");
    return 0;
    printf("************************************************************************************************\r\n\r\n");
    return 0;
}

int Is_A_Existence(char AN[],char AK[],int *times)
{
    AP=AL.head;
    while(strcmp((*AP).AccountNumber,AN)!=0)        //������ͷ��ʼ�����˺Ŵ治����
    {
        if((*AP).next==NULL)
        {
            printf("�˺Ų����ڣ�");           //ֱ������β��û���ҵ��˺ţ�������ʾ��ֱ���˳�����
            *times=*times+1;
            return 0;
        }else
        {
            AP=(*AP).next;
        }
    }

    if(!strcmp(Encryption(AK),(*AP).AccountKeys))       //�Ƚ������ǲ�����ȷ
    {
        printf("��¼�ɹ���\r\n");
        OU.UsersClass=0;
        OU.OnlineA=AP;
        printf("************************************************************************************************\r\n\r\n");
        return 1;
    }else
    {
        printf("������������µ�¼\r\n");           //������󣬵�¼������������Զ���һ���˳�����
        *times=*times+1;
        return 0;
    }
}

int UsersLogin()
{
    char AccountNumber[13];     //�˺�
    char AccountKeys[20];   //����
    int times=0;

    while(times<3)
    {
    printf("�û��˺ţ�");
    //scanf("%s",AccountNumber);
    //getchar();          //������Ļس��Ŷ���
     GetString(AccountNumber,13);
    printf("���룺");
    //scanf("%s",AccountKeys);
    //getchar();          //������Ļس��Ŷ���
    GetKeys(AccountKeys);
    if(Is_U_Existence(AccountNumber,AccountKeys,&times))
    {
        printf("��ӭ�����û����棡\r\n");
        return 1;
    }
    printf("ʣ���¼����Ϊ%d\r\n\r\n",3-times);
    }

    printf("��¼�������꣡\r\n");
    return 0;
}

int Is_U_Existence(char UN[],char UK[],int *times)
{
    UP=UL.head;
    while(strcmp((*UP).AccountNumber,UN)!=0)
    {
        if((*UP).next==NULL)
        {
            printf("�˺Ų����ڣ�\r\n");
            *times=*times+1;
            return 0;
        }else
        {
            UP=(*UP).next;
        }
    }

    if(!strcmp(Encryption(UK),(*UP).AccountKeys))
    {
        printf("��¼�ɹ���\r\n");
        OU.UsersClass=1;
        OU.OnlineU=UP;
        printf("************************************************************************************************\r\n\r\n");
        return 1;
    }else
    {
        printf("������������µ�¼\r\n");
        *times=*times+1;
        return 0;
    }
}

void ShowAdministrators()
{
    AP=AL.head;
    printf("%-15s%-15s%-10s%-8s%-4s\r\n","�˺�","����","����","�Ա�","����Ȩ");
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
    printf("%-15s%-15s%-10s%-8s%-10s%-15s\r\n","�˺�","����","����","�Ա�","��Ա","����ͼ����Ŀ");
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
        printf("�����ˣ�\r\n");
        return -1;
    }
    printf("%-15s%-15s%-10s%-8s%-10s%-15s\r\n","�˺�","ѧ��","����","�Ա�","��Ա","����ͼ����Ŀ");
    printf("%-15s%-15s%-10s%-8s%-10d%-15d\r\n",(* (OU.OnlineU)).AccountNumber,(*(OU.OnlineU)).StudentNumber,(*(OU.OnlineU)).Name,(*(OU.OnlineU)).Sex,(*OU.OnlineU).Leaguer,(*OU.OnlineU).BorrowingNumber);
    printf("************************************************************************************************\r\n\r\n");
}

void ShowOA()
{
    if(OU.UsersClass!=0)
    {
        printf("�����ˣ�\r\n");
        return -1;
    }
    printf("%-15s%-15s%-10s%-8s%-10s\r\n","�˺�","����","����","�Ա�","����Ȩ��");
    printf("%-15s%-15s%-10s%-8s%-10d\r\n",(* (OU.OnlineA)).AccountNumber,(*(OU.OnlineA)).AccountKeys,(*(OU.OnlineA)).Name,(*(OU.OnlineA)).Sex,(*OU.OnlineA).Jurisdiction);
    printf("************************************************************************************************\r\n\r\n");
}

void ChangeMessage()
{
    if(OU.UsersClass==0)
    {
        printf("�������޸ĵ���Ϣ��\r\n");
        printf("���룺");
        //scanf("%s",(*OU.OnlineA).AccountKeys);
       // getchar();
        GetKeys((*OU.OnlineA).AccountKeys);
        Encryption((*OU.OnlineA).AccountKeys);
        printf("������");
        //scanf("%s",(*OU.OnlineA).Name);
        //getchar();
        GetString((*OU.OnlineA).Name,20);
        printf("�Ա�");
        //scanf("%s",(*OU.OnlineA).Sex);
        //getchar();
        GetString((*OU.OnlineA).Sex,3);
        printf("�޸ĳɹ���\r\n");
        ALChange=1;
        SaveAL();
    }else if(OU.UsersClass==1)
    {
        printf("�������޸ĵ���Ϣ��\r\n");
        printf("���룺");
        //scanf("%s",(*OU.OnlineU).AccountKeys);
        //getchar();
        GetKeys((*OU.OnlineU).AccountKeys);
        Encryption((*OU.OnlineU).AccountKeys);
        printf("������");
        //scanf("%s",(*OU.OnlineU).Name);
        //getchar();
        GetString((*OU.OnlineU).Name,20);
        printf("�Ա�");
        //scanf("%s",(*OU.OnlineU).Sex);
        //getchar();
        GetString((*OU.OnlineU).Sex,3);
        printf("ѧ�ţ�");
        //scanf("%s",(*OU.OnlineU).StudentNumber);
        //getchar();
        GetString((*OU.OnlineU).StudentNumber,13);
        printf("�޸ĳɹ���\r\n");
        ULChange=1;
        SaveUL();
    }else
    {
        printf("�����ˣ�\r\n");
    }
}

int SaveAL()
{
    FILE *fp;

    if(ALChange)
    {
         if((fp=fopen("Administrators.bin","wb"))==NULL)        //�򿪹���Ա�ļ�
            {
                printf("�򿪹���Ա�ļ�ʧ�ܣ�\r\n");
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
        printf("����ɹ���\r\n");
        printf("************************************************************************************************\r\n\r\n");
    }

    return 0;
}

int SaveUL()
{
    FILE *fp;

    if(ULChange)
    {
         if((fp=fopen("Users.bin","wb"))==NULL)        //���û��ļ�
            {
                printf("���û��ļ�ʧ�ܣ�\r\n");
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
        printf("����ɹ���\r\n");
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
        printf("��ǰû�н���ͼ�飡\r\n");
        printf("************************************************************************************************\r\n\r\n");
        return 0;
    }

    printf("���õ���Ϊ\r\n");
    printf("************************************************************************************************\r\n\r\n");
    printf("%-15s%-15s%-10s%-15s%-8s%-8s\r\n","��¼��","����","����","������","�����","�ݲ�ʣ������");
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
        printf("�㻹���ǻ�Ա���޷����飡\r\n");
        printf("************************************************************************************************\r\n\r\n");
        return 0;
    }
    while(1)
    {
        printf("������Ҫ�����ĵ�¼�ţ�");
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
            printf("û���Ȿ�飡\r\n");
        }else if(((*OU.OnlineU).BorrowingNumber)>=5)
        {
            printf("���Ѿ��ﵽ�������ޣ������ٽ���");
            return 0;
        }else if((*BP).RemainingNumber==0)
        {
            printf("�Ȿ���ʣ������Ϊ0�������ٽ��ˣ�\r\n");
        }
        else
        {
            printf("Ҫ�������ϢΪ��\r\n");
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
            printf("����ɹ���\r\n");
        }
        printf("����Y�������飬N�˳�\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("�����ˣ�\r\n");
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
        printf("�㵱ǰû�н��ĵ�ͼ�飡\r\n");
        return 0;
    }

    //printf("����ĵ���Ϊ��\r\n");
    ShowBorrowing();

    while(1)
    {
        printf("������Ҫ������ĵ�¼�ţ�");
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
                    BP=(*BP).next;                      //Ĭ��ͼ������Ȿ��
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
                    printf("��û�н����Ȿ�飡\r\n");
                }
            }
        }
        printf("��Y������N�˳�\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("�����ˣ�\r\n");
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
    printf("��Y�����Ա��N�������Ա\r\n");
    c=getch();
    if(c=='Y')
    {
        if((fp=fopen("ApplyForVIP.bin","ab"))==NULL)
        {
            printf("�򿪻�Ա�����ļ�ʧ�ܣ�ע��ʧ�ܣ�\r\n");
            return -1;
        }
        while(fwrite((*OU.OnlineU).AccountNumber,13,1,fp)!=1);
        printf("����ɹ����ȴ�ͨ����\r\n");
        fclose(fp);
    }else if(c=='N')
    {
        return 0;
    }else
    {
        printf("�������\r\n");
        return -1;
    }
}

void UserManagement()
{
    int flag,flag1;
    flag1=1;
    while(flag1)
    {
        printf("1����ʾ�����û�\r\n2��ע����Ա\r\n3��ɾ���û�\r\n4���˳�\r\n");
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
        printf("Ҫע����Ա���û��˺ţ�");
        //scanf("%s",s);
        //getchar();
         GetString(s,13);
        UP=UL.head;
        while((UP!=NULL)&&(strcmp((*UP).AccountNumber,s)!=0))       //�����û�����
        {
            UP=(*UP).next;
        }
        if(UP==NULL)
        {
            printf("û�д˻�Ա��\r\n");
        }else
        {
            (*UP).Leaguer=0;                    //�޸Ļ�Ա��־
            ULChange=1;
            printf("ע���ɹ���\r\n");
        }
        printf("��Y������N�˳�\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("�����ˣ�\r\n");
            return -1;
        }
    }
    SaveUL();           //���޸��û���ͱ��棬�ں�������ж���û���޸��û���
}

void DeleteUsers()
{
    char c,s[13];
    struct Users *UP1,*UP2;
    while(1)
    {
        printf("������Ҫɾ���û����˺ţ�");
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
            printf("ɾ���ɹ���\r\n");
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
                    printf("ɾ���ɹ���\r\n");
                    ULChange=1;
                }else
                {
                    printf("û���Ȿ�飡\r\n");
                }
            }else
            {
                (*UP1).next=(*UP2).next;
                free(UP2);
                BL.number--;
                printf("ɾ���ɹ���\r\n");
                ULChange=1;
            }
        }
        printf("��Y������N�˳�\r\n");
        c=getch();
        if(c=='N')
        {
            break;
        }else if(c=='Y')
        {
            continue;
        }else
        {
            printf("�����ˣ�\r\n");
            return -1;
        }
    }
    SaveUL();
}

void UserRegistration()
{
    struct Users *UP1;
    UP1=(struct Users*)malloc(sizeof(struct Users));
    printf("�˺ţ�");
    //scanf("%s",(*UP1).AccountNumber);
    //getchar();
     GetString((*UP1).AccountNumber,13);
    printf("���룺");
    //scanf("%s",(*UP1).AccountKeys);
    GetKeys((*UP1).AccountKeys);
    Encryption((*UP1).AccountKeys);
    //getchar();
    printf("������");
    //scanf("%s",(*UP1).Name);
   // getchar();
    GetString((*UP1).Name,20);
    printf("�Ա�");
    //scanf("%s",(*UP1).Sex);
    //getchar();
    GetString((*UP1).Sex,3);
    printf("ѧ�ţ�");
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
    printf("ע��ɹ���\r\n");
    printf("************************************************************************************************\r\n\r\n");
}

void ADRegistration()
{
    struct Administrators *AP1;
    FILE *fp;
    AP1=(struct Administrators*)malloc(sizeof(struct Administrators));
    printf("�˺ţ�");
    //scanf("%s",(*AP1).AccountNumber);
    //getchar();
     GetString((*AP1).AccountNumber,13);
    printf("���룺");
    //scanf("%s",(*AP1).AccountKeys);
    GetKeys((*AP1).AccountKeys);
    Encryption((*AP1).AccountKeys);
    //getchar();
    printf("������");
    //scanf("%s",(*AP1).Name);
    //getchar();
    GetString((*AP1).Name,20);
    printf("�Ա�");
    //scanf("%s",(*AP1).Sex);
    //getchar();
    GetString((*AP1).Sex,3);
    (*AP1).Jurisdiction=0;

    if((fp=fopen("ADRegistration.bin","ab"))==NULL)
    {
        printf("�򿪹���Աע���ļ�ʧ�ܣ�ע��ʧ�ܣ�\r\n");
        return -1;
    }

    while(fwrite(AP1,sizeof(struct Administrators),1,fp)!=1);
    printf("ע��ɹ����ȴ�ͨ����\r\n");
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
        printf("1����Ա�������\r\n2������Աע�����\r\n3���˳�\r\n");
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
        printf("�򿪻�Ա�����ļ�ʧ�ܣ�\r\n");
        return -1;
    }

    while(feof(fp)==0)
    {
        if(fread(s,13,1,fp)==1)      //��ȡ�ļ���ȷ
        {
            UP=UL.head;
            while((UP!=NULL)&&(strcmp((*UP).AccountNumber,s)!=0))   //Ѱ�Ҹ��û�����
            {
                UP=(*UP).next;
            }

            if(UP==NULL)
            {
                printf("�����ˣ�\r\n");
                continue;
            }else
            {
                printf("Ҫ�����Ա���û����ϣ�\r\n");
                printf("************************************************************************************************\r\n\r\n");
                printf("%-15s%-15s%-10s%-8s%-10s%-15s\r\n","�˺�","����","����","�Ա�","��Ա","����ͼ����Ŀ");
                printf("%-15s%-15s%-10s%-8s%-10d%-15d\r\n",(* UP).AccountNumber,(*UP).AccountKeys,(*UP).Name,(*UP).Sex,(*UP).Leaguer,(*UP).BorrowingNumber);
                printf("************************************************************************************************\r\n\r\n");
                printf("��Yͨ�����룬N��ͨ��\r\n");

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
                        printf("�������,�������룡\r\n");
                        continue;
                    }
                }
            }
        }
    }
    SaveUL();
    printf("�Ѿ�û��Ҫ�����Ա���û��ˣ�\r\n");
    fclose(fp);

    if((fp=fopen("ApplyForVIP.bin","wb"))==NULL)
    {
        printf("�򿪻�Ա�����ļ�ʧ�ܣ�\r\n");
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
        printf("�򿪹���Աע���ļ�ʧ�ܣ�ע��ʧ�ܣ�\r\n");
        return -1;
    }
    while(feof(fp)==0)
    {
        AP1=(struct Administrators*)malloc(sizeof(struct Administrators));
        if(fread(AP1,sizeof(struct Administrators),1,fp)==1)
        {
            printf("Ҫ�������Ա���û���Ϣ��\r\n");
            printf("************************************************************************************************\r\n\r\n");
            printf("%-15s%-15s%-10s%-8s%-4s\r\n","�˺�","����","����","�Ա�","����Ȩ");
            printf("%-15s%-15s%-10s%-8s%-4d\r\n",(*AP1).AccountNumber,(*AP1).AccountKeys,(*AP1).Name,(*AP1).Sex,(*AP1).Jurisdiction);
            printf("************************************************************************************************\r\n\r\n");
            printf("��Yͨ����N��ͨ��\r\n");
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
                    printf("���������������룡\r\n");
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
        printf("�򿪹���Աע���ļ�ʧ�ܣ�ע��ʧ�ܣ�\r\n");    //����ļ�
        return -1;
    }
    fclose(fp);
    printf("�Ѿ�û���û��������Ա�ˣ�\r\n");
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
            printf("\r\n���볬���������޶����ַ��������������룡\r\n");
            i=0;
        }
    }
    s[i]='\0';
    putchar('\n');
}
