#include "StdAfx.h"
#include "RssObject.h"

CRssObject::CRssObject(void)
{
	listItem = gcnew System::Collections::ArrayList();
}

bool CRssObject::LoadFromFile(System::String ^ fileName, int nbMax_, System::String ^ fileComment)
{
	try
	{
		Xml::XmlDocument ^ xml = gcnew Xml::XmlDocument();
		xml->Load(fileName);
		Xml::XmlDocument ^ xmlComment;
		if (fileComment != nullptr && fileComment->Length > 0 )
		{
			xmlComment = gcnew Xml::XmlDocument();
			xmlComment->Load(fileComment);
		}
		return LoadObject(xml, nbMax_, xmlComment );
	}
	catch (Exception ^ e)
	{
		return false;
	}
}

bool CRssObject::LoadFromUrl(System::String ^ url, int nbMax_, System::String ^ urlComment)
{
	HttpWebResponse ^ HttpWResp;
	StreamReader ^ sr;
	try
	{
		HttpWebRequest ^ HttpWReq = dynamic_cast<HttpWebRequest^>(WebRequest::Create(url));
		HttpWReq->CachePolicy = gcnew Cache::HttpRequestCachePolicy(Cache::HttpRequestCacheLevel::Reload);
		HttpWResp = dynamic_cast<HttpWebResponse^>(HttpWReq->GetResponse());
		sr = gcnew StreamReader(HttpWResp->GetResponseStream());
		Xml::XmlDocument ^ xml = gcnew Xml::XmlDocument();
		xml->LoadXml(sr->ReadToEnd());

		Xml::XmlDocument ^ xmlComment;
		if (urlComment != nullptr && urlComment->Length > 0)
		{
			HttpWReq = dynamic_cast<HttpWebRequest^>(WebRequest::Create(urlComment));
			HttpWReq->CachePolicy = gcnew Cache::HttpRequestCachePolicy(Cache::HttpRequestCacheLevel::Reload);
			HttpWResp = dynamic_cast<HttpWebResponse^>(HttpWReq->GetResponse());
			sr = gcnew StreamReader(HttpWResp->GetResponseStream());
			xmlComment = gcnew Xml::XmlDocument();
			xmlComment->LoadXml(sr->ReadToEnd());
		}

		return LoadObject(xml, nbMax_, xmlComment);
	}
	catch (Exception ^ e)
	{
		return false;
	}
	finally
	{
		if (HttpWResp)
			HttpWResp->Close();
		if (sr)
			sr->Close();
	}
}

bool CRssObject::LoadObject(Xml::XmlDocument ^ xml, int nbMax_, Xml::XmlDocument ^ xmlComment)
{
	if (!xml)
		return false;
	Xml::XmlNode ^xn = xml->SelectSingleNode("rss");
	if (isRssVersion2(xn))
	{
		xn = xn->SelectSingleNode("channel");
		if (xn)
		{
			this->title = GetText(xn, "title");
			this->link = GetText(xn, "link");
			this->description = GetText(xn, "description");
			this->language = GetText(xn, "language");

			int nb = 0;
			for each (Xml::XmlNode ^ item in xn->SelectNodes("item"))
			{
				if (nb == nbMax_)
					break;
				CItemRss ^ itemRss = gcnew CItemRss();
				itemRss->title = GetText(item, "title");
				itemRss->author = GetText(item, "author");
				itemRss->link = GetText(item, "link");

				itemRss->nbComments = -1; // impossible de récuperer les commentaires
				if (xmlComment)
				{
					Xml::XmlNode ^ xnc = xmlComment->SelectSingleNode("rss");
					if (isRssVersion2(xnc))
					{
						xnc = xnc->SelectSingleNode("channel");
						if (xnc)
						{
							int nbComments = 0;
							for each (Xml::XmlNode ^ itemComment in xnc->SelectNodes("item"))
								if (GetText(itemComment, "link")->Contains(itemRss->link))
									nbComments++;
							itemRss->nbComments = nbComments;
						}

					}
				}
				this->listItem->Add(itemRss);
				nb++;
			}
		}
		return true;
	}
	else
		return false;
}

bool CRssObject::isRssVersion2(Xml::XmlNode ^ xn)
{
	if (xn)
	{
		for each (Xml::XmlAttribute ^ xa in xn->Attributes)
		{
			if (xa->Name == "version")
				if (xa->Value->Substring(0,1) == "2")
					return true;
		}
	}
	return false;
}

String ^ CRssObject::GetText(Xml::XmlNode ^xn, String ^ value)
{
	Xml::XmlNode ^ tmpNode = xn->SelectSingleNode(value);
	if (tmpNode)
		return tmpNode->InnerText;
	return "";
}

