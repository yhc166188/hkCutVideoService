#pragma  once
namespace defaultSetting
{
	static char* settings[][2] = {
		//{ key,                 default value                                }
		  {"ip" ,             "192.168.0.104"    },
		  {"port",             "80"   },
		  {"username",         "admin"      },
		  {"password",         "admin12345" },
		  {"threadnum",         "3"},
          {"runtime",         "-1" },
          {"picpath",         "C:\\Program Files (x86)\\360\\ags\\1" },
	};
    static char* camerainfo[][3] = {
        { "9d36ed060ad047b29b080f7f5ce9cf89" ,      u8"Camera 01" ,"1"},
       //{ "9d36ed060ad047b29b080f7f5ce9cf89",       u8"北杭州味道通道" ,"0"},  //
    };
};