#include "stdafx.h"
#include "FileStreams.h"

using namespace std;
using namespace boost::filesystem;

const char* MSG_FAILED_TO_OPEN = "failed to open file";

static ios_base::failure CreateError(const char* msg)
{
	return ios_base::failure(msg, error_code(errno, std::iostream_category()));
}

CFileOutputStream::CFileOutputStream(const boost::filesystem::path& path)
{
	m_stream.exceptions(std::ofstream::badbit);
	m_stream.open(path.c_str());
	if (m_stream.fail())
	{
		throw CreateError(MSG_FAILED_TO_OPEN);
	}
}

void CFileOutputStream::WriteByte(uint8_t data)
{
	m_stream.put(data);
}
void CFileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	m_stream.write(static_cast<const uint8_t*>(srcData), size);
}

CFileInputStream::CFileInputStream(const boost::filesystem::path& path)
{
	m_stream.exceptions(std::ofstream::badbit);
	m_stream.open(path.c_str());
	if (m_stream.fail())
	{
		throw CreateError(MSG_FAILED_TO_OPEN);
	}
}
bool CFileInputStream::IsEOF()const
{
	return m_stream.eof();
}

uint8_t CFileInputStream::ReadByte()
{
	uint8_t val = 0;
	if (!m_stream.get(val))
	{
		throw CreateError("Failed to read byte");
	}
	return val;
}
std::streamsize CFileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	if (!m_stream.read(static_cast<uint8_t*>(dstBuffer), size))
	{
		return m_stream.gcount();
	}
	return size;
}
