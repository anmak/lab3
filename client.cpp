// including libraries 
#include <iostream>
#include <fstream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
	// Initialise Winsock
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		cout<<"Winsock initialization failed\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// Create socket
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		cout<<"Socket creation Failed.. error!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// Resolve IP address for hostname
	struct hostent *host;
	if((host=gethostbyname("localhost"))==NULL)
	{
		std::cout<<"Failed to resolve hostname.\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// Setup our socket address structure
	SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(55958);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);

	// Attempt to connect to server
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
	{
		std::cout<<"Failed to establish connection with server\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}






	

	// enter  the file path ...
	char filepath[1024];
	cout << "Please enter the path to the file you would like to upload" << endl;
	cin>>filepath;


	ifstream file;
	file.open(filepath);		//open file
	
	if(file.is_open()){
		file.seekg(0, ios::end);
		//file size! 
		int size = file.tellg();	
		
		cout << "The file size is " << size << " Bytes" << endl;
		//sets location back to beginning of file
		file.seekg(0, ios::beg);		
		
		char* rbuffer =new char [size] ;
		//write file to buffer
		file.read(rbuffer, size);		

		cout<<rbuffer;
		//send file to server
		
		int j = send(Socket, rbuffer, strlen(rbuffer), 0);	
		


	}


	// Shutdown our socket
	shutdown(Socket,SD_SEND);

	// Close our socket entirely
	closesocket(Socket);

	// Cleanup Winsock
	WSACleanup();
	system("PAUSE");
	return 0;
}