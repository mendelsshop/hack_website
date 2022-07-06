#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 128
typedef char * string;
struct results {
    char urls[BUFSIZE];
    int code;
};

struct results webCheck(char url[BUFSIZE])
{
    char command[BUFSIZE];
    strcpy(command, "curl -s -I -L -w \"end: %{http_code} %{url_effective}\n\" ");
    FILE *fp;
    char buf[BUFSIZE];
    int status;
    strcpy(command, strcat(command, url));
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(buf, BUFSIZE, fp) != NULL) {
        if (strncmp("end: ", buf, 5) == 0) {
            printf("%s\n", buf);
            strcpy(url, strtok(buf, " "));
            strcpy(url, strtok(NULL, " "));
            status = atoi(url);
            strcpy(url, strtok(NULL, "\0"));
            if (url[strlen(url)-1] == '\n') {
                url[strlen(url)-1] = '\0';
            }
            if (url[strlen(url)-1] == 13) {
                url[strlen(url)-1] = '\0';
            }
            
            if (status >= 200 && status < 300) {
                status = 0;
            } else {
                status = 1;
            }
            
        }
    }
    pclose(fp);
    struct results e = {"", status} ;
    strcpy(e.urls, url);
    return e;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <website-url>\n", argv[0]);
        return 1;
    }
    char url[BUFSIZE];
    strcpy(url, argv[1]);
    struct results result = webCheck(url);
    printf("status: %i", result.code);
    if (result.code == 0)
    {
        printf("%s is up!\n" , result.urls);
    }
    else
    {
        printf("%s is down!\n" , result.urls);
    }
    return 0;
}
