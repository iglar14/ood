#include "stdafx.h"
#include "Editor.h"
#include "HtmlExporter.h"
#include "IDocument.h"
#include "WordException.h"
#include <boost/lexical_cast.hpp>

using namespace std;
namespace ph = std::placeholders;

namespace
{
boost::optional<size_t> ReadPos(istream& in)
{
	string dest;
	in >> dest;
	boost::optional<size_t> pos;
	if (dest != "end")
	{
		pos = boost::lexical_cast<size_t>(dest);
	}
	return pos;
}

string ReadText(istream& in)
{
	string text;
	getline(in, text);
	boost::algorithm::trim_all(text);
	return text;
}

void CallAndCatch(const std::function<void()>& f)
{
	try
	{
		f();
	}
	catch (CWordException& e)
	{
		cerr << "Error: " << e.what() << "\n";
	}
	catch (std::exception& e)
	{
		cerr << "Exception: " << e.what() << "\n";
	}
	catch (...)
	{
		cerr << "Unexpected exception\n";
	}
}
}

CEditor::CEditor(const DocumentFactory& docFac)  //-V730
	: m_document(docFac())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
	AddMenuItem("insertParagraph", "Inserts new paragraph. Args: <pos> <text...>", &CEditor::InsertParagraph);
	AddMenuItem("insertImage", "Inserts image. Args: <pos> <width> <height> <path>", &CEditor::InsertImage);
	AddMenuItem("replaceText", "Replaces text in paragraph. Args <pos> <text...>", &CEditor::ReplaceText);
	AddMenuItem("resizeImage", "Changes image size. Args <pos> <width> <height>", &CEditor::ResizeImage);
	AddMenuItem("deleteItem", "Deletes item. Args <pos>", &CEditor::DeleteItem);
	AddMenuItem("save", "Save to html. Args <path>", &CEditor::Save);
	AddMenuItem("list", "Show document", &CEditor::List);
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
}

CEditor::~CEditor() = default;

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, [this, handler](istream& in) {
		CallAndCatch(std::bind(handler, this, std::ref(in)));
	});
}

void CEditor::SetTitle(istream & in)
{
	string title = ReadText(in);
	m_document->SetTitle(title);
}

void CEditor::InsertParagraph(istream & in)
{
	boost::optional<size_t> pos = ReadPos(in);
	string par = ReadText(in);
	m_document->InsertParagraph(par, pos);
}

void CEditor::InsertImage(istream & in)
{
	boost::optional<size_t> pos = ReadPos(in);
	int width = 0;
	int height = 0;
	in >> width;
	in >> height;
	const string path = ReadText(in);

	if (path.empty())
	{
		cout << "Insufficient parameters\n";
		return;
	}
	if (!boost::filesystem::exists(path))
	{
		cout << "File \"" << path << "\"not found\n";
		return;
	}

	m_document->InsertImage(path, width, height, pos);
}

void CEditor::ReplaceText(std::istream & in)
{
	size_t pos = 0;
	in >> pos;
	const string text = ReadText(in);
	if (auto para = m_document->GetItem(pos).GetParagraph())
	{
		para->SetText(text);
	}
	else
	{
		throw CWordException("Item is not a paragraph");
	}
}

void CEditor::ResizeImage(std::istream & in)
{
	size_t pos = 0;
	int width = 0;
	int height = 0;
	in >> pos >> width >> height;
	if (auto image = m_document->GetItem(pos).GetImage())
	{
		image->Resize(width, height);
	}
	else
	{
		throw CWordException("Item is not an image");
	}
}

void CEditor::DeleteItem(std::istream & in)
{
	size_t pos = 0;
	in >> pos;
	m_document->DeleteItem(pos);
}

void CEditor::Save(std::istream& in)
{
	const string path = ReadText(in);
	CHtmlExporter exporter;
	exporter.Export(*m_document, path);
}

void CEditor::List(istream &)
{
	cout << "-------------" << endl;
	cout << m_document->GetTitle() << endl;
	cout << "-------------" << endl;
	const size_t count = m_document->GetItemsCount();
	for (size_t i = 0; i < count; ++i)
	{
		cout << i << ": ";
		auto item = m_document->GetItem(i);
		if (auto image = item.GetImage())
		{
			cout << "Image " << image->GetWidth() << "x" << image->GetHeight() << " " << image->GetPath() << endl;
		}
		else if (auto paragraph = item.GetParagraph())
		{
			cout << paragraph->GetText() << endl;
		}
	}
}

void CEditor::Undo(istream &)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		cout << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream &)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		cout << "Can't redo" << endl;
	}
}
