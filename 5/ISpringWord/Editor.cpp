#include "stdafx.h"
#include "Editor.h"
#include "Document.h"

using namespace std;
namespace ph = std::placeholders;

CEditor::CEditor()  //-V730
	: m_document(make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
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
	m_menu.AddItem(shortcut, description, bind(handler, this, ph::_1));
}

void CEditor::SetTitle(istream & in)
{
	string title;
	getline(in, title);
	boost::algorithm::trim_all(title);
	
	m_document->SetTitle(title);
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
//			image->
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
