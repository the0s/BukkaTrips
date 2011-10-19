#ifndef _BASEFORM_H_
#define _BASEFORM_H_

#include <FBase.h>
#include <FUi.h>

class BaseForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	BaseForm(void);
	virtual ~BaseForm(void);
	bool Initialize();

// Implementation
protected:
	static const int ID_BUTTON_OK = 101;
	static const int ID_SOFTKEY_RIGHT = 110;

	Osp::Ui::Controls::Button *__pButtonOk;


public:
	static const int ID_TAB_ONE = 200;
	static const int ID_TAB_TWO = 201;
	static const int ID_TAB_THREE = 202;
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);



private: int id;
};

#endif	//_BASEFORM_H_
