/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1998--2000  R Development Core Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef R_EXT_GRAPHICS_H_
#define R_EXT_GRAPHICS_H_

/*
 *	Some Notes on Color
 *
 *	R uses a 24-bit color model.  Colors are specified in 32-bit
 *	integers which are partitioned into 4 bytes as follows.
 *
 *		<-- most sig	    least sig -->
 *		+-------------------------------+
 *		|   0	| blue	| green |  red	|
 *		+-------------------------------+
 *
 *	The red, green and blue bytes can be extracted as follows.
 *
 *		red   = ((color	     ) & 255)
 *		green = ((color >>  8) & 255)
 *		blue  = ((color >> 16) & 255)
 */
#define R_RGB(r,g,b)	((r)|((g)<<8)|((b)<<16))
#define R_RED(col)	(((col)	   )&255)
#define R_GREEN(col)	(((col)>> 8)&255)
#define R_BLUE(col)	(((col)>>16)&255)

/*
 *	Some Notes on Line Textures
 *
 *	Line textures are stored as an array of 4-bit integers within
 *	a single 32-bit word.  These integers contain the lengths of
 *	lines to be drawn with the pen alternately down and then up.
 *	The device should try to arrange that these values are measured
 *	in points if possible, although pixels is ok on most displays.
 *
 *	If newlty contains a line texture description it is decoded
 *	as follows:
 *
 *		ndash = 0;
 *		for(i=0 ; i<8 && newlty & 15 ; i++) {
 *			dashlist[ndash++] = newlty & 15;
 *			newlty = newlty>>4;
 *		}
 *		dashlist[0] = length of pen-down segment
 *		dashlist[1] = length of pen-up segment
 *		etc
 *
 *	An integer containing a zero terminates the pattern.  Hence
 *	ndash in this code fragment gives the length of the texture
 *	description.  If a description contains an odd number of
 *	elements it is replicated to create a pattern with an
 *	even number of elements.  (If this is a pain, do something
 *	different its not crucial).
 *
 */

/*--- The basic numbered & names line types; Here device-independent:
  e.g. "dashed" == "44",  "dotdash" == "1343"
*/

#define LTY_BLANK	-1
#define LTY_SOLID	0
#define LTY_DASHED	4 + (4<<4)
#define LTY_DOTTED	1 + (3<<4)
#define LTY_DOTDASH	1 + (3<<4) + (4<<8) + (3<<12)
#define LTY_LONGDASH	7 + (3<<4)
#define LTY_TWODASH	2 + (2<<4) + (6<<8) + (2<<12)

#ifndef R_GRAPHICS_INTERNAL
	/* possible coordinate systems (for specifying locations) */
typedef enum {
 DEVICE	= 0,	/* native device coordinates (rasters) */
 NDC	= 1,	/* normalised device coordinates x=(0,1), y=(0,1) */
 INCHES = 13,	/* inches x=(0,width), y=(0,height) */
 NIC	= 6,	/* normalised inner region coordinates (0,1) */
 OMA1	= 2,	/* outer margin 1 (bottom) x=NIC, y=LINES */
 OMA2	= 3,	/* outer margin 2 (left) */
 OMA3	= 4,	/* outer margin 3 (top) */
 OMA4	= 5,	/* outer margin 4 (right) */
 NFC	= 7,	/* normalised figure region coordinates (0,1) */
 NPC	= 16,	/* normalised plot region coordinates (0,1) */
 USER	= 12,	/* user/data/world corrdinates;
		 * x,=(xmin,xmax), y=(ymin,ymax) */
 MAR1	= 8,	/* figure margin 1 (bottom) x=USER(x), y=LINES */
 MAR2	= 9,	/* figure margin 2 (left)   x=USER(y), y=LINES */
 MAR3	= 10,	/* figure margin 3 (top)    x=USER(x), y=LINES */
 MAR4	= 11,	/* figure margin 4 (right)  x=USER(y), y=LINES */

	/* possible, units (for specifying dimensions) */
	/* all of the above, plus ... */

 LINES = 14,	/* multiples of a line in the margin (mex) */
 CHARS = 15	/* multiples of text height (cex) */
} GUnit;
#endif

struct colorDataBaseEntry {
	char *name;	/* X11 Color Name */
	char *rgb;	/* #RRGGBB String */
	unsigned int code;  /* Internal R Color Code */
};

typedef struct colorDataBaseEntry ColorDataBaseEntry;

extern int R_ColorTableSize;
extern unsigned int R_ColorTable[];
extern ColorDataBaseEntry ColorDataBase[];
extern char *DefaultPalette[];

/* Graphics State:
 *
 * The following structure defines state for a graphics device driver.
 * Two copies are kept; the ``default'' set of values, and a set which
 * can be modified during calls to an application program.  When a
 * new graphics frame is started, the values revert to the defaults
 *
 */

#ifndef R_GRAPHICS_INTERNAL
typedef struct {
/* opaque structure */
int dummy;
} GPar;

typedef struct {
/* opaque structure */
int dummy;
} DevDesc;
#endif

#ifndef R_NO_REMAP
#define addDevice		Rf_addDevice
#define char2col		Rf_char2col
#define col2name		Rf_col2name
#define copyDisplayList		Rf_copyDisplayList
#define copyGPar		Rf_copyGPar
#define CreateAtVector		Rf_CreateAtVector
#define curDevice		Rf_curDevice
#define CurrentDevice		Rf_CurrentDevice
#define currentFigureLocation	Rf_currentFigureLocation
#define deviceNumber		Rf_deviceNumber
#define DevNull			Rf_DevNull
#define FixupCex		Rf_FixupCex
#define FixupCol		Rf_FixupCol
#define FixupFont		Rf_FixupFont
#define FixupLty		Rf_FixupLty
#define FixupLwd		Rf_FixupLwd
#define FixupPch		Rf_FixupPch
#define FixupVFont		Rf_FixupVFont
#define GArrow			Rf_GArrow
#define GBox			Rf_GBox
#define GCheckState		Rf_GCheckState
#define GCircle			Rf_GCircle
#define GClip			Rf_GClip
#define GClipPolygon		Rf_GClipPolygon
#define GConvert		Rf_GConvert
#define GConvertX		Rf_GConvertX
#define GConvertXUnits		Rf_GConvertXUnits
#define GConvertY		Rf_GConvertY
#define GConvertYUnits		Rf_GConvertYUnits
#define GEndPath		Rf_GEndPath
#define GetAxisLimits		Rf_GetAxisLimits
#define GetDevice		Rf_GetDevice
#define GExpressionHeight	Rf_GExpressionHeight
#define GExpressionWidth	Rf_GExpressionWidth
#define GForceClip		Rf_GForceClip
#define GLine			Rf_GLine
#define GLocator		Rf_GLocator
#define GLPretty		Rf_GLPretty
#define GMapUnits		Rf_GMapUnits
#define GMapWin2Fig		Rf_GMapWin2Fig
#define GMathText		Rf_GMathText
#define GMetricInfo		Rf_GMetricInfo
#define GMMathText		Rf_GMMathText
#define GMode			Rf_GMode
#define GMtext			Rf_GMtext
#define GNewPlot		Rf_GNewPlot
#define GPolygon		Rf_GPolygon
#define GPolyline		Rf_GPolyline
#define GPretty			Rf_GPretty
#define GRect			Rf_GRect
#define GReset			Rf_GReset
#define GRestore		Rf_GRestore
#define GRestorePars		Rf_GRestorePars
#define GSavePars		Rf_GSavePars
#define GScale			Rf_GScale
#define GSetState		Rf_GSetState
#define GSetupAxis		Rf_GSetupAxis
#define GStartPath		Rf_GStartPath
#define GStrHeight		Rf_GStrHeight
#define GStrWidth		Rf_GStrWidth
#define GSymbol			Rf_GSymbol
#define GText			Rf_GText
#define GVStrHeight		Rf_GVStrHeight
#define GVStrWidth		Rf_GVStrWidth
#define GVText			Rf_GVText
#define inhibitDisplayList	Rf_inhibitDisplayList
#define initDisplayList		Rf_initDisplayList
#define KillDevice		Rf_KillDevice
#define killDevice		Rf_killDevice
#define labelformat		Rf_labelformat
#define LTYget			Rf_LTYget
#define LTYpar			Rf_LTYpar
#define name2col		Rf_name2col
#define number2col		Rf_number2col
#define NewFrameConfirm		Rf_NewFrameConfirm
#define nextDevice		Rf_nextDevice
#define NoDevices		Rf_NoDevices
#define NumDevices		Rf_NumDevices
#define playDisplayList		Rf_playDisplayList
#define prevDevice		Rf_prevDevice
#define ProcessInlinePars	Rf_ProcessInlinePars
#define recordGraphicOperation	Rf_recordGraphicOperation
#define rgb2col			Rf_rgb2col
#define RGB2rgb			Rf_RGB2rgb
#define RGBpar			Rf_RGBpar
#define ScaleColor		Rf_ScaleColor
#define selectDevice		Rf_selectDevice
#define Specify2		Rf_Specify2
#define StartDevice		Rf_StartDevice
#define str2col			Rf_str2col
#define StrMatch		Rf_StrMatch
/* which of these conversions should be public? maybe all?*/
#define xDevtoNDC		Rf_xDevtoNDC
#define xDevtoNFC		Rf_xDevtoNFC
#define xDevtoNPC		Rf_xDevtoNPC
#define xDevtoUsr		Rf_xDevtoUsr
#define xNPCtoUsr		Rf_xNPCtoUsr
#define yDevtoNDC		Rf_yDevtoNDC
#define yDevtoNFC		Rf_yDevtoNFC
#define yDevtoNPC		Rf_yDevtoNPC
#define yDevtoUsr		Rf_yDevtoUsr
#define yNPCtoUsr		Rf_yNPCtoUsr
#endif


		/* User Callable Functions */

/*-------------------------------------------------------------------
 *
 *  DEVICE FUNCTIONS are concerned with the creation and destruction
 *  of devices.
 *
 */

/* Return a pointer to the current device. */
DevDesc* CurrentDevice(void);
/* Return a pointer to a device which is identified by number */
DevDesc* GetDevice(int);
/* Kill device which is identified by number. */
void KillDevice(DevDesc*);
/* Is the null device the current device? */
int NoDevices(void);
/* How many devices exist ? (>= 1) */
int NumDevices(void);
/* Get the index of the specified device. */
int deviceNumber(DevDesc*);
/* Create a new device. */
int StartDevice(SEXP, SEXP, int, SEXP, int);

void DevNull(void);

/* Miscellaneous */
void NewFrameConfirm(void);
void recordGraphicOperation(SEXP, SEXP, DevDesc*);
void initDisplayList(DevDesc *dd);
void copyDisplayList(int);
void playDisplayList(DevDesc*);
void inhibitDisplayList(DevDesc*);

/*-------------------------------------------------------------------
 *
 *  DEVICE UTILITIES are concerned with providing information
 *  for R interpreted functions.
 *
 */

/* Return the number of the current device. */
int curDevice(void);
/* Return the number of the next device. */
int nextDevice(int);
/* Return the number of the previous device. */
int prevDevice(int);
/* Make the specified device (specified by number) the current device */
int selectDevice(int);
/* Kill device which is identified by number. */
void killDevice(int);
/* ...NO DOC... */
void addDevice(DevDesc *);


/*-------------------------------------------------------------------
 *
 *  GPAR FUNCTIONS are concerned with operations on the
 *  entire set of graphics parameters for a device
 *  (e.g., initialisation, saving, and restoring)
 */

/* Reset the current graphical parameters from the default ones: */
void GRestore(DevDesc*);
/* Make a temporary copy of the current parameters */
void GSavePars(DevDesc*);
/* Restore the temporary copy saved by GSavePars */
void GRestorePars(DevDesc*);

		/* More Programmer GPar functions */

void ProcessInlinePars(SEXP, DevDesc*);
void Specify2(char*, SEXP, DevDesc*);
void RecordGraphicsCall(SEXP);

SEXP FixupPch(SEXP, int);
SEXP FixupLty(SEXP, int);
SEXP FixupFont(SEXP, int);
SEXP FixupCol(SEXP, unsigned int);
SEXP FixupCex(SEXP, double);
SEXP FixupLwd(SEXP, double);
SEXP FixupVFont(SEXP);



/*-------------------------------------------------------------------
 *
 *  DEVICE STATE FUNCTIONS are concerned with getting and setting
 *  the current state of the device;  is it ready to be drawn into?
 */

/* has plot.new been called yet? */
void GCheckState(DevDesc*);
/* Set to 1 when plot.new succeeds
 * Set to 0 when don't want drawing to go ahead */
void GSetState(int, DevDesc*);



/*-------------------------------------------------------------------
 *
 *  GRAPHICAL PRIMITIVES are the generic front-end for the functions
 *  that every device driver must provide.
 *
 *  NOTE that locations supplied to these functions may be in any
 *  of the valid coordinate systems (each function takes a "coords"
 *  parameter to indicate the coordinate system);  the device-specific
 *  version of the function is responsible for calling GConvert to get
 *  the location into device coordinates.
 *
 */


/* Draw a circle, centred on (x,y) with radius r (in inches). */
void GCircle(double, double, int, double, int, int, DevDesc*);
/* Set clipping region (based on current setting of dd->gp.xpd).
 * Only clip if new clipping region is different from the current one */
void GClip(DevDesc*);
/* Polygon clipping: */
int GClipPolygon(double *, double *, int, int, int,
		 double *, double *, DevDesc *);
/* Always clips */
void GForceClip(DevDesc*);
/* Draw a line from (x1,y1) to (x2,y2): */
void GLine(double, double, double, double, int, DevDesc*);
/* Return the location of the next mouse click: */
Rboolean GLocator(double*, double*, int, DevDesc*);
/* Return the height, depth, and width of the specified
 * character in the specified units: */
void GMetricInfo(int, double*, double*, double*, GUnit, DevDesc*);
/* Set device "mode" (drawing or not drawing) here for windows and mac drivers.
 */
void GMode(int, DevDesc*);
/* Draw a polygon using the specified lists of x and y values: */
void GPolygon(int, double*, double*, int, int, int, DevDesc*);
/* Draw series of straight lines using the specified lists of x and y values: */
void GPolyline(int, double*, double*, int, DevDesc*);
/* Draw a rectangle given two opposite corners: */
void GRect(double, double, double, double, int, int, int, DevDesc*);
/* Return the height of the specified string in the specified units: */
double GStrHeight(char*, GUnit, DevDesc*);
/* Return the width of the specified string in the specified units */
double GStrWidth(char*, GUnit, DevDesc*);
/* Draw the specified text at location (x,y) with the specified
 * rotation and justification: */
void GText(double, double, int, char*, double, double, double, DevDesc*);


void GStartPath(DevDesc*);
void GEndPath(DevDesc*);

void GMathText(double, double, int, SEXP, double, double, double, DevDesc*);
void GMMathText(SEXP, int, double, int, double, int, DevDesc*);

void GVText(double x, double y, int unit, char* s, int typeface, int fontindex,
	    double xadj, double yadj, double rot, DevDesc *dd);
double GVStrWidth(const unsigned char *s, int typeface, int fontindex,
		  int unit, DevDesc *dd);
double GVStrHeight(const unsigned char *s, int typeface, int fontindex,
		   int unit, DevDesc *dd);

/*-------------------------------------------------------------------
 *
 *  GRAPHICAL UTILITIES are functions that produce graphical output
 *  using the graphical primitives (i.e., they are generic - NOT
 *  device-specific).
 *
 */

/* Draw a line from (x1,y1) to (x2,y2) with an arrow head
 * at either or both ends. */
void GArrow(double, double, double, double, int, double, double, int, DevDesc*);
/* Draw a box around specified region:
 *  1=plot region, 2=figure region, 3=inner region, 4=device. */
void GBox(int, DevDesc*);
/* Return a "nice" min, max and number of intervals for a given
 * range on a linear or _log_ scale, respectively: */
void GPretty(double*, double*, int*);
void GLPretty(double*, double*, int*);
/* Draw text in margins. */
void GMtext(char*, int, double, int, double, int, DevDesc*);
/* Draw one of the predefined symbols (circle, square, diamond, ...) */
void GSymbol(double, double, int, int, DevDesc*);

double GExpressionHeight(SEXP, GUnit, DevDesc*);
double GExpressionWidth(SEXP, GUnit, DevDesc*);



/*-------------------------------------------------------------------
 *
 *  COLOUR CODE is concerned with the internals of R colour representation
 *
 */

/* Convert an R colour specification (which might be a number or */
/* a string) into an internal colour specification. */
unsigned int RGBpar(SEXP, int);


/*-------------------------------------------------------------------
 *
 *  LINE TEXTURE CODE is concerned with the internals of R
 *  line texture representation.
 */
unsigned int LTYpar(SEXP, int);
SEXP LTYget(unsigned int);


/*----------------------------------------------------------------------
 *
 *  TRANSFORMATIONS are concerned with converting locations between
 *  coordinate systems and dimensions between different units.
 */

/* Convert an R unit (e.g., "user") into an internal unit (e.g., USER)> */
GUnit GMapUnits(int);
/* Convert a LOCATION from one coordinate system to another: */
void GConvert(double*, double*, GUnit, GUnit, DevDesc*);
double GConvertX(double, GUnit, GUnit, DevDesc*);
double GConvertY(double, GUnit, GUnit, DevDesc*);
/* Convert an x/y-dimension from one set of units to another: */
double GConvertXUnits(double, GUnit, GUnit, DevDesc*);
double GConvertYUnits(double, GUnit, GUnit, DevDesc*);

/* Set up the different regions on a device (i.e., inner region,
 * figure region, plot region) and transformations for associated
 * coordinate systems (called whenever anything that affects the
 * coordinate transformations changes):
 */
void GReset(DevDesc*);

/* Set up the user coordinate transformations: */
void GMapWin2Fig(DevDesc*);
/* Set up the device for a new plot by Resetting graphics parameters
 * and Resetting the regions and coordinate Systems */
DevDesc *GNewPlot(int, int);
/* Set up the user coordinates based on the axis limits */
void GScale(double, double, int, DevDesc*);
/* Set up the axis limits based on the user coordinates */
void GSetupAxis(int, DevDesc*);
/* Return row and column of current figure in the layout matrix */
void currentFigureLocation(int*, int*, DevDesc*);

double R_Log10(double);

/* which of these conversions should be public? maybe all? [NO_REMAP] */
double xDevtoNDC(double, DevDesc*);
double yDevtoNDC(double, DevDesc*);
double xDevtoNFC(double, DevDesc*);
double yDevtoNFC(double, DevDesc*);
double xDevtoNPC(double, DevDesc*);
double yDevtoNPC(double, DevDesc*);
double xDevtoUsr(double, DevDesc*);
double yDevtoUsr(double, DevDesc*);
double xNPCtoUsr(double, DevDesc*);
double yNPCtoUsr(double, DevDesc*);


		/* Miscellaneous (from graphics.c & colors.c) */

unsigned int rgb2col(char *);
unsigned int name2col(char *);
unsigned int number2col(char *);
unsigned int char2col(char *);/* rgb2col() or name2col() */
unsigned int str2col(char *);

char* col2name(unsigned int);

unsigned int ScaleColor(double x);

char* RGB2rgb(unsigned int, unsigned int, unsigned int);

int StrMatch(char *s, char *t);
void copyGPar(GPar *, GPar *);

/* some functions that plot.c needs to share with plot3d.c */
SEXP CreateAtVector(double*, double*, int, Rboolean);
void GetAxisLimits(double, double, double*, double*);
SEXP labelformat(SEXP);

/* Vector fonts */

double GVStrWidth (const unsigned char *, int, int, int, DevDesc *);
double GVStrHeight (const unsigned char *, int, int, int, DevDesc *);
void GVText (double, double, int, char *, int, int,
	     double, double, double, DevDesc *);

#endif /* R_EXT_GRAPHICS_H_ */
