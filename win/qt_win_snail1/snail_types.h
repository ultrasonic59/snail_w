#pragma once
/*
#define RECT_TYPE		0
#define FRECT_TYPE	    1
#define LINE_TYPE		2
#define CIRCLE_TYPE		3
*/
enum en_item_type {
	RECT_TYPE = 0,
	FRECT_TYPE = 1,
	VLINE_TYPE = 2,
	HLINE_TYPE = 3,
	CIRCLE_TYPE = 4,
	POINT_TYPE = 5

};
enum en_rej {
	// keep this in sync with QMessageBox::ButtonRole and QPlatformDialogHelper::ButtonRole
	REJ_SELECT = 0,
	REJ_PLACE = 1
};
#if 1
enum ActionTypes {
	_DefaultType,
	VLineType,
	HLineType,
	RectangleType,
	CircleType,
	SelectionType
};
#endif
