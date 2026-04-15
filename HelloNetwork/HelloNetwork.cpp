#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>


#pragma comment(lib, "ws2_32.lib")

using namespace std;



struct Target
{
    string name;
    string ip;
    int port;
    bool isOpen = false;
};




void Status(Target& target)
{
    cout << "Info Target: " << endl;
    cout << "IP: " << target.ip << endl;
    cout << "PORT: " << target.port << endl;
    cout << "Status: " << target.isOpen << endl;
}




void Info()
{
    cout << "Usa: status, list, info, help, exit\nclose, disconnect, localhost\nrun, exploit, start\ncls, clear" << endl;
}





void Exploit(Target& target)
{
    WSADATA info; 
    WSAStartup(MAKEWORD(2,2), &info);
    
    SOCKET mySocket = socket(AF_INET, SOCK_STREAM, 0);

    if (mySocket == INVALID_SOCKET) {
        cout << "[!] ERROR: Failed Creation Socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return; 
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(target.port);
    service.sin_addr.s_addr = inet_addr(target.ip.c_str());

    cout << "[i] Tentativo di connessione..." << endl;

    int connessione = connect(mySocket, (SOCKADDR*)&service, sizeof(service));

    if (connessione == SOCKET_ERROR) {
        cout << "[!] ERROR: Connessione fallita" << endl;
        target.isOpen = false;
    } else {
        target.isOpen = true;
        cout << "[+] CONNESSO: Sei dentro al bersaglio" << endl;
    }
    closesocket(mySocket); 
    WSACleanup();
}





void Change(Target& target)
{
    cout << "*************************" << endl;
    cout << " Change Server           " << endl;
    cout << "*************************" << endl;
    
    cout << endl;
    string ip;
    int port;
    
    cout << "Inserisci IP > ";
    cin >> ip;
    target.ip = ip;
    
    cout << "Inserisci PORT > ";
    cin >> port;
    target.port = port;
    
    cout << "[i] Server Cambiato con successo" << endl;
    Sleep(700);
    system("cls");
}




int main() {
    
    system("title System Logic Scanner");

    
    string command;
    Target target = {"LocalHost", "127.0.0.1", 443};
    
    
   
    
    

    
    while(true)
    {
        cout << "\nShell> ";
        cin >> command;
        
        
        if (command == "status")
        {
            Status(target);
        
        } else if (command == "change")
        {
            Change(target);
            
        } else if (command == "clear" || command == "cls")
        {
            system("cls");
            
        } else if (command == "info" || command == "target") {
            
            Status(target);
            
        } else if (command == "list" || command == "help")
        {
            Info();
        
        } else if (command == "localhost")
        {
            cout << target.name << endl;
        
        } else if (command == "start" || command == "exploit" || command == "run") {
            Exploit(target);
        
        } else if (command == "exit" || command == "close" || command == "disconnect")
        {
            cout << "[i] Exit..." << endl;
            break;
        
        }else{
            cout << "[!] Comando sconosciuto. Usa: list, info o help per visualizzare i comandi" << endl;
        }
    }

    system("pause");
    return 0;
}










