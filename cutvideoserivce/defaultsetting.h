#pragma  once
namespace defaultSetting
{
	static char* settings[][2] = {
		//{ key,                 default value                                }
		  {"ip" ,             "192.168.0.104"    },
		  {"port",             "80"   },
		  {"username",         "admin"      },
		  {"password",         "admin12345" },
		  {"threadnum",         "30"},
          {"runtime",         "-1" },
          {"picpath",         "C:\\Program Files (x86)\\360\\ags\\1" },
	};
    static char* camerainfo[][4] = {
        { "9d36ed060ad047b29b080f7f5ce9cf89" ,      u8"Camera 01" ,"1","60"},
       //{ "9d36ed060ad047b29b080f7f5ce9cf89",       u8"������ζ��ͨ��" ,"0"},  //
    };
};