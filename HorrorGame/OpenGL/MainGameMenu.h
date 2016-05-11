#pragma once
#include "Game.h"
#include "OptionsGameMenu.h"
#include "AboutGameMenu.h"
#include "LoadingGameWindow.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define FULLSCREEN_DEFAULT false

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainGameMenu
	/// </summary>
	public ref class MainGameMenu : public System::Windows::Forms::Form
	{
	public:
		MainGameMenu(void)
		{ 
			//loading = gcnew LoadingGameWindow();
			//loading->ShowDialog();

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			width = SCREEN_WIDTH;
			height = SCREEN_HEIGHT;
			fullscreen = FULLSCREEN_DEFAULT;

			//loading->Hide();
		}

	protected:
		LoadingGameWindow ^loading;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainGameMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel2;
	protected:
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Panel^  panel1;


	protected:


		int width, height;

		bool fullscreen;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;

	protected:


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainGameMenu::typeid));
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button4);
			this->panel2->Controls->Add(this->button3);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->button1);
			this->panel2->Location = System::Drawing::Point(207, 12);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(295, 386);
			this->panel2->TabIndex = 3;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(27, 333);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(240, 23);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Exit";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainGameMenu::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(27, 260);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(240, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"About";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainGameMenu::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(27, 231);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(240, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Options";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainGameMenu::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(27, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(240, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainGameMenu::button1_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Control;
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(189, 386);
			this->panel1->TabIndex = 2;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainGameMenu::panel1_Paint);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainGameMenu::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainGameMenu::backgroundWorker1_RunWorkerCompleted);
			// 
			// MainGameMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(514, 410);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"MainGameMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Horror Game - Main Menu";
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: Game *game; System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->Hide();
		char *argv[1];
		int argc = 1;
		argv[0] = strdup("Myappname");
		game = new Game(&argc, argv, "Horror xD", width, height, fullscreen);

		//backgroundWorker1->RunWorkerAsync(1);		// <--- uncomment for loading window

		game->run();
		this->Close();
	}

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	OptionsGameMenu options(width, height, fullscreen);
	options.ShowDialog();
	width = options.getWidth();
	height = options.getHeight();
	fullscreen = options.getFullscreenInfo();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
{
	AboutGameMenu about;
	about.ShowDialog();
}
private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private:
	; System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		//LoadingGameWindow ^loading = gcnew LoadingGameWindow();
		loading->Show();
		while (true)
		{
			if (game->checkInitStatus())
			{
				std::cout << "inicjalizacja zakonczona" << std::endl;
				loading->Close();
				break;
			}
		}
}
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
}
};
}