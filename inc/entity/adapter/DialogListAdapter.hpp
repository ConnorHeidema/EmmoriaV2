#ifndef __DIALOG_LIST_IADAPTER__
#define __DIALOG_LIST_IADAPTER__

#include "entity/adapter/IAdapter.hpp"
#include "component/functional/DialogComp.hpp"

#include <list>

// BottomDialog 5 Our tale begins in the small sacred forest by your home village.
// You have stumbled into a strange cavern and need to find your way out!-*Files/0,0* *
/**
 * Purpose:
 */
class DialogListAdapter
	: public IAdapter
{
public:
	std::istringstream TransformData(std::string inData) override;

private:
	std::list<DialogComp> unshortenedDialogs;
	std::list<DialogComp> shortenedDialogs;
};

#endif