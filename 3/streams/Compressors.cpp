#include "stdafx.h"
#include "Compressors.h"

using namespace std;

CRleCompress::CRleCompress(IOutputDataStream& stream)
	: m_stream(stream)
{

}

CRleCompress::~CRleCompress()
{

}

void CRleCompress::WriteByte(uint8_t data)
{

}
void CRleCompress::WriteBlock(const void * srcData, std::streamsize size)
{

}

CRleDecompress::CRleDecompress(IInputDataStream& stream)
	: m_stream(stream)
{

}

CRleDecompress::~CRleDecompress()
{

}

bool CRleDecompress::IsEOF()const
{
	return (m_counter == 0) && m_stream.IsEOF();
}

uint8_t CRleDecompress::ReadByte()
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

std::streamsize CRleDecompress::ReadBlock(void * dstBuffer, std::streamsize size)
{

}
