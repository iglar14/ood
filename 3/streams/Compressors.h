#pragma once
#include "IStreams.h"

class CRleCompress final : public IOutputDataStream
{
public:
	CRleCompress(IOutputDataStream& stream);
	~CRleCompress() override;

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;
private:
	IOutputDataStream& m_stream;
};

class CRleDecompress final : public IInputDataStream
{
public:
	CRleDecompress(IInputDataStream& stream);
	~CRleDecompress() override;

	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;
private:
	IInputDataStream& m_stream;
	char m_counter = 0;
	uint8_t m_value = 0;
};