#pragma once
#include "IStreams.h"

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(const boost::filesystem::path& path);
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	std::basic_ofstream<uint8_t> m_stream;
};

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(const boost::filesystem::path& path);
	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	std::basic_ifstream<uint8_t> m_stream;
};