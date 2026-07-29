#include "Pattern.h"

#include <cassert>
#include <cstdint>

int main()
{
	unsigned char bytes[] = { 0x00, 0xAA, 0xBB, 0xCC };

	// The byte after the two-byte logical range must not participate in a match.
	auto outsideLogicalRange = Pattern::Scan(
		reinterpret_cast<DWORD64>(&bytes[1]),
		2,
		"AA BB CC");
	assert(outsideLogicalRange == 0);

	// Preserve a match whose final byte is exactly at the end of the range.
	auto lastValidStart = Pattern::Scan(
		reinterpret_cast<DWORD64>(bytes),
		sizeof(bytes),
		"AA BB CC");
	assert(lastValidStart == reinterpret_cast<DWORD64>(&bytes[1]));

	return 0;
}
