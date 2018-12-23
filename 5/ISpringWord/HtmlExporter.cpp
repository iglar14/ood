#include "stdafx.h"
#include "HtmlExporter.h"
#include "IDocument.h"
#include "SaveStorage.h"
#include <boost/algorithm/string/replace.hpp>

namespace fs = boost::filesystem;

namespace
{
std::string Escape(std::string text)
{
	static const std::pair<std::string, std::string> SUBSTITUTES[] =
	{
		{ "<", "&lt;" },
		{ ">", "&gt;" },
		{ "&", "&amp;" },
		{ "\"", "&quot;" },
		{ "\'", "&apos;" },
	};
	for (const auto subst : SUBSTITUTES)
	{
		boost::algorithm::replace_all(text, subst.first, subst.second);
	}
	return text;
}
void AddTitleTag(std::ofstream& strm, const std::string& title)
{
	strm << "<title>" << Escape(title) << "</title>";
}
void AddImageTag(std::ofstream& strm, const fs::path& p, int width, int height)
{
	strm << "<p><img src=\"" << Escape(p.string()) << "\" width=\"" << width << "\" height=\"" << height << "\"></p>\n";
}
void AddParagraphTag(std::ofstream& strm, const std::string& text)
{
	strm << "<p>" << Escape(text) << "</p>\n";
}
}

void CHtmlExporter::Export(const IDocument& doc, const fs::path& path)
{
	std::ofstream strm;
	strm.open(path.c_str(), std::ios_base::trunc | std::ios_base::out);

	CSaveStorage storage(path);
	fs::path baseDir = path.parent_path();

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
			fs::path relPath = fs::relative(copy->GetPath(), baseDir);
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
