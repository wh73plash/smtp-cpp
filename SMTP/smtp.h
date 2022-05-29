//
//  smtp.h
//  SMTP
//
//  Created by 김제인 on 2022/05/30.
//

#ifndef smtp_h
#define smtp_h

#include <iostream>
#include <cstdio>
#include <fstream>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <cstring>
#include <netdb.h>

#define SOCKET int
#define INVALID_SOCKET -1

using namespace std;

class smtp{
public:
    smtp(){};
    ~smtp(){};
    
    void send(void){
        std::ofstream fp;
        char send_buffer[512], receive_buffer[512];
        
        fp.open("test.txt");
        if(fp.fail()){
            throw std::runtime_error("file open error");
            exit(EXIT_FAILURE);
        }else if(!fp.is_open()){
            throw std::runtime_error("failed to open the file \'test.txt\'");
            exit(EXIT_FAILURE);
        }
        SOCKET server_socket = NULL;
        struct sockaddr_in serv_addr;
        server_socket = socket(PF_INET, SOCK_STREAM, 0);
        if(server_socket == INVALID_SOCKET){
            throw std::runtime_error("socket error");
        }else{
            std::memset(&serv_addr, 0, sizeof(serv_addr));
        }
        
        hostent* target = gethostbyname("");
        if(target == NULL){
            throw std::runtime_error("gethostbyname error");
            exit(EXIT_FAILURE);
        }else{
            std::memcpy(&(serv_addr.sin_addr), target->h_addr_list, target->h_length);
            serv_addr.sin_family = target->h_addrtype;
            serv_addr.sin_port = htons(8080);
        }
        
        int buffer = connect(server_socket, (sockaddr*)&serv_addr, sizeof(serv_addr));
        if(buffer == INVALID_SOCKET){
            throw std::runtime_error("connect error");
        }
        
        ssize_t bytes = recv(server_socket, receive_buffer, sizeof(receive_buffer), 0);
        receive_buffer[bytes] = '\0';
        fp << receive_buffer;
        //-----
    }
};

#endif /* smtp_h */
