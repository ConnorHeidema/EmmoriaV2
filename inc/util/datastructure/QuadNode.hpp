#ifndef QUAD_NODE
#define QUAD_NODE

static int entityId = 0;

class QuadNode
{
public:
	QuadNode(int left, int top, int right, int bottom)
		: m_left(left)
		, m_top(top)
		, m_right(right)
		, m_bottom(bottom)
		, m_id(entityId++)
	{};

	int m_id;
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
private:

};

#endif