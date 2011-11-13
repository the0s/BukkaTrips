#ifndef _OVERLAY_H_
#define _OVERLAY_H_

#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FLocations.h>
#include <FBaseColArrayList.h>

#define OVERLAY_STROKE_WEIGHT 20

class Overlay
{
public:
	
protected :
	static const int MAX_OVERLAY_ROWCNT = 6;
	static const int MAX_OVERLAY_COLCNT = 6;
	static const int RECT_WIDTH = 200;
	static const int RECT_HEIGHT = 200;
public:
	Overlay(Osp::Locations::Controls::Map *pMap){_pMap = pMap; _iOverlayId=1;};
	~Overlay(void);

	Osp::Locations::Controls::MapOverlayPolygon * MakePolygon();
	Osp::Locations::Controls::MapOverlayPolyline * MakePolyline();
	Osp::Locations::Controls::MapOverlayRectangle * MakeRectangle();
	Osp::Locations::Controls::MapOverlayCircle * MakeCircle();
	Osp::Locations::Controls::MapOverlayMarker * MakeMarker();
	Osp::Locations::Controls::NativeMapInfoWindow * MakeInfoWindow(int style=0);
	Osp::Graphics::Bitmap* GetBitmapN(const Osp::Base::String& name);

protected:
	int GetOverlayId(){return _iOverlayId++;}
		
protected:
	Osp::Locations::Controls::Map* _pMap;
	int _iOverlayId;
};



#endif //_OVERLAY_H_
