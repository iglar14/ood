#pragma once

class IDocument;
class IStorage;

class CHtmlExporter
{
public:
	using PathConverter = std::function<std::filesystem::path(const std::filesystem::path&)>;
	//CHtmlExporter();

	void Export(const IDocument& doc, const std::filesystem::path& path);
	void Export(const IDocument& doc, std::ostream& strm, IStorage& storage, const PathConverter& pathConverter);
private:

};