#pragma once


namespace lecteurRss {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			
		}

	protected:
		
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: rssFeeder::rssFeederControl^  rssFeederControl1;
	protected: 
	private: rssFeeder::rssFeederControl^  rssFeederControl2;
	private: rssFeeder::rssFeederControl^  rssFeederControl3;
	private: rssFeeder::rssFeederControl^  rssFeederControl4;

	private:
		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->rssFeederControl1 = (gcnew rssFeeder::rssFeederControl());
			this->rssFeederControl2 = (gcnew rssFeeder::rssFeederControl());
			this->rssFeederControl3 = (gcnew rssFeeder::rssFeederControl());
			this->rssFeederControl4 = (gcnew rssFeeder::rssFeederControl());
			this->SuspendLayout();
			// 
			// rssFeederControl1
			// 
			this->rssFeederControl1->interval = L"300";
			this->rssFeederControl1->Location = System::Drawing::Point(381, 165);
			this->rssFeederControl1->Name = L"rssFeederControl1";
			this->rssFeederControl1->nbMax = L"3";
			this->rssFeederControl1->Size = System::Drawing::Size(258, 138);
			this->rssFeederControl1->TabIndex = 0;
			this->rssFeederControl1->url = L"http://blog.developpez.com/xmlsrv/rss2.php\?blog=1";
			this->rssFeederControl1->urlComment = L"http://blog.developpez.com/xmlsrv/rss2.comments.php\?blog=1";
			// 
			// rssFeederControl2
			// 
			this->rssFeederControl2->interval = L"300";
			this->rssFeederControl2->Location = System::Drawing::Point(12, 12);
			this->rssFeederControl2->Name = L"rssFeederControl2";
			this->rssFeederControl2->nbMax = L"5";
			this->rssFeederControl2->Size = System::Drawing::Size(302, 147);
			this->rssFeederControl2->TabIndex = 1;
			this->rssFeederControl2->url = L"http://blogs.developpeur.org/MainFeed.aspx";
			this->rssFeederControl2->urlComment = nullptr;
			this->rssFeederControl2->itemClick += gcnew rssFeeder::rssFeederControl::ItemClickHandler(this, &Form1::rssFeederControl2_itemClick);
			// 
			// rssFeederControl3
			// 
			this->rssFeederControl3->interval = L"300";
			this->rssFeederControl3->Location = System::Drawing::Point(374, 12);
			this->rssFeederControl3->Name = L"rssFeederControl3";
			this->rssFeederControl3->nbMax = L"5";
			this->rssFeederControl3->Size = System::Drawing::Size(265, 166);
			this->rssFeederControl3->TabIndex = 2;
			this->rssFeederControl3->url = L"http://blogs.developpeur.org/brunews/rss.aspx";
			this->rssFeederControl3->urlComment = L"";
			// 
			// rssFeederControl4
			// 
			this->rssFeederControl4->interval = L"300";
			this->rssFeederControl4->Location = System::Drawing::Point(12, 171);
			this->rssFeederControl4->Name = L"rssFeederControl4";
			this->rssFeederControl4->nbMax = L"3";
			this->rssFeederControl4->Size = System::Drawing::Size(294, 132);
			this->rssFeederControl4->TabIndex = 3;
			this->rssFeederControl4->url = L"http://blogs.developpeur.org/arnotic/rss.aspx";
			this->rssFeederControl4->urlComment = L"";
			this->rssFeederControl4->itemClick += gcnew rssFeeder::rssFeederControl::ItemClickHandler(this, &Form1::rssFeederControl4_itemClick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(667, 343);
			this->Controls->Add(this->rssFeederControl4);
			this->Controls->Add(this->rssFeederControl3);
			this->Controls->Add(this->rssFeederControl2);
			this->Controls->Add(this->rssFeederControl1);
			this->Name = L"Form1";
			this->Text = L"Mon lecteur RSS";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void rssFeederControl4_itemClick(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) 
			 {
				System::Diagnostics::Process::Start(e->Link->LinkData->ToString());
				e->Link->Visited = true;
			 }
private: System::Void rssFeederControl2_itemClick(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) 
		 {
			 MessageBox::Show("Vous avez cliqué sur " + e->Link->LinkData->ToString());
		 }
};
}

