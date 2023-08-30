#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <vector>
#include <algorithm>
using std::vector;

static vector<int> open_ports;