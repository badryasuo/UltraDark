// Speech API from Microsoft is required.
#include <sapi.h>
#include "std.hpp"
namespace dark
{
	class Voice
	{
	protected:
		HRESULT	hr = S_OK;
		ISpVoice * me = NULL;
		// child/teen/etc
		dark::char_ptr voice;
		// 'F' for Female, 'M' for Male
		dark::uchar gender;
		// -10 to +10
		dark::ushort pitch;
		// 0 to 100
		dark::ushort volume;
		
		
		
	public:
		static bool Init()
		{
			return ::CoInitialize(NULL);
		}
		static void Uninit()
		{
			CoUninitialize();
		}
		Voice(dark::char_ptr voice, dark::uchar gender, dark::ushort pitch)
		{
			this->voice =voice;
			this->gender = gender;
			this->pitch = pitch;
			hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&me);
		}

	};
}