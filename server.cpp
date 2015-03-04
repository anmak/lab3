// including libraries
#include <iostream>
#include <winsock2.h>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		std::cout<<"WSA Initialization failed!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// socket connection 
	
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Socket==INVALID_SOCKET)
	{
		std::cout<<"Socket creation failed.\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	
	// setting the socket
	SOCKADDR_IN serverInf;
	serverInf.sin_family=AF_INET;
	serverInf.sin_addr.s_addr=INADDR_ANY;
	serverInf.sin_port=htons(55595);

	// bind socket to port
	if(bind(Socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
	{
		std::cout<<"Unable to bind socket!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// listen socket
	listen(Socket,1);

	SOCKET TempSock=SOCKET_ERROR;
	while(TempSock==SOCKET_ERROR)
	{
		std::cout<<"Waiting for incoming connections...\r\n";
		TempSock=accept(Socket,NULL,NULL);
	}
	Socket=TempSock;

	std::cout<<"Client connected!\r\n\r\n";

	


	char buffer1[1000];
	memset(buffer1,0,999);

	// receive data 
	int inDataLength=recv(Socket,buffer1,1000,0);
	
	
	// file creation at server end

	ofstream myfile ("sample1.txt");
  if (myfile.is_open())
  {
    myfile <<buffer1;
  
    myfile.close();
  }
  else cout << "Unable to open file";


	// Shutdown  socket
	shutdown(Socket,SD_SEND);

	// Close socket entirely
	closesocket(Socket);

	// Cleanup Winsock
	WSACleanup();
	system("PAUSE");
	return 0;
}