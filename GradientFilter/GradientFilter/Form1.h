//////////////////////////////////////////////////////////////////////////////
//																			//
//	Project topic: Gradient filtering (north direction)						//
// 																			//
//	Short description of algorithm: 										//
//	Filtering with mask 3x3 by iterating over bytes and its neighbourhood.	//
//	Multiplied bytes are summed and then divided to calculate new value		//
//	achiving brighter colours for horizontal edges and detecting them.		//
//																			//
//	Date: 28.01.2023														//
//																			//
//	Semester: 5																//
//																			//
//	Academic year: 22/23													//
//																			//
//	Author: Roch Fedorowicz													//
//																			//
//	Version: 1.0															//
//																			//
//////////////////////////////////////////////////////////////////////////////

#pragma once

ref class LibManager;
ref class BMPManager;

namespace GradientFilterApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Timers;

	// Class responsible for GUI and handling communication with user
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		// Default constructor 
		Form1(void);

	protected:

		// Default destructor 
		~Form1();

	private: 

		// All components
		LibManager^ libManager;
		BMPManager^ bmpManager;
		Bitmap^ loadedBitmap;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Button^ button2;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::PictureBox^ pictureBox2;
		System::Windows::Forms::RadioButton^ radioButton1;
		System::Windows::Forms::RadioButton^ radioButton2;
		System::Windows::Forms::GroupBox^ groupBox1;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::TrackBar^ trackBar1;
		System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		System::Windows::Forms::TextBox^ textBox1;
		System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
		System::Windows::Forms::Button^ button3;
		System::Windows::Forms::TextBox^ textBox2;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		// Function initializing all components
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1 - Load picture button
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->Location = System::Drawing::Point(12, 100);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(267, 52);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Load picture";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2 - Run button
			// 
			this->button2->Enabled = false;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->Location = System::Drawing::Point(12, 333);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(266, 52);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Run\r\n";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// pictureBox1 - After filtration pictureBox
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlDark;
			this->pictureBox1->Location = System::Drawing::Point(752, 92);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(417, 442);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2 - Before filtration pictureBox
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ControlDark;
			this->pictureBox2->Location = System::Drawing::Point(301, 92);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(417, 442);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			// 
			// radioButton1 - C option radioButton
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(6, 73);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(45, 29);
			this->radioButton1->TabIndex = 4;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"C";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2 - ASM option radioButton
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Location = System::Drawing::Point(6, 37);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(117, 29);
			this->radioButton2->TabIndex = 5;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"ASM x64";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// groupBox1 - group of option buttons
			// 
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->groupBox1->Location = System::Drawing::Point(11, 158);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 108);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"DLL type";
			// 
			// label1 - Original image label
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(392, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(224, 37);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Original image";
			// 
			// label2 - Filtered image label
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(868, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(219, 37);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Filtered image";
			// 
			// label3 - Menu label
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->Location = System::Drawing::Point(86, 33);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(96, 37);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Menu";
			// 
			// trackBar1 - Number of threads trackBar 
			// 
			this->trackBar1->LargeChange = 8;
			this->trackBar1->Location = System::Drawing::Point(64, 282);
			this->trackBar1->Maximum = 128;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(215, 45);
			this->trackBar1->TabIndex = 9;
			this->trackBar1->TickFrequency = 8;
			this->trackBar1->Value = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Bmp files (*.bmp)|*.bmp";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// textBox1 - Number of threads textBox
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox1->Location = System::Drawing::Point(12, 282);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(51, 35);
			this->textBox1->TabIndex = 12;
			this->textBox1->Text = L"1";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->WordWrap = false;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveFileDialog1_FileOk);
			// 
			// button3 - Save button
			// 
			this->button3->Enabled = false;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->Location = System::Drawing::Point(11, 391);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(267, 52);
			this->button3->TabIndex = 13;
			this->button3->Text = L"Save";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// textBox2 - Output information textBox
			// 
			this->textBox2->Location = System::Drawing::Point(12, 449);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(266, 84);
			this->textBox2->TabIndex = 14;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1196, 587);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Form1";
			this->Text = L"Gradient filter";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		// Function triggered when Load picture button is clicked, invoking open file dialog
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);

		// Function triggered when Run button is clicked, invoking filtration with option specified by 
		// option radio buttons and number of threads trackBar
		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);

		// Function triggered when Save button is clicked, invoking save file dialog
		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);

		// Function triggered when file in open file dialog is approved, invoking loading BMP file
		System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);

		// Function triggered when application starts to load, loading DLLs and functions
		System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e);

		// Function triggered when file in save file dialog is approved, invoking saving BMP file
		System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);

		// Function triggered when value of number of threads trackBar has changed, propagating value to
		// number of threads textBox
		System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e);

		// Function triggered when text of number of threads textBox has changed, checking it and propagating
		// value to number of threads trackBar
		System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e);
};
}