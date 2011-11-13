#include "NavigatorConstants.h"
#include "NavigatorRouteServices.h"
#include "NavigatorUtil.h"
#include <FUiControls.h>

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Locations;
using namespace Osp::Locations::Services;
using namespace Osp::Ui::Controls;


static const int MAX_NUM_POINTS = 1000;

/*
 * Life Cycle
 */
INavigatorRouteServicesDelegate::~INavigatorRouteServicesDelegate(){}
NavigatorRouteServices::NavigatorRouteServices(void) :
	__pRouteServiceProvider (null),
	__pRoutePreferences (null),
	__pRoute (null),
	__pDelegate (null)
{
}

NavigatorRouteServices::~NavigatorRouteServices(void)
{
	__pDelegate = null;
	delete __pRouteServiceProvider;
	delete __pRoutePreferences;
	delete __pRoute;
}

bool
NavigatorRouteServices::Construct()
{
	String property = L"";
	RouteServicePreferences* pPreferences = null;
	IRouteServiceProvider* pRouteProvider = null;

	// connecting to a route service provider
	pRouteProvider = static_cast<IRouteServiceProvider*>(ProviderManager::ConnectToServiceProviderN(L"", LOC_SVC_PROVIDER_TYPE_ROUTE, ROUTE_SVC_EXTRA_INFO));
	if(pRouteProvider == null) {
		AppLog("Connecting to Default route service provider failed.");
		goto CATCH;
	}

	// getting RouteServicePreferences
	pPreferences = static_cast<RouteServicePreferences*>(pRouteProvider->GetServicePreferencesN(true));
	if(pPreferences == null) {
		AppLog("Getting RouteServicePreferences failed.");
		goto CATCH;
	}

	// setting up general preferences
	pPreferences->SetRouteType					(null);
	pPreferences->SetTransportMode				(null);
	pPreferences->SetInstructionsUsed			(true);
	pPreferences->SetGeometryUsed				(true);
	pPreferences->SetInstructionGeometryUsed	(false);
	pPreferences->SetInstructionBoundingBoxUsed	(true);

	// route initialization is done. Clean up.
	__pRoutePreferences = pPreferences;
	__pRouteServiceProvider = pRouteProvider;

	return true;

CATCH:
	delete pPreferences;
	delete pRouteProvider;

	return false;
}


/*
 * Route Request
 */
bool
NavigatorRouteServices::GetRoute(const Osp::Base::Collection::IList& waypoints, const Osp::Base::String& countrycode)
{
	result r = E_SUCCESS;
	RequestId reqId;

	if(__pRoutePreferences == null || __pRouteServiceProvider == null) {
		goto CATCH;
	}

	// clean up previous route data
	ClearRoute();

	// request the route
	r = __pRouteServiceProvider->GetRoute(waypoints, __pRoutePreferences, *this, reqId);
	if(IsFailed(r)) {
		AppLog("[%s] GetRoute failed.", GetErrorMessage(r));
		goto CATCH;
	}

	return true;

CATCH:
	return false;
}


/*
 * IRouteServiceListener
 */
void
NavigatorRouteServices::OnRouteReceivedN(RequestId requestId, const IRouteServiceProvider& provider,
								Osp::Base::Collection::IList* pRoute, result r,
								const Osp::Base::String& errorCode,	const Osp::Base::String& errorMsg)
{
	String popupMsg = L"Unknown Error";
	const IList* pGeometry = null;
	const RectangleGeographicArea* pBoundingBox = null;

	Route* pCurrRoute = null;
	IList* pRouteList = pRoute;

	// when either r is failed or response is null
	if(IsFailed(r) || pRouteList == null)
	{
		switch(r)
		{
		case E_SERVER:
			popupMsg = L"ErrorCode:" + errorCode + " ErrorMsg:" + errorMsg;
			break;
		case E_LOCATION_SERVICE:
			popupMsg = L"Network Error";
			break;
		case E_OPERATION_CANCELED:
			popupMsg = L"Operation Canceled";
			break;
		case E_OUT_OF_MEMORY:
			popupMsg = L"Insufficient Memory";
			break;
		case E_SUCCESS:
			popupMsg = L"Empty route list";
			break;
		}
		goto CATCH;
	}

	// get the first route from the list; remove the list
	pCurrRoute = static_cast<Route *>(pRouteList->GetAt(0));
	pRouteList->RemoveAt(0, false);
	pRouteList->RemoveAll(true);
	delete pRouteList;
	pRouteList = null;

	// geometry checking
	pGeometry = pCurrRoute->GetGeometry();
	if(pGeometry == null) {
		popupMsg = L"Empty route geometry";
		goto CATCH;
	}
	else if(pGeometry->GetCount() > MAX_NUM_POINTS) {
		popupMsg = L"Route is too large.";
		goto CATCH;
	}
	// bounding box checking
	pBoundingBox = pCurrRoute->GetGeographicArea();
	if(pBoundingBox == null) {
		popupMsg = L"Empty route geographic area.";
		goto CATCH;
	}

	// update data and draw the result
	delete __pRoute;
	__pRoute = pCurrRoute;
	__pDelegate->RouteReceived();

	return;

CATCH:
	if(pRouteList != null)
	{
		pRouteList->RemoveAll(true);
		delete pRouteList;
	}
	delete pCurrRoute;

	int modal = 0;
	MessageBox messageBox;
	messageBox.Construct(L"Error", popupMsg, MSGBOX_STYLE_NONE, 3000);
	messageBox.ShowAndWait(modal);

	AppLog("[%s] OnRouteReceived failed.", GetErrorMessage(r));
}


/*
 * Helper Methods
 */
void
NavigatorRouteServices::SetDelegate(const INavigatorRouteServicesDelegate& delegate)
{
	__pDelegate = const_cast<INavigatorRouteServicesDelegate*>(&delegate);
}

void
NavigatorRouteServices::ClearRoute()
{
	delete __pRoute;
	__pRoute = null;

	__pDelegate->RouteCleared();
}

const Osp::Locations::Services::Route*
NavigatorRouteServices::GetRouteData(void) const
{
	return __pRoute;
}

const Osp::Base::Collection::IList*
NavigatorRouteServices::GetRouteSegments(void) const
{
	return __pRoute != null ? __pRoute->GetSegments() : null;
}

int
NavigatorRouteServices::GetRouteSegmentsCount(void) const
{
	const IList* pSegments = GetRouteSegments();
	return pSegments != null ? pSegments->GetCount() : 0;
}

const Osp::Locations::Services::RouteSegment*
NavigatorRouteServices::GetRouteSegmentAt(int index) const
{
	const IList* pSegments = index >= 0 ? GetRouteSegments() : null;
	if(pSegments != null && pSegments->GetCount() > index)
		return static_cast<const RouteSegment *>(pSegments->GetAt(index));
	return null;
}

const Osp::Locations::RectangleGeographicArea*
NavigatorRouteServices::GetRouteSegmentAreaAt(int index) const
{
	const RouteSegment* pSegment = GetRouteSegmentAt(index);
	return pSegment != null ? pSegment->GetGeographicArea() : null;
}

