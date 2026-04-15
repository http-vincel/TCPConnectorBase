# TCPConnectorBase


🇮🇹 Italiano
Descrizione

TCPConnectorBase C++ è un semplice scanner di porte TCP scritto in C++.
Il programma permette di verificare se una specifica porta su un indirizzo IP è aperta o chiusa.

Questo progetto è stato sviluppato a scopo didattico, per esercitarsi con:

- Socket programming
- Networking di base
- C++
- Strumenti di sicurezza di base


## Funzionalità

- Verifica singola porta
- Controllo stato porta (Open / Closed)
- Implementazione semplice e leggera
- Facile da modificare ed estendere


## Deployment
#### Compilation

Linux / Mac:
```bash
  g++ scanner.cpp -o namefile
```

Windows (MinGW):
```bash
  g++ scanner.cpp -o namefile.exe
```


## Disclaimer ⚠️

Questo software è stato creato solo a scopo educativo.

Utilizzare questo strumento solo su reti o sistemi di cui si possiede l'autorizzazione.
L'autore non è responsabile per eventuali usi impropri o danni causati da questo software.



## Possibili miglioramenti futuri
- Supporto multithreading
- Scansione range di porte
- Timeout configurabile
- Output colorato
- Supporto IPv6







🇬🇧 English
Description

TCPConnectorBase C++ is a basic TCP port scanner written in C++.
The program allows you to check whether a specific port on an IP address is open or closed.

This project was created for educational purposes, to practice:

- Socket programming
- Basic networking
- C++
- Basic security tools



## Features
- Single port scanning
- Open / Closed port detection
- Lightweight implementation
- Easy to modify and extend





## Deployment
#### Compilation

Linux / Mac:
```bash
  g++ scanner.cpp -o namefile
```

Windows (MinGW):
```bash
  g++ scanner.cpp -o namefile.exe
```


## Disclaimer ⚠️

This software is intended for educational purposes only.

Use this tool only on networks and systems you own or have permission to test.
The author is not responsible for any misuse or damage caused by this software.



## Future Improvements
- Multithreading support
- Port range scanning
- Configurable timeout
- Colored output
- IPv6 support






## Usage/Examples

```cpp
// Function Exploit
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
```



```cpp
// Function Change Target
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
```



```cpp
// Function Command
void Info()
{
    cout << "Usa: status, list, info, help, exit\nclose, disconnect, localhost\nrun, exploit, start\ncls, clear" << endl;
}
```
