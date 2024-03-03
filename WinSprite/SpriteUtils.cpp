#include"SpriteUtils.h"
#include<Windows.h>
using namespace std;

namespace SpriteFrameWork
{

	namespace Utils
	{

		string& replace_str(string& str, const string& to_replaced, const string& newchars)
		{
			for (string::size_type pos(0); pos != string::npos; pos += newchars.length())
			{
				pos = str.find(to_replaced, pos);
				if (pos != string::npos)
					str.replace(pos, to_replaced.length(), newchars);
				else
					break;
			}
			return str;
		}

		std::string GetRootDir()     //当前可执行文件所在目录的绝对路径。exe所在路径
		{
			CHAR szapipath[_MAX_PATH];
			memset(szapipath, 0, _MAX_PATH);
			GetModuleFileNameA(NULL, szapipath, _MAX_PATH);  //全路径

			std::string exefilepath = szapipath;
			std::string filepath = exefilepath;

			replace_str(exefilepath, "\\", "/");

			string::size_type pos(0);

			size_t offset = -1;

			while (pos != std::string::npos)
			{
				offset = pos;
				pos = exefilepath.find("/", pos + 1);
			}

			std::string dir(filepath.begin(), filepath.begin() + offset);

			return dir;
		}

	}

}