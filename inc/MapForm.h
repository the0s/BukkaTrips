#ifndef _MAPFORM_H_
#define _MAPFORM_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FSystem.h>
#include <FUiControls.h>
#include <FApp.h>
#include <FLocations.h>
#include "Overlay.h"
#include "BukkaMain.h"
#include "NavigatorUtil.h"
#include "NavigatorRouteServices.h"

class MapForm :
	public Osp::Ui::Controls::Form,
	public Osp::Locations::Controls::IMapInfoWindowEventListener,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IOrientationEventListener,
	public Osp::App::IAppControlEventListener,
	public Osp::Locations::Services::IGeocodingServiceListener,
	public Osp::Ui::ITouchEventListener
{
public:
	MapForm();
	~MapForm();

private:
	enum
	{
		ACTION_ID_ROTATE_CW = 10000,
		ACTION_ID_ROTATE_CCW,
		ACTION_ID_MY_LOCATION,
		ACTION_ID_OVERLAY,
		ACTION_ID_INFOWINDOW,
		ACTION_ID_INFOWINDOW2,
		ACTION_ID_MARKERMOVE,
		ACTION_ID_ALL,
		ACTION_ID_BUTTON_OK_POPUP,
		ACTION_ID_GET_ADDRESS,
		ACTION_ID_INFOWINDOW_BUTTON = 1,
		ACTION_ID_OVERLAY_BUTTON,
		ACTION_ID_ROTATE_BUTTON,
		ACTION_ID_BACK,
		ACTION_ID_BUTTON_MAX
	};

// listener functions
public:

	// button action event
	void 	OnActionPerformed(const Osp::Ui::Control &source, int actionId);

	virtual void OnOrientationChanged(const Osp::Ui::Control& source, Osp::Ui::OrientationStatus orientationStatus);

	//InfoWindow Event;
	void OnClosingEnded(const Osp::Locations::Controls::IMapInfoWindow& source);
	void OnInfoWindowClicked(const Osp::Locations::Controls::IMapInfoWindow& source){}
	void OnInfoWindowDoublePressed(const Osp::Locations::Controls::IMapInfoWindow& source){}

	// app Event
	void OnAppControlCompleted (const Osp::Base::String &appControlId, const Osp::Base::String &operationId, const Osp::Base::Collection::IList *pResultList);

	// IGeocodingServiceListener listener
	virtual void OnGeocodingRequestResultReceivedN(RequestId requestId, const Osp::Locations::Services::IGeocodingServiceProvider& provider,
		Osp::Base::Collection::IList* pLandmarks, result r, const Osp::Base::String& errorCode,
		const Osp::Base::String& errorMsg);
	virtual void OnReverseGeocodingRequestResultReceivedN(RequestId requestId, const Osp::Locations::Services::IGeocodingServiceProvider& provider,
		Osp::Base::Collection::IList* pLandmarks, result r, const Osp::Base::String& errorCode,
		const Osp::Base::String& errorMsg);

	// touch event
	virtual void OnTouchPressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo) {};
	virtual void OnTouchLongPressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);
	virtual void OnTouchReleased(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo) {};
	virtual void OnTouchMoved(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo) {};
	virtual void OnTouchDoublePressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo) {};
	virtual void OnTouchFocusIn(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo) {}
	virtual void OnTouchFocusOut(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo) {}

	virtual result OnTerminating(void);

public:
	result CreateForm(Osp::Ui::Controls::Frame* pFrame);

private:
	bool InitializeMapService(void);
	void CreatePopups();
	bool ShowOverlays(bool bShowed = true );
	bool ShowInfoWindow(bool bShowed = true);
	bool ShowInfoWindowWithImage(bool bShowed = true);
	bool ShowMyLocation(bool bShowed = true);
	void ShowAll(bool bShowed = true);
	bool MoveMarker(bool bMoved = true);
	void Redraw(void);
	void RotateMap(bool clockwise);
	void ShowContextMenu(const Osp::Graphics::Point& position);
	void RequestReverseGeocode(const Osp::Graphics::Point& position);
	void CreateAndShowContextMenu(int menuItem ,Osp::Graphics::Point position);
	void CloseContextMenu(void);

private:
	Osp::Locations::Services::IMapServiceProvider*	_pMapSvcProvider;
	Osp::Locations::Controls::Map*					_pMap;

	Overlay *				_pOverlay;
	
	Osp::Locations::Controls::NativeMapInfoWindow *	_pInfoWindow;		
	Osp::Locations::Controls::MapOverlayMarker *		_pMarker;
	Osp::Locations::Controls::MapOverlayMarker *		_pMovedMarker1;
	Osp::Locations::Controls::MapOverlayMarker *		_pMovedMarker2;
	Osp::Locations::Controls::MapOverlayMarker *		_pMovedMarker3;

	Osp::Locations::Controls::MapOverlayCircle *		_pCircle;
	Osp::Locations::Controls::MapOverlayPolygon *		_pPolygon;
	Osp::Locations::Controls::MapOverlayRectangle *	_pRectangle;
	Osp::Locations::Controls::MapOverlayPolyline *	_pPolyline;

	Osp::Ui::Controls::Frame*					_pFrame;

	bool					_showAll;
	bool					_showOverlay;
	bool					_showInfo;
	bool					_showInfoWithImage;
	bool					_showMe;
	bool					_movedMarker;
	bool					_popupShow;

	// pop up for setting
	Osp::Ui::Controls::Popup*	_pPopup;
	Osp::Ui::Controls::Label*	_pLabel;
	Osp::Ui::Controls::Button*	_pBtn;
	Osp::Ui::Controls::ContextMenu*					_pContextMenu;
	Osp::Locations::Services::IGeocodingServiceProvider* _pGeocodingSvcProvider;
	Osp::Graphics::Point							_positionOfContextMenu;
};

#endif
