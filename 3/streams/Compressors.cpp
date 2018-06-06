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
	const size_t nChars = m_sequence.size();
	if (nChars == 0)
	{
		assert(m_repeatCounter == 0);
		m_sequence.push_back(data);
		m_repeatCounter = 1;
	}
	else
	{
		if (nChars == 1)
		{
			if (data == m_sequence[0])
			{
				assert(m_repeatCounter > 0);
				if (m_repeatCounter == 0)
				{
					m_repeatCounter = 2;
				}
				else
				{
					++m_repeatCounter;
				}
			}
			else
			{
				if (m_repeatCounter < 2)
				{
					m_sequence.push_back(data);
				}
				else
				{
					WriteRepeat();
					m_sequence = { data };
					m_repeatCounter = 1;
				}
			}
		}
		else //if (nChars > 1)
		{
			if (data == m_sequence[nChars - 1])
			{
				WriteSequence(nChars - 1);
				++m_repeatCounter;
			}
			else
			{
				m_sequence.push_back(data);
			}
		}
	}
}
void CRleCompressStream::WriteBlock(const void * srcData, std::streamsize size)
{
	for (streamsize i = 0; i < size; ++i)
	{
		WriteByte(static_cast<const uint8_t*>(srcData)[i]);
	}
}

void CRleCompressStream::Flush()
{
	const size_t nChars = m_sequence.size();
	if (nChars == 1)
	{
		WriteRepeat();
	}
	else if (nChars > 1)
	{
		WriteSequence(nChars);
	}
}

void CRleCompressStream::WriteSequence(size_t size)
{
	assert(size <= m_sequence.size());
	assert(size > 0);

	m_stream.WriteByte(-static_cast<char>(size));
	m_stream.WriteBlock(&m_sequence[0], size);
	m_sequence.erase(m_sequence.begin(), m_sequence.begin() + size);

	m_repeatCounter = m_sequence.empty() ? 0 : 1;
}

void CRleCompressStream::WriteRepeat()
{
	assert(m_repeatCounter > 0);
	assert(m_sequence.size() == 1);

	m_stream.WriteByte(m_repeatCounter);
	m_stream.WriteByte(m_sequence[0]);
	m_sequence.clear();
	m_repeatCounter = 0;
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
		if (m_counter == 0)
		{
			throw ios_base::failure("Broken compressed data format");
		}
		if (m_counter > 0)
		{
			m_value = m_stream.ReadByte();
		}
		return ReadByte();
	}
}

streamsize CRleDecompressStream::ReadBlock(void * dstBuffer, streamsize size)
{
//	const streamsize readBytes = m_stream.ReadBlock(dstBuffer, size);
	uint8_t* dstUint = static_cast<uint8_t*>(dstBuffer);
	streamsize i = 0;
	for (i = 0; (i < size) && !IsEOF(); ++i)
	{
		dstUint[i] = ReadByte();
	}
	return i;
}
