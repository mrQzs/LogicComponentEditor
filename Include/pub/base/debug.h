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
	vsprintf(out, fmt, body);// 译注：格式化输入的字符串 fmtt</span>
	va_end(body);//       到输出字符串 ou</span>
	OutputDebugString(out);// 译注：输出格式化后的字符串到调试器</span>
};


#define ASSERT(x) {if(!(x)) _asm{int 0x03}}
#define VERIFY(x) {if(!(x)) _asm{int 0x03}}// 译注：为调试版本时产生中断有效</span>

#else
#define ASSERT(x)
#define VERIFY(x) x                  // 译注：为发行版本时不产生中断</span>
#endif

#ifdef _DEBUG
#define TRACE _trace

#else
inline void _trace(LPCTSTR fmt, ...) { }
#define TRACE  1 ? (void)0 : _trace
#endif

#endif// __DEBUG_H__</span>
