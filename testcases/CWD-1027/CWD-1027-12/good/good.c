#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef unsigned char GLboolean;
typedef int GLint;
typedef unsigned int GLuint;
typedef uint64_t fg_time_t;
typedef void* SFG_PlatformDisplay;
typedef void* SFG_WindowHandleType;
typedef void* SFG_WindowContextType;
typedef void* SFG_WindowColormapType;
typedef void* SFG_PlatformContext;
typedef void* SFG_PlatformWindowState;

#define FGAPI
#define FGAPIENTRY
#define FREEGLUT_PRINT_ERRORS 1
#define FREEGLUT_MAX_MENUS 3
#define TOTAL_CALLBACKS 24

typedef void* FGCBUserData;
typedef void (*FGErrorUC)(const char *fmt, va_list ap, FGCBUserData userData);
typedef void (*FGCBIdleUC)(FGCBUserData);
typedef void (*FGCBMenuUC)(int, FGCBUserData);
typedef void (*FGCBDestroyUC)(FGCBUserData);
typedef void (*FGCBMenuStatusUC)(int, int, int, FGCBUserData);

typedef enum {
    GLUT_EXEC_STATE_INIT,
    GLUT_EXEC_STATE_RUNNING,
    GLUT_EXEC_STATE_STOP
} fgExecutionState;

typedef struct tagSFG_XYUse SFG_XYUse;
struct tagSFG_XYUse {
    GLint X, Y;
    GLboolean Use;
};

typedef struct tagSFG_List SFG_List;
struct tagSFG_List {
    void *First;
    void *Last;
};

typedef struct tagSFG_Node SFG_Node;
struct tagSFG_Node {
    void *Next;
    void *Prev;
};

typedef struct tagSFG_State SFG_State;
struct tagSFG_State {
    SFG_XYUse Position;
    SFG_XYUse Size;
    unsigned int DisplayMode;
    GLboolean Initialised;
    int DirectContext;
    GLboolean ForceIconic;
    GLboolean UseCurrentContext;
    GLboolean GLDebugSwitch;
    GLboolean XSyncSwitch;
    int KeyRepeat;
    int Modifiers;
    GLuint FPSInterval;
    GLuint SwapCount;
    GLuint SwapTime;
    fg_time_t Time;
    SFG_List Timers;
    SFG_List FreeTimers;
    FGCBIdleUC IdleCallback;
    FGCBUserData IdleCallbackData;
    int ActiveMenus;
    void (*MenuStateCallback)(int);
    FGCBMenuStatusUC MenuStatusCallback;
    FGCBUserData MenuStatusCallbackData;
    void* MenuFont;
    SFG_XYUse GameModeSize;
    int GameModeDepth;
    int GameModeRefresh;
    int ActionOnWindowClose;
    fgExecutionState ExecState;
    char *ProgramName;
    GLboolean JoysticksInitialised;
    int NumActiveJoysticks;
    GLboolean InputDevsInitialised;
    int MouseWheelTicks;
    int AuxiliaryBufferNumber;
    int SampleNumber;
    GLboolean SkipStaleMotion;
    GLboolean StrokeFontDrawJoinDots;
    GLboolean AllowNegativeWindowPosition;
    int MajorVersion;
    int MinorVersion;
    int ContextFlags;
    int ContextProfile;
    int HasOpenGL20;
    FGErrorUC ErrorFunc;
    FGCBUserData ErrorFuncData;
    void (*WarningFunc)(const char*, va_list);
    FGCBUserData WarningFuncData;
};

typedef struct tagSFG_Window SFG_Window;
typedef struct tagSFG_Menu SFG_Menu;
typedef struct tagSFG_MenuContext SFG_MenuContext;
typedef void (*SFG_Proc)();

typedef struct tagSFG_MenuEntry SFG_MenuEntry;
struct tagSFG_MenuEntry {
    SFG_Node Node;
    int ID;
    int Ordinal;
    char* Text;
    SFG_Menu* SubMenu;
    GLboolean IsActive;
    int Width;
};

struct tagSFG_Menu {
    SFG_Node Node;
    void *UserData;
    int ID;
    SFG_List Entries;
    FGCBMenuUC Callback;
    FGCBUserData CallbackData;
    FGCBDestroyUC Destroy;
    FGCBUserData DestroyData;
    GLboolean IsActive;
    void* Font;
    int Width;
    int Height;
    int X, Y;
    SFG_MenuEntry *ActiveEntry;
    SFG_Window *Window;
    SFG_Window *ParentWindow;
};

typedef enum {
    DesireHiddenState,
    DesireIconicState,
    DesireNormalState
} fgDesiredVisibility;

typedef struct tagSFG_WindowState SFG_WindowState;
struct tagSFG_WindowState {
    int Xpos;
    int Ypos;
    int Width;
    int Height;
    GLboolean Visible;
    int Cursor;
    GLboolean IsFullscreen;
    unsigned int WorkMask;
    int DesiredXpos;
    int DesiredYpos;
    int DesiredWidth;
    int DesiredHeight;
    int DesiredZOrder;
    fgDesiredVisibility DesiredVisibility;
    SFG_PlatformWindowState pWState;
    long JoystickPollRate;
    fg_time_t JoystickLastPoll;
    int MouseX, MouseY;
    GLboolean IgnoreKeyRepeat;
    GLboolean VisualizeNormals;
};

typedef struct tagSFG_Context SFG_Context;
struct tagSFG_Context {
    SFG_WindowHandleType Handle;
    SFG_WindowContextType Context;
    SFG_WindowColormapType cmap;
    int cmap_size;
    SFG_PlatformContext pContext;
    int DoubleBuffered;
    GLint attribute_v_coord;
    GLint attribute_v_normal;
    GLint attribute_v_texture;
};

struct tagSFG_Window {
    SFG_Node Node;
    int ID;
    SFG_Context Window;
    SFG_WindowState State;
    SFG_Proc CallBacks[TOTAL_CALLBACKS];
    FGCBUserData CallbackDatas[TOTAL_CALLBACKS];
    void *UserData;
    SFG_Menu* Menu[FREEGLUT_MAX_MENUS];
    SFG_Menu* ActiveMenu;
    SFG_Window* Parent;
    SFG_List Children;
    GLboolean IsMenu;
};

typedef struct tagSFG_Structure SFG_Structure;
struct tagSFG_Structure {
    SFG_List Windows;
    SFG_List Menus;
    SFG_List WindowsToDestroy;
    SFG_Window* CurrentWindow;
    SFG_Menu* CurrentMenu;
    SFG_MenuContext* MenuContext;
    SFG_Window* GameModeWindow;
    int WindowID;
    int MenuID;
};

struct tagSFG_MenuContext {
    SFG_WindowContextType MContext;
};

#define FREEGLUT_EXIT_IF_NOT_INITIALISED( string )               \
  if ( ! fgState.Initialised )                                    \
  {                                                               \
    fgError ( " ERROR:  Function <%s> called"                     \
              " without first calling 'glutInit'.", (string) ) ;  \
  }

#define freeglut_return_if_fail( expr ) \
    if( !(expr) )                        \
        return;

extern SFG_State fgState;
extern SFG_Structure fgStructure;

void fgError( const char *fmt, ... );
void fgDeinitialize( void );
void fgListAppend(SFG_List *list, SFG_Node *node);
void fghCalculateMenuBoxSize( void );

void fgError( const char *fmt, ... )
{
    va_list ap;

    if (fgState.ErrorFunc) {

        va_start( ap, fmt );

        /* call user set error handler here */
        fgState.ErrorFunc(fmt, ap, fgState.ErrorFuncData);

        va_end( ap );

    } else {
#ifdef FREEGLUT_PRINT_ERRORS
        va_start( ap, fmt );

        fprintf( stderr, "freeglut ");
        if( fgState.ProgramName )
            fprintf( stderr, "(%s): ", fgState.ProgramName );
        vfprintf( stderr, fmt, ap );
        fprintf( stderr, "\n" );

        va_end( ap );
#endif

        if ( fgState.Initialised )
            fgDeinitialize ();

        exit( 1 );
    }
}

void FGAPIENTRY glutAddMenuEntry( const char* label, int value )
{
    SFG_MenuEntry* menuEntry;
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutAddMenuEntry" );
    
    freeglut_return_if_fail( fgStructure.CurrentMenu );
    if (fgState.ActiveMenus)
        fgError("Menu manipulation not allowed while menus in use.");

    menuEntry = (SFG_MenuEntry *)calloc( sizeof(SFG_MenuEntry), 1 );
    menuEntry->Text = strdup( label );
    menuEntry->ID   = value;

    /* Have the new menu entry attached to the current menu */
    fgListAppend( &fgStructure.CurrentMenu->Entries, &menuEntry->Node );

    fghCalculateMenuBoxSize( );
}
