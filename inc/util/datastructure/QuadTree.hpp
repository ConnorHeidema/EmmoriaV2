#ifndef QUAD_TREE
#define QUAD_TREE

#include "QuadNode.hpp"

#include "iostream"

#include <list>
#include <memory>
#include <array>

/**
 * The quadtree is meant to simplify which objects an object should check collision for
 * it segments the window into quadrants each time there are too many objects in a list
 * and stores new objects into those quadrants. At some point, I will probably want to add
 * a balance function but an easy way to do that I suppose is just create a new quad with
 * the values again.
 */
class QuadTree
{
public:
	/**
	 * This will determine the bounds for the current quadtree
	 * Any recursive trees will be in a sub quadrant of the values
	 * given here.
	 */
	QuadTree(
		int const& leftBound,
		int const& topBound,
		int const& rightBound,
		int const& bottomBound);

	/**
	 * Retrieves the list of objects that are inside of the current object
	 * @param left the left edge of the object
	 * @param top the top edge of the object
	 * @param right the right edge of the object
	 * @param bottom the bottom edge of the object
	 * @return List of objects which are touching the object
	 */
	std::list<std::shared_ptr<QuadNode>> Retrieve(int const& left, int const& top, int const& right, int const& bottom);

	/**
	 * Inserts an object into the quad tree
	 * @param pQuadNode A node to insert
	 */
	void Insert(std::shared_ptr<QuadNode> pQuadNode);

	/**
	 * Removes a quadnode based on its unique id
	 * @param id a unique id
	 * @return If true the object was removed, if false,
	 * the object never existed in the quadtree to begin with
	 */
	bool Remove(int const& id);

	/**
	 * Empties the entire quad tree and its children
	 */
	void Clear();

private:

	enum SubQuads
	{
		TOP_LEFT = 0,
		TOP_RIGHT = 1,
		BOTTOM_RIGHT = 2,
		BOTTOM_LEFT = 3
	};

	std::list<std::shared_ptr<QuadNode>> m_rootNodePtrList;

	int m_leftBound;
	int m_topBound;
	int m_rightBound;
	int m_bottomBound;

	int m_heightMidPoint;
	int m_widthMidPoint;

	int const k_breakingNodeSize;

	std::array<std::unique_ptr<QuadTree>, 4> subTrees;
};

#endif