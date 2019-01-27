#pragma once
#include <Windows.h>
#include <wlanapi.h>
#pragma comment(lib, "wlanapi.lib")
#include <string>
#pragma warning (disable : 4996)

namespace ultra
{
	class wlan
	{
		static inline wchar_t* create_str(wchar_t *str) noexcept
		{
			size_t l = wcslen(str);
			wchar_t* new_str = (wchar_t*)calloc(1, l + 1);
			for (unsigned long i = 0; i < l; ++i)
				new_str[i] = str[i];
			return new_str;
		}
	public:
		static DWORD last_error_code;

		/*-----________-----*/
		/*   Enumerations   */
		/*-----~~~~~~~~-----*/

		enum interface_state
		{
			not_ready,
			connected,
			ad_hoc_network_formed,
			disconnecting,
			disconnected,
			associating,
			discovering,
			authenticating
		};
		enum BSS_type
		{
			BSS_type_infrastructure = 1,
			BSS_type_independent = 2,
			BSS_type_any = 3
		};
		enum auth_algorithm {
			AUTH_ALGO_80211_OPEN = 1,
			AUTH_ALGO_80211_SHARED_KEY = 2,
			AUTH_ALGO_WPA = 3,
			AUTH_ALGO_WPA_PSK = 4,
			AUTH_ALGO_WPA_NONE = 5,               // used in NatSTA only
			AUTH_ALGO_RSNA = 6,
			AUTH_ALGO_RSNA_PSK = 7,
			AUTH_ALGO_IHV_START = 0x80000000,
			AUTH_ALGO_IHV_END = 0xffffffff
		};

		/*------_____------*/
		/*    Functions    */
		/*------~~~~~------*/

		static std::string to_cstr(const GUID &guid) noexcept
		{
			char *guid_str = new char[39];
			sprintf(guid_str, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
			return guid_str;
		}
		// return the state id into a human-readable const string.
		static const char* to_cstr(const interface_state &state) noexcept
		{
			switch (state)
			{
			case wlan::interface_state::not_ready:
				return "not ready";
				break;
			case wlan::interface_state::connected:
				return "connected";
				break;
			case wlan::interface_state::ad_hoc_network_formed:
				return "ad hoc network formed";
				break;
			case wlan::interface_state::disconnecting:
				return "disconnecting";
				break;
			case wlan::interface_state::disconnected:
				return "disconnected";
				break;
			case wlan::interface_state::associating:
				return "associating";
				break;
			case wlan::interface_state::discovering:
				return "discovering";
				break;
			case wlan::interface_state::authenticating:
				return "authenticating";
				break;
			default:
				return "unknown";
				break;
			}
		}
		static const char* to_cstr(const auth_algorithm &algorithm)
		{
			switch (algorithm)
			{
			case wlan::auth_algorithm::AUTH_ALGO_80211_OPEN:
				return "802.11 Open";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_80211_SHARED_KEY:
				return "802.11 Shared-Key";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_WPA:
				return "WPA";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_WPA_PSK:
				return "WPA-PSK";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_WPA_NONE:
				return "WPA-None";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_RSNA:
				return "RSNA";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_RSNA_PSK:
				return "RSNA-PSK";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_IHV_START:
				return "IHV-Start";
				break;
			case wlan::auth_algorithm::AUTH_ALGO_IHV_END:
				return "IHV-End";
				break;
			default:
				return "unknown";
				break;
			}
		}
		static std::string to_string(GUID guid) noexcept
		{
			char guid_str[39] = { 0 };
			sprintf(guid_str, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
			return std::string(guid_str);
		}
		// return the state id into a human-readable & modifiable string.
		static std::string state_to_string(interface_state state) noexcept
		{ return std::string(to_cstr(state)); }

		/*-------_____-------*/
		/*    Structures     */
		/*-------~~~~~-------*/



		struct device_interface
		{
			GUID guid;
			wchar_t description[256];
			interface_state state;
		};
		struct interface_list
		{
			unsigned long size;
			unsigned long index;
			device_interface list[1];
		};
		struct SSID
		{
			unsigned long length;
			unsigned char name[32];
		};
		struct network
		{
			wchar_t profile_name[WLAN_MAX_NAME_LENGTH];
			SSID ssid;
			BSS_type bss_type;
			unsigned long number_of_bssids;
			bool connectable;
			WLAN_REASON_CODE not_connectable_reason;
			unsigned long number_of_phy_types;
			DOT11_PHY_TYPE phy_types[WLAN_MAX_PHY_TYPE_NUMBER];
			// bMorePhyTypes is set to TRUE if the PHY types for the network
			// exceeds WLAN_MAX_PHY_TYPE_NUMBER.
			// In this case, uNumerOfPhyTypes is WLAN_MAX_PHY_TYPE_NUMBER and the
			// first WLAN_MAX_PHY_TYPE_NUMBER PHY types are returned.
			bool more_phy_types;
			WLAN_SIGNAL_QUALITY signal_quality;
			bool security;
			auth_algorithm auth_algorithm;
			DOT11_CIPHER_ALGORITHM default_cipher_algorithm;
			DWORD flags;
			DWORD reserved;
		};
		struct network_list
		{
			unsigned long size;
			unsigned long index;
			network list[1];
		};


		/*------________------*/
		/*   WLAN Functions   */
		/*------~~~~~~~~------*/


		static void* open_handle(DWORD version) noexcept
		{
			void *client_handle = NULL;
			last_error_code = WlanOpenHandle(version, nullptr, &version, &client_handle);
			return client_handle;
		}
		static interface_list* get_all_interfaces(void* handle)
		{
			interface_list *list = nullptr;
			last_error_code = WlanEnumInterfaces(handle, nullptr, (PWLAN_INTERFACE_INFO_LIST*)&list);
			return list;
		}
		static network_list* get_available_networks(void* handle, GUID *guid, DWORD flags)
		{
			network_list* networks = nullptr;
			WlanGetAvailableNetworkList(handle, guid, flags, nullptr, (PWLAN_AVAILABLE_NETWORK_LIST*)&networks);
			return networks;
		}
	};
	unsigned long wlan::last_error_code = ERROR_SUCCESS;
}