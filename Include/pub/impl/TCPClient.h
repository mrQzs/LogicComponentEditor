#pragma once
#include "platform.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include "StringHelper.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

#ifndef SOCKET_OK
#define SOCKET_OK         				(0)
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR					(-1)
#endif

#ifdef _WIN32
#define CLOSE_SOCKET(a)					closesocket(a)
#else
#define CLOSE_SOCKET(a)					close(a)
#endif

#ifdef _WIN32
#define SOCKET_HANDLE					SOCKET
#else
#define SOCKET_HANDLE					int32
#endif

#define __SET_BLOCKING_AFTER_CONNECTED__

// TCP客户端操作类
class CTCPClient
{
public:
	// 初始化库
	static bool InitializeLibrary() {
		if (LibraryInitialized()) {
			return true;
		}
		LibraryInitialized() = true;
#ifdef _WIN32
		WORD wVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		return (0 == WSAStartup(wVersion, &wsaData));
#else
		return true;
#endif
	}

	// 反初始化库
	static bool UnInitializeLibrary() {
		if (!LibraryInitialized()) {
			return true;
		}
		LibraryInitialized() = false;
#ifdef _WIN32
		WSACleanup();
		return true;
#else
		return true;
#endif
	}

	// 是否已经初始化库
	static bool& LibraryInitialized() {
		static bool bInitialized = false;
		return bInitialized;
	}

public:
	// 默认构造函数
	CTCPClient() {
		m_hClientSocket = INVALID_SOCKET;
		memset(m_szServerIP, 0x00, sizeof(m_szServerIP));
		m_nServerPort = 0;
		m_nTimeoutInMilliseconds = 0;
		m_bBlocking = false;
		m_bClosedByPeer = false;
		m_nErrorCode = SOCKET_OK;
		m_bConnected = false;
	}

	// 析钩函数
	~CTCPClient() {
		Disconnect();
	}

public:
	// 设置服务器参数
	bool SetParameters(const char* lpszServerIP, uint16 nServerPort, uint32 nTimeoutInMilliseconds, bool bBlocking) {
		m_nErrorCode = SOCKET_OK;
		if (NULL == lpszServerIP || strlen(lpszServerIP) <= 0 || 0 == nServerPort) {
			m_nErrorCode = -1;
			m_strErrorMsg = "IP地址或端口无效";
			return false;
		}

		sprintf_s(m_szServerIP, sizeof(m_szServerIP) - 1, "%s", lpszServerIP);
		m_nServerPort = nServerPort;
		m_nTimeoutInMilliseconds = nTimeoutInMilliseconds;
		m_bBlocking = bBlocking;

		return (strlen(m_szServerIP) > 0 && m_nServerPort > 0);
	}

	// 获取服务器IP
	const char* GetServerIP() const {
		return m_szServerIP;
	}

	// 获取服务器端口
	uint16 GetServerPort() const {
		return m_nServerPort;
	}

	// 建立连接
	bool Connect(int8 nMaxRetries) {
		m_nErrorCode = SOCKET_OK;
		if (!CTCPClient::InitializeLibrary()) {
			m_strErrorMsg = "初始化库失败";
			return false;
		}
		if (IsConnected()) {
			return true;
		}

		m_bConnected = false;
		int32 nRetries = 0;
		do
		{
			if (INVALID_SOCKET == (m_hClientSocket = socket(PF_INET, SOCK_STREAM, 0))) {
#ifdef _WIN32
				m_nErrorCode = (int32)WSAGetLastError();
				m_strErrorMsg = "创建套接字失败";
#else
				m_nErrorCode = errno;
#endif
				this->GenerateSocketErrorMsg();
				return m_bConnected;
			}

			struct sockaddr_in addrSrv;
			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(m_nServerPort);
			addrSrv.sin_addr.s_addr = inet_addr(m_szServerIP);

			if (m_bBlocking) {
				while ((nRetries++) < nMaxRetries) {
					m_bConnected = ConnectWithBlocking((struct sockaddr*)&addrSrv, (int32)sizeof(struct sockaddr));
					if (m_bConnected) {
						// 设置收发超时时间
						SetSocketSendRecvTimeout();
						break;
					}
					Disconnect();
					Sleep(100);
				}
			}
			else
			{
				while ((nRetries++) < nMaxRetries) {
					m_bConnected = ConnectWithNoBlocking((struct sockaddr*)&addrSrv, (int32)sizeof(struct sockaddr));
					if (m_bConnected) {
						// 设置收发超时时间
						SetSocketSendRecvTimeout();
						break;
					}
					Disconnect();
					Sleep(100);
				}
			}
			if (m_bConnected) {
				break;
			}

			CLOSE_SOCKET(m_hClientSocket);
			m_hClientSocket = INVALID_SOCKET;
		} while (false);

		return m_bConnected;
	}

	// 关闭连接
	bool Disconnect() {
		if (IsConnected()) {
			CLOSE_SOCKET(m_hClientSocket);
			m_hClientSocket = INVALID_SOCKET;
		}
		m_bClosedByPeer = false;
		m_bConnected = false;

		return true;
	}

	// 服务器是否已经连接
	bool IsConnected() {
		return (INVALID_SOCKET != m_hClientSocket && m_bConnected);
	}

	// 向缓冲区写入数据：-1--失败，0--超时，>0--成功
	int32 WriteData(const byte* lpszBuffer, int32 nSize) {
		m_nErrorCode = SOCKET_OK;
		m_bClosedByPeer = false;
		if (!Connect(1)) {
			return -1;
		}

		struct timeval timeout;
		timeout.tv_sec = m_nTimeoutInMilliseconds / 1000;
		timeout.tv_usec = (m_nTimeoutInMilliseconds % 1000) * 1000;
		fd_set wfds;
		FD_ZERO(&wfds);
		fd_set expfds;
		FD_ZERO(&expfds);
		FD_SET(m_hClientSocket, &wfds);
		FD_SET(m_hClientSocket, &expfds);

#ifdef _WIN32
		int32 nRet = select((int)m_hClientSocket + 1, 0, &wfds, &expfds, &timeout);
#else
		int32 nRet = select(0, 0, &wfds, &expfds, &timeout);
#endif
		// 检测错误
		if (nRet < 0) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "查询套接字可写性失败";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			FD_CLR(m_hClientSocket, &wfds);
			FD_CLR(m_hClientSocket, &expfds);

			return -1;
		}
		// 超时
		else if (nRet == 0) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "查询套接字可写性超时";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			FD_CLR(m_hClientSocket, &wfds);
			FD_CLR(m_hClientSocket, &expfds);

			return 0;
		}

		// 异常发生
		if (FD_ISSET(m_hClientSocket, &expfds)) {
			char szStdError[32 + 1] = { 0x00 };
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "写入套接字异常";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			FD_CLR(m_hClientSocket, &wfds);
			FD_CLR(m_hClientSocket, &expfds);

			return -1;
		}

		// 当前套接字可写
		if (FD_ISSET(m_hClientSocket, &wfds)) {
#ifdef _WIN32
			nRet = send(m_hClientSocket, (const char*)lpszBuffer, nSize, 0);
#else
			nRet = send(m_hClientSocket, (const void*)lpszBuffer, nSize, MSG_NOSIGNAL);
#endif
			if (nRet < 0) {
#ifdef _WIN32
				m_nErrorCode = (int32)WSAGetLastError();
				m_strErrorMsg = "写入套接字错误";
#else
				m_nErrorCode = errno;
#endif
				this->GenerateSocketErrorMsg();
				FD_CLR(m_hClientSocket, &wfds);
				FD_CLR(m_hClientSocket, &expfds);
#ifdef _WIN32
				if (WSAECONNRESET == m_nErrorCode) {
					m_bClosedByPeer = true;
					Disconnect();
				}
#endif
				return -1;
			}
			else if (nRet == 0) {
#ifdef _WIN32
				m_nErrorCode = (int32)WSAGetLastError();
				m_strErrorMsg = "写入套接字时对端关闭连接";
#else
				m_nErrorCode = errno;
#endif
				this->GenerateSocketErrorMsg();
				FD_CLR(m_hClientSocket, &wfds);
				FD_CLR(m_hClientSocket, &expfds);
#ifdef _WIN32
				if (WSAECONNRESET == m_nErrorCode) {
					m_bClosedByPeer = true;
					Disconnect();
				}
#endif
				return 0;
			}

			FD_CLR(m_hClientSocket, &wfds);
			FD_CLR(m_hClientSocket, &expfds);
			return nRet;
		}

		FD_CLR(m_hClientSocket, &wfds);
		FD_CLR(m_hClientSocket, &expfds);
		return -1;
	}

	// 从缓冲区读取数据：-1--失败，0--超时，>0--成功
	int32 ReadData(LPBYTE lpszBuffer, int32 nSize) {
		m_nErrorCode = SOCKET_OK;
		m_bClosedByPeer = false;
		if (!Connect(1)) {
			return -1;
		}

		struct timeval timeout;
		timeout.tv_sec = m_nTimeoutInMilliseconds / 1000;
		timeout.tv_usec = (m_nTimeoutInMilliseconds % 1000) * 1000;
		fd_set rfds;
		fd_set expfds;
		FD_ZERO(&rfds);
		FD_ZERO(&expfds);
		FD_SET(m_hClientSocket, &rfds);
		FD_SET(m_hClientSocket, &expfds);

#ifdef _WIN32
		int32 nRet = select(0, &rfds, 0, &expfds, &timeout);
#else
		int32 nRet = select((int)m_hClientSocket + 1, &rfds, 0, &expfds, &timeout);
#endif
		// 有错误发生
		if (nRet < 0) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "查询套接字可读性失败";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			FD_CLR(m_hClientSocket, &rfds);
			FD_CLR(m_hClientSocket, &expfds);

			return -1;
		}
		// 超时
		else if (nRet == 0) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "查询套接字可读性超时";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			FD_CLR(m_hClientSocket, &rfds);
			FD_CLR(m_hClientSocket, &expfds);

			return 0;
		}

		// 异常发生
		if (FD_ISSET(m_hClientSocket, &expfds)) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "读取套接字异常";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			FD_CLR(m_hClientSocket, &rfds);
			FD_CLR(m_hClientSocket, &expfds);

			return -1;
		}

		// 当前套接字可读
		if (FD_ISSET(m_hClientSocket, &rfds)) {
#ifdef _WIN32
			nRet = recv(m_hClientSocket, (char*)lpszBuffer, nSize, 0);
#else
			nRet = recv(m_hClientSocket, (void*)lpszBuffer, nSize, 0);
#endif
			// 读取失败
			if (nRet < 0) {
#ifdef _WIN32
				m_nErrorCode = (int32)WSAGetLastError();
				m_strErrorMsg = "读取套接字错误";
#else
				m_nErrorCode = errno;
#endif
				this->GenerateSocketErrorMsg();
				FD_CLR(m_hClientSocket, &rfds);
				FD_CLR(m_hClientSocket, &expfds);

				return -1;
			}
			// 如果对方主动断开连接，根据TCP协议，select会返回一个可读标志，
			// 但是如果你去读取数据，recv()会返回0
			else if (nRet == 0) {
				m_bClosedByPeer = true;
#ifdef _WIN32
				m_nErrorCode = (int32)WSAGetLastError();
				m_strErrorMsg = "读取套接字时对端关闭连接";
#else
				m_nErrorCode = errno;
#endif
				this->GenerateSocketErrorMsg();
				FD_CLR(m_hClientSocket, &rfds);
				FD_CLR(m_hClientSocket, &expfds);
				Disconnect();
				return 0;
			}

			FD_CLR(m_hClientSocket, &rfds);
			FD_CLR(m_hClientSocket, &expfds);

			return nRet;
		}

		FD_CLR(m_hClientSocket, &rfds);
		FD_CLR(m_hClientSocket, &expfds);

		return -1;
	}

	// 获取SOCKET句柄
	SOCKET_HANDLE GetClientSocket() {
		return m_hClientSocket;
	}

	// 对端是否关闭连接
	bool IsClosedByPeer() {
		return m_bClosedByPeer;
	}

	// 获取错误
	int32 GetErroCode() {
		return m_nErrorCode;
	}
	const char* GetErrorMsg() {
		return m_strErrorMsg.c_str();
	}

private:
	// 设置阻塞模式
	bool SetSocketBlocking(bool bBlocking) {
		if (INVALID_SOCKET == m_hClientSocket) {
			return false;
		}
#ifdef _WIN32
		unsigned long ulBlocking = bBlocking ? 0 : 1;
		if (SOCKET_ERROR == ioctlsocket(m_hClientSocket, FIONBIO, (u_long*)&ulBlocking)) {
			m_strErrorMsg = "设置套接字非阻塞失败";
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}
		else {
			return true;
		}
#else 
		int32 nFlags = 0;
		if ((nFlags = fcntl(m_hClientSocket, F_GETFL, 0)) < 0)
		{
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}
		if (bBlocking) {
			nFlags |= O_NONBLOCK;
		}
		else {
			nFlags &= ~O_NONBLOCK;
		}
		if (fcntl(m_hClientSocket, F_SETFL, nFlags) < 0)
		{
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}
#endif
	}

	// 非阻塞模式连接
	bool ConnectWithNoBlocking(struct sockaddr* pServerAddress, int32 nSize) {
		if (INVALID_SOCKET == m_hClientSocket) {
			return true;
		}

		// 设置为非阻塞模式
		if (!SetSocketBlocking(false)) {
			return false;
		}

		// 连接
		int32 nResult = connect(m_hClientSocket, pServerAddress, nSize);
		if (SOCKET_OK == nResult) {
			// 连接成功。则重新设置为阻塞模式
#ifdef __SET_BLOCKING_AFTER_CONNECTED__
			if (!SetSocketBlocking(true)) {
				return false;
			}
#endif
			return true;
		}

		// 不在连接中（即连接出错）
#ifdef _WIN32
		m_nErrorCode = WSAGetLastError();
		if (WSAEWOULDBLOCK != m_nErrorCode && WSAEINPROGRESS != m_nErrorCode) {
			m_strErrorMsg = "非阻塞模式连接套接字失败";
			// 重新设置为阻塞模式
			if (!SetSocketBlocking(true)) {
				return false;
			}
			return false;
		}
#else
		if (errno != EINPROGRESS) {
			// 重新设置为阻塞模式
			if (!SetSocketBlocking(true)) {
				return false;
			}
			return false;
		}
#endif

		// 超时时间内检查连接是否成功
		fd_set fdr, fdw;
		struct timeval timeout;

		FD_ZERO(&fdr);
		FD_ZERO(&fdw);
		FD_SET(m_hClientSocket, &fdr);
		FD_SET(m_hClientSocket, &fdw);

		timeout.tv_sec = 0;
		timeout.tv_usec = m_nTimeoutInMilliseconds * 1000;

#ifdef _WIN32
		int32 nRet = select(0, &fdr, &fdw, NULL, &timeout);
#else
		int32 nRet = select((int)m_hClientSocket + 1, &fdr, &fdw, NULL, &timeout);
#endif
		// select error
		if (nRet < 0) {
			char szStdError[32 + 1] = { 0x00 };
			// 重新设置为阻塞模式
#ifdef __SET_BLOCKING_AFTER_CONNECTED__
			if (!SetSocketBlocking(true)) {
				return false;
			}
#endif
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "非阻塞模式查询套接字连接性失败";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}
		// select timeout
		else if (nRet == 0) {
			m_strErrorMsg = "非阻塞模式查询套接字连接性超时";
			// 重新设置为阻塞模式
#ifdef __SET_BLOCKING_AFTER_CONNECTED__
			if (!SetSocketBlocking(true)) {
				return false;
			}
#endif
			return false;
		}
		else
		{
			// connected
			if (FD_ISSET(m_hClientSocket, &fdw))
			{
				// 重新设置为阻塞模式
#ifdef __SET_BLOCKING_AFTER_CONNECTED__
				if (!SetSocketBlocking(true)) {
					return false;
				}
#endif
				return true;
			}
			// timeout
			else
			{
				m_strErrorMsg = "非阻塞模式连接套接字超时";
				// 重新设置为阻塞模式
#ifdef __SET_BLOCKING_AFTER_CONNECTED__
				if (!SetSocketBlocking(true)) {
					return false;
				}
#endif
				return false;
			}
		}

		return false;
	}

	// 阻塞模式连接
	bool ConnectWithBlocking(struct sockaddr* pServerAddress, int32 nSize) {
		if (INVALID_SOCKET == m_hClientSocket) {
			return false;
		}

		if (SOCKET_OK != connect(m_hClientSocket, pServerAddress, nSize)) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "阻塞模式连接套接字失败";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}

		return true;
	}

	// 设置收发超时时间
	bool SetSocketSendRecvTimeout() {
		struct timeval send_timeout; send_timeout.tv_sec = 5; send_timeout.tv_usec = 0;
		struct timeval recv_timeout; recv_timeout.tv_sec = 5; recv_timeout.tv_usec = 0;
		int32 nRet = setsockopt(m_hClientSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&send_timeout, sizeof(send_timeout));
		if (SOCKET_ERROR == nRet) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "设置套接字发送超时失败";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}
		nRet = setsockopt(m_hClientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&recv_timeout, sizeof(recv_timeout));
		if (SOCKET_ERROR == nRet) {
#ifdef _WIN32
			m_nErrorCode = (int32)WSAGetLastError();
			m_strErrorMsg = "设置套接字接收超时失败";
#else
			m_nErrorCode = errno;
#endif
			this->GenerateSocketErrorMsg();
			return false;
		}

		return true;
	}

private:
	// 生成socket错误描述
	void GenerateSocketErrorMsg() {
#ifdef _WIN32
		switch (WSAGetLastError()) {
		case WSAEINTR:
			m_strErrorMsg = "Interrupted function call";
			break;
		case WSAEBADF:
			m_strErrorMsg = "The file handle supplied is not valid";
			break;
		case WSAEACCES:
			m_strErrorMsg = "Permission denied";
			break;
		case WSAEFAULT:
			m_strErrorMsg = "Bad address";
			break;
		case WSAEINVAL:
			m_strErrorMsg = "Invalid argument";
			break;
		case WSAEMFILE:
			m_strErrorMsg = "Too many open files";
			break;
		case WSAEWOULDBLOCK:
			m_strErrorMsg = "Resource temporarily unavailable";
			break;
		case WSAEINPROGRESS:
			m_strErrorMsg = "Operation now in progress";
			break;
		case WSAEALREADY:
			m_strErrorMsg = "Operation already in progress";
			break;
		case WSAENOTSOCK:
			m_strErrorMsg = "Socket operation on non-socket";
			break;
		case WSAEDESTADDRREQ:
			m_strErrorMsg = "Destination address required";
			break;
		case WSAEMSGSIZE:
			m_strErrorMsg = "Message too long";
			break;
		case WSAEPROTOTYPE:
			m_strErrorMsg = "Protocol wrong type for socket";
			break;
		case WSAENOPROTOOPT:
			m_strErrorMsg = "Bad protocol option";
			break;
		case WSAEPROTONOSUPPORT:
			m_strErrorMsg = "Protocol not supported";
			break;
		case WSAESOCKTNOSUPPORT:
			m_strErrorMsg = "Socket type not supported";
			break;
		case WSAEOPNOTSUPP:
			m_strErrorMsg = "Operation not supported";
			break;
		case WSAEPFNOSUPPORT:
			m_strErrorMsg = "Protocol family not supported";
			break;
		case WSAEAFNOSUPPORT:
			m_strErrorMsg = "Address family not supported by protocol family";
			break;
		case WSAEADDRINUSE:
			m_strErrorMsg = "Address already in use";
			break;
		case WSAEADDRNOTAVAIL:
			m_strErrorMsg = "Cannot assign requested address";
			break;
		case WSAENETDOWN:
			m_strErrorMsg = "Network is down";
			break;
		case WSAENETUNREACH:
			m_strErrorMsg = "Network is unreachable";
			break;
		case WSAENETRESET:
			m_strErrorMsg = "Network dropped connection on reset";
			break;
		case WSAECONNABORTED:
			m_strErrorMsg = "Software caused connection abort";
			break;
		case WSAECONNRESET:
			m_strErrorMsg = "Connection reset by peer";
			break;
		case WSAENOBUFS:
			m_strErrorMsg = "No buffer space available";
			break;
		case WSAEISCONN:
			m_strErrorMsg = "Socket is already connected";
			break;
		case WSAENOTCONN:
			m_strErrorMsg = "Socket is not connected";
			break;
		case WSAESHUTDOWN:
			m_strErrorMsg = "Cannot send after socket shutdown";
			break;
		case WSAETOOMANYREFS:
			m_strErrorMsg = "Too many references to some kernel object";
			break;
		case WSAETIMEDOUT:
			m_strErrorMsg = "Connection timed out";
			break;
		case WSAECONNREFUSED:
			m_strErrorMsg = "Connection refused";
			break;
		case WSAELOOP:
			m_strErrorMsg = "Cannot translate name";
			break;
		case WSAENAMETOOLONG:
			m_strErrorMsg = "Name component or name was too long";
			break;
		case WSAEHOSTDOWN:
			m_strErrorMsg = "Host is down";
			break;
		case WSAEHOSTUNREACH:
			m_strErrorMsg = "No route to host";
			break;
		case WSAENOTEMPTY:
			m_strErrorMsg = "Cannot remove a directory that is not empty";
			break;
		case WSAEPROCLIM:
			m_strErrorMsg = "Too many processes";
			break;
		case WSAEUSERS:
			m_strErrorMsg = "Ran out of quota";
			break;
		case WSAEDQUOT:
			m_strErrorMsg = "Ran out of disk quota";
			break;
		case WSAESTALE:
			m_strErrorMsg = "File handle reference is no longer available";
			break;
		case WSAEREMOTE:
			m_strErrorMsg = "Item is not available locally";
			break;
		case WSASYSNOTREADY:
			m_strErrorMsg = "Network subsystem is unavailable";
			break;
		case WSATYPE_NOT_FOUND:
			m_strErrorMsg = "Class type not found";
			break;
		case WSAHOST_NOT_FOUND:
			m_strErrorMsg = "Host not found";
			break;
		case WSATRY_AGAIN:
			m_strErrorMsg = "Non-authoritative host not found";
			break;
		case WSAVERNOTSUPPORTED:
			m_strErrorMsg = "WINSOCK.DLL version out of range";
			break;
		case WSAEDISCON:
			m_strErrorMsg = "Graceful shutdown in progress";
			break;
		}
#endif
	}

private:
	// SOCKET句柄
	SOCKET_HANDLE		m_hClientSocket;
	// 服务器名称
	char 				m_szServerIP[80 + 1];
	// 服务器端口
	uint16				m_nServerPort;
	// 超时时间
	uint32				m_nTimeoutInMilliseconds;
	// 是否为阻塞模式
	bool				m_bBlocking;
	// 错误
	int32				m_nErrorCode;
	std::string			m_strErrorMsg;
	// 对端是否关闭连接
	bool				m_bClosedByPeer;
	// 是否已经连接
	bool				m_bConnected;
};
