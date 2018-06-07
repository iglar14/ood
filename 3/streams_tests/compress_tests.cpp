#include "stdafx.h"
#include "../streams/Compressors.h"
#include "../streams/FileStreams.h"
#include "../streams/MemoryStreams.h"

static const char* STRING_TO_COMPRESS = "HELLO   WORLD!!!1111";
static const char* COMPRESSED_STRING = "\xFEHE\x02L\xffO\x03 \xFBWORLD\x03!\x04" "1";

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
	BOOST_CHECK_EQUAL_COLLECTIONS(outData.begin(), outData.end(), (uint8_t*)COMPRESSED_STRING, (uint8_t*)COMPRESSED_STRING + strlen(COMPRESSED_STRING));
}

BOOST_AUTO_TEST_CASE(decompresses_data_by_single_character)
{
	std::vector<uint8_t> inData(COMPRESSED_STRING, COMPRESSED_STRING + strlen(COMPRESSED_STRING));
	CMemoryInputStream in(inData);
	CRleDecompressStream decompressor(in);

	std::string outString;
	while (!decompressor.IsEOF())
	{
		outString.push_back(static_cast<char>(decompressor.ReadByte()));
	}

	BOOST_CHECK_EQUAL_COLLECTIONS(outString.c_str(), outString.c_str() + outString.size(), STRING_TO_COMPRESS, STRING_TO_COMPRESS + strlen(STRING_TO_COMPRESS));
}

BOOST_AUTO_TEST_CASE(compresses_data_by_blocks)
{
	CMemoryOutputStream out;
	CRleCompressStream compressor(out);

	const size_t length = strlen(STRING_TO_COMPRESS);
	size_t size = 1;
	size_t pos = 0;
	while (pos < length)
	{
		const size_t blockSize = pos + size <= length ? size : length - pos;
		compressor.WriteBlock(&STRING_TO_COMPRESS[pos], blockSize);
		pos += size;
		size += 1;
	}
	compressor.Flush();

	std::vector<uint8_t> outData = out.GetData();
	BOOST_CHECK_EQUAL_COLLECTIONS(outData.begin(), outData.end(), (uint8_t*)COMPRESSED_STRING, (uint8_t*)COMPRESSED_STRING + strlen(COMPRESSED_STRING));
}

BOOST_AUTO_TEST_CASE(decompresses_data_by_blocks)
{
	std::vector<uint8_t> inData(COMPRESSED_STRING, COMPRESSED_STRING + strlen(COMPRESSED_STRING));
	CMemoryInputStream in(inData);
	CRleDecompressStream decompressor(in);

	std::string outString;
	std::streamsize size = 1;
	while (!decompressor.IsEOF())
	{
		std::string buf(static_cast<size_t>(size), ' ');
		const std::streamsize readBytes = decompressor.ReadBlock(&buf[0], size);
		buf.resize(static_cast<size_t>(readBytes));
		outString += buf;
	}

	BOOST_CHECK_EQUAL_COLLECTIONS(outString.c_str(), outString.c_str() + outString.size(), STRING_TO_COMPRESS, STRING_TO_COMPRESS + strlen(STRING_TO_COMPRESS));
}
BOOST_AUTO_TEST_CASE(compresses_repeats_without_overflow)
{
	CMemoryOutputStream out;
	CRleCompressStream compressor(out);

	for (size_t i = 0; i < 127; i++)
	{
		compressor.WriteByte('a');
	}
	for (size_t i = 0; i < 127; i++)
	{
		compressor.WriteByte('b');
	}
	compressor.Flush();
	const char* COMPRESSED_DATA = "\x7F" "a\x7F" "b";

	std::vector<uint8_t> outData = out.GetData();
	BOOST_CHECK_EQUAL_COLLECTIONS(outData.begin(), outData.end(), (uint8_t*)COMPRESSED_DATA, (uint8_t*)COMPRESSED_DATA + strlen(COMPRESSED_DATA));

	CMemoryInputStream in(outData);
	CRleDecompressStream decompressor(in);
	for (size_t i = 0; i < 127; i++)
	{
		BOOST_CHECK_EQUAL(decompressor.ReadByte(), 'a');
	}
	for (size_t i = 0; i < 127; i++)
	{
		BOOST_CHECK_EQUAL(decompressor.ReadByte(), 'b');
	}
}

BOOST_AUTO_TEST_CASE(compresses_repeats_with_properly_handling_overflow)
{
	CMemoryOutputStream out;
	CRleCompressStream compressor(out);

	for (size_t i = 0; i < 128; i++)
	{
		compressor.WriteByte('a');
	}
	for (size_t i = 0; i < 127 * 2; i++)
	{
		compressor.WriteByte('b');
	}
	compressor.Flush();
	const char* COMPRESSED_DATA = "\x7F" "a" "\xff" "a" "\x7F" "b" "\x7F" "b";

	std::vector<uint8_t> outData = out.GetData();
	BOOST_CHECK_EQUAL_COLLECTIONS(outData.begin(), outData.end(), (uint8_t*)COMPRESSED_DATA, (uint8_t*)COMPRESSED_DATA + strlen(COMPRESSED_DATA));

	CMemoryInputStream in(outData);
	CRleDecompressStream decompressor(in);
	for (size_t i = 0; i < 128; i++)
	{
		BOOST_CHECK_EQUAL(decompressor.ReadByte(), 'a');
	}
	for (size_t i = 0; i < 127 * 2; i++)
	{
		BOOST_CHECK_EQUAL(decompressor.ReadByte(), 'b');
	}
}

BOOST_AUTO_TEST_SUITE_END()