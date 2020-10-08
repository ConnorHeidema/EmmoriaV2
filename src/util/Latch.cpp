#include "util/Latch.hpp"

Latch::Latch(int const& numberOfCalls)
	: mk_numberOfCalls(numberOfCalls)
	, m_currentCall(numberOfCalls)
{}

bool Latch::CheckLatch()
{
	if (!m_currentCall)
	{
		m_currentCall = mk_numberOfCalls;
		return true;
	}
	m_currentCall--;
	return false;
}

bool Latch::Peek()
{
	return !m_currentCall;
}

void Latch::Reset()
{
	m_currentCall = mk_numberOfCalls;
}