#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Page.h"
#include "Login.h"
#include "Books.h"

int main()
{
    AdministratorsLoad();
    UsersLoad();
    BL.number=0;
    BooksLoad();

    ShowAdministrators();
    //ShowUsers();
    Homepage();

    printf("\r\nϵͳ�����������ӭ�ٴε�¼���飡\r\n");
    return 0;
}
