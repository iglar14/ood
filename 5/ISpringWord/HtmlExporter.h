#pragma once

class IDocument;

class CHtmlExporter
{
public:
	//CHtmlExporter();

	void Export(const IDocument& doc, const boost::filesystem::path& path);
private:

};