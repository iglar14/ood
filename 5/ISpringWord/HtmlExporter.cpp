#include "stdafx.h"
#include "HtmlExporter.h"
#include "IDocument.h"
#include "SaveStorage.h"
#include "WordException.h"
#include <boost/algorithm/string/replace.hpp>

namespace fs = boost::filesystem;

namespace
{
std::string Escape(std::string text)
{
	static const std::pair<std::string, std::string> SUBSTITUTES[] =
	{
		{ "&", "&amp;" },
		{ "<", "&lt;" },
		{ ">", "&gt;" },
		{ "\"", "&quot;" },
		{ "\'", "&apos;" },
	};
	for (const auto subst : SUBSTITUTES)
	{
		boost::algorithm::replace_all(text, subst.first, subst.second);
	}
	return text;
}
void AddTitleTag(std::ostream& strm, const std::string& title)
{
	strm << "<title>" << Escape(title) << "</title>";
}
void AddImageTag(std::ostream& strm, const fs::path& p, int width, int height)
{
	strm << "<img src=\"" << Escape(p.string()) << "\" width=\"" << width << "\" height=\"" << height << "\">\n";
}
void AddParagraphTag(std::ostream& strm, const std::string& text)
{
	strm << "<p>" << Escape(text) << "</p>\n";
}

std::ofstream Open(const fs::path& path)
{
	fs::path filename = path.filename();
	if (fs::is_directory(path) || filename.empty() || (filename == ".") || (filename == ".."))
	{
		throw CWordException("Empty or invalid output file name");
	}
	std::ofstream strm;
	strm.open(path.c_str(), std::ios_base::trunc | std::ios_base::out);
	if (!strm.is_open())
	{
		throw CWordException("Could not open file");
	}
	return strm;
}
}

void CHtmlExporter::Export(const IDocument& doc, const fs::path& path)
{
	std::ofstream strm = Open(path);
	CSaveStorage storage(path);
	auto baseDir = path.parent_path();
	if (baseDir.empty())
	{
		baseDir = ".";
	}
	auto pathConverter = [baseDir](const fs::path& absPath) {
		return fs::relative(absPath, baseDir);
	};
	Export(doc, strm, storage, pathConverter);
}

void CHtmlExporter::Export(const IDocument& doc, std::ostream& strm, IStorage& storage, const PathConverter& pathConverter)
{
	strm << "<html>\n";
	strm << "<head>";
	AddTitleTag(strm, doc.GetTitle());
	strm << "</head>\n";
	strm << "<body>\n";

	for (size_t i = 0; i < doc.GetItemsCount(); ++i)
	{
		const auto item = doc.GetItem(i);
		if (auto image = item.GetImage())
		{
			auto copy = storage.AddFile(image->GetPath());
			fs::path relPath = pathConverter(copy->GetPath());
			AddImageTag(strm, relPath, image->GetWidth(), image->GetHeight());
		}
		else if (auto paragraph = item.GetParagraph())
		{
			AddParagraphTag(strm, paragraph->GetText());
		}
	}

	strm << "</body>\n";
	strm << "</html>";
}
