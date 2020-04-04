#include <iostream>
#include "tinyxml.h"

using namespace std;


void tinymentCircleAttributeGet(TiXmlElement* elementNode)
{
	TiXmlAttribute* categoryArribute = elementNode->FirstAttribute();
	while (categoryArribute)
	{
		cout << "  (" << categoryArribute->Name() << ";" << categoryArribute->Value() << ")";
		categoryArribute = categoryArribute->Next();
	}
}

void tinyxmlCircleElementGet(TiXmlElement* element, int i = 1)
{
	if (element)
	{
		cout << "  ";
		/*for (int m = 0; m < i; i++)
		{
			cout << "  ";
		}*/

		cout << element->Value();

		const char* text = element->GetText();

		tinymentCircleAttributeGet(element);

		if (text)
		{
			cout << "  " << text;
		}
		cout << endl;
		for (TiXmlElement* next = element->FirstChildElement(); next; next = next->NextSiblingElement())
		{
			tinyxmlCircleElementGet(next, i + 1);
		}
	}
}

void tinyxmlCircleNodeGet(TiXmlNode* node, int i = 1)
{
	if (node)
	{
		/*for (int m = 0; m < i; i++)
		{
			cout << "  ";
		}*/
		cout << "  ";
		cout << node->Value();
		TiXmlElement* element = node->ToElement();
		if (element)
		{
			tinymentCircleAttributeGet(element);
		}
		cout << endl;

		for (TiXmlNode* next = node->FirstChild(); next; next = next->NextSibling())
		{
			tinyxmlCircleNodeGet(next, i + 1);
		}
	}
}

void tinyXmlWriteBookInfor() 
{
	const char* xmlFile = "Book_Infor_TinyXML_Write.xml";
	TiXmlDocument doc;

	//create xml document declaration
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "utf-8", "");

	//create xml comment
	TiXmlComment* comment = new TiXmlComment("this is XML comment");


	//create books node
	TiXmlElement* bookElements = new TiXmlElement("books");

	//create book node
	TiXmlElement* bookElement1 = new TiXmlElement("book");
	//set attribute for this node, key is category, value is web
	bookElement1->SetAttribute("category", "WEB");

	//create title node
	TiXmlElement* titleElement = new TiXmlElement("title");
	//set attribute for this node, key is lang, value is en
	titleElement->SetAttribute("lang", "en");
	//this node owns textnode:"Learing XML"
	titleElement->LinkEndChild(new TiXmlText("Learning XML"));

	//create author node
	TiXmlElement* authorElement = new TiXmlElement("author");
	//this node owns textnode:"Erik T.Ray"
	authorElement->LinkEndChild(new TiXmlText("Erik T.Ray"));

	//create year node
	TiXmlElement* yearElement = new TiXmlElement("year");
	yearElement->LinkEndChild(new TiXmlText("2003"));

	//create price node
	TiXmlElement* priceElement = new TiXmlElement("price");
	priceElement->LinkEndChild(new TiXmlText("39.95"));

	//set title, author, year, price as attributes for the node of book
	bookElement1->LinkEndChild(titleElement);
	bookElement1->LinkEndChild(authorElement);
	bookElement1->LinkEndChild(yearElement);
	bookElement1->LinkEndChild(priceElement);


	//create one more book node
	TiXmlElement* bookElement2 = new TiXmlElement("book");
	//set attribute for this node, key is category, value is web
	bookElement2->SetAttribute("category", "C++");

	//create title node
	titleElement = new TiXmlElement("title");
	//set attribute for this node, key is lang, value is en
	titleElement->SetAttribute("lang", "china");
	//this node owns textnode:"Learing XML"
	titleElement->LinkEndChild(new TiXmlText("windows core programming"));

	//create author node
	authorElement = new TiXmlElement("author");
	//this node owns textnode:"Erik T.Ray"
	authorElement->LinkEndChild(new TiXmlText("Jeffrey Richter"));

	//create year node
	yearElement = new TiXmlElement("year");
	yearElement->LinkEndChild(new TiXmlText("2005"));

	//create price node
	priceElement = new TiXmlElement("price");
	priceElement->LinkEndChild(new TiXmlText("59.95"));

	//set title, author, year, price as attributes for the node of book
	bookElement2->LinkEndChild(titleElement);
	bookElement2->LinkEndChild(authorElement);
	bookElement2->LinkEndChild(yearElement);
	bookElement2->LinkEndChild(priceElement);

	//set book for books node 
	bookElements->LinkEndChild(bookElement1);
	bookElements->LinkEndChild(bookElement2);

	doc.LinkEndChild(decl);
	doc.LinkEndChild(comment);
	doc.LinkEndChild(bookElements);
	doc.SaveFile(xmlFile);
}

void tinyXmlReadBookInfor()
{
	cout << endl << "Read Tiny XML!" << endl;

	char strError[1024];
	memset(strError, '0', sizeof(strError));

	const char* xmlFile = "Book_Infor_TinyXML.xml";
	TiXmlDocument doc;
	//using doc object to load xml into memory
	if (doc.LoadFile(xmlFile, TIXML_ENCODING_UTF8))
	{
		doc.Print();
	}
	else
	{
		char error[126];
		memset(strError, '0', sizeof(strError));
		sprintf_s(error, "row:%d col:%d id:%d\n", doc.ErrorRow(), doc.ErrorCol(), doc.ErrorId());
		strcpy_s(strError, error);
		cout << strError;
		return;
	}

	
	//obtain the root node 
	TiXmlElement* rootElement = doc.RootElement();

	if (!rootElement) { return; }

	//the first iteration for element
	/*cout << "tinyxmlCircleElementGet()" << endl;
	tinyxmlCircleElementGet(rootElement);*/

	//the second iteration for node
	cout << "tinyxmlCircleNodeGet()" << endl;
	tinyxmlCircleNodeGet(rootElement);
}

int main()
{

	//tinyXmlWriteBookInfor();
	tinyXmlReadBookInfor();

	//cout << "Hello World!" << endl;
	
	return 0;
}