#pragma once

// INCLUDES
#include <windows.h>

// PROTO
void InjectDLL( DWORD, char* );
void EjectDLL( );
DWORD CallFunction( DWORD, void*, DWORD, BOOL );
DWORD CallFunctionByName( char* , char* , void* , DWORD , BOOL );
void ReadRemoteString( DWORD, DWORD, char*, DWORD );
int GetRemoteCalls( DWORD, int* );

// Global variables
HANDLE hThread;
HANDLE hProcess;
HMODULE hKernel32;
DWORD hLibModule;


namespace Telepathy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;	
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for frmMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  lstFunctions;
	private: System::Windows::Forms::ComboBox^  cmbProcess;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtAddress;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  txtParams;

	private: System::Windows::Forms::Label^  label3;
	public: System::Windows::Forms::TextBox^  txtReturn;
	private: 


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btCall;
	private: System::Windows::Forms::Button^  btInject;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  btUpdateProcess;


	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::CheckBox^  chkString;
	private: System::Windows::Forms::ComboBox^  cmbDll;
	private: System::Windows::Forms::Button^  btModules;
	private: System::Windows::Forms::Label^  lblAddress;
	private: System::Windows::Forms::Button^  btGetAddress;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  btAnalize;


	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMain::typeid));
			this->lstFunctions = (gcnew System::Windows::Forms::ListBox());
			this->cmbProcess = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtAddress = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtParams = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtReturn = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btCall = (gcnew System::Windows::Forms::Button());
			this->btInject = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->btUpdateProcess = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->chkString = (gcnew System::Windows::Forms::CheckBox());
			this->cmbDll = (gcnew System::Windows::Forms::ComboBox());
			this->btModules = (gcnew System::Windows::Forms::Button());
			this->lblAddress = (gcnew System::Windows::Forms::Label());
			this->btGetAddress = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btAnalize = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lstFunctions
			// 
			this->lstFunctions->FormattingEnabled = true;
			this->lstFunctions->Location = System::Drawing::Point(12, 51);
			this->lstFunctions->Name = L"lstFunctions";
			this->lstFunctions->Size = System::Drawing::Size(172, 342);
			this->lstFunctions->Sorted = true;
			this->lstFunctions->TabIndex = 0;
			this->lstFunctions->SelectedIndexChanged += gcnew System::EventHandler(this, &frmMain::lstFunctions_SelectedIndexChanged);
			// 
			// cmbProcess
			// 
			this->cmbProcess->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbProcess->FormattingEnabled = true;
			this->cmbProcess->Location = System::Drawing::Point(193, 32);
			this->cmbProcess->Name = L"cmbProcess";
			this->cmbProcess->Size = System::Drawing::Size(239, 21);
			this->cmbProcess->Sorted = true;
			this->cmbProcess->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(190, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Process List:";
			// 
			// txtAddress
			// 
			this->txtAddress->Location = System::Drawing::Point(193, 84);
			this->txtAddress->Name = L"txtAddress";
			this->txtAddress->Size = System::Drawing::Size(288, 20);
			this->txtAddress->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(190, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Function Address/Name:";
			// 
			// txtParams
			// 
			this->txtParams->Location = System::Drawing::Point(193, 187);
			this->txtParams->Multiline = true;
			this->txtParams->Name = L"txtParams";
			this->txtParams->Size = System::Drawing::Size(319, 72);
			this->txtParams->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(190, 171);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(89, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Function Params:";
			// 
			// txtReturn
			// 
			this->txtReturn->Location = System::Drawing::Point(193, 317);
			this->txtReturn->Multiline = true;
			this->txtReturn->Name = L"txtReturn";
			this->txtReturn->Size = System::Drawing::Size(319, 76);
			this->txtReturn->TabIndex = 5;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(190, 301);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(71, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Return value:";
			// 
			// btCall
			// 
			this->btCall->Location = System::Drawing::Point(359, 265);
			this->btCall->Name = L"btCall";
			this->btCall->Size = System::Drawing::Size(153, 23);
			this->btCall->TabIndex = 7;
			this->btCall->Text = L"Remote Call";
			this->btCall->UseVisualStyleBackColor = true;
			this->btCall->Click += gcnew System::EventHandler(this, &frmMain::btCall_Click);
			// 
			// btInject
			// 
			this->btInject->Location = System::Drawing::Point(193, 265);
			this->btInject->Name = L"btInject";
			this->btInject->Size = System::Drawing::Size(145, 23);
			this->btInject->TabIndex = 7;
			this->btInject->Tag = L"0";
			this->btInject->Text = L"Inject DLL";
			this->btInject->UseVisualStyleBackColor = true;
			this->btInject->Click += gcnew System::EventHandler(this, &frmMain::btInject_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(454, -147);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(169, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// btUpdateProcess
			// 
			this->btUpdateProcess->Location = System::Drawing::Point(438, 31);
			this->btUpdateProcess->Name = L"btUpdateProcess";
			this->btUpdateProcess->Size = System::Drawing::Size(74, 23);
			this->btUpdateProcess->TabIndex = 7;
			this->btUpdateProcess->Tag = L"0";
			this->btUpdateProcess->Text = L"UPDATE";
			this->btUpdateProcess->UseVisualStyleBackColor = true;
			this->btUpdateProcess->Click += gcnew System::EventHandler(this, &frmMain::btUpdateProcess_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(190, 120);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(58, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"DLL Name";
			// 
			// chkString
			// 
			this->chkString->AutoSize = true;
			this->chkString->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->chkString->Location = System::Drawing::Point(424, 300);
			this->chkString->Name = L"chkString";
			this->chkString->Size = System::Drawing::Size(88, 17);
			this->chkString->TabIndex = 8;
			this->chkString->Text = L"Return String";
			this->chkString->UseVisualStyleBackColor = true;
			// 
			// cmbDll
			// 
			this->cmbDll->FormattingEnabled = true;
			this->cmbDll->Location = System::Drawing::Point(193, 136);
			this->cmbDll->Name = L"cmbDll";
			this->cmbDll->Size = System::Drawing::Size(288, 21);
			this->cmbDll->Sorted = true;
			this->cmbDll->TabIndex = 9;
			// 
			// btModules
			// 
			this->btModules->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btModules->Location = System::Drawing::Point(487, 135);
			this->btModules->Name = L"btModules";
			this->btModules->Size = System::Drawing::Size(25, 23);
			this->btModules->TabIndex = 10;
			this->btModules->Tag = L"0";
			this->btModules->Text = L"+";
			this->btModules->UseVisualStyleBackColor = true;
			this->btModules->Click += gcnew System::EventHandler(this, &frmMain::btModules_Click);
			// 
			// lblAddress
			// 
			this->lblAddress->AutoSize = true;
			this->lblAddress->Location = System::Drawing::Point(446, 68);
			this->lblAddress->Name = L"lblAddress";
			this->lblAddress->Size = System::Drawing::Size(66, 13);
			this->lblAddress->TabIndex = 4;
			this->lblAddress->Text = L"0x00000000";
			// 
			// btGetAddress
			// 
			this->btGetAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btGetAddress->Location = System::Drawing::Point(487, 83);
			this->btGetAddress->Name = L"btGetAddress";
			this->btGetAddress->Size = System::Drawing::Size(25, 23);
			this->btGetAddress->TabIndex = 10;
			this->btGetAddress->Tag = L"0";
			this->btGetAddress->Text = L"+";
			this->btGetAddress->UseVisualStyleBackColor = true;
			this->btGetAddress->Click += gcnew System::EventHandler(this, &frmMain::btGetAddress_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"DLL files|*.dll|All files|*.*";
			this->openFileDialog1->Title = L"Select the DLL to inject";
			// 
			// btAnalize
			// 
			this->btAnalize->Location = System::Drawing::Point(12, 12);
			this->btAnalize->Name = L"btAnalize";
			this->btAnalize->Size = System::Drawing::Size(172, 23);
			this->btAnalize->TabIndex = 11;
			this->btAnalize->Tag = L"0";
			this->btAnalize->Text = L"ANALIZE";
			this->btAnalize->UseVisualStyleBackColor = true;
			this->btAnalize->Click += gcnew System::EventHandler(this, &frmMain::btAnalize_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(524, 402);
			this->Controls->Add(this->btAnalize);
			this->Controls->Add(this->btGetAddress);
			this->Controls->Add(this->btModules);
			this->Controls->Add(this->cmbDll);
			this->Controls->Add(this->chkString);
			this->Controls->Add(this->btUpdateProcess);
			this->Controls->Add(this->btInject);
			this->Controls->Add(this->btCall);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txtReturn);
			this->Controls->Add(this->txtParams);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->lblAddress);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txtAddress);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->cmbProcess);
			this->Controls->Add(this->lstFunctions);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"frmMain";
			this->Text = L"Telepathy v0.1";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	DWORD GetPID()
	{
		// Get the PID
		String^ process = cmbProcess->SelectedItem->ToString();
		array<String^> ^pid = process->Split(';');			
		DWORD PID = Int32::Parse(pid[1]->ToString());

		return PID;
	}

private: 
	System::Void frmMain_Load(System::Object^  sender, System::EventArgs^  e) 
	{
		// Load all processes
		LoadProcesses();		
	}

private: 
	System::Void btInject_Click(System::Object^  sender, System::EventArgs^  e) 
	{		
		if (btInject->Tag == "1")
		{
			// Free the loaded library
			EjectDLL();

			// Prepare GUI
			btInject->Text = "Inject DLL";
			btInject->Tag = "0";
			cmbProcess->Enabled = TRUE;
			btUpdateProcess->Enabled = TRUE;
		} else {
			// Get the library
			if (openFileDialog1->ShowDialog() ==  System::Windows::Forms::DialogResult::OK)
			{		
				// Get the filename
				char* strFile = (char*)(void*) Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);

				// Inject the DLL
				InjectDLL(GetPID(), strFile);

				// Prepare GUI
				String^ process = cmbProcess->SelectedItem->ToString();
				btInject->Text = "Release DLL (" + process + ")";
				btInject->Tag = "1";
				cmbProcess->Enabled = FALSE;
				btUpdateProcess->Enabled = FALSE;

				// Free the String
				Marshal::FreeHGlobal(IntPtr((void*)strFile));
			}
		}
	}

private: 
	System::Void btUpdateProcess_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		// Update the processes list
		LoadProcesses();
	}

	// Load all processes
private:
	System::Void LoadProcesses()
	{
		// Clear the list
		cmbProcess->Items->Clear();

		// Fill the process list	
		array<Process^> ^plist = Process::GetProcesses();
		for each(Process^ p in plist)
		{
			if ((p->Id == 0) || (p->Id == 4))
				continue;
			cmbProcess->Items->Add(p->ProcessName->ToUpper() + ";" + p->Id.ToString());			
		}

		// Set the first process selected
		cmbProcess->SelectedIndex = 0;
	}

	// Load all modules from selected process
private:
	System::Void LoadModules(Process^ p)
	{
		// Clear the list
		cmbDll->Items->Clear();		

		// Fill the list 
		for each(ProcessModule^ m in p->Modules)
		{
			cmbDll->Items->Add(m->FileName);			
		}
	}

private: 
	System::Void btCall_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		DWORD ret = 0;

		// Prepare the Strings		
		char* strDll = (char*)(void*) Marshal::StringToHGlobalAnsi(cmbDll->Text);				
		char* strAdr = (char*)(void*) Marshal::StringToHGlobalAnsi(txtAddress->Text);				
		char* strPrm = (char*)(void*) Marshal::StringToHGlobalAnsi(txtParams->Text);				

		// Remove 0x at start if exist
		String ^check = gcnew String(reinterpret_cast<const char*>(strAdr));
		if (check->StartsWith("0x"))
		{
			check = check->Remove(0, 2);
			strAdr = (char*)(void*) Marshal::StringToHGlobalAnsi(check);
		}

		// Check if is a Address Call or Call by Name
		if (cmbDll->Text == "")
		{
			Int32 addr = Int32::Parse(check, System::Globalization::NumberStyles::AllowHexSpecifier);
			ret = CallFunction(Int32::Parse(check, System::Globalization::NumberStyles::AllowHexSpecifier), strPrm, txtParams->Text->Length, TRUE);
		} else {
			ret = CallFunctionByName(strDll, strAdr, strPrm, txtParams->Text->Length, TRUE);
		}

		// Free Strings
		Marshal::FreeHGlobal(IntPtr((void*)strDll));
		Marshal::FreeHGlobal(IntPtr((void*)strAdr));
		Marshal::FreeHGlobal(IntPtr((void*)strPrm));

		// Show result
		if (chkString->Checked)
		{
			char str[2048];			
			ReadRemoteString(GetPID(), ret, str, 2048);
			txtReturn->Text = gcnew String(str);
		} else {
			txtReturn->Text = String::Format("0x{0:X8}", ret);
		}
	}
private: 
	System::Void btModules_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		// Load the modules
		LoadModules(Process::GetProcessById(GetPID()));
	}
private: 
	System::Void btGetAddress_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		// Prepare the Strings		
		char* strDll = (char*)(void*) Marshal::StringToHGlobalAnsi(cmbDll->Text);				
		char* strAdr = (char*)(void*) Marshal::StringToHGlobalAnsi(txtAddress->Text);				

		// Variables
		void* pTemp = NULL;		
		DWORD pFunction;     				
	    
		// Get the function address
		pTemp = LoadLibraryA(strDll);
		pFunction = (DWORD)GetProcAddress((HMODULE)pTemp, strAdr);

		// Show address
		if (pFunction)
			lblAddress->Text = String::Format("0x{0:X8}", pFunction);

		// Free resources
		FreeLibrary((HMODULE)pTemp);   
		Marshal::FreeHGlobal(IntPtr((void*)strDll));
		Marshal::FreeHGlobal(IntPtr((void*)strAdr));
	}

// Analyze any call from remote process
private: 
	System::Void btAnalize_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		int *calls = (int*)malloc(sizeof(int) * 1000);
		int size = GetRemoteCalls(GetPID(), calls);
		if (size == -1)
		{
			MessageBox::Show("Cannot access to process", "Analyze Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		lstFunctions->Items->Clear();
		int i = 0;
		for (i = 0; i<size; i++)
		{
			String ^str = String::Format("0x{0:X8}", *calls);
			if (lstFunctions->Items->IndexOf(str) < 0)
				lstFunctions->Items->Add(str);			
			calls++;
		}		
	}
private: System::Void lstFunctions_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 txtAddress->Text = lstFunctions->SelectedItem->ToString();
		 }
};
}

