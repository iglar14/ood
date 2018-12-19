#include "stdafx.h"
#include "Document.h"
#include "Editor.h"
#include "Storage.h"

using namespace std;
using namespace std::placeholders;

std::unique_ptr<IStorage> CreateStorage()
{
	return std::make_unique<CStorage>();
}

std::unique_ptr<IDocument> CreateDocument()
{
	return std::make_unique<CDocument>(CreateStorage());
}

int main()
{
	CEditor editor(&CreateDocument);
	editor.Start();
	return 0;
}

