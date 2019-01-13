#include "stdafx.h"
#include "MockStorage.h"
#include "../ISpringWord/Document.h"
#include "../ISpringWord/HtmlExporter.h"
#include "../ISpringWord/WordException.h"

namespace fs = std::filesystem;
using namespace std;

namespace
{

static const string HTML_START = "<html>\n<head><title>";
static const string HTML_BODY_START = "</title></head>\n<body>\n";
static const string HTML_END = "</body>\n</html>";

static const string SPECIAL_CHARACTERS = "<h1>\"Hello&goodbye\"</h1>";
static const string ESCAPED_SPECIAL_CHARACTERS = "&lt;h1&gt;&quot;Hello&amp;goodbye&quot;&lt;/h1&gt;";

struct Document_
{
	CDocument m_document;
	CHtmlExporter m_exporter;
	MockStorage m_storage;
	std::stringstream m_stream;

	Document_()
		: m_document(std::make_unique<MockStorage>())
	{
	}

	void Export()
	{
		m_exporter.Export(m_document, m_stream, m_storage, [](const fs::path& p) { return p; });
	}
};
}

BOOST_FIXTURE_TEST_SUITE(HtmlExporter_tests, Document_)

BOOST_AUTO_TEST_CASE(exports_empty_document)
{
	Export();
	BOOST_CHECK_EQUAL(m_stream.str(), HTML_START + HTML_BODY_START + HTML_END);
}

BOOST_AUTO_TEST_CASE(escapes_special_characters_in_title)
{
	m_document.SetTitle(SPECIAL_CHARACTERS);
	Export();
	BOOST_CHECK_EQUAL(m_stream.str(), HTML_START + ESCAPED_SPECIAL_CHARACTERS + HTML_BODY_START + HTML_END);
}
BOOST_AUTO_TEST_CASE(exports_escaped_paragraph)
{
	m_document.InsertParagraph(SPECIAL_CHARACTERS);
	Export();
	BOOST_CHECK_EQUAL(m_stream.str(), HTML_START + HTML_BODY_START + "<p>" + ESCAPED_SPECIAL_CHARACTERS + "</p>\n" + HTML_END);
}
BOOST_AUTO_TEST_CASE(exports_image)
{
	static const string IMAGE_PATH = "c:\\img.jpg";
	m_document.InsertImage(IMAGE_PATH, 1024, 768);
	Export();
	BOOST_CHECK_EQUAL(m_stream.str(), HTML_START + HTML_BODY_START + "<img src=\"" + IMAGE_PATH + "\" width=\"1024\" height=\"768\">\n" + HTML_END);
}
BOOST_AUTO_TEST_CASE(escapes_special_characters_in_path)	// тест не актуален, потому что настоящий Storage не сгенерит такой путь
{
	static const string IMAGE_PATH = "c:\\&img.jpg";
	static const string ESCAPED_IMAGE_PATH = "c:\\&amp;img.jpg";
	m_document.InsertImage(IMAGE_PATH, 1024, 768);
	Export();
	BOOST_CHECK_EQUAL(m_stream.str(), HTML_START + HTML_BODY_START + "<img src=\"" + ESCAPED_IMAGE_PATH + "\" width=\"1024\" height=\"768\">\n" + HTML_END);
}
BOOST_AUTO_TEST_CASE(throws_when_empty_filename)
{
	auto exportTo = [&](auto&& p){
		BOOST_CHECK_THROW(m_exporter.Export(m_document, std::forward<decltype(p)>(p)), CWordException);
	};
	for (auto p : { "", ".\\", "..\\", "..", ".", "\\", "c:\\" })
	{
		exportTo(p);
	}
}

BOOST_AUTO_TEST_SUITE_END()
