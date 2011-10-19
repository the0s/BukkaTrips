/*
 * BukkaMain.h
 *
 *  Created on: 19 Oct 2011
 *      Author: Andrea
 */

#ifndef BUKKAMAIN_H_
#define BUKKAMAIN_H_

#include <FApp.h>
#include <FSystem.h>
#include <FBase.h>
#include <FUi.h>

class BukkaMain :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
 	public Osp::Ui::ITouchModeChangedEventListener
	{

public:

	BukkaMain();
	virtual ~BukkaMain();
	bool Initialize(void);

protected:
	static const int ID_ICON_LIST_ITEM1 =221;
	static const int ID_ICON_LIST_ITEM2 =222;
	static const int ID_ICON_LIST_ITEM3 =223;

	static const int ID_SOFTKEY_ATTRACTIONS = 600;
	static const int ID_SOFTKEY_PLANNER = 601;
	static const int ID_SOFTKEY_ABOUT = 602;
	static const int ID_SOFTKEY_MAP = 603;


	Osp::Ui::Controls::Button *__pButtonAttraction;
	Osp::Ui::Controls::Button *__pButtonPlanner;
	Osp::Ui::Controls::Button *__pButtonAbout;
	Osp::Ui::Controls::Button *__pButtonMap;


/*	Osp::Graphics::Bitmap* pBitmapNormal1;
	Osp::Graphics::Bitmap* pBitmapNormal2;
	Osp::Graphics::Bitmap* pBitmapNormal3;

	result CreateBitmaps(void);
	result DeleteBitmaps(void);*/

public:
	result OnInitializing(void);
	result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);

	virtual void OnTouchModeChanged(const Osp::Ui::Control& source, bool isInTouchMode);
};

#endif /* BUKKAMAIN_H_ */
