#pragma once
#include <Windows.h>
namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoadingGameWindow
	/// </summary>
	public ref class LoadingGameWindow : public System::Windows::Forms::Form
	{
	public:
		LoadingGameWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->label1->Refresh();
			this->progressBar1->Refresh();
			
			backgroundWorker1->RunWorkerAsync(1);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoadingGameWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 34);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(171, 23);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(171, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Please wait. The game is loading...";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &LoadingGameWindow::backgroundWorker1_DoWork);
			// 
			// LoadingGameWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(193, 68);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->Cursor = System::Windows::Forms::Cursors::No;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LoadingGameWindow";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Please wait";
			this->TopMost = true;
			this->Activated += gcnew System::EventHandler(this, &LoadingGameWindow::LoadingGameWindow_Activated);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &LoadingGameWindow::LoadingGameWindow_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		void closeWindow()
		{
			this->Close();
		}

	private: System::Void LoadingGameWindow_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
	{
	}
	private: System::Void LoadingGameWindow_Activated(System::Object^  sender, System::EventArgs^  e) {
		this->Hide();
	}
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		Sleep(500);
		this->Hide();
	}
};
}
