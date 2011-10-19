
#ifndef _BASEABOUT_H_
#define _BASEABOUT_H_

#include <FBase.h>
#include <FUi.h>



class Baseabout :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	Baseabout(void);
	virtual ~Baseabout(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:
	static const int ID_LEFT_SOFTKEY = 900;
	static const int ID_RIGHT_SOFTKEY = 901;


// Generated call-back functions
public:
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);

	virtual void OnTouchModeChanged(const Osp::Ui::Control& source, bool isInTouchMode);
};

#endif
