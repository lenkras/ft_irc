// #pragma once
// #include "Socket.hpp"
// #include "Signal.hpp"
// #include "Client.hpp"
// #include <vector>
// #include <poll.h>
// #include <iostream>
// #include <exception>
// #include <fcntl.h>
// #include <cstdlib>
// #include <sstream>
// #include <map>
// // #include <algorithm>

// class Serv
// {
//     private:
//         int port;
//         int _new_socket;
//         std::string pass;
//         Socket* sock;
//          std::vector<pollfd> fds;
// 		 std::map<int, Client> clients;


         
//     public:
//         //construc
//         Serv(int port, std::string pass);
//         ~Serv();

//         ///functions
//         void creating_socket();
//         int get_port() const;
// 		std::string get_pass();
//         void set_non_blocking(int sock_fd);
//         void accepter();
//         void launch();

// 		int parse_command(int client_fd, const std::string& line);
// 		bool authenticate_password(int client_fd, std::vector<std::string> tokens);
// 		bool addNickname(int client_fd, std::vector<std::string> tokens);
// 		bool addUser(int client_fd, std::vector<std::string> tokens);
// 		bool uniqueNickname(const std::string& nickname);
//         void send_message(int client_fd, const std::string& message);
// 		int findClient(int client_fd);
// 		void sendWelcomeMsg(int client_fd);

// 		static std::vector<std::string> splitStr (const std::string& str, std::string delim);
// };
#pragma once
#include "Socket.hpp"
#include "Signal.hpp"
#include "Client.hpp"
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <fcntl.h>
#include <cstdlib>
#include <sstream>
#include <map>
// #include <algorithm>
#include "Channel.hpp"
#include <memory>  // for shared_ptr

class Serv
{
    private:
        int port;
        int _new_socket;
        std::string pass;
        Socket* sock;
         std::vector<pollfd> fds;
		
        static std::map<std::string, std::shared_ptr<Channel>> _channels;

        std::map<int, Client> clients;
         
    public:
        //construc
        Serv(int port, std::string pass);
        ~Serv();

        ///functions
        void creating_socket();
        int get_port() const;
        std::string get_pass();
        void set_non_blocking(int sock_fd);
        void accepter();
        void launch();

		int parse_command(int client_fd, const std::string& line);
		bool authenticate_password(int client_fd, std::vector<std::string> tokens);
		bool addNickname(int client_fd, std::string name);
		bool addUser(int client_fd, std::vector<std::string> tokens);
		bool uniqueNickname(std::string nickname);
        void send_message(int client_fd, const std::string& message);
		int findClient(int client_fd);
		int findLatestMatch(int client_fd, std::string nickname);
		void sendWelcomeMsg(int client_fd);

        static std::vector<std::string> splitStr (const std::string& str, std::string delim);

        //Channel CMDs Handler
        std::shared_ptr<Channel> createChannel(const std::string &name);
        int cmdJOIN(int fd, std::vector<std::string> line);
        int cmdPART(int fd, std::vector<std::string> line);
        int cmdINVITE(int fd, std::vector<std::string> line);
        int cmdMODE(int fd, std::vector<std::string> line);
        int cmdKICK(int fd, std::vector<std::string> line);
        int cmdTOPIC(int fd, std::vector<std::string> line);
        Client* getClientByFd(int fd);
        Client* getClientByNickname(const std::string& nickname);

};
