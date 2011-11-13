#include "MapForm.h"
#include <FMedia.h>

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
	
MapForm::MapForm()
: _pMapSvcProvider(null),
_pMap(null),
_pOverlay(null),
_pInfoWindow(null),
_pMarker(null),
_pMovedMarker1(null),
_pMovedMarker2(null),
_pMovedMarker3(null),
_pCircle(null),
_pPolygon(null),
_pRectangle(null),
_pPolyline(null),
_pFrame(null),
_showAll(false),
_showOverlay(false),
_showInfo(false),
_showInfoWithImage(false),
_showMe(false),
_movedMarker(false),
_popupShow(false),
_pPopup(null),
_pLabel(null),
_pBtn(null),
_pContextMenu(null),
_pGeocodingSvcProvider(null)
{
}


MapForm::~MapForm()
{
	CloseContextMenu();

	delete _pPopup;
	_pPopup = null;

	delete _pOverlay;
	_pOverlay = null;

	delete _pMapSvcProvider;
	_pMapSvcProvider = null;

	delete _pInfoWindow;
	_pInfoWindow = null;

	delete _pPolygon;
	_pPolygon = null;

	delete _pPolyline;
	_pPolyline = null;

	delete _pCircle;
	_pCircle = null;

	delete _pRectangle;
	_pRectangle = null;

	delete _pMarker;
	_pMarker = null;

	delete _pMovedMarker1;
	_pMovedMarker1 = null;

	delete _pMovedMarker2;
	_pMovedMarker2 = null;

	delete _pMovedMarker3;
	_pMovedMarker3 = null;

}

result
MapForm::OnTerminating(void)
{
	delete _pGeocodingSvcProvider;
	_pGeocodingSvcProvider = null;

	return E_SUCCESS;
}
void
MapForm::CreateAndShowContextMenu(int menuItem,Osp::Graphics::Point position){

	if (_pContextMenu == null) {
		_pContextMenu = new ContextMenu();
		_pContextMenu->Construct(position, CONTEXT_MENU_STYLE_LIST);

		switch (menuItem) {

		case ACTION_ID_INFOWINDOW_BUTTON: {
			_pContextMenu->AddItem("Text Window", ACTION_ID_INFOWINDOW);
			_pContextMenu->AddItem("Image Window", ACTION_ID_INFOWINDOW2);
		}
			break;
		case ACTION_ID_OVERLAY_BUTTON: {
			_pContextMenu->AddItem("Markers", ACTION_ID_MARKERMOVE);
			_pContextMenu->AddItem("Overlays", ACTION_ID_OVERLAY);
			_pContextMenu->AddItem("All", ACTION_ID_ALL);
		}break;
		case ACTION_ID_ROTATE_BUTTON: {
			_pContextMenu->AddItem("Clockwise", ACTION_ID_ROTATE_CW);
			_pContextMenu->AddItem("CounterClockwise", ACTION_ID_ROTATE_CCW);
		}break;
	}
		_pContextMenu->AddActionEventListener(*this);
		_pContextMenu->Show();
	}
}

void
MapForm::CloseContextMenu(void){

	if (_pContextMenu) {
		_pContextMenu->RemoveActionEventListener(*this);
		delete _pContextMenu;
		_pContextMenu = null;
	}
}

result
MapForm::CreateForm(Frame* pFrame)
{
	result r = E_SUCCESS;
	_pFrame = pFrame;

	r = Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_HEADER | FORM_STYLE_INDICATOR | FORM_STYLE_FOOTER);

	Header* pHeader = GetHeader();
	if (pHeader)
	{
		pHeader->SetStyle(HEADER_STYLE_TITLE);
		pHeader->SetName(L"Map Control");
		pHeader->SetTitleText(L"Map");

	}

	Footer* pFooter = GetFooter();
	if (pFooter)
	{
		pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT );

		FooterItem footerItem1;
		footerItem1.Construct(ACTION_ID_MY_LOCATION);
		footerItem1.SetText("My\nLocation");
		pFooter->AddItem(footerItem1);

		FooterItem footerItem2;
		footerItem2.Construct(ACTION_ID_INFOWINDOW_BUTTON);
		footerItem2.SetText("Show\nInfowindow");
		pFooter->AddItem(footerItem2);

		FooterItem footerItem3;
		footerItem3.Construct(ACTION_ID_OVERLAY_BUTTON);
		footerItem3.SetText("Show\nOverlays");
		pFooter->AddItem(footerItem3);

		FooterItem footerItem4;
		footerItem4.Construct(ACTION_ID_ROTATE_BUTTON);
		footerItem4.SetText("Rotate\nMap");
		pFooter->AddItem(footerItem4);

		pFooter->AddActionEventListener(*this);
	}
	if (!InitializeMapService())
	{
		AppLog("Form::InitializeMapService() has failed.");
		goto CATCH;
	}

	AddOrientationEventListener(*this);
	SetOrientation(ORIENTATION_AUTOMATIC_FOUR_DIRECTION);
	
	CreatePopups();
	_pFrame->AddControl(*this);

	Draw();
	Show();

	return E_SUCCESS;

CATCH:
	return E_FAILURE;
}

void
MapForm::CreatePopups()
 {
	result r = E_SUCCESS;
	// popup for setting location services
	_pPopup = new Popup();

	if (_pPopup != null) {
		r = _pPopup->Construct(false, Dimension(450, 335));

		if (r != E_SUCCESS) {
			delete _pPopup;
			_pPopup = null;
			return;
		}
		_pLabel = new Label();
		if (_pLabel != null) {
			r = _pLabel->Construct(Rectangle(0, 0, 435, 220),L"Move to the current\nlocation failed.\nThe location information may\n be temporarily unavailable.");
			if (r == E_SUCCESS) {
				_pLabel->SetTextConfig(35, LABEL_TEXT_STYLE_NORMAL);
				_pLabel->SetBackgroundColor(SYSTEM_COLOR_POPUP_BACKGROUND);
				_pPopup->AddControl(*_pLabel);
			} else {
				delete _pLabel;
				_pLabel = null;
			}
		}
		_pBtn = new Button();
		if (_pBtn != null) {
			r = _pBtn->Construct(Rectangle(450 / 2 - 90, 300 / 2 + 80, 180, 70), L"OK");
			if (r == E_SUCCESS) {
				_pBtn->SetActionId(ACTION_ID_BUTTON_OK_POPUP);
				_pBtn->AddActionEventListener(*this);
				_pPopup->AddControl(*_pBtn);
			} else {
				delete _pBtn;
				_pBtn = null;
			}
		}

	}
}

void
MapForm::Redraw(void)
{
	if (_pFrame)
	{
		_pFrame->RequestRedraw(true);
	}
}

void
MapForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	if (null == _pMap) return;

	switch(actionId)
	{
	case ACTION_ID_INFOWINDOW_BUTTON:
	case ACTION_ID_OVERLAY_BUTTON:
	case ACTION_ID_ROTATE_BUTTON:
		{
		Rectangle clientRect = GetClientAreaBounds();
		CloseContextMenu();
		int sectors = clientRect.width / int(ACTION_ID_BUTTON_MAX);
		Point pos;
		pos.y =clientRect.height + ((this->GetHeight() - clientRect.height)/2);
		pos.x = (sectors / 2) + (sectors * actionId);
		CreateAndShowContextMenu(actionId,pos);
	}
		break;
	case ACTION_ID_ROTATE_CW: {
			RotateMap(true);
		}
		break;
	case ACTION_ID_ROTATE_CCW: {
			RotateMap(false);
		}
		break;
	case ACTION_ID_OVERLAY: {
		if (_showAll) {
				ShowAll(false);
				ShowOverlays(true);
		} else {
				MoveMarker(false);
				ShowInfoWindow(false);
				ShowInfoWindowWithImage(false);
				ShowMyLocation(false);

			if (_showOverlay == false) {
					ShowOverlays(true);
			} else {
					ShowOverlays(false);
				}
			}

			Redraw();
		}
		break;
	case ACTION_ID_INFOWINDOW: {
		if (_showAll) {
				ShowAll(false);
				ShowInfoWindow(true);
		} else {
				MoveMarker(false);
				ShowOverlays(false);
				ShowInfoWindowWithImage(false);
				ShowMyLocation(false);

			if (_showInfo == false) {
					ShowInfoWindow(true);
			} else {
					ShowInfoWindow(false);
				}
			}

			Redraw();
		}
		break;
	case ACTION_ID_INFOWINDOW2: {
		if (_showAll) {
				ShowAll(false);
				ShowInfoWindowWithImage(true);
		} else {
				MoveMarker(false);
				ShowOverlays(false);
				ShowInfoWindow(false);
				ShowMyLocation(false);

			if (_showInfoWithImage == false) {
					ShowInfoWindowWithImage(true);
			} else {
					ShowInfoWindowWithImage(false);
				}
			}

			Redraw();
		}
		break;
	case ACTION_ID_MY_LOCATION: {
		ShowAll(false);
		ShowMyLocation(true);

			Redraw();
		}
		break;

	case ACTION_ID_MARKERMOVE: {
		if (_showAll) {
				ShowAll(false);
				MoveMarker(true);
		} else {
				ShowOverlays(false);
				ShowInfoWindow(false);
				ShowInfoWindowWithImage(false);
				ShowMyLocation(false);

			if (_movedMarker) {
					MoveMarker(false);
			} else {
					MoveMarker(true);
				}
			}

			Redraw();
		}
		break;

	case ACTION_ID_ALL: {
		if (_showAll == false) {
				ShowAll(true);				
		} else {
				ShowAll(false);
			}

			Redraw();
		}
		break;
		
	case ACTION_ID_BUTTON_OK_POPUP: {
		if (_popupShow == true) {
				_pPopup->SetShowState(false);
				_pPopup->Show();

				_popupShow = false;

				Redraw();
			}
		}
		break;

	case ACTION_ID_GET_ADDRESS:
		RequestReverseGeocode(_positionOfContextMenu);
		break;
	}
}

bool
MapForm::InitializeMapService(void)
{
	result r = E_SUCCESS;

	// If you want to develop your own application with the location services.
	// Some service providers may need license key for displaying a map. refer to the developer guide for details.
	// Client name "guest" is invalid license.
	const String extraInfo =  L"ClientName=samsung-jc;ClientPassword=4xndosys;HostUrl=http://ws.decarta.com/openls/openls";

	Coordinates center;
	Rectangle clientRect = GetClientAreaBounds();

	// create map service provider and initialize map
	_pMapSvcProvider = static_cast<IMapServiceProvider*>(ProviderManager::ConnectToServiceProviderN(L"deCarta", LOC_SVC_PROVIDER_TYPE_MAP, extraInfo));
	if (null == _pMapSvcProvider)
	{
		AppLog( "ProviderManager::ConnectToServiceProviderN() has failed.");
		goto CATCH;
	}

	_pMap = new Map();
	if (null == _pMap)
	{
		AppLog( "MapForm::allocate new memory for map.");
		goto CATCH;
	}

	_pMap->Construct(Rectangle(0,0, clientRect.width, clientRect.height), *_pMapSvcProvider,true);
	if (IsFailed(r))
	{
		AppLog( "MapForm::fail to contruct map.");
		goto CATCH;
	}

	//Set the Prefetch Margin
	_pMap->SetPrefetchMargin(200,100);

	center.Set(51.499339, -0.126858, 0);
	_pMap->SetCenter(center, false);
	_pMap->SetZoomLevel(17.0, false);

	//This is used to make an application listen infowindow event.
	_pMap->AddMapInfoWindowEventListener(*this);

	_pMap->AddTouchEventListener(*this);

	AddControl(*_pMap);

	//Create overlay factory class
	_pOverlay = new Overlay(_pMap);

	// create geocoding service provider
	_pGeocodingSvcProvider = static_cast<IGeocodingServiceProvider*>(ProviderManager::ConnectToServiceProviderN(L"", LOC_SVC_PROVIDER_TYPE_GEOCODING, extraInfo));

	return true;

CATCH:

	delete _pMap;
	_pMap = null;

	delete _pMapSvcProvider;
	_pMapSvcProvider = null;
	return false;
}


void
MapForm::ShowAll(bool show)
{
	bool bState = false;
	
	_showAll = show;
	
	if(show == true)
		MoveMarker(false);
	bState = MoveMarker(show);
	bState = ShowInfoWindow(show);
	bState = ShowInfoWindowWithImage(show);
	bState = ShowOverlays(show);
}

bool
MapForm::ShowMyLocation(bool show)
{
	bool isMyLocationEnabled = false;
	
		_pMap->SetMyLocationEnabled(show);
	_showMe = show;

	if(show) {
		isMyLocationEnabled = _pMap->GetMyLocationEnabled();

		if(!isMyLocationEnabled)
		{
			bool value = false;
			SettingInfo::GetValue(L"GPSEnabled", value);

			if (!value){
				int modalResult = 0;
				MessageBox messageBox;
				messageBox.Construct(L"Information", L"Location services are disabled. Enable them in location settings?", MSGBOX_STYLE_YESNO);
				messageBox.ShowAndWait(modalResult);

				if (MSGBOX_RESULT_YES == modalResult){
			// Lunching SettingAppControl
			ArrayList* pDataList = new ArrayList();
			String* pData = new String(L"category:Location");

			pDataList->Construct();
			pDataList->Add(*pData);

			AppControl* pAc = AppManager::FindAppControlN(APPCONTROL_PROVIDER_SETTINGS, "");
			if(pAc)
			{
				pAc->Start(pDataList, this);
				delete pAc;
			}

			delete pDataList;
			delete pData;
		}
				else {
					_showMe = false;
				}
			}
		}
		else
		{
			if ( _pMap->MoveToMyLocation() != E_SUCCESS) {
				_pPopup->SetShowState(true);
				_pPopup->Show();
				_popupShow = true;
				_showMe = false;
				Redraw();
			}
		}
	}

	return _showMe;
	}
		
bool
MapForm::ShowOverlays(bool show)
{
	bool bRet = _showOverlay;
	
	if (_showOverlay == show)
	{
		return bRet;
	}

	_showOverlay = show;

	if (_pOverlay == null)
	{
		_pOverlay = new Overlay(_pMap);
	}

	if (show == false)
	{
		const LinkedListT<IMapOverlay*>* pList = _pMap->GetOverlayList();

		if (pList != null && pList->GetCount() > 0)
		{
			_pMap->RemoveMapOverlay(*_pPolygon);
			_pMap->RemoveMapOverlay(*_pPolyline);
			_pMap->RemoveMapOverlay(*_pCircle);
			_pMap->RemoveMapOverlay(*_pRectangle);
			_pMap->RemoveMapOverlay(*_pMarker);

			delete _pPolygon;
			_pPolygon = null;

			delete _pPolyline;
			_pPolyline = null;

			delete _pCircle;
			_pCircle = null;

			delete _pRectangle;
			_pRectangle = null;

			delete _pMarker;
			_pMarker = null;
		}
	}
	else
	{
		//Create polygon
		if (_pPolygon == null)
		{
			_pPolygon =  _pOverlay->MakePolygon();

			if (_pPolygon == null)
			{
				AppLog("Overlay::MakePolygon() has failed.");
			}else{
				_pMap->AddMapOverlay(*_pPolygon);
			}
		}


		//Create polyline
		if (_pPolyline == null)
		{
			_pPolyline =  _pOverlay->MakePolyline();
			if (_pPolyline == null)
			{
				AppLog("Overlay::MakePolyline() has failed.");
			}else{
				_pMap->AddMapOverlay(*_pPolyline);
			}
		}

		//Create circle
		if (_pCircle == null)
		{
			_pCircle =  _pOverlay->MakeCircle();
			if (_pCircle == null)
			{
				AppLog("Overlay::MakeCircle() has failed.");
			}else{
				_pMap->AddMapOverlay(*_pCircle);
			}
		}

		//Create Marker
		if (_pMarker == null)
		{
			_pMarker =  _pOverlay->MakeMarker();
			if (_pMarker == null)
			{
				AppLog("Overlay::MakeMarker() has failed.");
			}else{
				_pMap->AddMapOverlay(*_pMarker);
			}
		}

		//Create rectangle
		if (_pRectangle == null)
		{
			_pRectangle =  _pOverlay->MakeRectangle();
			if (_pRectangle == null)
			{
				AppLog("Overlay::MakeRectangle() has failed.");
			}else{
				_pMap->AddMapOverlay(*_pRectangle);
			}
		}
	}

	return bRet;
}

bool
MapForm::ShowInfoWindow(bool show)
{
	bool bRet = _showInfo;
	_showInfo = show;

	if (show == false)
	{
		if (_pInfoWindow != null)
		{
			_pMap->CloseInfoWindow(*_pInfoWindow);
			delete _pInfoWindow;
			_pInfoWindow = null;
		}
	}
	else
	{
		//Create infowindow
		_pInfoWindow =  _pOverlay->MakeInfoWindow();

		if (_pInfoWindow == null)
		{
			AppLog("Overlay::MakeInfoWindow() has failed.");
			return bRet;
		}

		_pMap->OpenInfoWindow(*_pInfoWindow, false);

	}

	return bRet;
}

bool
MapForm::ShowInfoWindowWithImage(bool show)
{
	bool bRet = _showInfoWithImage;
	
	_showInfoWithImage = show;

	if (show == false)
	{
		if (_pInfoWindow != null)
		{
			_pMap->CloseInfoWindow(*_pInfoWindow);
			delete _pInfoWindow;
			_pInfoWindow = null;
		}
	}
	else
	{
		//Create infowindow
		_pInfoWindow =  _pOverlay->MakeInfoWindow(1);

		if (_pInfoWindow == null)
		{
			AppLog("Overlay::MakeInfoWindow() has failed.");
			return bRet;
		}

		_pMap->OpenInfoWindow(*_pInfoWindow, true);

	}

	return bRet;
}

bool
MapForm::MoveMarker(bool bMoved)
{
	bool bRet = _movedMarker;
	
	_movedMarker = bMoved;

	if (bMoved)
	{
		//Create Marker
		if (_pMovedMarker1 == null)
		{
			_pMovedMarker1 =  _pOverlay->MakeMarker();
			if (_pMovedMarker1 == null)
			{
				AppLog("Overlay::MakeMarker() has failed.");
			}
			else
			{
				Coordinates coord;
				coord.Set(29.25, -103.25 ,0); //BIG BEN
				_pMovedMarker1->SetCoordinates(coord);
				_pMap->AddMapOverlay(*_pMovedMarker1);
			}
		}

		if (_pMovedMarker2 == null)
		{
			_pMovedMarker2 =  _pOverlay->MakeMarker();
			if (_pMovedMarker2 == null)
			{
				AppLog("Overlay::MakeMarker() has failed.");
			}
			else
			{
				Coordinates coord;
				coord.Set(51.500942,-0.125442,0);
				
				_pMovedMarker2->SetCoordinates(coord);
				_pMap->AddMapOverlay(*_pMovedMarker2);
			}
		}

		if (_pMovedMarker3 == null)
		{
			_pMovedMarker3 =  _pOverlay->MakeMarker();
			if (_pMovedMarker3 == null)
			{
				AppLog("Overlay::MakeMarker() has failed.");
			}
			else
			{
				Coordinates coord;
				coord.Set(51.500595,-0.126858,0);
				
				_pMovedMarker3->SetCoordinates(coord);
				_pMap->AddMapOverlay(*_pMovedMarker3);
			}
		}
	}
	else
	{
		if (_pMovedMarker1 != null)
		{
			_pMap->RemoveMapOverlay(*_pMovedMarker1);

			delete _pMovedMarker1;
			_pMovedMarker1 = null;
		}

		if (_pMovedMarker2 != null)
		{
			_pMap->RemoveMapOverlay(*_pMovedMarker2);

			delete _pMovedMarker2;
			_pMovedMarker2 = null;
		}

		if (_pMovedMarker3 != null)
		{
			_pMap->RemoveMapOverlay(*_pMovedMarker3);

			delete _pMovedMarker3;
			_pMovedMarker3 = null;
		}
	}
	
	return bRet;
}

void
MapForm::OnOrientationChanged(const Osp::Ui::Control& source, Osp::Ui::OrientationStatus orientationStatus)
{
	if (_pMap)
	{
		Rectangle clientRect = GetClientAreaBounds();
		_pMap->SetSize(clientRect.width, clientRect.height);
		
		Draw();
	}
}

void
MapForm::OnClosingEnded(const Osp::Locations::Controls::IMapInfoWindow& source)
{
	if (_showInfo)
	{
		_showInfo = false;
	}

	if (_showInfoWithImage)
	{
		_showInfoWithImage = false;
	}
}

void
MapForm::OnAppControlCompleted(const String& appControlId, const String& operationId, const IList* pResultList)
{
	String* pResult = null;
	if (appControlId.Equals(APPCONTROL_PROVIDER_SETTINGS))
	{
		pResult = (Osp::Base::String*)pResultList->GetAt(0);
		if (pResult->Equals(APPCONTROL_RESULT_SUCCEEDED))
		{
			pResult = (Osp::Base::String*)pResultList->GetAt(1);
			if (pResult->Equals(String(L"category:Location")))
			{
				pResult = (Osp::Base::String*)pResultList->GetAt(2);
				if (pResult->Equals(String(L"GPSEnabled")))
				{
					AppLog("LocationServices are enabled.");
				}
				else
				{
					AppLog("LocationServices are disabled.");
				}
			}
		}
	}
}

void
MapForm::RotateMap(bool clockwise)
{
	int azimuth = int(_pMap->GetAzimuth());
	if (clockwise)
	{
		azimuth += 330;
	}
	else
	{
		azimuth += 30;
	}
	azimuth %= 360;

	float rotated =	_pMap->Rotate(azimuth, true);
	if (!Float::IsNaN(rotated)) RequestRedraw(true);
}

void
MapForm::ShowContextMenu(const Osp::Graphics::Point& position)
{
	_positionOfContextMenu = position;
	Rectangle clientRect = GetClientAreaBounds();

	delete _pContextMenu;
	_pContextMenu = new ContextMenu();
	_pContextMenu->Construct(position + clientRect.GetTopLeft(), CONTEXT_MENU_STYLE_LIST);
	_pContextMenu->AddItem("Get Address", ACTION_ID_GET_ADDRESS);
	_pContextMenu->AddActionEventListener(*this);
	_pContextMenu->Show();
}

void
MapForm::RequestReverseGeocode(const Osp::Graphics::Point& position)
{
	Coordinates convertedCoords;
	if (_pMap->TransformPixelsToCoordinates(position, convertedCoords))
	{
		RequestId reqId;
		GeocodingServicePreferences* pPreferences = static_cast<GeocodingServicePreferences*>(_pGeocodingSvcProvider->GetServicePreferencesN(true));
		CountryCode countryCode = COUNTRY_GB;
		pPreferences->SetBaseCountryCode(&countryCode);
		_pGeocodingSvcProvider->ReverseGeocode(convertedCoords, pPreferences, *this, reqId);
		delete pPreferences;
	}
}

void
MapForm::OnGeocodingRequestResultReceivedN(RequestId requestId, const IGeocodingServiceProvider& provider,
	Osp::Base::Collection::IList* pLandmarks, result r, const Osp::Base::String& errorCode,
	const Osp::Base::String& errorMsg)
{

}

void
MapForm::OnReverseGeocodingRequestResultReceivedN(RequestId requestId, const IGeocodingServiceProvider& provider,
	Osp::Base::Collection::IList* pLandmarks, result r, const Osp::Base::String& errorCode,
	const Osp::Base::String& errorMsg)
{
	if (E_SUCCESS == r && pLandmarks && pLandmarks->GetCount() > 0)
	{
		Landmark* pLandmark = static_cast<Landmark*>(pLandmarks->GetAt(0));
		const AddressInfo* pAddressInfo = pLandmark->GetAddressInfo();
		const QualifiedCoordinates* pCoords = pLandmark->GetQualifiedCoordinates();
		if (pAddressInfo && pCoords)
		{
			String streetNumber = pAddressInfo->GetField(ADDRESS_FIELD_STREET_NUMBER);
			String streetName = pAddressInfo->GetField(ADDRESS_FIELD_STREET_NAME);
			String city = pAddressInfo->GetField(ADDRESS_FIELD_CITY);
			String state = pAddressInfo->GetField(ADDRESS_FIELD_STATE);
			String postalCode = pAddressInfo->GetField(ADDRESS_FIELD_POSTAL_CODE);
			String address = "Latitude: " ;
			address += Double::ToString(pCoords->GetLatitude());
			address += L"\n";
			address += L"Longitude: ";
			address += Double::ToString(pCoords->GetLongitude());
			address += L"\n";
			address += L"\n";

			if(!streetNumber.IsEmpty())
			{
				address += 	streetNumber;
			}

			if (!streetName.IsEmpty())
			{
				address += L" ";
				address += streetName;
			}
			if (!city.IsEmpty())
			{
				address += L" ";
				address += city;
			}
			if (!state.IsEmpty())
			{
				address += L", ";
				address += state;
			}
			if (!postalCode.IsEmpty())
			{
				address += L" ";
				address += postalCode;
			}

			int modalResult;
			MessageBox mbox;
			String title(L"Address Information");
			mbox.Construct(title, address, MSGBOX_STYLE_OK, 0);
			mbox.ShowAndWait(modalResult);
		}
	}
	else if (E_SERVER == r)
	{
		int modalResult;
		MessageBox mbox;
		String title(L"It failed to get the address.");
		mbox.Construct(title, errorMsg, MSGBOX_STYLE_OK, 0);
		mbox.ShowAndWait(modalResult);
	}
	if (pLandmarks) pLandmarks->RemoveAll(true);
	delete pLandmarks;
}

void
MapForm::OnTouchLongPressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	ShowContextMenu(currentPosition);
}
