#ifndef _FORM1_H_
#define _FORM1_H_

#include <FBase.h>
#include <FUi.h>

class Listview: public Osp::Ui::Controls::Form,
		public Osp::Ui::IActionEventListener,
		public Osp::Ui::Controls::IListViewItemEventListener,
		public Osp::Ui::Controls::IListViewItemProvider,
 	public Osp::Ui::ITouchEventListener {

	// Construction
public:
	Listview(void);
	virtual ~Listview(void);
	bool Initialize(void);

	// Implementation
protected:
	static const int ID_FORMAT_NULL = -1;
	static const int ID_FORMAT_STRING = 500;
	static const int ID_FORMAT_BITMAP = 501;
 	static const int ID_FORMAT_CUSTOM = 503;
 	static const int GO = 506;
 	static const int BACK = 507;


 	Osp::Ui::Controls::OptionMenu *menu_;
	Osp::Base::Collection::ArrayListT<Osp::Base::String*> __name;
	Osp::Base::Collection::ArrayListT<Osp::Base::String*> __bitmapPath;
	Osp::Base::Collection::ArrayListT<Osp::Base::String*> __SelectedAttrations;
	Osp::Ui::Controls::Label* __pLabelLog;


public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction);
	virtual void OnListViewItemLongPressed(Osp::Ui::Controls::ListView &listView, int index, int elementId, bool& invokeListViewItemCallback);

	//IListViewItemProvider
	virtual Osp::Ui::Controls::ListItemBase* CreateItem (int index, int itemWidth);
	virtual bool  DeleteItem (int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int GetItemCount(void);




	virtual void OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
};

#endif	//_FORM1_H_
