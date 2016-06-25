; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInfoPannel
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Viewer.h"
LastPage=0

ClassCount=12
Class1=CViewerApp
Class2=CViewerDoc
Class3=CViewerView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=COpenGLWnd
Class7=CPerspective
Class8=COrthographic
Class9=CFront
Class10=CTop
Class11=CSide
Resource2=IDD_ABOUTBOX
Class12=CInfoPannel
Resource3=IDD_INFOPANNEL

[CLS:CViewerApp]
Type=0
HeaderFile=Viewer.h
ImplementationFile=Viewer.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_FILE_OPEN

[CLS:CViewerDoc]
Type=0
HeaderFile=ViewerDoc.h
ImplementationFile=ViewerDoc.cpp
Filter=N

[CLS:CViewerView]
Type=0
HeaderFile=ViewerView.h
ImplementationFile=ViewerView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Viewer.cpp
ImplementationFile=Viewer.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_APP_ABOUT
CommandCount=3

[CLS:COpenGLWnd]
Type=0
HeaderFile=OpenGLWnd.h
ImplementationFile=OpenGLWnd.cpp
BaseClass=CView
Filter=C
LastObject=COpenGLWnd
VirtualFilter=VWC

[CLS:CPerspective]
Type=0
HeaderFile=Perspective.h
ImplementationFile=Perspective.cpp
BaseClass=COpenGLWnd
Filter=C
LastObject=CPerspective
VirtualFilter=WC

[CLS:COrthographic]
Type=0
HeaderFile=Orthographic.h
ImplementationFile=Orthographic.cpp
BaseClass=COpenGLWnd
Filter=C
LastObject=COrthographic
VirtualFilter=VWC

[CLS:CFront]
Type=0
HeaderFile=Front.h
ImplementationFile=Front.cpp
BaseClass=CView
Filter=C
LastObject=CFront

[CLS:CTop]
Type=0
HeaderFile=Top.h
ImplementationFile=Top.cpp
BaseClass=CView
Filter=C
LastObject=CTop

[CLS:CSide]
Type=0
HeaderFile=Side.h
ImplementationFile=Side.cpp
BaseClass=CView
Filter=C
LastObject=CSide

[DLG:IDD_INFOPANNEL]
Type=1
Class=CInfoPannel
ControlCount=5
Control1=IDC_STATIC,button,1342177287
Control2=IDC_UPPERLEFT,combobox,1344339971
Control3=IDC_UPPERRIGHT,combobox,1344339971
Control4=IDC_LOWERLEFT,combobox,1344339971
Control5=IDC_LOWERRIGHT,combobox,1344339971

[CLS:CInfoPannel]
Type=0
HeaderFile=InfoPannel.h
ImplementationFile=InfoPannel.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_UPPERLEFT
VirtualFilter=VWC

