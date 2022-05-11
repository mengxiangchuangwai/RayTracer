//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __REF_COUNTER_H__
#define __REF_COUNTER_H__

#include "Lock.h"

#define SAFE_DELETE(p) {		\
	if (p) {					\
		p->Release();			\
		if (p->GetRef() < 1) {	\
			delete p;			\
			p = NULL;			\
		}						\
	}							\
}

class RefCounter
{
	public:

		RefCounter() : m_count(1) {}

		virtual 
		~RefCounter() {}

		int 
		Release()	
		{ 
			int ret;
			m_cs.lock(); 
			ret = --m_count; 
			m_cs.unlock();
			return ret; 
		}

		int 
		AddRef()	
		{ 
			int ret;
			m_cs.lock();
			ret = ++m_count;
			m_cs.unlock();
			return ret;
		}

		int 
		GetRef() const
		{ 
			return m_count;
		}


	protected:

		mutable int			m_count;
		CriticalSection		m_cs;
};


#endif // __REF_COUNTER_H__
