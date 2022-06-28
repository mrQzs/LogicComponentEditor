#pragma once
#include <string>
using namespace std;

inline std::string operator <<(LPCSTR lval, std::string& rval)
{
	string str(lval);
	str += rval;
	return str;
}

inline std::string& operator <<(std::string& lval, LPCSTR rval)
{
	lval += rval;
	return lval;
}

inline std::string& operator <<(std::string& lval, const string& rval)
{

	lval += rval;
	return lval;
}
inline std::string& operator <<(std::string& lval, const uint32& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%u", rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const int32& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%d", rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const uint16& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%u", rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const int16& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%d", rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const uint8& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%u", (uint32)rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const char& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%d", (int32)rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval,const uint64& rval)
{
	char temp[20] = { 0 };
#ifdef __GUNC__
	sprintf(temp,"%llu", rval);
#else
	sprintf(temp,"%I64u", rval);
#endif
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const int64& rval)
{
	char temp[20] = { 0 };
#ifdef __GUNC__
	sprintf(temp, "%lld", rval);
#else
	sprintf(temp, "%I64d", rval);
#endif
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const float& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%f", rval);
	lval += temp;
	return lval;
}
inline std::string& operator <<(std::string& lval, const double& rval)
{
	char temp[20] = { 0 };
	sprintf(temp, "%lf", rval);
	lval += temp;
	return lval;
}

static int64_t stringToint64(LPCSTR strval)
{
#ifdef WIN32
	return _atoi64(strval);
#else
	return atoll(strval);
#endif

}
static string int64Tostring(int64_t nValue)
{
	char sz[100];
#ifdef WIN32
	sprintf(sz, "%I64u", nValue);
#else
	sprintf(sz, "%llu", nValue);
#endif
	return sz;
}

//10进制和x进制的换算
class CBaseDigitalConv
{
public:
	CBaseDigitalConv() {}
	virtual ~CBaseDigitalConv() {}

public:
	//10进制转化成的x进制长度，不足nMinLen长度的话高位补0，否则不改变什么
	string to_x(const string& src10, int nMinLen)
	{
		string dst;
		uint64_t src = stringToint64(src10);
		while (src != 0) {
			int nMod = src % m_nDigital;
			char szTmp[2];
			szTmp[0] = m_charSet[nMod];
			szTmp[1] = 0;
			dst.append(szTmp);

			src = src / m_nDigital;
		}

		reverse(dst.begin(), dst.end());
		string str = convMinLen(dst, nMinLen);
		return str;
	}

	//x进制转为10进制
	string to_10(const string& srcx, int nMinLen)
	{
		uint64_t dst = 0L;
		for (size_t i = 0; i < srcx.length(); i++)
		{
			char c = srcx[i];
			for (size_t j = 0; j < strlen(m_charSet); j++)
			{
				if (c == m_charSet[j])
				{
					dst = (dst * m_nDigital) + j;
					break;
				}
			}
		}

		string str = convMinLen(int64Tostring(dst), nMinLen);
		return str;
	}

protected:
	static string convMinLen(const string& src, int nMinLen)
	{
		int nAddLen = nMinLen - src.length();
		string strTmp;
		for (int i = 0; i < nAddLen; i++)
		{
			strTmp += "0";
		}
		return strTmp + src;
	}

	//初始化，设置字符集
	void init(const char* charSet)
	{
		strcpy(m_charSet, charSet);
		m_nDigital = strlen(m_charSet);
	}

private:
	char    m_charSet[128];
	int        m_nDigital;
};

//10进制和64进制的换算，如 0120160524121052485  --》 00008sKrPTsBmv
class CDigitalConv64 : public CBaseDigitalConv
{
public:
	CDigitalConv64()
	{
		init("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-");
	}
	virtual ~CDigitalConv64() {}
};
