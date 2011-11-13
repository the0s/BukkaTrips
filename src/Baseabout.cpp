
#include "Baseabout.h"
#include "BukkaMain.h"


using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;
using namespace Osp::System;


Baseabout::Baseabout(void)
{
}

Baseabout::~Baseabout(void)
{
}

bool
Baseabout::Initialize()
{
	Form::Construct(L"IDF_BASEABOUT");

	return true;
}

result
Baseabout::OnInitializing(void)
{
	result r = E_SUCCESS;

		SetSoftkeyActionId(SOFTKEY_1, ID_RIGHT_SOFTKEY);
		AddSoftkeyActionListener(SOFTKEY_1,*this);
	// TODO: Add your initialization code here

	return r;
}

result
Baseabout::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
Baseabout::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_LEFT_SOFTKEY:{
		AppLog("LEFT Button is clicked! \n");

		break;
	}
	case ID_RIGHT_SOFTKEY:{
		BukkaMain *pMain = new BukkaMain();
		pMain->Initialize();
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		pFrame->AddControl(*pMain);
		pFrame->SetCurrentForm(*pMain);
		pMain->Draw();
		pMain->Show();
		break;
	}
	default:
		break;
	}
}





void
Baseabout::OnTouchModeChanged(const Osp::Ui::Control& source, bool isInTouchMode)
{
	// TODO: Add your implementation codes here

}
