#pragma once
#include <iostream>
#include <string>
namespace OpenGL {

	typedef struct
	{
		int id;
		char *name;
		int width;
		int height;
	} windowSizes;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for OptionsGameMenu
	/// </summary>
	public ref class OptionsGameMenu : public System::Windows::Forms::Form
	{
	public:
		OptionsGameMenu(int w, int h, bool fullscr)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			width = w;
			height = h;
			fullscreen = fullscr;

			windowSizes sizes[14];

			sizes[0].id = 1;
			sizes[0].name = "640x480 4:3";
			sizes[0].width = 640;
			sizes[0].height = 480;
			sizes[1].id = 2;
			sizes[1].name = "800x600 4:3";
			sizes[1].width = 800;
			sizes[1].height = 600;
			sizes[2].id = 3;
			sizes[2].name = "1024x768 4:3";
			sizes[2].width = 1024;
			sizes[2].height = 768;
			sizes[3].id = 4;
			sizes[3].name = "1600x1200 4:3";
			sizes[3].width = 1600;
			sizes[3].height = 1200;
			sizes[4].id = 5;
			sizes[4].name = "1280x800 16:10";
			sizes[4].width = 1280;
			sizes[4].height = 800;
			sizes[5].id = 6;
			sizes[5].name = "1440x900 16:10";
			sizes[5].width = 1440;
			sizes[5].height = 900;
			sizes[6].id = 7;
			sizes[6].name = "1680x1050 16:10";
			sizes[6].width = 1680;
			sizes[6].height = 1050;
			sizes[7].id = 8;
			sizes[7].name = "1920x1200 16:10";
			sizes[7].width = 1920;
			sizes[7].height = 1200;
			sizes[8].id = 9;
			sizes[8].name = "2560x1600 16:10";
			sizes[8].width = 2560;
			sizes[8].height = 1600;
			sizes[9].id = 10;
			sizes[9].name = "1366x768 16:9";
			sizes[9].width = 1366;
			sizes[9].height = 768;
			sizes[10].id = 11;
			sizes[10].name = "1600x900 16:9";
			sizes[10].width = 1600;
			sizes[10].height = 900;
			sizes[11].id = 12;
			sizes[11].name = "1920x1080 16:9";
			sizes[11].width = 1920;
			sizes[11].height = 1080;
			sizes[12].id = 13;
			sizes[12].name = "2560x1440 16:9";
			sizes[12].width = 2560;
			sizes[12].height = 1440;
			sizes[13].id = 14;
			sizes[13].name = "3840x2160 16:9";
			sizes[13].width = 3840;
			sizes[13].height = 2160;

			for (int i = 0; i < 14; i++)
				this->comboBox1->Items->Add(gcnew String(sizes[i].name));

			for (int i = 0; i < 14; i++)
			{
				if (sizes[i].width == width && sizes[i].height == height)
				{
					String^ tmp = gcnew String(sizes[i].name);
					this->comboBox1->Text = tmp;
				}
			}

			this->textBox1->Text = (width).ToString();
			this->textBox2->Text = (height).ToString();
			this->checkBox1->Checked = fullscreen;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OptionsGameMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		int width, height;
	private: System::Windows::Forms::ComboBox^  comboBox1;
			 bool fullscreen;
	public: int getWidth() { return width; }
		int getHeight() { return height; }
		bool getFullscreenInfo() { return fullscreen; }
	private:
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 227);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(120, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &OptionsGameMenu::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(152, 227);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(120, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &OptionsGameMenu::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(215, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Width";
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(215, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Height";
			this->label2->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(105, 118);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(74, 17);
			this->checkBox1->TabIndex = 5;
			this->checkBox1->Text = L"Fullscreen";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(163, 141);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 6;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->textBox1->Visible = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(105, 185);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 7;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->textBox2->Visible = false;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(68, 46);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(156, 21);
			this->comboBox1->TabIndex = 8;
			// 
			// OptionsGameMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"OptionsGameMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Options";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: int getNewWindowSize()
{
	windowSizes sizes[14];

	sizes[0].id = 1;
	sizes[0].name = "640x480 4:3";
	sizes[0].width = 640;
	sizes[0].height = 480;
	sizes[1].id = 2;
	sizes[1].name = "800x600 4:3";
	sizes[1].width = 800;
	sizes[1].height = 600;
	sizes[2].id = 3;
	sizes[2].name = "1024x768 4:3";
	sizes[2].width = 1024;
	sizes[2].height = 768;
	sizes[3].id = 4;
	sizes[3].name = "1600x1200 4:3";
	sizes[3].width = 1600;
	sizes[3].height = 1200;
	sizes[4].id = 5;
	sizes[4].name = "1280x800 16:10";
	sizes[4].width = 1280;
	sizes[4].height = 800;
	sizes[5].id = 6;
	sizes[5].name = "1440x900 16:10";
	sizes[5].width = 1440;
	sizes[5].height = 900;
	sizes[6].id = 7;
	sizes[6].name = "1680x1050 16:10";
	sizes[6].width = 1680;
	sizes[6].height = 1050;
	sizes[7].id = 8;
	sizes[7].name = "1920x1200 16:10";
	sizes[7].width = 1920;
	sizes[7].height = 1200;
	sizes[8].id = 9;
	sizes[8].name = "2560x1600 16:10";
	sizes[8].width = 2560;
	sizes[8].height = 1600;
	sizes[9].id = 10;
	sizes[9].name = "1366x768 16:9";
	sizes[9].width = 1366;
	sizes[9].height = 768;
	sizes[10].id = 11;
	sizes[10].name = "1600x900 16:9";
	sizes[10].width = 1600;
	sizes[10].height = 900;
	sizes[11].id = 12;
	sizes[11].name = "1920x1080 16:9";
	sizes[11].width = 1920;
	sizes[11].height = 1080;
	sizes[12].id = 13;
	sizes[12].name = "2560x1440 16:9";
	sizes[12].width = 2560;
	sizes[12].height = 1440;
	sizes[13].id = 14;
	sizes[13].name = "3840x2160 16:9";
	sizes[13].width = 3840;
	sizes[13].height = 2160;

	String^ selectValue = this->comboBox1->Text;

	char *temp = (char*)(void*)Marshal::StringToHGlobalAnsi(selectValue);
	int selectedId;
	
	for (int i = 0; i < 14; i++)
	{
		if (!strcmp(sizes[i].name, temp))
		{
			selectedId = i;
			break;
		}
	}

	return selectedId;
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	windowSizes sizes[14];

	sizes[0].id = 1;
	sizes[0].name = "640x480 4:3";
	sizes[0].width = 640;
	sizes[0].height = 480;
	sizes[1].id = 2;
	sizes[1].name = "800x600 4:3";
	sizes[1].width = 800;
	sizes[1].height = 600;
	sizes[2].id = 3;
	sizes[2].name = "1024x768 4:3";
	sizes[2].width = 1024;
	sizes[2].height = 768;
	sizes[3].id = 4;
	sizes[3].name = "1600x1200 4:3";
	sizes[3].width = 1600;
	sizes[3].height = 1200;
	sizes[4].id = 5;
	sizes[4].name = "1280x800 16:10";
	sizes[4].width = 1280;
	sizes[4].height = 800;
	sizes[5].id = 6;
	sizes[5].name = "1440x900 16:10";
	sizes[5].width = 1440;
	sizes[5].height = 900;
	sizes[6].id = 7;
	sizes[6].name = "1680x1050 16:10";
	sizes[6].width = 1680;
	sizes[6].height = 1050;
	sizes[7].id = 8;
	sizes[7].name = "1920x1200 16:10";
	sizes[7].width = 1920;
	sizes[7].height = 1200;
	sizes[8].id = 9;
	sizes[8].name = "2560x1600 16:10";
	sizes[8].width = 2560;
	sizes[8].height = 1600;
	sizes[9].id = 10;
	sizes[9].name = "1366x768 16:9";
	sizes[9].width = 1366;
	sizes[9].height = 768;
	sizes[10].id = 11;
	sizes[10].name = "1600x900 16:9";
	sizes[10].width = 1600;
	sizes[10].height = 900;
	sizes[11].id = 12;
	sizes[11].name = "1920x1080 16:9";
	sizes[11].width = 1920;
	sizes[11].height = 1080;
	sizes[12].id = 13;
	sizes[12].name = "2560x1440 16:9";
	sizes[12].width = 2560;
	sizes[12].height = 1440;
	sizes[13].id = 14;
	sizes[13].name = "3840x2160 16:9";
	sizes[13].width = 3840;
	sizes[13].height = 2160;

	int i = getNewWindowSize();

	width = sizes[i].width;
	height = sizes[i].height;
	fullscreen = this->checkBox1->Checked;
	this->Close();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	this->Close();
}
};
}
