#include "util/datastructure/QuadTree.hpp"

QuadTree::QuadTree(
	int const& leftBound,
	int const& topBound,
	int const& rightBound,
	int const& bottomBound)
		: m_rootNodePtrList()
		, m_leftBound(leftBound)
		, m_topBound(topBound)
		, m_rightBound(rightBound)
		, m_bottomBound(bottomBound)
		, k_breakingNodeSize(8)
		, m_heightMidPoint((topBound + bottomBound) / 2)
		, m_widthMidPoint((leftBound + rightBound) / 2)
		, subTrees { nullptr, nullptr, nullptr, nullptr }
{}

std::list<std::shared_ptr<QuadNode>> QuadTree::Retrieve(int const& left, int const& top, int const& right, int const& bottom)
{
	std::list<std::shared_ptr<QuadNode>> returnedNodes;
	for (auto& node : m_rootNodePtrList)
	{
		bool leftInside = left >= node->m_left && left < node->m_right;
		bool topInside = top >= node->m_top && top < node->m_bottom;
		bool rightInside = right >= node->m_left && right < node->m_right;
		bool bottomInside = bottom >= node->m_top && bottom < node->m_bottom;
		if ((leftInside && topInside) ||
			(topInside && rightInside) ||
			(rightInside && bottomInside) ||
			(bottomInside && leftInside))
		{
			returnedNodes.emplace_back(node);
		}
	}
	if (left < m_widthMidPoint)
	{
		if (top < m_heightMidPoint && subTrees[TOP_LEFT])
		{
			returnedNodes.splice(
				returnedNodes.end(),
				subTrees[TOP_LEFT]->Retrieve(left, top, right, bottom));
		}
		if (bottom > m_heightMidPoint && subTrees[BOTTOM_LEFT])
		{
			returnedNodes.splice(
				returnedNodes.end(),
				subTrees[BOTTOM_LEFT]->Retrieve(left, top, right, bottom));
		}
	}
	if (right > m_widthMidPoint)
	{
		if (top < m_heightMidPoint && subTrees[TOP_RIGHT])
		{
			returnedNodes.splice(
				returnedNodes.end(),
				subTrees[TOP_RIGHT]->Retrieve(left, top, right, bottom));
		}
		if (bottom > m_heightMidPoint && subTrees[BOTTOM_RIGHT])
		{
			returnedNodes.splice(
				returnedNodes.end(),
				subTrees[BOTTOM_RIGHT]->Retrieve(left, top, right, bottom));
		}
	}
	return returnedNodes;
}

void QuadTree::Insert(std::shared_ptr<QuadNode> pQuadNode)
{
	if (m_rootNodePtrList.size() < (unsigned int)k_breakingNodeSize)
	{
		m_rootNodePtrList.emplace_back(pQuadNode);
		return;
	}

	if (pQuadNode->m_left > m_leftBound &&
		pQuadNode->m_top > m_topBound &&
		pQuadNode->m_right < m_widthMidPoint &&
		pQuadNode->m_bottom < m_heightMidPoint)
	{
		if (!subTrees[TOP_LEFT])
		{
			subTrees[TOP_LEFT] = std::make_unique<QuadTree>(
				m_leftBound,
				m_topBound,
				m_widthMidPoint,
				m_heightMidPoint);
		}
		subTrees[TOP_LEFT]->Insert(pQuadNode);
	}
	else if (pQuadNode->m_left > m_widthMidPoint &&
		pQuadNode->m_top > m_topBound &&
		pQuadNode->m_right < m_rightBound &&
		pQuadNode->m_bottom < m_heightMidPoint)
	{
		if (!subTrees[TOP_RIGHT])
		{
			subTrees[TOP_RIGHT] = std::make_unique<QuadTree>(
				m_widthMidPoint,
				m_topBound,
				m_rightBound,
				m_heightMidPoint);
		}
		subTrees[TOP_RIGHT]->Insert(pQuadNode);
	}
	else if (pQuadNode->m_left > m_widthMidPoint &&
		pQuadNode->m_top > m_heightMidPoint &&
		pQuadNode->m_right < m_rightBound &&
		pQuadNode->m_bottom < m_bottomBound)
	{
		if (!subTrees[BOTTOM_RIGHT])
		{
			subTrees[BOTTOM_RIGHT] = std::make_unique<QuadTree>(
				m_widthMidPoint,
				m_heightMidPoint,
				m_rightBound,
				m_bottomBound);
		}
		subTrees[BOTTOM_RIGHT]->Insert(pQuadNode);
	}
	else if (pQuadNode->m_left > m_leftBound &&
		pQuadNode->m_top > m_heightMidPoint &&
		pQuadNode->m_right < m_widthMidPoint &&
		pQuadNode->m_bottom < m_bottomBound)
	{
		if (!subTrees[BOTTOM_LEFT])
		{
			subTrees[BOTTOM_LEFT] = std::make_unique<QuadTree>(
				m_leftBound,
				m_heightMidPoint,
				m_widthMidPoint,
				m_bottomBound);
		}
		subTrees[BOTTOM_LEFT]->Insert(pQuadNode);
	}
}

bool QuadTree::Remove(int const& id)
{
	for (auto nodeIter = m_rootNodePtrList.begin();
		 nodeIter != m_rootNodePtrList.end();
		 nodeIter++)
	{
		if (id == (*nodeIter)->m_id)
		{
			m_rootNodePtrList.remove(*nodeIter);
			return true;
		}
	}
	if ((subTrees[TOP_LEFT] && subTrees[TOP_LEFT]->Remove(id)) ||
		(subTrees[TOP_RIGHT] && subTrees[TOP_RIGHT]->Remove(id)) ||
		(subTrees[BOTTOM_RIGHT] && subTrees[BOTTOM_RIGHT]->Remove(id)) ||
		(subTrees[BOTTOM_LEFT] && subTrees[BOTTOM_LEFT]->Remove(id)))
	{
		for (int treeCorner = 0; (unsigned int)treeCorner < subTrees.size(); treeCorner++)
		{
			if (subTrees[treeCorner] && subTrees[treeCorner]->m_rootNodePtrList.size() == 0)
			{
				subTrees[treeCorner] = nullptr;
			}
		}
		return true;
	}
	return false;
}

void QuadTree::Clear()
{
	for (int treeCorner = 0; (unsigned int)treeCorner < subTrees.size(); treeCorner++)
	{
		if (subTrees[treeCorner] && subTrees[treeCorner]->m_rootNodePtrList.size() == 0)
		{
			subTrees[treeCorner]->Clear();
			subTrees[treeCorner] = nullptr;
		}
	}
	m_rootNodePtrList.clear();
}
