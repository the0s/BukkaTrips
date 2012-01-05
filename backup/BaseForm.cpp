#include "BaseForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

BaseForm::BaseForm(void)
{
}

BaseForm::~BaseForm(void)
{
}

bool
BaseForm::Initialize()
{
	// Construct an XML form
	//Construct(L"IDF_BASEFORM");
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_INDICATOR|FORM_STYLE_SOFTKEY_1|FORM_STYLE_TEXT_TAB);


	//id = actionId;

	return true;
}

result
BaseForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a button via resource ID
/*	__pButtonOk = static_cast<Button *>(GetControl(L"IDC_BUTTON_OK"));
	if (__pButtonOk != null)
	{
		__pButtonOk->SetActionId(ID_BUTTON_OK);
		__pButtonOk->AddActionEventListener(*this);
	}*/

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


	return r;
}

result
BaseForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
BaseForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_OK:
		{
			AppLog("OK Button is clicked! \n");
		}
		break;
	default:
		break;
	}
}


