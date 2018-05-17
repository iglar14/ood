#pragma once
#include "IStreams.h"

class CMemoryOutputStream : public IOutputDataStream
{
public:
	CMemoryOutputStream();
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

	std::vector<uint8_t> GetData() const { return m_storage; }

private:
	std::vector<uint8_t> m_storage;
};

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(const std::vector<uint8_t>& storage);
	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	const std::vector<uint8_t>& m_storage;
	size_t m_pos = 0;
};