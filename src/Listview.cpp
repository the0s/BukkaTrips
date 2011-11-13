#include "Listview.h"
#include <FGraphics.h>
#include <FMedia.h>

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;
using namespace Osp::Graphics;

Listview::Listview(void) {
}

Listview::~Listview(void) {
}

bool Listview::Initialize() {
	// Construct an XML form
	Construct(L"IDF_LISTVIEW");

	return true;
}

result Listview::OnInitializing(void) {
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	__name.Construct();
	__name.Add(new String(L"Big Ben"));
	__name.Add(new String(L"Imperial College"));
	__name.Add(new String(L"Royal Albert Hall"));
	__name.Add(new String(L"Natural History Museum"));
	__name.Add(new String(L"Science Museum"));
	__name.Add(new String(L"Buckingham Palace"));

	__bitmapPath.Construct();
	__bitmapPath.Add(new String("/Res/Icons/BukkaTrips_type2.png"));
	__bitmapPath.Add(new String("/Res/Icons/BukkaTrips_type3.png"));
	__bitmapPath.Add(new String("/Res/Icons/BukkaTrips_type4.png"));
	__bitmapPath.Add(new String("/Res/Icons/Splash_type2.png"));
	__bitmapPath.Add(new String("/Res/Icons/Splash_type3.png"));
	__bitmapPath.Add(new String(L"/Res/Icons/Splash_type4.png"));


	menu_ = new OptionMenu();
	 menu_->Construct();
	 menu_->SetShowState(true);
	 menu_->AddItem(String("GO!"), ON_MENU_CALCULATE);
	 menu_->AddActionEventListener(*this);
	 this->AddControl(*menu_);
	 this->SetOptionkeyActionId(ON_MENU);
	 this->AddOptionkeyActionListener(*this);

	__pLabelLog = static_cast<Label *> (GetControl("IDC_LABEL1"));
	__pLabelLog->SetText(L"Log");
	__pLabelLog->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	ListView *pListview1 =
			static_cast<ListView *> (GetControl("IDC_LISTVIEW1"));
	if (pListview1) {
		pListview1->SetItemProvider(*this);
		pListview1->AddListViewItemEventListener(*this);
	}
	return r;
}

result Listview::OnTerminating(void) {
	result r = E_SUCCESS;

	Osp::Base::Collection::IEnumeratorT<String*>* pEnum =
			__name.GetEnumeratorN();
	int index = 0;
	while (pEnum->MoveNext() == E_SUCCESS) {
		String* temp;
		pEnum->GetCurrent(temp);
		delete temp;
		temp = null;
		AppLogDebug("String(%d)", index++);
	}
	__name.RemoveAll();

	return r;
}


void
Listview::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
 switch(actionId)
 {
    case ON_MENU:
        menu_->SetShowState(!menu_->GetShowState());
        menu_->Show();
        break;
    case ON_MENU_CALCULATE:
    	AppLog("GO!");
        // to be added later
        break;
 }
}

Osp::Ui::Controls::ListItemBase* Listview::CreateItem(int index, int itemWidth) {
	ListAnnexStyle style = LIST_ANNEX_STYLE_MARK;

	CustomItem* item = new CustomItem();
	item->Construct(Osp::Graphics::Dimension(itemWidth, 100), style);

	result r;
	Bitmap* bitmap;
	Image* bitmapDecoder = new Image();

	r = bitmapDecoder->Construct();
	if (IsFailed(r)) {
		AppLog("Failed to construct decoder!");
	}
	String* bitmapPath;
	__bitmapPath.GetAt(index, bitmapPath);

	bitmap = bitmapDecoder->DecodeN(*bitmapPath, BITMAP_PIXEL_FORMAT_ARGB8888);

	String *name;
	__name.GetAt(index, name);

	item->AddElement(Rectangle(10, 20, 60, 60), ID_FORMAT_BITMAP, *bitmap,
			null, null);
	item->AddElement(Rectangle(80, 25, 400, 50), ID_FORMAT_STRING, *name, true);
	item->SetElementSelectionEnabled(ID_FORMAT_BITMAP,true);
	return item;
}

bool Listview::DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem,
		int itemWidth) {
	return true;
}

int Listview::GetItemCount(void) {
	return __name.GetCount();
}

void Listview::OnListViewItemLongPressed(Osp::Ui::Controls::ListView &listView,
		int index, int elementId, bool& invokeListViewItemCallback) {
	String itemText(L"");

	switch (elementId) {
	case ID_FORMAT_STRING:
		itemText.Format(40, L"Item %d: Text Selected", index + 1);
		break;
	case ID_FORMAT_BITMAP:
		itemText.Format(40, L"Item %d: Bitmap Selected", index + 1);
		break;
	case ID_FORMAT_CUSTOM:
		itemText.Format(40, L"Item %d: Custom Selected", index + 1);
		break;
	case ID_FORMAT_NULL:
		itemText.Format(40, L"Item %d: Selected", index + 1);
		break;
	}

	__pLabelLog->SetText(itemText);
	__pLabelLog->Draw();
	__pLabelLog->Show();
}

void Listview::OnListViewItemStateChanged(
		Osp::Ui::Controls::ListView &listView, int index, int elementId,
		Osp::Ui::Controls::ListItemStatus status) {

	String itemText(L"");
	MessageBox msgbox;
	int modalResult = 0;
	AppLog("%d",elementId);

	switch (elementId) {
	case ID_FORMAT_STRING:
		itemText.Format(40, L"Item %d: Text Selected", index + 1);
		break;
	case ID_FORMAT_BITMAP:
		itemText.Format(40, L"Item %d: Bitmap Selected", index + 1);

		msgbox.Construct(
				"Info",
				"This item was created a few hours ago and it was a pain to understand how bada developers intended the listview use to be",
				MSGBOX_STYLE_NONE, 0);

		msgbox.ShowAndWait(modalResult);
		break;
	case ID_FORMAT_NULL:
		itemText.Format(40, L"Ite %d: Selected", index + 1);
		break;
	}
	__pLabelLog->SetText(itemText);
	__pLabelLog->Draw();
	__pLabelLog->Show();

}

void Listview::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView,
		int index, Osp::Ui::Controls::SweepDirection direction) {
}
//void
//Listview::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state)
//{
//	String contextItem(L"");
//	if (elementId == ID_CONTEXT_ITEM_1)
//		contextItem.Format(40, L"ContextItem %d :\n(Test1) Selected", index+1);
//	else
//		contextItem.Format(40, L"ContextItem %d :\n(Test2) Selected", index+1);
//
//	__pLabelLog->SetText(contextItem);
//	__pLabelLog->Draw();
//	__pLabelLog->Show();
//}
