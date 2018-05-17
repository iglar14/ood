#include "stdafx.h"
#include "MemoryStreams.h"

using namespace std;

static ios_base::failure CreateError(const char* msg)
{
	return ios_base::failure(msg, error_code(errno, std::iostream_category()));
}

CMemoryOutputStream::CMemoryOutputStream()
{
}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
//	m_stream.put(data);
}
void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
//	m_stream.write(static_cast<const uint8_t*>(srcData), size);
}

CMemoryInputStream::CMemoryInputStream(const std::vector<uint8_t>& storage)
	: m_storage(storage)
{
}
bool CMemoryInputStream::IsEOF()const
{
	return true;
}

uint8_t CMemoryInputStream::ReadByte()
{
	uint8_t val = 0;
/*	if (!m_stream.get(val))
	{
		throw CreateError("Failed to read byte");
	}*/
	return val;
}
std::streamsize CMemoryInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
/*	if (!m_stream.read(static_cast<uint8_t*>(dstBuffer), size))
	{
		return m_stream.gcount();
	}*/
	return size;
}
