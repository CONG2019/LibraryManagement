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

    printf("\r\n系统体验结束，欢迎再次登录体验！\r\n");
    return 0;
}
