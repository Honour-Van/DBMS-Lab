#include <stdlib.h>
#include <stdio.h>
static void before(void) __attribute__((constructor));
static void after(void) __attribute__((destructor));
static void middle(void);
static void before()
{
    // system("chcp 65001"); //切换字符集
    // system("chcp 936"); //切换字符集

    system("cls");
}

static void after()
{
    system("pause");
}