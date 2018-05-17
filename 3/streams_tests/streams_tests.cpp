#include "stdafx.h"
#include "../streams/Cryptors.h"
#include "../streams/FileStreams.h"
#include "../streams/MemoryStreams.h"

static const char* STRING_TO_COMPARE = "test\n1234\n\0\0\0\0";

static void ReadAndCheckTestSequence(IInputDataStream& stream)
{
	std::vector<uint8_t> v2(/*v1.size()*/16);
	BOOST_CHECK_EQUAL(v2[0] = stream.ReadByte(), STRING_TO_COMPARE[0]);
	BOOST_CHECK_EQUAL(v2[1] = stream.ReadByte(), STRING_TO_COMPARE[1]);
	BOOST_CHECK_EQUAL(v2[2] = stream.ReadByte(), STRING_TO_COMPARE[2]);
	BOOST_CHECK_EQUAL(v2[3] = stream.ReadByte(), STRING_TO_COMPARE[3]);
	BOOST_CHECK(!stream.IsEOF());

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[4], 4), 4);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.begin() + 8, STRING_TO_COMPARE, STRING_TO_COMPARE + 8);

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[8], 4), 2);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

	BOOST_CHECK(stream.IsEOF());

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[1], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[0], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

	BOOST_CHECK_THROW(stream.ReadByte(), std::ios_base::failure);
}

static void WriteTestSequence(IOutputDataStream& stream)
{
	stream.WriteByte('t');
	stream.WriteByte('e');
	stream.WriteByte('s');
	stream.WriteByte('t');

	stream.WriteBlock("\n1234", 5);
	stream.WriteByte('\n');
}

BOOST_AUTO_TEST_SUITE(CFileInputStream_tests)

BOOST_AUTO_TEST_CASE(CFileInputStream_opens_and_reads_existing_file)
{
	std::vector<uint8_t> v1(16);
	CFileInputStream fs("testExisting.txt");
	ReadAndCheckTestSequence(fs);
}

BOOST_AUTO_TEST_CASE(CFileInputStream_throws_when_file_is_missing)
{
	BOOST_CHECK_THROW({ CFileInputStream fs("testMissing.txt"); }, std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CFileOutputStream_opens_and_writes_to_file)
{
	{
		CFileOutputStream fs("testNew.txt");
		WriteTestSequence(fs);
	}
	std::vector<uint8_t> v1(16);
	CFileInputStream fs("testNew.txt");
	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[0], 16), 10);
	BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);
}

BOOST_AUTO_TEST_CASE(CFileOutputStream_throws_when_file_creation_fails)
{
	BOOST_CHECK_THROW({ CFileInputStream fs("p:\\non-existing-directory\\1234\\testMissing.txt"); }, std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CMemoryInputStream_reads_data_from_memory_vector)
{
	const std::vector<uint8_t> v1(STRING_TO_COMPARE, STRING_TO_COMPARE + 10);
	CMemoryInputStream ms(v1);

	ReadAndCheckTestSequence(ms);
}

BOOST_AUTO_TEST_CASE(CMemoryOutputStream_writes_to_vector)
{
	std::vector<uint8_t> vec;
	{
		CMemoryOutputStream ms;
		WriteTestSequence(ms);
		vec = ms.GetData();
	}
	BOOST_REQUIRE_EQUAL(vec.size(), 10u);
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 10);
}

BOOST_AUTO_TEST_CASE(decrypt_after_encrypt_makes_original_sequence)
{
	CMemoryOutputStream intremediateStorage;
	CEncryptor encr(intremediateStorage, 1488);
	WriteTestSequence(encr);

	auto encryptedData = intremediateStorage.GetData();
	CMemoryInputStream readIntermediateData(encryptedData);
	CDecryptor decr(readIntermediateData, 1488);
	ReadAndCheckTestSequence(decr);
}
BOOST_AUTO_TEST_SUITE_END()