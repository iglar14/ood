#include "stdafx.h"
#include "IStreams.h"
#include "Cryptors.h"
#include "MemoryStreams.h"

using namespace std;

int main()
{
	CMemoryOutputStream outS;
	CEncryptor encr(outS, 1488);

	return 0;
}