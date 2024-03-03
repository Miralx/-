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

		std::string GetRootDir()     //��ǰ��ִ���ļ�����Ŀ¼�ľ���·����exe����·��
		{
			CHAR szapipath[_MAX_PATH];
			memset(szapipath, 0, _MAX_PATH);
			GetModuleFileNameA(NULL, szapipath, _MAX_PATH);  //ȫ·��

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