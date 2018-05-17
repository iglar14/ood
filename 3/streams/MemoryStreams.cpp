#include "stdafx.h"
#include "MemoryStreams.h"

using namespace std;

CMemoryOutputStream::CMemoryOutputStream()
{
}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
	m_storage.push_back(data);
}
void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* uint8Data = static_cast<const uint8_t*>(srcData);
	m_storage.insert(m_storage.end(), uint8Data, uint8Data + size);
}

CMemoryInputStream::CMemoryInputStream(const std::vector<uint8_t>& storage)
	: m_storage(storage)
{
}
bool CMemoryInputStream::IsEOF()const
{
	return m_pos >= m_storage.size();
}

uint8_t CMemoryInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw ios_base::failure("Failed to read byte after EOF");
	}
	return m_storage[m_pos++];
}
std::streamsize CMemoryInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	if (IsEOF())
	{
		return 0;
	}
	const std::streamsize realSize = min(static_cast<streamsize>(m_storage.size() - m_pos), size);
	if (realSize > size || realSize == 0)
	{
		assert(false);
		throw std::logic_error("unexpected realSize value");
	}

	memcpy(dstBuffer, &m_storage[m_pos], static_cast<size_t>(realSize));
	m_pos += static_cast<size_t>(realSize);
	return realSize;
}
