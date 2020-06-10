#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <string.h>
#include <ctime>
#include <fstream>
#include <iostream>

struct proverkaClienta
{
    struct in_addr ip_clienta;
    int num_p = 0;
    time_t time = 0;
    struct tm* timeblock;
    bool blocked = false;
};

bool proverka_d(char x[], char y[])
{
    bool proverkalogin2 = false;
    bool proverka_res = false;
    bool proverkapassword = false;
    int numlogin = -1;
    char proverkalogin[4][40] = { "mike","kate","luke","alex" };
    char proverkapass[4][40] = { "1234","5678","9012","1256" };
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(x, proverkalogin[i]) == 0)
        {
            proverkalogin2 = true;
            numlogin = i;
        }
    }
    if (proverkalogin2)
    {
        for (int i = 0; i < 4; i++)
        {
            if (strcmp(y, proverkapass[i]) == 0)
            {
                proverkapassword = true;
                proverka_res = true;
            }
        }
    }
    else
    {
        proverka_res = false;
    }
    return proverka_res;
}

bool Digit(char argv)
{
    if (argv >= '0' && argv <= '9')
    return true;
	
return false;
}

bool number_p(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (Digit)
            return false;
    }
    return true;
}

bool PortPro(char* argv)
{
    return(number_p(argv));
}

bool proverka_diapos_less(char* argv)
{
    return(atoi(argv) > 1024);
}

bool proverka_diapos_more(char* argv)
{
    return(atoi(argv) < 49151);
}

int server_init(int argc, char** argv)
{
    int lie = atoi(argv[1]);
    //proverka count of arguments
    if (argc > 2 || argc < 2)
    {
        return 2;
    }
    proverkaClienta spisok[4];
    int sock;
    int ind = 0;
    int number;
    struct sockaddr_in addr;
    bool mistake = false;
    socklen_t addrlen = sizeof(addr); /* length of addresses */
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
    {
        perror("socket eror");
        exit(1);
    }
    else
    {
        perror("socket create");
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = inet_addr("127.0.0.0");
    if (bind(sock, (struct sockaddr*) & addr, sizeof(addr)) < 0)
    {
        perror("bind eror");
        exit(2);
    }
    else
    {
        perror("bind create");
        return 5;
        close(sock);
    }
    struct tm* local, * timeinfo;
    const time_t timecon = time(NULL);
    time_t t;
    t = time(NULL);
    char recivedlogin[40];
    char recivedpassword[40];
    int bytes_read;
    char true_d[64] = "Your login and password correct";
    char false_d[64] = "Your login or password wrong";
    char answer[64] = "Youre IP blocked for:";
    char answer2[64] = "You are blocked for minute!";
    while (1)
    {
        memset(recivedlogin, '\0', 40);
        memset(recivedpassword, '\0', 40);
        bytes_read = recvfrom(sock, recivedlogin, 40, 0, (struct sockaddr*) & addr, &addrlen);
        if (bytes_read > 0)
        {
            printf("Client login: %s\n", recivedlogin);
        }
        else
        {
            exit(3);
        }
        bytes_read = recvfrom(sock, recivedpassword, 40, 0, (struct sockaddr*) & addr, &addrlen);
        if (bytes_read > 0)
        {
            printf("Client password: %s\n", recivedpassword);
        }
        else
        {
            exit(3);
        }
        bool proverka = proverka_d(recivedlogin, recivedpassword);
        if (proverka == true)
        {
            sendto(sock, true_d, strlen(true_d), 0, (struct sockaddr*) & addr, addrlen);
            spisok[number].num_p = 0;
            close(sock);
        }
        else
        {
            if (spisok[number].blocked) {
                printf("You are blocked for: %s", timeinfo);
                sendto(sock, answer2, sizeof(answer2), 0, (struct sockaddr*) & addr, addrlen);
            }
            else if ((spisok[number].num_p >= 3) && (spisok[number].timeblock != localtime(&t)))
            {
                printf("You are blocked for: %s", timeinfo);
                sendto(sock, answer2, sizeof(answer2), 0, (struct sockaddr*) & addr, addrlen);
            }
            else
            {
                sendto(sock, false_d, strlen(true_d), 0, (struct sockaddr*) & addr, addrlen);
                spisok[number].num_p += 1;
            }
        }
        std::cout << "PROVERKA LOGIN AND PASSWORD! " << std::endl;
        for (int i = 0; i < 4; i++)
        {
            if (spisok[i].ip_clienta.s_addr = addr.sin_addr.s_addr)
            {
                number = i;
                if (spisok[i].num_p >= 3)
                {
                    if (spisok[i].time == 0)
                    {
                        spisok[i].blocked = true;
                        printf("Your IP blocked for minute! \n");
                        spisok[i].time = timecon;
                        spisok[i].time += 60;
                        timeinfo = localtime(&spisok[i].time);
                        spisok[i].timeblock = timeinfo;
                        printf(" Bloked time and date: %s", asctime(timeinfo));
                        strcat(answer, asctime(timeinfo));
                        sendto(sock, answer2, sizeof(answer2), 0, (struct sockaddr*) & addr, addrlen);
                        i = 5;
                    }
                    else
                    {
                        if (spisok[i].time <= time(NULL))
                        {
                            spisok[i].num_p = 0;
                            spisok[i].time = 0;
                            spisok[i].blocked = false;
                            i = 5;
                        }
                        else if (spisok[number].time > time(NULL))
                        {
                            spisok[i].blocked = true;
                            printf("Your IP blocked for minute! \n");
                            timeinfo = localtime(&spisok[i].time);
                            spisok[i].timeblock = timeinfo;
                            printf(" Bloked time and date: %s", asctime(timeinfo));
                            strcat(answer, asctime(timeinfo));
                            sendto(sock, answer2, sizeof(answer2), 0, (struct sockaddr*) & addr, addrlen);
                            i = 5;
                        }
                        else if ((spisok[i].timeblock = localtime(&t)) && (!spisok[i].blocked))
                        {
                            spisok[i].blocked = false;
                            spisok[i].num_p = 0;
                            spisok[i].time = 0;
                            spisok[i].timeblock = 0;
                            close(sock);
                            i = 5;
                        }
                        else if ((spisok[i].timeblock != localtime(&t)) && (spisok[i].blocked))
                        {
                            printf("You are blocked for: %s", asctime(local));
                            sendto(sock, answer2, sizeof(answer2), 0, (struct sockaddr*) & addr, addrlen);
                            i = 5;
                        }
                    }
                }
            }
        }
    }
    close(sock);
    return 0;
}




