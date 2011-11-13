#ifndef _MAPFORM2_H_
#define _MAPFORM2_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FSystem.h>
#include <FUiControls.h>
#include <FApp.h>
#include <FLocations.h>


class MapForm2 :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	MapForm2(void);
	virtual ~MapForm2(void);
	bool Initialize();
	enum{
		AID_ZOOM_IN = 300,
		AID_ZOOM_OUT,
		AID_ADD_AREA,
		AID_REMOVE_AREA,
		AID_MOVE_TO_MY_LOC
	};

// Implementation
protected:
	static const int ID_BUTTON_OK = 101;
	static const int ID_RIGHT_SOFTKEY = 901;

	Osp::Ui::Controls::Button *__pButtonOk;
	Osp::Locations::Controls::Map *__pMap;
	Osp::Ui::Controls::Tab *__pTab;

public:
	static const int ID_TAB_ONE = 200;
	static const int ID_TAB_TWO = 201;
	static const int ID_TAB_THREE = 202;
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);


private: int id;
bool __isLocationEnabled;
};
#endif
