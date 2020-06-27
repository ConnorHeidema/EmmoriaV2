#ifndef __PERSISTENT_COMP__
#define __PERSISTENT_COMP__

/**
 * This tag should be added to any entity which should keep on living when all other entities should be destroyed
 * The idea is that sometimes all other entities should stay on the screen for x frames while the movie entity
 * is getting prepared. Then when the movie is actually started we can destroy all other entities. It could
 * be used for other purposes in the future
 */
struct PersistentComp
{ };

#endif