#ifdef _WIN32
#include <winerror.h>
#define ULTRA_INVAL				WSAEINVAL
#define ULTRA_ADDRINUSE	 		WSAEADDRINUSE     
#define ULTRA_ADDRNOTAVAIL 		WSAEADDRNOTAVAIL  
#define ULTRA_AFNOSUPPORT 		WSAEAFNOSUPPORT   
#define ULTRA_ALREADY	 		WSAEALREADY       
#define ULTRA_BADMSG			WSAEBADMSG        
#define ULTRA_CANCELED	 		WSAECANCELED      
#define ULTRA_CONNABORTED 		WSAECONNABORTED   
#define ULTRA_CONNREFUSED 		WSAECONNREFUSED   
#define ULTRA_CONNRESET	 		WSAECONNRESET     
#define ULTRA_DESTADDRREQ 		WSAEDESTADDRREQ   
#define ULTRA_HOSTUNREACH 		WSAEHOSTUNREACH   
#define ULTRA_IDRM		 		WSAEIDRM          
#define ULTRA_INPROGRESS		WSAEINPROGRESS    
#define ULTRA_ISCONN			WSAEISCONN        
#define ULTRA_LOOP		 		WSAELOOP          
#define ULTRA_MSGSIZE	 		WSAEMSGSIZE       
#define ULTRA_NETDOWN	 		WSAENETDOWN       
#define ULTRA_NETRESET	 		WSAENETRESET      
#define ULTRA_NETUNREACH		WSAENETUNREACH    
#define ULTRA_NOBUFS			WSAENOBUFS        
#define ULTRA_NODATA			WSAENODATA        
#define ULTRA_NOLINK			WSAENOLINK        
#define ULTRA_NOMSG		 		WSAENOMSG         
#define ULTRA_NOPROTOOPT		WSAENOPROTOOPT    
#define ULTRA_NOSR		 		WSAENOSR          
#define ULTRA_NOSTR		 		WSAENOSTR         
#define ULTRA_NOTCONN	 		WSAENOTCONN       
#define ULTRA_NOTRECOVERABLE	WSAENOTRECOVERABLE
#define ULTRA_NOTSOCK	 		WSAENOTSOCK       
#define ULTRA_NOTSUP			WSAENOTSUP        
#define ULTRA_OPNOTSUPP	 		WSAEOPNOTSUPP     
#define ULTRA_OTHER		 		WSAEOTHER         
#define ULTRA_OVERFLOW	 		WSAEOVERFLOW      
#define ULTRA_OWNERDEAD	 		WSAEOWNERDEAD     
#define ULTRA_PROTO		 		WSAEPROTO         
#define ULTRA_PROTONOSUPPORT	WSAEPROTONOSUPPORT
#define ULTRA_PROTOTYPE	 		WSAEPROTOTYPE     
#define ULTRA_TIME		 		WSAETIME          
#define ULTRA_TIMEDOUT	 		WSAETIMEDOUT      
#define ULTRA_TXTBSY			WSAETXTBSY        
#define ULTRA_WOULDBLOCK		WSAEWOULDBLOCK
#else
#include <errno.h>
#define ULTRA_INVAL				EINVAL
#define ULTRA_ADDRINUSE	 		EADDRINUSE     
#define ULTRA_ADDRNOTAVAIL 		EADDRNOTAVAIL  
#define ULTRA_AFNOSUPPORT 		EAFNOSUPPORT   
#define ULTRA_ALREADY	 		EALREADY       
#define ULTRA_BADMSG			EBADMSG        
#define ULTRA_CANCELED	 		ECANCELED      
#define ULTRA_CONNABORTED 		ECONNABORTED   
#define ULTRA_CONNREFUSED 		ECONNREFUSED   
#define ULTRA_CONNRESET	 		ECONNRESET     
#define ULTRA_DESTADDRREQ 		EDESTADDRREQ   
#define ULTRA_HOSTUNREACH 		EHOSTUNREACH   
#define ULTRA_IDRM		 		EIDRM          
#define ULTRA_INPROGRESS		EINPROGRESS    
#define ULTRA_ISCONN			EISCONN        
#define ULTRA_LOOP		 		ELOOP          
#define ULTRA_MSGSIZE	 		EMSGSIZE       
#define ULTRA_NETDOWN	 		ENETDOWN       
#define ULTRA_NETRESET	 		ENETRESET      
#define ULTRA_NETUNREACH		ENETUNREACH    
#define ULTRA_NOBUFS			ENOBUFS        
#define ULTRA_NODATA			ENODATA        
#define ULTRA_NOLINK			ENOLINK        
#define ULTRA_NOMSG		 		ENOMSG         
#define ULTRA_NOPROTOOPT		ENOPROTOOPT    
#define ULTRA_NOSR		 		ENOSR          
#define ULTRA_NOSTR		 		ENOSTR         
#define ULTRA_NOTCONN	 		ENOTCONN       
#define ULTRA_NOTRECOVERABLE	ENOTRECOVERABLE
#define ULTRA_NOTSOCK	 		ENOTSOCK       
#define ULTRA_NOTSUP			ENOTSUP        
#define ULTRA_OPNOTSUPP	 		EOPNOTSUPP     
#define ULTRA_OTHER		 		EOTHER         
#define ULTRA_OVERFLOW	 		EOVERFLOW      
#define ULTRA_OWNERDEAD	 		EOWNERDEAD     
#define ULTRA_PROTO		 		EPROTO         
#define ULTRA_PROTONOSUPPORT	EPROTONOSUPPORT
#define ULTRA_PROTOTYPE	 		EPROTOTYPE     
#define ULTRA_TIME		 		ETIME          
#define ULTRA_TIMEDOUT	 		ETIMEDOUT      
#define ULTRA_TXTBSY			ETXTBSY        
#define ULTRA_WOULDBLOCK		EWOULDBLOCK
#endif
#include <stdexcept>
namespace ultra
{
	struct network_exception : public std::runtime_error
	{
		network_exception() noexcept : runtime_error(what_message) {}
		network_exception(const char* msg) noexcept : runtime_error(msg)
		{
		}
		const char* what() const throw()
		{
			return what_message.c_str();
		}
	private:
		std::string what_message;
		friend struct stream_socket;
		friend network_exception get_network_except();
		friend void init_api();
	};
	inline network_exception get_network_except()
	{
		ultra::network_exception e;
#ifdef _WIN32
		switch (WSAGetLastError())
#else
		switch (errno)
#endif
		{
		case 0:
			e.what_message = "No error has occurred.";
		case ULTRA_NOTSOCK:
			e.what_message = "Socket operation on nonsocket.";
			break;
		case ULTRA_ISCONN:
			e.what_message = "Socket is already connected to a socket.";
			break;
		case ULTRA_NOTCONN:
			e.what_message = "Socket is not connected.";
			break;
		case ULTRA_INVAL:
			e.what_message = "Invalid argument.";
			break;
		default:
			e.what_message = "Unknown exception.";
			break;
		}
		return e;
	}
}