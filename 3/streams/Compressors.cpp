#include "stdafx.h"
#include "Compressors.h"

using namespace std;

CRleCompressStream::CRleCompressStream(IOutputDataStream& stream)
	: m_stream(stream)
{

}

CRleCompressStream::~CRleCompressStream()
{

}

void CRleCompressStream::WriteByte(uint8_t data)
{

}
void CRleCompressStream::WriteBlock(const void * srcData, std::streamsize size)
{

}

void CRleCompressStream::Flush()
{

}

CRleDecompressStream::CRleDecompressStream(IInputDataStream& stream)
	: m_stream(stream)
{

}

CRleDecompressStream::~CRleDecompressStream()
{

}

bool CRleDecompressStream::IsEOF()const
{
	return (m_counter == 0) && m_stream.IsEOF();
}

uint8_t CRleDecompressStream::ReadByte()
{
	if (m_counter < 0)
	{
		++m_counter;
		return m_stream.ReadByte();
	}
	else if (m_counter > 0)
	{
		--m_counter;
		return m_value;
	}
	else	// m_counter == 0
	{
		m_counter = m_stream.ReadByte();
		m_value = m_stream.ReadByte();
		if (m_counter == 0)
		{
			throw ios_base::failure("Broken compressed data format");
		}
		return ReadByte();
	}
}

std::streamsize CRleDecompressStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	return 0;
}
