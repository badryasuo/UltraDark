#ifdef _WIN32
#include <winerror.h>
#define u_INVAL				WSAEINVAL
#define u_ADDRINUSE	 		WSAEADDRINUSE     
#define u_ADDRNOTAVAIL 		WSAEADDRNOTAVAIL  
#define u_AFNOSUPPORT 		WSAEAFNOSUPPORT   
#define u_ALREADY	 		WSAEALREADY       
#define u_BADMSG			WSAEBADMSG        
#define u_CANCELED	 		WSAECANCELED      
#define u_CONNABORTED 		WSAECONNABORTED   
#define u_CONNREFUSED 		WSAECONNREFUSED   
#define u_CONNRESET	 		WSAECONNRESET     
#define u_DESTADDRREQ 		WSAEDESTADDRREQ   
#define u_HOSTUNREACH 		WSAEHOSTUNREACH   
#define u_IDRM		 		WSAEIDRM          
#define u_INPROGRESS		WSAEINPROGRESS    
#define u_ISCONN			WSAEISCONN        
#define u_LOOP		 		WSAELOOP          
#define u_MSGSIZE	 		WSAEMSGSIZE       
#define u_NETDOWN	 		WSAENETDOWN       
#define u_NETRESET	 		WSAENETRESET      
#define u_NETUNREACH		WSAENETUNREACH    
#define u_NOBUFS			WSAENOBUFS        
#define u_NODATA			WSAENODATA        
#define u_NOLINK			WSAENOLINK        
#define u_NOMSG		 		WSAENOMSG         
#define u_NOPROTOOPT		WSAENOPROTOOPT    
#define u_NOSR		 		WSAENOSR          
#define u_NOSTR		 		WSAENOSTR         
#define u_NOTCONN	 		WSAENOTCONN       
#define u_NOTRECOVERABLE	WSAENOTRECOVERABLE
#define u_NOTSOCK	 		WSAENOTSOCK       
#define u_NOTSUP			WSAENOTSUP        
#define u_OPNOTSUPP	 		WSAEOPNOTSUPP     
#define u_OTHER		 		WSAEOTHER         
#define u_OVERFLOW	 		WSAEOVERFLOW      
#define u_OWNERDEAD	 		WSAEOWNERDEAD     
#define u_PROTO		 		WSAEPROTO         
#define u_PROTONOSUPPORT	WSAEPROTONOSUPPORT
#define u_PROTOTYPE	 		WSAEPROTOTYPE     
#define u_TIME		 		WSAETIME          
#define u_TIMEDOUT	 		WSAETIMEDOUT      
#define u_TXTBSY			WSAETXTBSY        
#define u_WOULDBLOCK		WSAEWOULDBLOCK
#else
#include <errno.h>
#define u_INVAL				EINVAL
#define u_ADDRINUSE	 		EADDRINUSE     
#define u_ADDRNOTAVAIL 		EADDRNOTAVAIL  
#define u_AFNOSUPPORT 		EAFNOSUPPORT   
#define u_ALREADY	 		EALREADY       
#define u_BADMSG			EBADMSG        
#define u_CANCELED	 		ECANCELED      
#define u_CONNABORTED 		ECONNABORTED   
#define u_CONNREFUSED 		ECONNREFUSED   
#define u_CONNRESET	 		ECONNRESET     
#define u_DESTADDRREQ 		EDESTADDRREQ   
#define u_HOSTUNREACH 		EHOSTUNREACH   
#define u_IDRM		 		EIDRM          
#define u_INPROGRESS		EINPROGRESS    
#define u_ISCONN			EISCONN        
#define u_LOOP		 		ELOOP          
#define u_MSGSIZE	 		EMSGSIZE       
#define u_NETDOWN	 		ENETDOWN       
#define u_NETRESET	 		ENETRESET      
#define u_NETUNREACH		ENETUNREACH    
#define u_NOBUFS			ENOBUFS        
#define u_NODATA			ENODATA        
#define u_NOLINK			ENOLINK        
#define u_NOMSG		 		ENOMSG         
#define u_NOPROTOOPT		ENOPROTOOPT    
#define u_NOSR		 		ENOSR          
#define u_NOSTR		 		ENOSTR         
#define u_NOTCONN	 		ENOTCONN       
#define u_NOTRECOVERABLE	ENOTRECOVERABLE
#define u_NOTSOCK	 		ENOTSOCK       
#define u_NOTSUP			ENOTSUP        
#define u_OPNOTSUPP	 		EOPNOTSUPP     
#define u_OTHER		 		EOTHER         
#define u_OVERFLOW	 		EOVERFLOW      
#define u_OWNERDEAD	 		EOWNERDEAD     
#define u_PROTO		 		EPROTO         
#define u_PROTONOSUPPORT	EPROTONOSUPPORT
#define u_PROTOTYPE	 		EPROTOTYPE     
#define u_TIME		 		ETIME          
#define u_TIMEDOUT	 		ETIMEDOUT      
#define u_TXTBSY			ETXTBSY        
#define u_WOULDBLOCK		EWOULDBLOCK
#endif
#include <stdexcept>
namespace u
{
	struct network_exception
	{
		network_exception() {}
		network_exception(const char* msg)
		{
		}
		const char* what() const throw()
		{
			return what_message.c_str();
		}
	private:
		std::string what_message = "";
		friend struct stream_socket;
		friend network_exception get_network_except();
		friend void init_api();
	};
	inline network_exception get_network_except()
	{
		u::network_exception e;
#ifdef _WIN32
		switch (WSAGetLastError())
#else
		switch (errno)
#endif
		{
		case 0:
			e.what_message = "No error has occurred.";
		case u_NOTSOCK:
			e.what_message = "Socket operation on nonsocket.";
			break;
		case u_ISCONN:
			e.what_message = "Socket is already connected to a socket.";
			break;
		case u_NOTCONN:
			e.what_message = "Socket is not connected.";
			break;
		case u_INVAL:
			e.what_message = "Invalid argument.";
			break;
		default:
			e.what_message = "Unknown exception.";
			break;
		}
		return e;
	}
}