#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main (int argc,char** argv)
{
    char wpp[150];
    srand((unsigned)time(NULL));
    int n = 1 + rand() % atoi(&argv[1][0]);
    FILE* fp = fopen("/home/him/.config/.wallpaper", "r");
    if(fp == NULL){
        printf("file err\n");
        return -1;
    }
    for(int i = 0; i < n; i++){
        memset(wpp, 150, '\0');
        fgets(wpp, 150, fp);
    }
    char cmd[200];
    memset(cmd, 200, '\0');
    *strstr(wpp, "\n") = '\'';
    sprintf(cmd, "swaybg -i '%s",wpp);
    system("killall -q swaybg");
    system(cmd);
}
