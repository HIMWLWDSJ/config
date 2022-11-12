#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TITLE_LEN 12
#define URL_LEN 15
#define SPAN_LEN 5

typedef struct
{
    char name[100];
    char url[50];
    int num;
} Obj;
char html[120000];
char *src;
void CreateObj(Obj *obj, int code)
{
    // Get Name
    char *start = strstr(src, "data-title=\"") + TITLE_LEN;
    char *end = strstr(src, "\" data-user-name");
    char name[end - start + 1];
    memset(name, '\0', sizeof(name));
    strncpy(name, start, end - start);
    while (strstr(name, "/") != NULL)
        *strstr(name, "/") = '.';
    while (strstr(name, "\\") != NULL)
        *strstr(name, "\\") = '.';
    while (strstr(name, "'") != NULL)
        *strstr(name, "'") = '.';
    while (strstr(name, "\"") != NULL)
        *strstr(name, "\"") = '.';
    sprintf(obj->name, "%d.%s", code, name);

    // Get URL
    start = strstr(end, "img-master/img/") + URL_LEN;
    end = strstr(start, "0_master1200.jpg");
    char url[end - start + 1];
    memset(url, '\0', sizeof(url));
    strncpy(url, start, end - start);
    strcpy(obj->url, url);

    // Get Num
    if (*(strstr(end, "<span") + SPAN_LEN) == '>') // Num > 1
    {
        start = strstr(end, "<span>") + SPAN_LEN + 1;
        end = strstr(start, "</span");
        char strNum[5];
        memset(strNum, '\0', 5);
        obj->num = atoi(strncat(strNum, start, end - start));
    }
    else
    { // Num = 1
        obj->num = 1;
    }

    // Set src html
    src = end;
}
int main()
{
    // Read HTML File
    char htmlPath[200];
    memset(htmlPath, '\0', 200);
    memset(html, '\0', 120000);
    printf("%s\n", "Enter HTML file's path (Lenth < 200):");
    scanf("%s", htmlPath);
    FILE *fp = fopen(htmlPath, "r"); // /home/himwl/pv.html
    if (fp == NULL)
    {
        printf("Error: Can't read %s\n", htmlPath);
        return 1;
    }

    for (int i = 0; i < 216; i++)
        fgets(html, 120000, fp);
    fclose(fp);
    src = html;

    // Create the Img Objects
    Obj imgs[50];
    int imgn = 0;
    for (int i = 0; i < 50; i++)
    {
        CreateObj(&imgs[i], i + 1);
        imgn += imgs[i].num;
    }
    printf("There are %d Pictures\nEnter Output Directory (Lenth < 200):\n", imgn);
    char directory[201];
    memset(directory, '\0', 201);
    scanf("%s", directory);
    if (*(strstr(directory, "\0") - 1) != '/' || *(strstr(directory, "\0") - 1) != '\\')
    {
        strcat(directory, "/");
    }
    while (strstr(directory, "'") != NULL)
        *strstr(directory, "'") = '.';
    while (strstr(directory, "\"") != NULL)
        *strstr(directory, "\"") = '.';
    char mkdir[210];
    memset(mkdir,'\0',210);
    sprintf(mkdir,"mkdir '%s'",directory);
    system(mkdir);

    // Download Pictures
    char cmd[280];
    for (int i = 0; i < 50; i++)
    {
        memset(cmd, '\0', 280);
        if (imgs[i].num == 1)
        {
            sprintf(cmd,
                    "wget -O '%s%s.jpg' '--referer=http://www.pixiv.net/' https://i.pximg.net/img-master/img/%s0_master1200.jpg",
                    directory,
                    imgs[i].name,
                    imgs[i].url);
            system(cmd);
        }
        else
        {
            for (int j = 0; j < imgs[i].num; j++)
            {
                memset(cmd,'\0',280);
                sprintf(cmd,
                    "wget -O '%s%s_%d.jpg' '--referer=http://www.pixiv.net/' https://i.pximg.net/img-master/img/%s%d_master1200.jpg",
                    directory,
                    imgs[i].name,
                    j+1,
                    imgs[i].url,
                    j);
                system(cmd);
            }
        }
    }
}
