#include "utils.h"

char result[11];

char *withLeadingZero(int value, const char *pattern)
{
	sprintf(result, pattern, value);
	return result;
}
