
#include "IGuidCounted.h"

// Initialize static counters.
size_t IGuidCounted::_nextGuid = 1;
size_t IGuidCounted::_totalCount = 0;