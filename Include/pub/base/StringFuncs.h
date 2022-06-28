#pragma once

#include <string>
#include <vector>
#include <regex>
using namespace std;

namespace Base
{
	class StringFuncs
	{
	public:


		static string _trim(const string& str)

		{

			size_t start = str.find_first_not_of(" \n\r\t");

			size_t until = str.find_last_not_of(" \n\r\t");

			string::const_iterator i = start == string::npos ? str.begin() : str.begin() + start;

			string::const_iterator x = until == string::npos ? str.end() : str.begin() + until + 1;

			return string(i, x);

		}

		static void parse_url(const string& url, string& protocol, string& domain, string& port, string& path,string& file, string& query) //with boost

		{

			int offset = 0;

			size_t pos1, pos2, pos3, pos4;
			string x = _trim(url);

			offset = offset == 0 && x.compare(0, 8, "https://") == 0 ? 8 : offset;
			offset = offset == 0 && x.compare(0, 7, "http://") == 0 ? 7 : offset;

			pos1 = x.find_first_of('/', offset + 1);
			path = pos1 == string::npos ? "" : x.substr(pos1);
			domain = string(x.begin() + offset, pos1 != string::npos ? x.begin() + pos1 : x.end());
			path = (pos2 = path.find("#")) != string::npos ? path.substr(0, pos2) : path;
			port = (pos3 = domain.find(":")) != string::npos ? domain.substr(pos3 + 1) : "";
			domain = domain.substr(0, pos3 != string::npos ? pos3 : domain.length());
			protocol = offset > 0 ? x.substr(0, offset - 3) : "";
			query = (pos4 = path.find("?")) != string::npos ? path.substr(pos4 + 1) : "";
			path = pos4 != string::npos ? path.substr(0, pos4) : path;
			file = (pos1 = path.rfind("/")) != string::npos? path.substr(pos1 + 1) : "";
			path = path.substr(0, pos1+1);
		}
		static int url2domain(const std::string &url, std::string &domain, unsigned &port)
		{
			int ret = -1;

			//使用迭代器拆分字符串 http://www.cppprog.com/2009/0112/48.html

			std::regex reg_domain_port("/");  //按/符拆分字符串
			std::cregex_token_iterator itrBegin(url.c_str(), url.c_str() + url.size(), reg_domain_port, -1);
			std::cregex_token_iterator itrEnd;

			int i = 0;
			std::string domain_port;

			for (std::cregex_token_iterator itr = itrBegin; itr != itrEnd; ++itr)
			{
				i++;
				if (i == 3)
				{
					domain_port = *itr;
				}
			}

			if (domain_port.size() == 0)
			{
				domain_port = url;
			}

			//考虑带端口的情况

			std::regex reg_port(":");
			std::cregex_token_iterator itrBegin2(domain_port.c_str(), domain_port.c_str() + domain_port.size(), reg_port, -1);
			std::cregex_token_iterator itrEnd2;

			int j = 0;
			for (std::cregex_token_iterator itr = itrBegin2; itr != itrEnd2; ++itr) {
				j++;
				if (j == 1) {
					domain = *itr;
				}
				if (j == 2)
				{
					port = std::stold(*itr);
					//itoa(port,*itr,5);;
				}
			}

			if (domain.size() == 0)
			{
				domain = domain_port;
			}
			return ret;
		}



		static bool HtmlText(std::string& strSrc, string& strOut, size_t start = 0)
		{
			strOut = "";
			size_t firstpos = strSrc.find(">", start);
			while (firstpos != string::npos)
			{
				if (strSrc[firstpos + 1] != '<')
				{
					size_t endpos = strSrc.find("<", firstpos + 1);
					if (endpos != string::npos)
					{
						strOut += strSrc.substr(firstpos + 1, endpos - (firstpos + 1));
						firstpos = strSrc.find(">", endpos + 1);
					}
					else
					{
						break;
					}
				}
				else
					firstpos = strSrc.find(">", firstpos + 1);

			}

			return (strOut != "");
		}
		//字符串提取
		static bool DistillStr(std::string& strSrc, const char* strfirst, const char* strend, string& strOut, bool isAllOut = false)
		{
			size_t firstsize = strlen(strfirst);
			size_t endsize = strlen(strend);
			size_t firstpos = strSrc.find(strfirst);
			if (firstpos != string::npos)
			{
				size_t endpos = strSrc.find(strend, firstpos + firstsize);
				if (endpos != string::npos)
				{
					if (isAllOut)
					{
						strOut = strSrc.substr(firstpos, endpos + endsize - firstpos);


					}
					else
					{
						strOut = strSrc.substr(firstpos + firstsize, endpos - (firstpos + firstsize));

					}
					return (strOut != "");
				}
			}

			return false;
		}
		static int DistillStrs(std::string& strSrc, const char* strfirst, const char* strend, vector<string>& outList, bool isAllOut)
		{
			outList.clear();
			size_t firstsize = strlen(strfirst);
			size_t endsize = strlen(strend);

			size_t firstpos = strSrc.find(strfirst);
			while (firstpos != string::npos)
			{
				size_t endpos = strSrc.find(strend, firstpos + firstsize);
				if (endpos != string::npos)
				{
					if (isAllOut)
					{
						outList.push_back(strSrc.substr(firstpos, endpos + endsize - firstpos));

					}
					else
					{
						outList.push_back(strSrc.substr(firstpos + firstsize, endpos - (firstpos + firstsize)));
					}
					firstpos = strSrc.find(strfirst, endpos + endsize);

				}
				else
				{
					break;
				}


			}


			return outList.size();
		}
		static int DistillStrsX(std::string& strSrc, const char* strfirst, const char* strend, vector<string*>& outList)
		{
			outList.clear();
			size_t firstsize = strlen(strfirst);
			size_t endsize = strlen(strend);

			size_t firstpos = strSrc.find(strfirst);
			while (firstpos != string::npos)
			{
				size_t endpos = strSrc.find(strend, firstpos + firstsize);
				if (endpos != string::npos)
				{
					outList.push_back(new string(strSrc.substr(firstpos, endpos + endsize - firstpos)));

				}

				firstpos = strSrc.find(strfirst, endpos + endsize);
			}


			return outList.size();
		}

		//字符串分割函数
		static size_t splitX(std::string str, std::string pattern, std::vector<std::string*>& veclist)
		{
			std::string::size_type pos;
			veclist.clear();
			str += pattern;//扩展字符串以方便操作
			size_t size = str.size();

			for (size_t i = 0; i < size; i++)
			{
				pos = str.find(pattern, i);
				if (pos < size)
				{
					std::string *s = new string(str.substr(i, pos - i));
					veclist.push_back(s);
					i = pos + pattern.size() - 1;
				}
			}
			return veclist.size();


		}

		static string& string_replace(string& s1, const string& s2, const string& s3)
		{
			string::size_type pos = 0;
			string::size_type a = s2.size();
			string::size_type b = s3.size();
			while ((pos = s1.find(s2, pos)) != string::npos)
			{
				s1.replace(pos, a, s3);
				pos += b;
			}

			return s1;
		}

		static std::string& trim(std::string &s)
		{
			if (s.empty())
			{
				return s;
			}

			s.erase(0, s.find_first_not_of(" "));
			s.erase(s.find_last_not_of(" ") + 1);
			return s;
		}


		static size_t split2(std::string str, std::string strleft, std::string strright, std::vector<std::string>& veclist)
		{

			veclist.clear();
			size_t size = str.size();

			for (size_t i = 0; i < size; i++)
			{
				std::string::size_type posLeft = str.find(strleft, i);
				if (posLeft != string::npos)
				{
					std::string::size_type posright = str.find(strright, posLeft + 1);
					if (posright != string::npos)
					{
						std::string s = str.substr(posLeft, posright - posLeft + 1);
						veclist.push_back(s);
						i = posright;
					}

				}
			}
			return veclist.size();
		}

		static size_t split(std::string str, std::string pattern, std::vector<std::string>& veclist)
		{
			if (str == "")
			{
				return 0;
			}
			std::string::size_type pos;
			veclist.clear();
			str += pattern;//扩展字符串以方便操作
			size_t size = str.size();

			for (size_t i = 0; i < size; i++)
			{
				pos = str.find(pattern, i);
				if (pos < size)
				{
					std::string s = str.substr(i, pos - i);
					veclist.push_back(s);
					i = pos + pattern.size() - 1;
				}
			}
			return veclist.size();


		}

		static void replacestring(char* szStr, char chreplace, char chDim)
		{
			if (szStr == nullptr || strlen(szStr) == 0)
			{
				return;
			}
			int i = 0;
			while (szStr[i])
			{
				if (szStr[i] == chreplace) szStr[i] = chDim;
				i++;
			}
		}

		static string getnums(const char* csSrc)
		{
			string strret;
			int len = strlen(csSrc);
			for (int i = 0;i < len;i++)
			{
				if (csSrc[i] >= '0' && csSrc[i] <= '9')
				{
					strret += csSrc[i];
				}
			}

			return strret;
		}

	};
}

