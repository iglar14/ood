#pragma once

class IDocument;
class IStorage;

class CHtmlExporter
{
public:
	using PathConverter = std::function<boost::filesystem::path(const boost::filesystem::path&)>;
	//CHtmlExporter();

	void Export(const IDocument& doc, const boost::filesystem::path& path);
	void Export(const IDocument& doc, std::ostream& strm, IStorage& storage, const PathConverter& pathConverter);
private:

};