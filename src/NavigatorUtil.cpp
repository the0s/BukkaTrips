#include "NavigatorUtil.h"

using namespace Osp::Locations;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Collection;

Coordinates*
NavigatorUtil::StringToCoordinatesN (const Osp::Base::String& value, bool isCommaSeparated)
{
	result r1 = E_SUCCESS;
	result r2 = E_SUCCESS;

	Coordinates* pCurrCoord = null;

	String lat(L"");
	String lon(L"");
	String pos(L"");
	double latValue = 0;
	double lonValue = 0;
	int    indexOf  = 0;

	if(isCommaSeparated)
		r1 = value.IndexOf(L',', 0, indexOf);
	else
		r1 = value.IndexOf(L' ', 0, indexOf);
	if(IsFailed(r1))
		goto CATCH;

	r1 = value.SubString(0, indexOf, lat);
	r2 = value.SubString(indexOf + 1, lon);
	if(IsFailed(r1) || IsFailed(r2))
		goto CATCH;

	lat.Trim();
	lon.Trim();

	r1 = Double::Parse(lat, latValue);
	r2 = Double::Parse(lon, lonValue);
	if(IsFailed(r1) || IsFailed(r2))
		goto CATCH;

	pCurrCoord = new Coordinates();
	if(pCurrCoord)
		pCurrCoord->Set(latValue, lonValue, 0);

	AppLog("Converting from string to coordinates succeeded.");
	return pCurrCoord;

CATCH:
	AppLog("Converting from string to coordinates failed.");
	delete pCurrCoord;
	return null;
}


String*
NavigatorUtil::CoordinatesToStringN (const Osp::Locations::Coordinates& value)
{
	return new String( Double::ToString(value.GetLatitude()) + L", " + Double::ToString(value.GetLongitude()) );
}

void
NavigatorUtil::GetCoordinatesFromRectangleArea(const Osp::Locations::RectangleGeographicArea& area, Osp::Locations::Coordinates& lowerLeft, Osp::Locations::Coordinates& upperRight)
{
	const IList* pCoordList = area.GetCoordinates();
	const Coordinates* pCoordLowerLeft  = static_cast<const Coordinates*>(pCoordList->GetAt(0));
	const Coordinates* pCoordUpperRight = static_cast<const Coordinates*>(pCoordList->GetAt(1));

	lowerLeft  = *pCoordLowerLeft;
	upperRight = *pCoordUpperRight;
}

void
NavigatorUtil::GetUnionRectangleArea(const Osp::Locations::RectangleGeographicArea& areaOne, const Osp::Locations::RectangleGeographicArea& areaTwo, Osp::Locations::RectangleGeographicArea& area)
{
	Coordinates lowerLeftOne, upperRightOne, lowerLeftTwo, upperRightTwo;

	GetCoordinatesFromRectangleArea(areaOne, lowerLeftOne, upperRightOne);
	GetCoordinatesFromRectangleArea(areaTwo, lowerLeftTwo, upperRightTwo);

	double minLat = Math::Min(lowerLeftOne .GetLatitude() , lowerLeftTwo .GetLatitude());
	double maxLat = Math::Max(upperRightOne.GetLatitude() , upperRightTwo.GetLatitude());
	double minLon = Math::Min(lowerLeftOne .GetLongitude(), lowerLeftTwo .GetLongitude());
	double maxLon = Math::Max(upperRightOne.GetLongitude(), upperRightTwo.GetLongitude());

	area.Set(minLat, maxLat, minLon, maxLon);
}
