#include "base/thinmutex.h"
#include <boost/thread.hpp>

using namespace icinga;

ThinMutex::~ThinMutex(void)
{
	if (m_Data > THINLOCK_LOCKED)
		delete reinterpret_cast<boost::mutex *>(m_Data);
}

void ThinMutex::MakeNative(void)
{
	boost::mutex *mtx = new boost::mutex();
	mtx->lock();
	__sync_bool_compare_and_swap(&m_Data, THINLOCK_LOCKED, mtx);
}

void ThinMutex::LockNative(void)
{
	boost::mutex *mtx = reinterpret_cast<boost::mutex *>(m_Data);
	mtx->lock();
}

void ThinMutex::UnlockNative(void)
{
	boost::mutex *mtx = reinterpret_cast<boost::mutex *>(m_Data);
	mtx->unlock();
}

