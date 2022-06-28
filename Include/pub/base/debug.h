#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef _DEBUG

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

inline void _trace(const char* fmt, ...)
{
	char out[1024] = {0};
	va_list body;
	va_start(body, fmt);
	vsprintf(out, fmt, body);// ��ע����ʽ��������ַ��� fmtt</span>
	va_end(body);//       ������ַ��� ou</span>
	OutputDebugString(out);// ��ע�������ʽ������ַ�����������</span>
};


#define ASSERT(x) {if(!(x)) _asm{int 0x03}}
#define VERIFY(x) {if(!(x)) _asm{int 0x03}}// ��ע��Ϊ���԰汾ʱ�����ж���Ч</span>

#else
#define ASSERT(x)
#define VERIFY(x) x                  // ��ע��Ϊ���а汾ʱ�������ж�</span>
#endif

#ifdef _DEBUG
#define TRACE _trace

#else
inline void _trace(LPCTSTR fmt, ...) { }
#define TRACE  1 ? (void)0 : _trace
#endif

#endif// __DEBUG_H__</span>
