#pragma comment(lib,"ws2_32.lib")
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>

#define DEFAULT_PORT 53
#define BUFFER_LENGTH 1024

using namespace std;



class typeofdns
{
public:
	string domain;
	string ip;
	int ttl;
	string mx;
	int mxpriority;
	string cname;
};
vector<typeofdns> alllist;
typeofdns temptypedns;



const string toHexString(const unsigned char* input, const int datasize)

{
	string output;
	char ch[3];

	for (int i = 0; i < datasize; ++i)
	{
		sprintf_s(ch, 3, "%02x", input[i]);
		output += ch;
	}
	return output;

}

const string ToHexString(const unsigned char* input, const int datasize)
{
	char  output[33];
	for (int j = 0; j < datasize; j++)
	{
		unsigned char b = *(input + j);
		sprintf_s(output + j * 2, 3, "%02x", b);
	}
	return string(output);
}

string byteToHexStr(char byte_arr[], int arr_len)
{
	string hexstr;
	for (int i = 0; i < arr_len; i++)
	{
		char hex1;
		char hex2;
		int value = byte_arr[i];
		int v1 = value / 16;
		int v2 = value % 16;

		if (v1 >= 0 && v1 <= 9)
			hex1 = (char)(48 + v1);
		else
			hex1 = (char)(55 + v1);

		if (v2 >= 0 && v2 <= 9)
			hex2 = (char)(48 + v2);
		else
			hex2 = (char)(55 + v2);

		hexstr = hexstr + hex1 + hex2;
	}
	return hexstr;
}



string Char2Hex(char a)
{
	string str = "";
	int n = a;
	for (int i = 2 * sizeof(char)-1; i >= 0; i--)
	{
		str += "0123456789ABCDEF"[((n >> i * 4) & 0xF)];
	}
	return str;
}
string GetStandardUrl(string in, string &id, string &in2)
{
	int j = 0;
	stringstream ss(in);
	string sub_str, res;
	while (getline(ss, sub_str, '^')) //以|为间隔分割test的内容
	{
		j++;
		if (j == 1)
		{
			id = sub_str;
		}
		if (j == 2)
		{
			in2 = sub_str;
		}
		if (j > 2)
		{
			res = res + sub_str + '.';
		}
	}
	res = res.assign(res.c_str(), res.length() - 1);
	return res;
}
string GetResponseText(string domain, string ip, string type, string id)
{
	string res = "";
	res = id;
	res = res + "84000001000100000000";

	return "";
}
int FindNumberOfAlllist(string in, string in2)
{
	for (int i = 0; i < alllist.size(); i++)
	{
		if (in2 == "A")// search domain
		{
			if (alllist[i].domain == in)
			{
				return i;
			}
		}
	}
	return -1;
}
string GetSearchInfo(string in)
{
	string id;
	id = in.substr(1, 2);
	return id;
}
void initiallist()
{
	temptypedns.domain = "www.tudou.com";
	temptypedns.ip = "127.0.0.1";
	temptypedns.ttl = 10;
	temptypedns.mx = "192.168.1.1";
	temptypedns.mxpriority = 10;
	temptypedns.cname = "my.tudou.com";
	alllist.push_back(temptypedns);
	temptypedns.domain = "www.youku.com";
	temptypedns.ip = "127.0.0.1";
	temptypedns.ttl = 10;
	temptypedns.mx = "192.168.1.1";
	temptypedns.mxpriority = 10;
	temptypedns.cname = "my.youku.com";
	alllist.push_back(temptypedns);
	// TODO: Add your control notification handler code here
}
void OnBnClickedButton2()
{
	GetSearchInfo("7DA50100000100000000000003777777057475646F7503636F6D0000010001");




	//string id, type;
	//string sss = GetStandardUrl("FF96^A^www^tudou^com", id, type);
	//int temp = FindNumberOfAlllist(sss, type);// 1 is for search A record
	//if (temp!=-1)// can find this domain in the list
	//{
	//	GetResponseText(sss, alllist[temp].ip, type, id);
	//}



	// TODO: Add your control notification handler code here
}
int AnalyseOriginalMessage(char in[])
{
	return 0;
}

void main()
{
	initiallist();
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sSocket;
	int iLen;
	int iSend;
	int iRecv;
	char send_buf[] = "Hello!I am a server.";
	char recv_buf[BUFFER_LENGTH];
	struct sockaddr_in ser, cli;
	printf("...................\n");
	printf("Server waiting\n");
	printf("...................\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n");
		return;
	}
	sSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sSocket == INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n", WSAGetLastError());
		return;
	}
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n", WSAGetLastError());
		return;
	}
	iLen = sizeof(cli);
	memset(recv_buf, 0, sizeof(recv_buf));
	while (1)
	{
		iRecv = recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&cli, &iLen);
		if (iRecv == SOCKET_ERROR)
		{
			printf("recvfrom()Failed:%d\n", WSAGetLastError());
			return;
		}
		else
		if (iRecv == 0)
			break;
		else
		{
			//printf("recvfrom():%s\n", recv_buf);
			//AnalyseOriginalMessage(recv_buf);
			//string sss= byteToHexStr(recv_buf, 60);
			//cout << sss;
			recv_buf[2] = (char)('a') + 35; recv_buf[7] = 1;// add head
			char tempdata = recv_buf[12]; int tempindex=12;
			while (tempdata!='\0')
			{
				tempindex = tempindex + tempdata + 1;
				tempdata = recv_buf[tempindex];
			}
			tempindex = tempindex + 5;
			recv_buf[tempindex] = (char)('a') + 95;
			tempindex++;recv_buf[tempindex] = 12; 
			tempindex++; recv_buf[tempindex] = '\0'; tempindex++; recv_buf[tempindex] = 1;
			tempindex++; recv_buf[tempindex] = '\0'; tempindex++; recv_buf[tempindex] = 1;
			tempindex++; recv_buf[tempindex] = '\0'; tempindex++; recv_buf[tempindex] = '\0'; tempindex++; tempindex++; recv_buf[tempindex] = 10;
			tempindex++; recv_buf[tempindex] = '\0'; tempindex++; recv_buf[tempindex] = 4;
			tempindex++; recv_buf[tempindex] = (char)('a') + 30;
			tempindex++; recv_buf[tempindex] = '\0'; tempindex++; recv_buf[tempindex] = '\0'; tempindex++; recv_buf[tempindex] = 1;
			printf("Accepted clint IP:[%s],port:[%d]\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
		}
		//iSend = sendto(sSocket, send_buf, sizeof(send_buf), 0, (SOCKADDR*)&cli, sizeof(cli));
		iSend = sendto(sSocket, recv_buf, sizeof(recv_buf), 0, (SOCKADDR*)&cli, sizeof(cli));
		if (iSend == SOCKET_ERROR)
		{
			printf("sendto()Failed:%d\n", WSAGetLastError());
			printf("....................\n");
			break;
		}
		else
		if (iSend == 0)
			break;
		else
		{
			printf("sendto()succeeded!\n");
			printf("................\n");
		}
	}
	closesocket(sSocket);
	WSACleanup();
}