#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>
#include <fstream>


#pragma comment(lib, "ws2_32.lib")

using namespace std;


struct Target
{
    string name;
    string ip;
    int port;
    bool isOpen = false;
    string banner;
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


void LogResult(Target& target)
{
    ofstream file;
    file.open("report.txt", ios::app);
    
    if (file.is_open()) {
        file << "-----------------------------" << endl;
        file << "TARGET: " << target.ip << endl;
        file << "PORTA : " << target.port << endl;
        file << "STATO : " << (target.isOpen ? "APERTA" : "CHIUSA") << endl;
        file << "BANNER: " << target.banner << endl;
        file << "-----------------------------" << endl;
        
        file.close();
        cout << "[+] Risultato salvato in report.txt" << endl;
    } else {
        cout << "[!] Errore: Impossibile creare il file di log." << endl;
    }
}


void Exploit(Target& target)
{
    
    ofstream logger;
    logger.open("log.txt", ios::app);
    
    
    
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
        target.banner = "Nessuna Risposta (Chiusa)";
        
        logger << "TARGET: " << target.ip << endl;
        logger << "PORTA : " << target.port << endl;
        logger << "STATO : " << (target.isOpen ? "APERTA" : "CHIUSA") << endl;
        logger << "BANNER: " << target.banner << endl;
        
        LogResult(target);
    } else {
        
        char buffer[1024] = {0};
        
        DWORD timeout = 2000;
        setsockopt(mySocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
        
        int bytesReceived = recv(mySocket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
            target.banner = string(buffer);
        } else
        {
            target.banner = "Banner non riconosciuto";
        }
        
        target.isOpen = true;

        logger << "TARGET: " << target.ip << endl;
        logger << "PORTA : " << target.port << endl;
        logger << "STATO : " << (target.isOpen ? "APERTA" : "CHIUSA") << endl;
        logger << "BANNER: " << target.banner << endl;
        
        LogResult(target);
    }
    closesocket(mySocket); 
    
    logger.close();
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



void FastScan(Target& target, int in, int fi)
{
    for (int i = in; i < fi; i++) 
    {
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
        
        DWORD timeout = 200;
        setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

        sockaddr_in service;
        service.sin_family = AF_INET;
        service.sin_port = htons(i);
        service.sin_addr.s_addr = inet_addr(target.ip.c_str());
        
        int connessione = connect(s, (SOCKADDR*)&service, sizeof(service));

        if (connessione != SOCKET_ERROR) 
        {
            cout << "[+] PORTA APERTA: " << i << endl;
            
            target.port = i;
            target.isOpen = true;
            target.banner = "Banner non richiesto"; 
            
            LogResult(target);
        }
        else 
        {
            cout << "[-] Porta " << i << " chiusa." << endl;
        }
        closesocket(s);
    }
    cout << "[i] Scansione completata." << endl;
}


int main() {
    
    WSADATA info; 
    WSAStartup(MAKEWORD(2,2), &info);
    
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
        } else if (command == "scan") {
            int in, fi;
            cout << "Porta iniziale: ";
            cin >> in;
            cout << "Porta finale: ";
            cin >> fi;
            
            FastScan(target, in, fi);
            
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
    
    
    
    int a = 10;
    int b = 5;

    if (a > b)
    {
        std::cout << "";
    }
    

    WSACleanup();
    system("pause");
    return 0;
}