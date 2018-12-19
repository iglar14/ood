#pragma once
#include "Menu.h"
#include "IWorkCopy.h"

class IDocument;

class CEditor : boost::noncopyable
{
public:
	using DocumentFactory = std::function<std::unique_ptr<IDocument>()>;
	CEditor(const DocumentFactory& docFac);  //-V730
	~CEditor();

	void Start();

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(std::istream & in);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);
	void SetTitle(std::istream & in);
	void InsertParagraph(std::istream & in);
	void InsertImage(std::istream & in);
	void ReplaceText(std::istream & in);
	void ResizeImage(std::istream & in);
	void DeleteItem(std::istream & in);
	void List(std::istream &);
	void Undo(std::istream &);
	void Redo(std::istream &);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
	// DocumentFactory m_docFac;
};
