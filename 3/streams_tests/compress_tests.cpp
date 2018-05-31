#include "stdafx.h"
#include "../streams/Compressors.h"
#include "../streams/FileStreams.h"
#include "../streams/MemoryStreams.h"

static const char* STRING_TO_COMPRESS = "HELLO   WORLD!!!1111";
static const char* COMPRESSED_STRING = "\xFBHELLO\x03 \xFBWORLD\x03!\x041";

BOOST_AUTO_TEST_SUITE(compression_tests)
BOOST_AUTO_TEST_CASE(compresses_data_by_single_character)
{
	CMemoryOutputStream out;
	CRleCompressStream compressor(out);

	const size_t length = strlen(STRING_TO_COMPRESS);
	for (size_t i = 0; i < length; i++)
	{
		compressor.WriteByte(STRING_TO_COMPRESS[i]);
	}
	compressor.Flush();

	std::vector<uint8_t> outData = out.GetData();
	BOOST_CHECK_EQUAL(outData.size(), strlen(COMPRESSED_STRING));
	BOOST_CHECK_EQUAL_COLLECTIONS(outData.begin(), outData.end(), COMPRESSED_STRING, COMPRESSED_STRING + strlen(COMPRESSED_STRING));
}

BOOST_AUTO_TEST_SUITE_END()