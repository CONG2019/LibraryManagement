#include "Page.h"

void Homepage()
{
    int flag;
    int flag1=1;
    while(flag1)
    {
    printf("��ӭʹ��ͼ�����Ϣ����ϵͳ��\r\n");
    printf("���ȵ�¼��\r\n");
    printf("1���û���¼\r\n2������Ա��¼\r\n3���û�ע��\r\n4������Աע��\r\n5���˳�\r\n");
    printf("************************************************************************************************\r\n\r\n");
    scanf("%d",&flag);
    switch(flag)
    {
    case 1:
        if(UsersLogin())
        {
            UsersPage();
            printf("�ɹ�\r\n");
        }else
        {
            flag1=0;
        }
        break;
    case 2:
        if(AdministratorsLogin())
        {
            AdministratorsPage();
            printf("�ɹ�\r\n");
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
    printf("1����ʾ������Ϣ\r\n2���޸ĸ�����Ϣ\r\n3����ʾ���õ�ͼ��\r\n4������\r\n5������\r\n6�������Ա\r\n7����ʾ����ͼ��\r\n8������ͼ��\r\n9���˳�\r\n");
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
        printf("1����ʾ������Ϣ\r\n2���޸ĸ�����Ϣ\r\n3����ʾ����ͼ��\r\n4��ͼ��¼��\r\n5��ͼ��ɾ��\r\n6��ͼ����Ϣ�޸�\r\n7��ͼ������\r\n8������\r\n9���û�����\r\n10���������\r\n11���˳�\r\n");
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
        printf("������Ҫɾ���鱾�ĵ�¼�ţ�");
        //scanf("%s",s);
        //getchar();
         GetString(s,13);
        if(SearchByAN(s))
        {
            //ShowResult();
            printf("Ҫɾ���������Ϣ�ǣ�\r\n");
            ShowBook((*Result.next).Book);
            printf("����Yɾ����N��ɾ��\r\n");
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
                printf("�������,��ɾ����\r\n");
            }
        }
        printf("����ɾ����Y���˳���N\r\n");
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
    printf("��ѡ������ʽ��\r\n1������������\r\n2�������������\r\n3������������\r\n");
    while(flag1)
    {
        scanf("%c",&flag);
        getchar();
        switch(flag)
        {
        case '1':
            SorttingByName();
            printf("������Ϊ��\r\n");
            printf("************************************************************************************************\r\n\r\n");
            ShowBooks();
            flag1=0;     //������ȷ���ص�������
            break;
        case '2':
            SorttingByClass();
            printf("������Ϊ��\r\n");
            printf("************************************************************************************************\r\n\r\n");
            ShowBooks();
            flag1=0;     //������ȷ���ص�������
            break;
        case '3':
            SorttingByAuthor();
            printf("������Ϊ��\r\n");
            printf("************************************************************************************************\r\n\r\n");
            ShowBooks();
            flag1=0;     //������ȷ���ص�������
            break;
        default :
            break;
        }
    }
}
