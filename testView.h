// testView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__E70381F0_C5FC_4B1B_87BB_DCC630284BC0__INCLUDED_)
#define AFX_TESTVIEW_H__E70381F0_C5FC_4B1B_87BB_DCC630284BC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestView : public CFormView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

public:
	//{{AFX_DATA(CTestView)
	enum{ IDD = IDD_TEST_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CTestDoc* GetDocument();

// Operations
public:
	CBitmap cmp,cmp1;
	BITMAP bm;
	PBYTE imagearray;
	PBYTE temp,temp1,temp2,temp3,temp4;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	long medianfilter(PBYTE br,int a,int b);
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnButtonReading();
	afx_msg void OnReadgray();
	afx_msg void OnButton4();
	afx_msg void OnMedianFilter();
	afx_msg void OnCentroid();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnButton1();
	afx_msg void OnEdge();
	afx_msg void OnTop();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnBottom();
	afx_msg void OnSobel();
	afx_msg void OnCorelation();
	afx_msg void OnPrewitt();
	afx_msg void OnRobert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in testView.cpp
inline CTestDoc* CTestView::GetDocument()
   { return (CTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__E70381F0_C5FC_4B1B_87BB_DCC630284BC0__INCLUDED_)
