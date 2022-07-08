# hack_website
## About:
This is a C program that checks if a website is up and is so it will add the website to /etc/hosts. so that it redirects the website to 127.0.1.1

## why:
A while ago there were a bunch people who wanted to "heckers" so they installed Kali Linux (and some daily drove it). They went to the terminal/shell and ran sudo hack somewebsite.com. This is prank program to "hack" a website and bring down for only the users computer. 

## How it works:
1. check if the user ran with a second argument (the website) if not then exit
2. check if the user ran it with super user permissions if not then exit
3. check if the website is up using curl -sIL (silent, Head, Location (used to follow redirects)) 
4. format the curl ouptut with `"end: %{http_code} %{url_effective}\n\"` using the -w option and store it in a variable
6. remove check if their is a new line and or carriage return in the variable and remove them is so
6. if the website is up then add the website to /etc/hosts
7. open /etc/hosts and a temp file and copy the hosts to the temp file when we reach the second line of the hosts file then add the variable were we stored the curl output to the temp file
8. copy the temp file to the hosts file and then delete the temp file

## install:
1. compile the program with `gcc hack.c -o hack` or `make hack`
2. put the program in the `/bin` or the `/usr/bin` directory
3. if the program wont execute, make the program executable with `chmod +x hack`
4. have fun

## future improvements:
- check if the the second argument has a . if not exit with a message saying that the website needs to have a . in the name
- have a prompt if we succeedd to open the website in the browser to show that its down
- have it aviable via package managers