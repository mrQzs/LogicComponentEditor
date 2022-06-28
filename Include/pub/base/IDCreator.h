#pragma once
#include "platform.h"
#include "Singleton.h"
#include "pubfuncs.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>




#define NewID IDCreator::instance()->GetIDString().c_str()


class GIDGenerate :public Base::Singleton<GIDGenerate>
{
	int get_seed()
	{
		int hour = std::atoi(__TIME__);
		int min = std::atoi(__TIME__ + 3);
		int sec = std::atoi(__TIME__ + 6);
		return 10000 * hour + 100 * min + sec;
	}

	std::string GetGID()
	{
		// get_seed() returns an int based on __TIME__ (a string literal
	// set by the preprocessor), which is known at compile time.
	//
	// Also, w/r/t the engines in <random>: not setting a seed explicitly
	// will use a default seed, which is known at compile time.  So if
	// you're OK getting the same sequence of numbers for any compilation,
	// then "std::mt19937_64 rng;" may be all you need.
		std::mt19937_64 rng(get_seed());
		std::uniform_real_distribution<double> zero_one(0.0, 1.0);
		const int COUNT = 1000;
		std::generate_n(std::ostream_iterator<double>(std::cout, "\n"), COUNT,
			[&rng, &zero_one]() { return zero_one(rng); });
		return 0;
	}
public:

};



template<uint64 tid>
class IDCreator:public Base::Singleton<IDCreator<tid>>
{
public:

	IDCreator()
	{
		m_id = 0;
		
	}

	unsigned long GetID()
	{
		AUTOLOCK(m_mtx);
		m_id++;
		if (m_id>= 0xffffffff)
		{
			m_id=1;
		}
		return m_id;
	}
	const char* GetIDString()
	{
		unsigned int id = GetID();
		char szID[50] = { 0 };
		sprintf_s(szID, "%u", id);
		return szID;
	}

	unsigned int m_id;
	
	std::mutex m_mtx;
};


template<>
class IDCreator<0>
{
public:

	IDCreator()
	{
		m_id = 0;

	}

	unsigned long GetID()
	{
		AUTOLOCK(m_mtx);
		m_id++;
		if (m_id >= 0xffffffff)
		{
			m_id = 1;
		}
		return m_id;
	}
	const char* GetIDString()
	{
		
		AUTOLOCK(m_mtx);
		m_id++;
		if (m_id >= 0xffffffff)
		{
			m_id = 1;
		}
		sprintf_s(szID, "%u", m_id);
		return szID;
	}

	char szID[50] = { 0 };
	unsigned int m_id;
	std::mutex m_mtx;
};

