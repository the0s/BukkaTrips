#include "MapForm.h"
#include <FMedia.h>

#include <FUiCtrlForm.h>
#include <FBase.h>
#include <FGraphics.h>
#include <FSystem.h>
#include <FUiControls.h>
#include <FApp.h>
#include <FLocations.h>
#include "BukkaMain.h"


using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;
using namespace Osp::Locations;
using namespace Osp::Locations::Controls;
using namespace Osp::Locations::Services;
using namespace Osp::System;
using namespace Osp::Locales;

MapForm::MapForm(void)
{
}

MapForm::~MapForm(void)
{
}

bool
MapForm::Initialize()
{
	// Construct an XML form
	Construct(L"IDF_MAPFORM");
	//Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_INDICATOR|FORM_STYLE_SOFTKEY_1|FORM_STYLE_TEXT_TAB);


	//id = actionId;

	return true;
}

result
MapForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	SetSoftkeyActionId(SOFTKEY_1, ID_RIGHT_SOFTKEY);
	AddSoftkeyActionListener(SOFTKEY_1,*this);
	// TODO: Add your initialization code here
	 __pMap = static_cast<Osp::Locations::Controls::Map *>(GetControl(L"IDC_MAP1"));
	 __pTab = static_cast<Tab *>(GetControl(L"IDC_TABBAR1"));
	 //__pMap->AddTouchEventListener(*this);

	// Get a button via resource ID
/*	__pButtonOk = static_cast<Button *>(GetControl(L"IDC_BUTTON_OK"));
	if (__pButtonOk != null)
	{
		__pButtonOk->SetActionId(ID_BUTTON_OK);
		__pButtonOk->AddActionEventListener(*this);
	}*/
/*
	SetSoftkeyText(SOFTKEY_1, "Back");
	SetSoftkeyActionId(SOFTKEY_1, ID_SOFTKEY_RIGHT);
	AddSoftkeyActionListener(SOFTKEY_1,*this);

	Tab* pTab= GetTab();
	if (pTab){
		//add the tabs
		pTab->AddItem(L"One", ID_TAB_ONE);
		pTab->AddItem(L"Two", ID_TAB_TWO);
		pTab->AddItem(L"Three", ID_TAB_THREE);

		//set the selected tab
		pTab->SetSelectedItem(pTab->GetItemIndexFromActionId(id));

		//add the action event listener
		pTab->AddActionEventListener(*this);

	}
*/

	return r;
}

result
MapForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
MapForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
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

