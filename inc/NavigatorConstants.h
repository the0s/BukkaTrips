#ifndef _NAVIGATOR_CONSTANTS_H_
#define _NAVIGATOR_CONSTANTS_H_

#include <FBaseString.h>

// If you want to develop your own application with the location services.
//  Some service providers may need license key for displaying a map. refer to the developer guide for details.
// Client name "guest" is invalid license.
static const Osp::Base::String ROUTE_SVC_EXTRA_INFO    (L"ClientName=samsung-jc;ClientPassword=4xndosys;HostUrl=http://ws.decarta.com/openls/openls");

static const int MAP_MAX_ZOOM = 16;

#endif /* _NAVIGATOR_CONSTANTS_H_ */
