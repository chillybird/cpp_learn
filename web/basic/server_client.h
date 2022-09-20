//
// Created by zhang on 2022/9/20.
//

#ifndef WEB_SERVER_CLIENT_0_H
#define WEB_SERVER_CLIENT_0_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/time.h>

#include <fcntl.h>

/*
 * gethostbyname
 * */
#include <netdb.h>
#include <sys/types.h>

/* stream server */
#define MYPORT 4000
#define BACKLOG 10
#define LOOPFLAG 1

/* stream client */
#define PORT 4000
#define MAXDATASIZE 100

/* datagram listener*/
#define MYPORT_1 5000
#define MAXBUFLEN 100

/*select fd use*/
#define STDIN 0
#define STDOUT 1
#define STDERR 2

int sock_fd, new_fd;

void sig_urg(int signo);

void run_stream_server() {

    void (*old_sig_urg_handle)(int);

    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;

    int sin_size, n;
    char buff[100];

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);

    if (bind(sock_fd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sock_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    // setting out of bound transmission process function
    old_sig_urg_handle = signal(SIGURG, sig_urg);
    // modify owner
    fcntl(sock_fd, F_SETOWN, getpid());

    while (LOOPFLAG) {
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sock_fd, (struct sockaddr *) &their_addr, (socklen_t *) &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        printf("server: got connection from %s.\n", inet_ntoa(their_addr.sin_addr));

        if (!fork()) {
            /* child process */
            // recv
            while (LOOPFLAG) {
                if ((n = recv(new_fd, buff, sizeof(buff)-1, 0)) == 0)
                {
                    printf("received EOF. \n");
                    break ;
                }
                if (n == -1)
                    continue;
                buff[n] = 0;
                printf("Recv %d bytes: %s \n", n, buff);
            }

            // send
//            if (send(new_fd, "Hello world!\n", 14, 0) == -1) {
//                perror("send");
//                close(new_fd);
//                exit(0);
//            }
            printf("%s connection is closed.\n", inet_ntoa(their_addr.sin_addr));
            close(new_fd);
        }
    }

    /* 等待所有的子进程都退出 */
    while (waitpid(-1, NULL, WNOHANG) > 0);
    /* 恢复系统以前对SIGURG 的处理器 */
    signal(SIGURG, old_sig_urg_handle);
}

void sig_urg(int signo)
{
    int n;
    char buff[100];
    printf("SIGURG received \n");
    n = recv(new_fd, buff, sizeof(buff)-1, MSG_OOB);
    buff[n]= 0 ;
    printf("recv %d OOB byte: %s. \n" , n, buff);
}

void run_stream_client(int argc, char *argv[]) {
    int sockfd, numbytes;
    char buf[MAXDATASIZE];

    struct hostent *he;
    struct sockaddr_in their_addr;

    if (argc != 2) {
        fprintf(stderr, "usage:client hostname\n");
        exit(1);
    }

    if ((he = gethostbyname(argv[1])) == NULL) {
        herror("get host by name");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *) he->h_addr);
    bzero(&(their_addr.sin_zero), 8);

    if (connect(sockfd, (struct sockaddr *) &their_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    //send
    if (send(sockfd, "123", 3, 0) == -1)
    {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 3 byte of normal data \n");
    sleep(1);

    if(send(sockfd, "4", 1, MSG_OOB) == -1)
    {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 1 byte of OOB data \n");
    sleep(1);

    if(send(sockfd, "56", 2, 0) == -1)
    {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 2 byte of normal data \n");
    sleep(1);

    // recv
//    if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
//        perror("recv");
//        exit(1);
//    }
//    buf[numbytes] = '\0';
//    printf("received: %s", buf);
    close(sockfd);
}

void run_datagram_listener() {
    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;

    int addr_len, numbytes;
    char buf[MAXBUFLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 将阻塞IO socket 转换为非阻塞的 IO
    // fcntl(sockfd, F_SETFL, O_NONBLOCK);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    addr_len = sizeof(struct sockaddr);
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN, 0, (struct sockaddr *) &their_addr, (socklen_t *) &addr_len)) == -1) {
        perror("recv from");
        exit(1);
    }

    printf("got packet from %s\n", inet_ntoa(their_addr.sin_addr));
    printf("packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("packet contains \"%s\"\n", buf);

    close(sockfd);
}

void run_datagram_talker(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in their_addr;
    struct hostent *he;
    int numbytes;

    if (argc != 3) {
        fprintf(stderr,"usage: talker hostname message\n");
        exit(1);
    }

    if ((he = gethostbyname(argv[1])) == NULL) {
        herror("get host by name");
        exit(1);
    }
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(MYPORT);
    their_addr.sin_addr = *((struct in_addr *) he->h_addr);
    bzero(&(their_addr.sin_zero), 8);

    if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *) &their_addr, sizeof(struct sockaddr))) == -1) {
        perror("recv from");
        exit(1);
    }
    printf("sent % d bytes to %s\n",numbytes, inet_ntoa(their_addr.sin_addr));

    close(sockfd);
}

// select() IO多路复用
void select_fd_use()
{
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 2;
    tv.tv_usec = 500000;

    // clear file descriptor set
    FD_ZERO(&readfds);
    // add new file descriptor to set
    FD_SET(STDIN, &readfds);

    select(STDIN + 1, &readfds, NULL, NULL, &tv);
    // judge a fd whether it has in set
    if (FD_ISSET(STDIN, &readfds))
    {
        printf("A key has pressed!\n");
    }
    else
    {
        printf("Timed out.\n");
    }
}

void test_server_client()
{
    /* 流式套接字 + OOB*/
    run_stream_server();
//    run_stream_client(argc, argv);

    /* 数据报套接字 */
//    run_datagram_listener();
//    run_datagram_talker(argc, argv);

    /*IO多路复用*/
//    select_fd_use();
}
#endif //WEB_SERVER_CLIENT_0_H
