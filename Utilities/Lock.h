//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __LOCK_H__
#define __LOCK_H__

#include <windows.h>

class CriticalSection
{
	public:

		CriticalSection() 
		{ 
			::InitializeCriticalSection(&m_cs); 
		}
	
		~CriticalSection() 
		{ 
			::DeleteCriticalSection(&m_cs); 
		}

		void lock() 
		{ 
			::EnterCriticalSection(&m_cs); 
		}

		void unlock() 
		{ 
			::LeaveCriticalSection(&m_cs); 
		}


	private:

		CRITICAL_SECTION m_cs;
};


#endif	// __LOCK_H__