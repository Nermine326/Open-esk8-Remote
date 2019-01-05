#pragma once

using namespace System;

ref class CItemRss
{
public:
	CItemRss(void);
	String ^ author;
	String ^ title;
	String ^ link;
	int nbComments;
};
