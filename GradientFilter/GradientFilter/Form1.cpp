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

#include "pch.h"

#include "Form1.h"

#include "libManager.h"
#include "bmpManager.h"

GradientFilterApp::Form1::Form1() {
	InitializeComponent();
	this->libManager = (gcnew LibManager());
	this->bmpManager = (gcnew BMPManager());
}

GradientFilterApp::Form1::~Form1() {
	if (components)
	{
		delete components;
	}
	delete this->libManager;
	delete this->bmpManager;
}

System::Void GradientFilterApp::Form1::Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	while (!this->libManager->loadLibrary("JADll.dll")) { 
		this->textBox2->AppendText("Failed to load ASM DLL! Trying again ...\r\n"); 
	}
	this->textBox2->AppendText("ASM DLL loaded successfully!\r\n");
	while (!this->libManager->loadLibrary("CDll.dll")) { 
		this->textBox2->AppendText("Failed to load C DLL! Trying again ...\r\n");
	}
	this->textBox2->AppendText("C DLL loaded successfully!\r\n");
	while (!this->libManager->loadFunction("JADll.dll", "calculatePixelsWithVI")) { 
		this->textBox2->AppendText("Failed to load ASM procedure! Trying again ...\r\n");
	}
	this->textBox2->AppendText("ASM procedure loaded successfully!\r\n");
	while (!this->libManager->loadFunction("CDll.dll", "calculatePixels")) { 
		this->textBox2->AppendText("Failed to load C function! Trying again ...\r\n");
	}
	this->textBox2->AppendText("C function loaded successfully!\r\n");
}

System::Void GradientFilterApp::Form1::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->openFileDialog1->ShowDialog();
}

System::Void GradientFilterApp::Form1::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	while (true) {
		try {
			BMP bmpFile = this->bmpManager->getBitmap();
			BYTE* inputBytes = bmpFile.copyOfBytes;
			DWORD height = bmpFile.bmpInfo.heightBytes;
			DWORD width = bmpFile.bmpInfo.sizeBytesOfRawData / height;
			BYTE* outputBytes = (BYTE*)malloc(bmpFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
			BITMAP_CHANGE_FN_TYPE functionType;

			if (this->radioButton1->Checked)
				functionType = this->libManager->getFunction("calculatePixels");

			else if (this->radioButton2->Checked)
				functionType = this->libManager->getFunction("calculatePixelsWithVI");

			auto threads = this->trackBar1->Value;
			auto proccess = std::bind(instantiateThreads, threads, functionType, inputBytes, height, width, outputBytes);
			auto time = measureTime(proccess);
			this->textBox2->AppendText("It has taken " + time / 1000000000. + " s\r\n");

			delete this->loadedBitmap;
			this->bmpManager->exportBitmap("tempOutputFile.bmp", outputBytes);
			this->loadedBitmap = gcnew Bitmap("tempOutputFile.bmp");
			this->pictureBox1->Image = loadedBitmap;
			break;
		} catch (System::DivideByZeroException^ e) {
			this->textBox2->AppendText("There is problem with loaded bitmap! Trying to reload...\r\n");
			this->bmpManager->loadBitmap(this->openFileDialog1->FileName);
			this->textBox2->AppendText("Loaded bitmap!\r\n");
		}
	}
	this->button3->Enabled = true;
}

System::Void GradientFilterApp::Form1::button3_Click(System::Object^ sender, System::EventArgs^ e) {
	this->saveFileDialog1->ShowDialog();
}

System::Void GradientFilterApp::Form1::openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	this->pictureBox2->Image = gcnew Bitmap(this->openFileDialog1->FileName);
	this->bmpManager->loadBitmap(this->openFileDialog1->FileName);
	this->textBox2->AppendText("Loaded bitmap!\r\n");
	this->button2->Enabled = true;
}

System::Void GradientFilterApp::Form1::saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	this->loadedBitmap->Save(this->saveFileDialog1->FileName);
	this->textBox2->AppendText("Save bitmap!\r\n");
}

System::Void GradientFilterApp::Form1::trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
	this->textBox1->Text = "" + this->trackBar1->Value;
}

System::Void GradientFilterApp::Form1::textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	try {
		if (System::Int32::Parse(this->textBox1->Text) > 128 || System::Int32::Parse(this->textBox1->Text) < 1) {
			this->textBox1->Text = "1";
			this->trackBar1->Value = 1;
		}
		else {
			this->trackBar1->Value = System::Int32::Parse(this->textBox1->Text);
		}
	}
	catch (System::Exception^ e) {
		this->textBox1->Text = "1";
		this->trackBar1->Value = 1;
	}
}