#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <ctype.h>

#define BUFSIZE 128
typedef char * string;

// taken from: https://stackoverflow.com/questions/47116974/remove-a-substring-from-a-string-in-c
char * strremove(char * str,
  const char * sub) {
  char * p, * q, * r;
  if ( * sub && (q = r = strstr(str, sub)) != NULL) {
    size_t len = strlen(sub);
    while ((r = strstr(p = r + len, sub)) != NULL) {
      while (p < r)
        *
        q++ = * p++;
    }
    while (( * q++ = * p++) != '\0')
      continue;
  }
  return str;
}

string webCheck(char url[BUFSIZE]) {
  char command[BUFSIZE];
  strcpy(command, "curl -s -I -L -o /dev/null -w \"%{scheme} %{url_effective}\" ");

  FILE * fp;
  char buf[BUFSIZE];
  int status;
  char string_code[BUFSIZE];
  char url_header[BUFSIZE];
  strcpy(command, strcat(command, url));
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }

  printf("checking website\n");
  fgets(buf, BUFSIZE, fp);
  if (buf == NULL) {
    printf("error\n");
    exit(1);
  }
  strcpy(url_header, strtok(buf, " "));
  // make url_header lowercase
  for (int i = 0; i < strlen(url_header); i++) {
    url_header[i] = tolower(url_header[i]);
  }
  //append :// to url_header
  strcpy(url_header, strcat(url_header, "://"));

  strcpy(url, strtok(NULL, " "));
  // removing / from the end of the url
  if (url[strlen(url) - 1] == 47) {
    url[strlen(url) - 1] = '\0';
  }
  // remove url_header from the beginning of the url
  strcpy(url, strremove(url, url_header));
  return url;
}

int main(int argc, string argv[]) {
  system("clear");
  printf("\x1b[40;38;5;34m");

  if (argc != 2) {
    printf("Usage: %s <website-url>\n", argv[0]);
    return 1;
  }
  if (getuid()) {
    printf("This program requires root acces!\n");
    printf("Try running this program with sudo.\n");
    printf("Like: sudo %s %s\n", argv[0], argv[1]);
    return 1;
  }
  char urla[BUFSIZE];
  char url[BUFSIZE];
  // running the webCheck function and getting the url
  strcpy(urla, webCheck(argv[1]));
  char hosts[BUFSIZE] = "127.0.0.1       ";
  strcpy(hosts, strcat(hosts, urla));
  strcpy(hosts, strcat(hosts, "\n"));
  FILE * fp = fopen("/etc/hosts", "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    exit(1);
  }
  fseek(fp, 0, SEEK_SET);

  FILE * fp1 = fopen("temp.txt", "w");
  if (fp1 == NULL) {
    printf("Failed to open file\n");
    exit(1);
  }
  int i = 0;
  while (fgets(url, BUFSIZE, fp) != NULL) {
    if (i == 2) {
      fprintf(fp1, "%s", hosts);
      i++;
    }
    fprintf(fp1, "%s", url);

    i++;
  }
  fclose(fp);
  fclose(fp1);

  fp = fopen("/etc/hosts", "w");
  fp1 = fopen("temp.txt", "r");
  while (fgets(url, BUFSIZE, fp1) != NULL) {
    fprintf(fp, "%s", url);
  }
  fclose(fp);
  fclose(fp1);

  remove("temp.txt");

  printf("%s is down!\n", urla);

  printf("\x1b[0m"); // reset color
  return 0;
}