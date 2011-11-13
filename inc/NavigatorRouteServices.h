#ifndef _NAVIGATOR_ROUTE_SERVICES_H_
#define _NAVIGATOR_ROUTE_SERVICES_H_

#include <FBase.h>
#include <FLocations.h>

class INavigatorRouteServicesDelegate
{
public:
	virtual ~INavigatorRouteServicesDelegate();
	virtual void RouteCleared(void) = 0;
	virtual void RouteReceived(void) = 0;
};

class NavigatorRouteServices :
	public Osp::Locations::Services::IRouteServiceListener
{

// Life Cycle
public:
	NavigatorRouteServices(void);
	~NavigatorRouteServices(void);
	bool Construct(void);

// Route Request
public:
	bool GetRoute(const Osp::Base::Collection::IList& waypoints, const Osp::Base::String& countrycode);

// Route Response - IRouteServiceListener
private:
	void OnRouteReceivedN (RequestId requestId, const Osp::Locations::Services::IRouteServiceProvider& provider, Osp::Base::Collection::IList* pRoute,
							result r, const Osp::Base::String& errorCode, const Osp::Base::String& errorMsg);

// Helper Methods
public:
	void SetDelegate(const INavigatorRouteServicesDelegate& delegate);
	void ClearRoute(void);
	const Osp::Locations::Services::Route* GetRouteData(void) const;
	const Osp::Base::Collection::IList* GetRouteSegments(void) const;
	int GetRouteSegmentsCount(void) const;
	const Osp::Locations::Services::RouteSegment* GetRouteSegmentAt(int index) const;
	const Osp::Locations::RectangleGeographicArea* GetRouteSegmentAreaAt(int index) const;

// Instance Variables
private:
	Osp::Locations::Services::IRouteServiceProvider* __pRouteServiceProvider;
	Osp::Locations::Services::RouteServicePreferences* __pRoutePreferences;
	Osp::Locations::Services::Route* __pRoute;
	INavigatorRouteServicesDelegate* __pDelegate;

}; /* NavigatorMapForm */

#endif /* _NAVIGATOR_ROUTE_SERVICES_H_ */
