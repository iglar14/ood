#include "stdafx.h"
#include "../streams/Cryptors.h"
#include "../streams/FileStreams.h"
#include "../streams/MemoryStreams.h"

static const char* STRING_TO_COMPARE = "test\n1234\n\0\0\0\0";
static const size_t STRING_SIZE = 10;
static const size_t BUFFER_SIZE = 16;

static void ReadAndCheckTestSequence(IInputDataStream& stream)
{
	std::vector<uint8_t> v2(BUFFER_SIZE);
	BOOST_CHECK_EQUAL(v2[0] = stream.ReadByte(), STRING_TO_COMPARE[0]);
	BOOST_CHECK_EQUAL(v2[1] = stream.ReadByte(), STRING_TO_COMPARE[1]);
	BOOST_CHECK_EQUAL(v2[2] = stream.ReadByte(), STRING_TO_COMPARE[2]);
	BOOST_CHECK_EQUAL(v2[3] = stream.ReadByte(), STRING_TO_COMPARE[3]);
	BOOST_CHECK(!stream.IsEOF());

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[4], 4), 4);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.begin() + 8, STRING_TO_COMPARE, STRING_TO_COMPARE + 8);

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[8], 4), 2);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + BUFFER_SIZE);

	BOOST_CHECK(stream.IsEOF());

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[1], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + BUFFER_SIZE);

	BOOST_CHECK_EQUAL(stream.ReadBlock(&v2[0], 4), 0);
	BOOST_CHECK_EQUAL_COLLECTIONS(v2.begin(), v2.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + BUFFER_SIZE);

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
	std::vector<uint8_t> v1(BUFFER_SIZE);
	CFileInputStream fs("testExisting.txt");
	ReadAndCheckTestSequence(fs);
}

BOOST_AUTO_TEST_CASE(CFileInputStream_throws_when_file_is_missing)
{
	BOOST_CHECK_THROW({ CFileInputStream fs("testMissing.txt"); }, std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CFileOutputStream_opens_and_writes_to_file)
{
	auto filePath = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
	BOOST_SCOPE_EXIT(&filePath) {
		boost::filesystem::remove(filePath);
	} BOOST_SCOPE_EXIT_END

	{
		CFileOutputStream fs(filePath.c_str());
		WriteTestSequence(fs);
	}
	std::vector<uint8_t> v1(BUFFER_SIZE);
	CFileInputStream fs(filePath.c_str());
	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[0], BUFFER_SIZE), STRING_SIZE);
	BOOST_CHECK_EQUAL_COLLECTIONS(v1.begin(), v1.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + BUFFER_SIZE);
}

BOOST_AUTO_TEST_CASE(CFileOutputStream_throws_when_file_creation_fails)
{
	BOOST_CHECK_THROW({ CFileInputStream fs("p:\\non-existing-directory\\1234\\testMissing.txt"); }, std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(CMemoryInputStream_reads_data_from_memory_vector)
{
	const std::vector<uint8_t> v1(STRING_TO_COMPARE, STRING_TO_COMPARE + STRING_SIZE);
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
	BOOST_REQUIRE_EQUAL(vec.size(), STRING_SIZE);
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(), STRING_TO_COMPARE, STRING_TO_COMPARE + STRING_SIZE);
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

BOOST_AUTO_TEST_CASE(cant_decrypt_sequence_with_different_key)
{
	CMemoryOutputStream intremediateStorage;
	CEncryptor encr(intremediateStorage, 14);
	WriteTestSequence(encr);

	auto encryptedData = intremediateStorage.GetData();
	CMemoryInputStream readIntermediateData(encryptedData);
	CDecryptor decr(readIntermediateData, 88);

	std::vector<uint8_t> decryptedResult(BUFFER_SIZE);
	BOOST_CHECK_EQUAL(decr.ReadBlock(&decryptedResult[0], decryptedResult.size()), STRING_SIZE);
	size_t differences = 0;
	for (size_t i = 0; i < decryptedResult.size(); ++i)
	{
		if (decryptedResult[i] != STRING_TO_COMPARE[i])
		{
			++differences;
		}
	}
	BOOST_CHECK(differences > STRING_SIZE / 2);
}

BOOST_AUTO_TEST_CASE(file_stream_detects_eof_correctly)
{
	std::vector<uint8_t> v1(BUFFER_SIZE);
	CFileInputStream fs("testExisting.txt");
	BOOST_CHECK_EQUAL(fs.ReadBlock(&v1[0], STRING_SIZE), STRING_SIZE);

	BOOST_CHECK(fs.IsEOF());
}

BOOST_AUTO_TEST_CASE(memory_stream_detects_eof_correctly)
{
	std::vector<uint8_t> buf(STRING_SIZE);
	std::vector<uint8_t> v1(STRING_SIZE);
	CMemoryInputStream ms(buf);
	BOOST_CHECK(!ms.IsEOF());
	BOOST_CHECK_EQUAL(ms.ReadBlock(&v1[0], STRING_SIZE), STRING_SIZE);

	BOOST_CHECK(ms.IsEOF());
}

BOOST_AUTO_TEST_CASE(empty_memory_stream_is_eof)
{
	std::vector<uint8_t> buf;
	CMemoryInputStream ms(buf);
	BOOST_CHECK(ms.IsEOF());
}

BOOST_AUTO_TEST_SUITE_END()