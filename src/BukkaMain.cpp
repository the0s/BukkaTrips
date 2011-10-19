/*
 * BukkaMain.cpp
 *
 *  Created on: 19 Oct 2011
 *      Author: Andrea
 */

#include "BukkaMain.h"
#include "BaseForm.h"
#include "MapForm.h"
#include "Baseabout.h"
#include "BukkaTrips.h"



using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;
using namespace Osp::System;


BukkaMain::BukkaMain(void)
{
}

BukkaMain::~BukkaMain(void)
{
}

bool
BukkaMain::Initialize()
{
	// Construct an XML form
	//Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_INDICATOR|FORM_STYLE_SOFTKEY_1|FORM_STYLE_TEXT_TAB);
	Construct(L"IDF_BASEMAIN");


	return true;
}

result
BukkaMain::OnInitializing(void)
{
	result r = E_SUCCESS;

	__pButtonAttraction = static_cast<Button *>(GetControl(L"IDC_BUTTONATTR"));
	if (__pButtonAttraction != null){
		__pButtonAttraction->SetActionId(ID_SOFTKEY_ATTRACTIONS);
		__pButtonAttraction->AddActionEventListener(*this);
	}
	__pButtonPlanner = static_cast<Button *>(GetControl(L"IDC_BUTTONPLANNER"));
	if (__pButtonPlanner != null){
		__pButtonPlanner->SetActionId(ID_SOFTKEY_PLANNER);
		__pButtonPlanner->AddActionEventListener(*this);
	}
	__pButtonAbout = static_cast<Button *>(GetControl(L"IDC_BUTTONABOUT"));
	if (__pButtonAbout != null){
		__pButtonAbout->SetActionId(ID_SOFTKEY_ABOUT);
		__pButtonAbout->AddActionEventListener(*this);
	}
	__pButtonMap = static_cast<Button *>(GetControl(L"IDC_BUTTONMAP"));
	if (__pButtonMap != null){
		__pButtonMap->SetActionId(ID_SOFTKEY_MAP);
		__pButtonMap->AddActionEventListener(*this);
	}
	return r;
}

result
BukkaMain::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
BukkaMain::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_SOFTKEY_ATTRACTIONS:{
		AppLog("Attration Button is clicked! \n");

		break;
	}
	case ID_SOFTKEY_PLANNER:{
		AppLog("Planner Button is clicked! \n");
		break;
	}
	case ID_SOFTKEY_MAP:{
		MapForm *pMap = new MapForm();
		pMap->Initialize();
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		pFrame->AddControl(*pMap);
		pFrame->SetCurrentForm(*pMap);
		pMap->Draw();
		pMap->Show();
		break;
	}
	case ID_SOFTKEY_ABOUT:{
		Baseabout *pAbout = new Baseabout();
		pAbout->Initialize();
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		pFrame->AddControl(*pAbout);
		pFrame->SetCurrentForm(*pAbout);
		pAbout->Draw();
		pAbout->Show();

		break;
	}
	break;
	default:
		break;
	}
}





void
BukkaMain::OnTouchModeChanged(const Osp::Ui::Control& source, bool isInTouchMode)
{
	// TODO: Add your implementation codes here

}
