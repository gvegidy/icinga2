#ifndef THINMUTEX_H
#define THINMUTEX_H

#include "base/i2-base.h"

#define THINLOCK_UNLOCKED 0
#define THINLOCK_LOCKED 1

namespace icinga {

class I2_BASE_API ThinMutex
{
public:
	inline ThinMutex(void)
		: m_Data(THINLOCK_UNLOCKED)
	{ }

	~ThinMutex(void);

	inline void Lock(void)
	{
		bool contended = false;

		while (!__sync_bool_compare_and_swap(&m_Data, THINLOCK_UNLOCKED, THINLOCK_LOCKED)) {
			if (__sync_add_and_fetch(&m_Data, 0) > THINLOCK_LOCKED) {
				LockNative();
				return;
			}

			contended = true;
		}

		if (contended)
			MakeNative();
	}

	void MakeNative(void);
	void LockNative(void);

	inline void Unlock(void)
	{
		if (!__sync_bool_compare_and_swap(&m_Data, THINLOCK_LOCKED, THINLOCK_UNLOCKED))
			UnlockNative();
	}

	void UnlockNative(void);

private:
	uintptr_t m_Data;
};

}

#endif /* THINMUTEX_H */
