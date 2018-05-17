#pragma once
#include "IStreams.h"

class CEncryptor final: public IOutputDataStream
{
public:
	using KeyType = std::mt19937::result_type;
	CEncryptor(IOutputDataStream& stream, KeyType key);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;
private:
	IOutputDataStream& m_stream;
	std::mt19937 m_cryptEngine;
};

class CDecryptor final : public IInputDataStream
{
public:
	using KeyType = std::mt19937::result_type;
	CDecryptor(IInputDataStream& stream, KeyType key);

	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;
private:
	IInputDataStream& m_stream;
	std::mt19937 m_cryptEngine;
};