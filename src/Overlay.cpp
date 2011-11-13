#include "Overlay.h"
#include <FBaseColArrayList.h>
#include <FBaseColMapEntry.h>
#include <FBaseInteger.h>
#include <FBaseUtilStringTokenizer.h>
#include <FIoFile.h>
#include <FMediaImage.h>
#include <FGrpBitmapCommon.h>

	
using namespace Osp::Media;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;
using namespace Osp::Locations;
using namespace Osp::Locations::Controls;
using namespace Osp::Locations::Services;
using namespace Osp::Io;

Overlay::~Overlay(void)
{
}

MapOverlayPolygon *
Overlay::MakePolygon()
{
	Coordinates Coord1, Coord2, Coord3, Coord4, Coord5;

	Coord1.Set(51.503373,-0.129197 ,0);
	Coord2.Set(51.503146,-0.126171 ,0);
	Coord3.Set(51.502145,-0.126343 ,0);
	Coord4.Set(51.502278,-0.129046 ,0);
	Coord5.Set(51.501356,-0.129111 ,0);

	ArrayList coordsList;
	coordsList.Construct();

	PolygonGeographicArea * pPolyBnd =  new PolygonGeographicArea();
	
	coordsList.Add(Coord1);
	coordsList.Add(Coord2);
	coordsList.Add(Coord3);
	coordsList.Add(Coord4);
	coordsList.Add(Coord5);

	pPolyBnd->Set(coordsList);
	
	MapOverlayPolygon * pPolygon = new MapOverlayPolygon(*pPolyBnd);
	if(pPolygon == null)
	{
		AppLog( "MapOverlayPolygon::Construct() is failed.");
		goto CATCH;
	}

	pPolygon->SetStrokeWidth(OVERLAY_STROKE_WEIGHT);
	pPolygon->SetStrokeColor(Color::COLOR_BLACK);
	pPolygon->SetFillColor(Color::COLOR_YELLOW);
	pPolygon->SetId(GetOverlayId());
	pPolygon->SetPriority(1);

	delete pPolyBnd;
	pPolyBnd = null;

	return pPolygon;
CATCH:
	delete pPolyBnd;
	return null;
}



MapOverlayPolyline *
Overlay::MakePolyline()
{
	result r = E_SUCCESS;

	Coordinates Coord1, Coord2, Coord3, Coord4;
	Coord1.Set(51.500275,-0.130548,0);
	Coord2.Set(51.500355,-0.129669,0);
	Coord3.Set(51.499687,-0.129454,0);
	Coord4.Set(51.499687,-0.130548,0);
	
	ArrayList coordsList;

	coordsList.Construct();
	MapOverlayPolyline * pPolyline = new MapOverlayPolyline();

	coordsList.Add(Coord1);
	coordsList.Add(Coord2);
	coordsList.Add(Coord3);
	coordsList.Add(Coord4);

	r = pPolyline->Construct(coordsList, true);
	if (r != E_SUCCESS)
	{
		AppLog( "MapOverlayPolyline::Construct() failed.");
		goto CATCH;
	}

	pPolyline->SetStrokeWidth(OVERLAY_STROKE_WEIGHT);
	pPolyline->SetStrokeColor(Color::COLOR_BLACK);
	pPolyline->SetId(GetOverlayId());
	pPolyline->SetPriority(1);

	return pPolyline;
CATCH:
	delete pPolyline;
	return null;
}



MapOverlayRectangle *
Overlay::MakeRectangle()
{
	result r = E_SUCCESS;
	
	Coordinates lbCoord, ruCoord;
	lbCoord.Set(51.500942,-0.125442,0);
	ruCoord.Set(51.502011,-0.123918,0);

	MapOverlayRectangle *pRect = new MapOverlayRectangle();
	
	r = pRect->Construct(lbCoord.GetLatitude(), ruCoord.GetLatitude(), lbCoord.GetLongitude(), ruCoord.GetLongitude());
	if(r != E_SUCCESS)
	{
		AppLog( "MapOverlayRectangle::Construct() has failed.");
		goto CATCH;
	}

	pRect->SetStrokeWidth(OVERLAY_STROKE_WEIGHT);
	pRect->SetStrokeColor(Color::COLOR_BLACK);
	pRect->SetFillColor(Color::COLOR_BLUE);
	pRect->SetId(GetOverlayId());
	pRect->SetPriority(1);

	return pRect;
CATCH:
	delete pRect;
	return null;
}


NativeMapInfoWindow *
Overlay::MakeInfoWindow(int style)
{
	result r = E_SUCCESS;

	Bitmap* pBitmap = null;
	Coordinates ctCoord;
	Point mapPt, offPt;
	int width, height;
	String title = L"Bug's restaurant";
	String content = L"This is a 5 star restaurant.\nI went there with my honey for my 1st wedding anniversary.";

	NativeMapInfoWindow *pInfoWindow = new NativeMapInfoWindow();

	if(style == 0)
	{
		width = 300;
		height = 225;

		offPt.x = 0;
		offPt.y = 0;

		ctCoord.Set(51.498987,-0.126858,0);
		r = pInfoWindow->Construct((MapInfoWindowStyle)(MAP_INFOWINDOW_STYLE_RIGHT_DOWN), width, height, ctCoord, offPt);
		if(IsFailed(r))
		{
			AppLog( "NativeMapInfoWindow::Construct() has failed.");
			goto CATCH;
		}

		pInfoWindow->SetTitle(title);
		pInfoWindow->SetContent(content, 20, Color::COLOR_VIOLET);
		pInfoWindow->SetCloseButtonEnabled(true);
	}
	else
	{
		width = 300;
		height = 300;

		offPt.x = 0;
		offPt.y = 0;

		ctCoord.Set(51.498987,-0.126858,0);
		r = pInfoWindow->Construct((MapInfoWindowStyle)(MAP_INFOWINDOW_STYLE_RIGHT_DOWN), width, height, ctCoord, offPt);
		if(IsFailed(r))
		{
			AppLog( "NativeMapInfoWindow::Construct() has failed.");
			goto CATCH;
		}

		pInfoWindow->SetTitle(title);
		pInfoWindow->SetContent(L"/Res/pin.png");
		pInfoWindow->SetCloseButtonEnabled(true);
	}

	if (pBitmap)
	{
		delete pBitmap;
		pBitmap = null;
	}
	
	return pInfoWindow;
CATCH:
	delete pInfoWindow;
	
	if (pBitmap)
	{
		delete pBitmap;
		pBitmap = null;
	}
	
	return null;
}


MapOverlayCircle *
Overlay::MakeCircle()
{

	float radius = 70;
	Coordinates centerCoords;
	centerCoords.Set(51.500595,-0.126858,0);
	
	CircleGeographicArea cgr;
	MapOverlayCircle * pCircle = null;

	cgr.Set(centerCoords, radius);

	pCircle = new MapOverlayCircle(cgr);
	if(pCircle != null)
	{
		pCircle->SetStrokeWidth(OVERLAY_STROKE_WEIGHT);
		pCircle->SetStrokeColor(Color::COLOR_BLACK);
		pCircle->SetFillColor(Color::COLOR_RED);
		pCircle->SetId(GetOverlayId());
		pCircle->SetPriority(1);
	
		return pCircle;
	}
	else
	{
		return null;
	}
}

MapOverlayMarker *
Overlay::MakeMarker()
{
	Coordinates ctCoord;
	ctCoord.Set(51.498987,-0.126858,0);
	
	MapOverlayMarker* pMarker = new MapOverlayMarker(ctCoord);

	if(pMarker != null)
	{
		pMarker->SetImage(null, Point(1,1));
		pMarker->SetId(GetOverlayId());
		pMarker->SetPriority(1);
		pMarker->SetDragDropEnabled(true);
	
		return pMarker;
	}
	else
	{
		return null;
	}
}

Bitmap*
Overlay::GetBitmapN(const String& name)
{
	Bitmap* pBitmap = null;
	Image* pImage = new Image();

	String fullname(L"/Res/");
	fullname.Append(name);

	pImage->Construct();				
	
	if(fullname.EndsWith(L"jpg"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);			
	}
	else if(fullname.EndsWith(L"bmp"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	else if(fullname.EndsWith(L"png"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_ARGB8888);
	}
	else if (fullname.EndsWith(L"gif"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	delete pImage;
	
	return pBitmap;
}
