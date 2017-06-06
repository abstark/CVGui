; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "test.h"
LastPage=0

ClassCount=5
Class1=CTestApp
Class2=CTestDoc
Class3=CTestView
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource7=IDD_TEST_FORM

[CLS:CTestApp]
Type=0
HeaderFile=test.h
ImplementationFile=test.cpp
Filter=N

[CLS:CTestDoc]
Type=0
HeaderFile=testDoc.h
ImplementationFile=testDoc.cpp
Filter=N

[CLS:CTestView]
Type=0
HeaderFile=testView.h
ImplementationFile=testView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_CORELATION


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=test.cpp
ImplementationFile=test.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_TEST_FORM]
Type=1
Class=CTestView
ControlCount=19
Control1=IDC_BUTTON_READING,button,1342242816
Control2=IDC_READGRAY,button,1342242816
Control3=IDC_MedianFilter,button,1342242816
Control4=IDC_CENTROID,button,1342242816
Control5=IDC_RADIO1,button,1342177289
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_SEA,button,1342242816
Control8=IDC_Edge,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_TOP,button,1342242816
Control12=IDC_BOTTOM,button,1342242816
Control13=IDC_LEFT,button,1342242816
Control14=IDC_RIGHT,button,1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_PREWITT,button,1342242816
Control17=IDC_ROBERT,button,1342242816
Control18=IDC_SOBEL,button,1342242816
Control19=IDC_CORELATION,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

