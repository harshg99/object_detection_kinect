#include "MainForm.h"
using namespace System::Windows::Forms;
using namespace System;
void Main() {
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault;
	handGesture::MainForm form;
	Application::Run(%form);

}
