#include "stdafx.h"
#include "Cryptors.h"

using namespace std;

uint8_t Encrypt(uint8_t val, mt19937& cryptEngine)
{
	uint8_t key = cryptEngine() >> 24;
	return val + key;
}

uint8_t Decrypt(uint8_t val, mt19937& cryptEngine)
{
	uint8_t key = cryptEngine() >> 24;
	return val - key;
}

CEncryptor::CEncryptor(IOutputDataStream& stream, KeyType key)
	: m_stream(stream)
	, m_cryptEngine(key)
{
}

void CEncryptor::WriteByte(uint8_t data)
{
	m_stream.WriteByte(Encrypt(data, m_cryptEngine));
}

void CEncryptor::WriteBlock(const void* srcData, streamsize size)
{
	for (streamsize i = 0; i < size; ++i)
	{
		WriteByte(static_cast<const uint8_t*>(srcData)[i]);
	}
}

void CEncryptor::Flush()
{
	m_stream.Flush();
}

CDecryptor::CDecryptor(IInputDataStream& stream, KeyType key)
	: m_stream(stream)
	, m_cryptEngine(key)
{
}

bool CDecryptor::IsEOF()const
{
	return m_stream.IsEOF();
}

uint8_t CDecryptor::ReadByte()
{
	return Decrypt(m_stream.ReadByte(), m_cryptEngine);
}

streamsize CDecryptor::ReadBlock(void* dstBuffer, streamsize size)
{
	const streamsize readBytes = m_stream.ReadBlock(dstBuffer, size);
	uint8_t* dstUint = static_cast<uint8_t*>(dstBuffer);
	for (streamsize i = 0; i < readBytes; ++i)
	{
		dstUint[i] = Decrypt(dstUint[i], m_cryptEngine);
	}
	return readBytes;
}
