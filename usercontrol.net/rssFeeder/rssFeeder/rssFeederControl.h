#pragma once

#include "RssObject.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace rssFeeder {

	
	[ToolboxBitmap(rssFeeder::rssFeederControl::typeid)]
	public ref class rssFeederControl : public System::Windows::Forms::UserControl
	{
	public:
		delegate void ItemClickHandler(Object ^ sender, LinkLabelLinkClickedEventArgs ^ e);
		rssFeederControl(void)
		{
			nbMax_ = 0;
			interval_ = 300; // 5 minutes par défaut
			InitializeComponent();
			refreshControl();
		}

		[Category("Configuration"), Browsable(true), Description("Evènement associé au click sur un item")]
		event ItemClickHandler ^ itemClick;

		[Category("Configuration")]
		[Description("Entrez le nombre maximum de news à afficher")]
		property String ^ nbMax
		{
			String ^ get(){ return Convert::ToString(nbMax_); }
			void set(String ^ value) 
			{ 
				nbMax_ = Convert::ToInt32(value);
				refreshControl();
			}
		}
		[Category("Configuration")]
		[Description("Url du fil rss")]
		property String ^ url
		{
			String ^ get() { return url_; }
			void set(String ^ value) 
			{ 
				url_ = value; 
				refreshControl();
			}
		}

		[Category("Configuration")]
		[Description("Url du fil rss de commentaires")]
		property String ^ urlComment
		{
			String ^ get() { return urlComment_; }
			void set(String ^ value) 
			{ 
				urlComment_ = value; 
				refreshControl();
			}
		}

		[Category("Configuration")]
		[Description("Délai de raffraichissement (en secondes)")]
		property String ^ interval
		{
			String ^ get(){ return Convert::ToString(interval_); }
			void set(String ^ value) 
			{ 
				interval_ = Convert::ToInt32(value);
				timer1->Stop();
				timer1->Interval = interval_ * 1000;
				timer1->Start();
				refreshControl();
			}
		}


	protected:
		
		~rssFeederControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		

		String ^ url_, ^ urlComment_;
		int nbMax_;
		int interval_;
		System::Windows::Forms::ToolTip^  toolTip1;
		System::Windows::Forms::Timer^  timer1;
		cli::array<System::Windows::Forms::LinkLabel ^, 1> ^ listOfNews;
		System::Windows::Forms::GroupBox ^ groupBox;
		CRssObject ^ rssObj_;


#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			
			this->timer1->Tick += gcnew System::EventHandler(this, &rssFeederControl::timer1_Tick);
			
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Name = L"rssFeederControl";
			this->ResumeLayout(false);

		}
#pragma endregion
		void refreshControl()
		{
			this->Controls->Clear();
			if (url_== nullptr || url_ == "")
			{
				System::Windows::Forms::Label ^ label = gcnew System::Windows::Forms::Label();
				label->AutoSize = true;
				label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				label->Location = System::Drawing::Point(0, 5);
				label->Name = L"label1";
				label->Size = System::Drawing::Size(51, 16);
				label->TabIndex = 1;
				label->Text = "! -- Saisir une url de fil rss -- !";
				this->Controls->Add(label);
				return;
			}
			if (nbMax_ <= 0)
			{
				System::Windows::Forms::Label ^ label = gcnew System::Windows::Forms::Label();
				label->AutoSize = true;
				label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				label->Location = System::Drawing::Point(0, 5);
				label->Name = L"label1";
				label->Size = System::Drawing::Size(51, 16);
				label->TabIndex = 1;
				label->Text = "! -- Saisissez un nombre de news à afficher -- !";
				this->Controls->Add(label);
				return;
			}

			listOfNews = gcnew cli::array<System::Windows::Forms::LinkLabel ^>(nbMax_);
			CRssObject ^ rssObject = GetObjRss(true);
			if (!rssObject)
			{
				System::Windows::Forms::Label ^ label = gcnew System::Windows::Forms::Label();
				label->AutoSize = true;
				label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				label->Location = System::Drawing::Point(0, 5);
				label->Name = L"label1";
				label->Size = System::Drawing::Size(51, 16);
				label->TabIndex = 1;
				label->Text = "! -- Le flux RSS n'est pas valide 2.0 -- !";
				this->Controls->Add(label);
				return;
			}

			groupBox = gcnew System::Windows::Forms::GroupBox();
			groupBox->Location = System::Drawing::Point(0, 30);
			groupBox->Name = L"groupBox1";
			groupBox->AutoSize = false;
			groupBox->Size = System::Drawing::Size(136, 35);
			groupBox->TabIndex = 2;
			groupBox->TabStop = false;
			groupBox->Text = rssObject->title;

			for (int i=0;i<nbMax_;i++)
			{
				if (i < rssObject->listItem->Count)
				{
					CItemRss ^ currItem = static_cast<CItemRss ^>(rssObject->listItem[i]);
					System::Windows::Forms::LinkLabel^ linkLabel;
					linkLabel = gcnew System::Windows::Forms::LinkLabel();
					linkLabel->AutoSize = true;
					linkLabel->Location = System::Drawing::Point(5, 20+(15*i));
					linkLabel->Name = L"linkLabel"+Convert::ToString(i);
					linkLabel->Size = System::Drawing::Size(55, 13);
					linkLabel->TabIndex = 0;
					linkLabel->TabStop = true;
					linkLabel->AutoSize = true;
					linkLabel->LinkArea = System::Windows::Forms::LinkArea(0, currItem->title->Length + 5);
					linkLabel->Links[0]->LinkData = currItem->link;
					linkLabel->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &rssFeeder::rssFeederControl::linkLabel_LinkClicked);
					linkLabel->MouseHover += gcnew System::EventHandler(this, &rssFeeder::rssFeederControl::linkLabel_MouseHover);
					linkLabel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &rssFeederControl::linkLabel_Paint);
					if (currItem->nbComments >= 0)
						linkLabel->Text = currItem->title + " ("+Convert::ToString(currItem->nbComments)+")";
					else
						linkLabel->Text = currItem->title;
					listOfNews[i] = linkLabel;
					groupBox->Height += 15;
					groupBox->Controls->Add(listOfNews[i]);
				}
			}
			this->Controls->Add(groupBox);

		}

		CRssObject ^ GetObjRss(bool forceReload)
		{
			if (forceReload || !rssObj_)
			{
				rssObj_ = gcnew CRssObject();
				if (!rssObj_->LoadFromUrl(url_, nbMax_, urlComment_))
					return nullptr;
			}
			return rssObj_;
		}

		void linkLabel_LinkClicked(Object ^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^ e) 
		{
			if (&rssFeederControl::itemClick != nullptr)
				itemClick(this, e);
		}

		private: System::Void linkLabel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {
			 LinkLabel ^ ll = static_cast<LinkLabel ^>(sender);
			 CRssObject ^ rssObject = GetObjRss(false);
			 CItemRss ^ itemRss;
			 for each (itemRss in rssObject->listItem)
				 if (itemRss->link == ll->Links[0]->LinkData->ToString())
					 break;
			 SizeF ^ size = e->Graphics->MeasureString(ll->Text, ll->Font);
			 int i = 1;
			 while (size->Width >= this->Width - 15)
			 {
				 if (itemRss->nbComments >=0)
					 ll->Text = itemRss->title->Substring(0,itemRss->title->Length - i) + " ... (" + Convert::ToString(itemRss->nbComments) + ")";
				 else
					 ll->Text = itemRss->title->Substring(0,itemRss->title->Length - i) + " ...";
				 size = e->Graphics->MeasureString(ll->Text, ll->Font);
				 i++;
			 }
			 groupBox->Width = this->Width - 5;
		 }

private: System::Void linkLabel_MouseHover(System::Object^  sender, System::EventArgs^  e) 
		 {
			 LinkLabel ^ ll = static_cast<LinkLabel ^>(sender);
			 CRssObject ^ rssObject = GetObjRss(false);
			 for each (CItemRss ^ itemRss in rssObject->listItem)
				 if (itemRss->link == ll->Links[0]->LinkData->ToString())
				 {
					 String ^ author;
					 if (itemRss->author != "")
						 author = " (par " + itemRss->author +")";
					 toolTip1->Show(itemRss->title + author , static_cast<Windows::Forms::IWin32Window ^>(sender));
				 }
		 }


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				 refreshControl();
			 }
	};
}
