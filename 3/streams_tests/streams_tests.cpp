#include "stdafx.h"
#include "../streams/FileStreams.h"
#include "../streams/MemoryStreams.h"

static const char* STRING_TO_COMPARE = "test\n1234\n\0\0\0\0";

BOOST_AUTO_TEST_SUITE(CFileInputStream_tests)

BOOST_AUTO_TEST_CASE(CFileInputStream_opens_and_reads_existing_file)
{
	std::vector<uint8_t> v1(16);
	CFileInputStream fs("testExisting.txt");
	BOOST_CHECK_EQUAL(v1[0] = fs.ReadByte(), 't');
	BOOST_CHECK_EQUAL(v1[1] = fs.ReadByte(), 'e');
	BOOST_CHECK_EQUAL(v1[2] = fs.ReadByte(), 's');
	BOOST_CHECK_EQUAL(v1[3] = fs.ReadByte(), 't');
	BOOST_CHECK(!fs.IsEOF());

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[4], 4), 4);
BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.begin() + 8, STRING_TO_COMPARE, STRING_TO_COMPARE + 8);

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[8], 4), 2);
	BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

	BOOST_CHECK(fs.IsEOF());

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[10], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[0], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

	BOOST_CHECK_THROW(fs.ReadByte(), std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CFileInputStream_throws_when_file_is_missing)
{
	BOOST_CHECK_THROW({ CFileInputStream fs("testMissing.txt"); }, std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CFileOutputStream_opens_and_writes_to_file)
{
	{
		CFileOutputStream fs("testNew.txt");
		fs.WriteByte('t');
		fs.WriteByte('e');
		fs.WriteByte('s');
		fs.WriteByte('t');

		fs.WriteBlock("\n1234", 5);
		fs.WriteByte('\n');
	}
	std::vector<uint8_t> v1(16);
	CFileInputStream fs("testNew.txt");
	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[0], 16), 10);
	BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + 16);

//	BOOST_CHECK_THROW(fs.ReadByte(), std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CFileOutputStream_throws_when_file_creation_fails)
{
	BOOST_CHECK_THROW({ CFileInputStream fs("p:\\non-existing-directory\\1234\\testMissing.txt"); }, std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CMemoryInputStream_reads_data_from_memory_vector)
{
	const std::vector<uint8_t> v1(STRING_TO_COMPARE, STRING_TO_COMPARE + 10);
	CMemoryInputStream fs(v1);

	std::vector<uint8_t> v2(v1.size());
	BOOST_CHECK_EQUAL(v2[0] = fs.ReadByte(), STRING_TO_COMPARE[0]);
	BOOST_CHECK_EQUAL(v2[1] = fs.ReadByte(), STRING_TO_COMPARE[1]);
	BOOST_CHECK_EQUAL(v2[2] = fs.ReadByte(), STRING_TO_COMPARE[2]);
	BOOST_CHECK_EQUAL(v2[3] = fs.ReadByte(), STRING_TO_COMPARE[3]);
	BOOST_CHECK(!fs.IsEOF());

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v2[4], 4), 4);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.begin() + 8, STRING_TO_COMPARE, STRING_TO_COMPARE + 8);

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v2[8], 4), 2);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), v1.begin(), v1.end());

	BOOST_CHECK(fs.IsEOF());

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v2[1], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), v1.begin(), v1.end());

	BOOST_CHECK_EQUAL(fs.ReadBlock(&v2[0], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), v1.begin(), v1.end());

	BOOST_CHECK_THROW(fs.ReadByte(), std::ios_base::failure);
}
BOOST_AUTO_TEST_SUITE_END()