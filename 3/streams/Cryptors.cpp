#include "stdafx.h"
#include "Cryptors.h"

uint8_t encrypt(uint8_t val, std::mt19937& cryptEngine)
{
	uint8_t key = cryptEngine() >> 24;
	return val + key;
}

uint8_t decrypt(uint8_t val, std::mt19937& cryptEngine)
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
	m_stream.WriteByte(encrypt(data, m_cryptEngine));
}

void CEncryptor::WriteBlock(const void* srcData, std::streamsize size)
{
	m_stream.WriteBlock(srcData, size);
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
	return decrypt(m_stream.ReadByte(), m_cryptEngine);
}

std::streamsize CDecryptor::ReadBlock(void* dstBuffer, std::streamsize size)
{
	return m_stream.ReadBlock(dstBuffer, size);
}
