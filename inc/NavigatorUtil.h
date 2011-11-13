#ifndef _NAVIGATOR_UTIL_H_
#define _NAVIGATOR_UTIL_H_

#include <FBase.h>
#include <FLocations.h>

class NavigatorUtil
{
public:
	static Osp::Locations::Coordinates* StringToCoordinatesN (const Osp::Base::String& value, bool isCommaSeparated = true);
	static Osp::Base::String* CoordinatesToStringN (const Osp::Locations::Coordinates& value);
	static void GetCoordinatesFromRectangleArea (const Osp::Locations::RectangleGeographicArea& area, Osp::Locations::Coordinates& lowerLeft, Osp::Locations::Coordinates& upperRight);
	static void GetUnionRectangleArea (const Osp::Locations::RectangleGeographicArea& areaOne, const Osp::Locations::RectangleGeographicArea& areaTwo, Osp::Locations::RectangleGeographicArea& area);
};

#endif //_NAVIGATOR_UTIL_H_
