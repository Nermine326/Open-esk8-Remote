#pragma once

using namespace System;
using namespace System::Net;
using namespace System::IO;

#include "ItemRss.h"

ref class CRssObject
{
public:
	CRssObject(void);
	String ^ title;
	String ^ link;
	String ^ description;
	String ^ language;
	System::Collections::ArrayList ^ listItem;
	bool LoadFromUrl(String ^, int, String ^);
	bool LoadFromFile(String ^, int, String ^);
private:
	bool isRssVersion2(Xml::XmlNode ^);
	String ^ GetText(Xml::XmlNode ^, String ^);
	bool LoadObject(Xml::XmlDocument ^, int, Xml::XmlDocument ^);
};