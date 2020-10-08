#ifndef __LATCH__
#define __LATCH__

class Latch
{
public:
	Latch(int const& numberOfCalls);
	bool CheckLatch();
	void Reset();
private:
	int const mk_numberOfCalls;
	int m_currentCall;
};

#endif