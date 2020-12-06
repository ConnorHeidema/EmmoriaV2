#ifndef __DIALOG_QUEUE__
#define __DIALOG_QUEUE__

#include <string>
#include <list>

class DialogQueue
{
public:
	struct DialogMessage
	{
		uint32_t imageIndex;
		std::string messageContent;
		uint32_t centerXLocation;
		uint32_t centerYLocation;
	};
	DialogQueue();
	~DialogQueue();
	void Push(DialogMessage message);
	DialogMessage Pop();
private:
	std::list<DialogMessage> pDialogMessageList;
};

#endif