#include "prtScn.h"
#include <iostream>
std::string IpV4 = "127.0.0.1";
void help()
{
    std::cout << "Please specify flag:\n"
                 "'0' - Enter IPv4 adress(By default it's 127.0.0.1)\n"
                 "'1' - Scan system ports\n"
                 "'2' - Scan user ports\n"
                 "'3' - Scan user ports\n"
                 "'4' - Scan all ports\n"
                 "'5' - Print this help message\n"
                  "'-1' - Quit application\n";
}
inline void print_ports() {
    std::sort(open_ports.begin(),open_ports.end());
    for (int i: open_ports)
    {
        std::cout << "OPEN PORT: " << i << "\n";
    }
    open_ports.erase(open_ports.begin(),open_ports.end());
}
void count_open_ports(int start, int end,std::string ipv4)
{
int sockfd;
struct sockaddr_in tower;

if(inet_pton(AF_INET,IpV4.c_str(),&tower.sin_addr) < 1)
{
    fprintf(stderr, "problem loading IP adress");
    exit(EXIT_FAILURE);
}
memset(&tower, 0, sizeof(tower));
tower.sin_family = AF_INET;
tower.sin_addr.s_addr = inet_addr(IpV4.c_str());
  for(int i = start; i < end; ++i)
{
    tower.sin_port = htons(i);

    if((sockfd = socket(PF_INET,SOCK_STREAM, 0))< 0)
    {
        fprintf(stderr,"Problem with creating socket. Try Again.");
        close(sockfd);
         --i;
        continue;
    }

    if(connect(sockfd,(struct sockaddr*)&tower, sizeof(tower)) == 0)
    {
        open_ports.push_back(i);
    }
    close(sockfd);
   }
}
int main(int argc, char* argv[]) {
  help();
    int c, start, end;
    while(true)
    {
        std::cin >> c;
        switch(c)
        {
            case 0:
            {
                IpV4.erase(IpV4.begin(),IpV4.end());
                std::cout << "IpV4: ";
                std::cin >> IpV4;
            }

            case 1:
            {
                start = 0;
                end = 1023;
                count_open_ports(start,end,IpV4);
                print_ports();
            }break;

            case 2:
            {
                start = 1024;
                end = 49151;
                count_open_ports(start,end,IpV4);
                print_ports();
            }break;

            case 3:
            {
                start = 49152;
                end = 65535;
                count_open_ports(start,end,IpV4);
                print_ports();
            }break;

            case 4:
            {
                start = 0;
                end = 65535;
                count_open_ports(start,end,IpV4);
                print_ports();
            }break;

            case 5:
            {
                help();
            }break;

            case -1:
            {
                std::cout << "GOODBYE!\n";
                return 1;
            }
        }

    }
}