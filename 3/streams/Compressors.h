#pragma once
#include "IStreams.h"

class CRleCompressStream final : public IOutputDataStream
{
public:
	CRleCompressStream(IOutputDataStream& stream);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;
	void Flush() override;
private:
	void WriteSequence(size_t size);
	void WriteRepeat();

	IOutputDataStream& m_stream;

	size_t m_repeatCounter = 0;
	std::basic_string<uint8_t> m_sequence;
};

class CRleDecompressStream final : public IInputDataStream
{
public:
	CRleDecompressStream(IInputDataStream& stream);

	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;
private:
	IInputDataStream& m_stream;
	char m_counter = 0;
	uint8_t m_value = 0;
};