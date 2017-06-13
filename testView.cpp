// testView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"
#include "testView.h"
#include <vector>
#include<algorithm>
#include "Wingdi.h"
#include <afxwin.h>
#include<string.h>
#include<math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CFormView)

BEGIN_MESSAGE_MAP(CTestView, CFormView)
	//{{AFX_MSG_MAP(CTestView)
	ON_BN_CLICKED(IDC_BUTTON_READING, OnButtonReading)
	ON_BN_CLICKED(IDC_READGRAY, OnReadgray)
	ON_BN_CLICKED(IDC_MedianFilter, OnMedianFilter)
	ON_BN_CLICKED(IDC_CENTROID, OnCentroid)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_SEA, OnButton1)
	ON_BN_CLICKED(IDC_TOP, OnTop)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_BOTTOM, OnBottom)
	ON_BN_CLICKED(IDC_SOBEL, OnSobel)
	ON_BN_CLICKED(IDC_PREWITT, OnPrewitt)
	ON_BN_CLICKED(IDC_ROBERT, OnRobert)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
	: CFormView(CTestView::IDD)
{
	//{{AFX_DATA_INIT(CTestView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CTestView::~CTestView()
{
}

void CTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnButtonReading()   //for reading the image from the file.
{
	CFileDialog FileDlg(TRUE, "*", "*.*");

	if( FileDlg.DoModal ()==IDOK )
	{
		//An HINSTANCE to the current instance of the application. If called from within a DLL linked with the USRDLL version of MFC, an HINSTANCE to the DLL is returned.
		/* AfxGetInstanceHandle always returns the HINSTANCE of your executable file (.EXE) unless it is called from within a DLL linked with the USRDLL version of MFC. In this case, it returns an HINSTANCE to the DLL.
 */
		HBITMAP hbmp=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),FileDlg.GetPathName(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		if(!hbmp)
			MessageBox("incorrect image uplooaded");
		else
		{
			if(cmp.DeleteObject())
				cmp.Detach();
			cmp.Attach(hbmp);
			cmp.GetBitmap(&bm);
			imagearray=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
			cmp.GetBitmapBits(bm.bmHeight*bm.bmWidth,imagearray);
			CClientDC dc(this);
			CDC dcMem;
			dcMem.CreateCompatibleDC(&dc);
			dcMem.SelectObject(&cmp);
		    dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
		//	dc.StretchBlt(0,0, (bm.bmWidth), (bm.bmHeight), &dcMem, 120, 120, bm.bmWidth, bm.bmHeight, SRCCOPY);
			

		}		
	}
	Invalidate();
}
void CTestView::OnMedianFilter() 
{
	temp1=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);

	FILE *fp1=fopen("grayvalue.txt","w+");
	int i=0,j=0;
	
	for(i=1;i<bm.bmHeight-1;i++)	
	{
		for(j=1;j<bm.bmWidth-1;j++)
		{
			int ss=imagearray[i*bm.bmWidth+j];
			fprintf(fp1,"%d\t",ss);
			temp1[i*bm.bmWidth+j]=medianfilter(imagearray,i,j);
		}
		fprintf(fp1,"\n");

	}
	fclose(fp1);


	cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp1);
	/*CClientDC dc(this);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(&cmp);
	//dc.BitBlt(100, 100, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
	dc.StretchBlt(0,0, (bm.bmWidth), (bm.bmHeight), &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);*/
	Invalidate();

}
void CTestView::OnReadgray() 
{

	int a=0;
	FILE *fg=fopen("grayvalue.txt","w+");
	temp=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
	for(int i=0;i<bm.bmHeight;i++)
	{
		for(int j=0;j<bm.bmWidth;j++)
		{
		//	fprintf(fg,"%d ",imagearray[i*bm.bmWidth+j]);
			if(imagearray[i*bm.bmWidth+j]>=90)
			{
				temp[i*bm.bmWidth+j]=255;
			}
			else
				temp[i*bm.bmWidth+j]=0;
		}
	//	fprintf(fg,"\n");
	}
	cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp);
	Invalidate();
}

void CTestView::OnButton4() 
{
	// TODO: Add your control notification handler code here
	
}



long CTestView::medianfilter(PBYTE br, int a, int b)
{
	int ar[9];
	int l,k;
	ar[0] = br [(a-1)*bm.bmWidth+(b-1)];
	ar[1] = br [(a-1)*bm.bmWidth+b];
	ar[2] = br [(a-1)*bm.bmWidth+(b+1)];
	ar[3] = br [a*bm.bmWidth+(b-1)];
	ar[4] = br [a*bm.bmWidth+b];
	ar[5] = br [a*bm.bmWidth+(b+1)];
	ar[6] = br [(a+1)*bm.bmWidth+(b-1)];
	ar[7] = br [(a+1)*bm.bmWidth+b];
	ar[8] = br [(a+1)*bm.bmWidth+(b+1)];

	for(l =0 ; l<8; l++)
		for(k = 0 ; k <=l ; k++)
		{
			if(ar[k]> ar[k+1])
			{
				int temp=ar[k+1];
				ar[k+1]=ar[k];
				ar[k]=temp;
			}
		}
			
			return ar[4];
}

void CTestView::OnDraw(CDC* pDC) 
{
	//cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,imagearray);
	CClientDC dc(this);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(&cmp);
	dc.StretchBlt(0,0, (bm.bmWidth), (bm.bmHeight), &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	
}

void CTestView::OnCentroid() 
{
	int sumx=0;
	int sumy=0;
	int avx,avy;
	int c=0;

	for(int i=0;i<bm.bmHeight;i++)
	{
		for(int j=0;j<bm.bmWidth;j++)
		{
			if(temp[i*bm.bmWidth+j]==0)
			{
				sumx+=i;
				sumy+=j;
				c+=1;

			}
			if(c>11)
				break;
		}
		if(c>11)
			break;
			
	}
	avx=int(sumx/c);
	avy=int(sumy/c);
	CClientDC dc(this);
	
	Ellipse(dc, avx, avy, avx+5, avy+5);  //ellipse for locating the centroid

}

void CTestView::OnRadio1() 
{
	temp1=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
		for(int i=1;i<bm.bmHeight-1;i++)	
		{
			for(int j=1;j<bm.bmWidth-1;j++)
			{
				int a=imagearray[i*bm.bmWidth+j];
				if(a>150)
					temp1[i*bm.bmWidth+j]=0;
				else
					temp1[i*bm.bmWidth+j]=255;
			}
		}
	  cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp1);
	  
	  Invalidate();
}

void CTestView::OnRadio2() //for adaptive thresholding using integral images
{

	FILE * fp3=fopen("checking.txt","w+");
	FILE * fp9=fopen("grayvalue.txt","w+");
	PBYTE temp2;
	const int constant=bm.bmWidth;
	unsigned long *intImg=(unsigned long *)malloc(sizeof(unsigned long)*bm.bmHeight*bm.bmWidth);\

	temp2=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
	
	
	int i=0,j=0;
	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			fprintf(fp9,"%d\t",imagearray[i*bm.bmWidth+j]);
		}
		fprintf(fp9,"\n");
	}

	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			temp2[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j];
		}
	}
	int sum=0;
	for(i=0;i<bm.bmHeight;i++)
	{
		sum=0;
		for(j=0;j<bm.bmWidth;j++)
		{
			sum+=temp2[i*bm.bmWidth+j];
			if(i==0)
			{
				intImg[i*bm.bmWidth+j]=sum;
			}
			else
			{
			intImg[i*bm.bmWidth+j]=intImg[(i-1)*bm.bmWidth+j]+sum;
			}
			
			fprintf(fp3,"%d\t",intImg[i*bm.bmWidth+j]);
		}
		fprintf(fp3,"\n");
	}
	temp3=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth); //temp3 for the output of the adpative threshold
	FILE * fp10=fopen("checking_new.txt","w+");
	int s=(int)bm.bmWidth/2;
	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			int sum=0;
			int x1=i-s/2;
			int x2=i+s/2;
			int y1=j-s/2;
			int y2=j+s/2;
			sum=intImg[x2*bm.bmWidth+y2]-intImg[x2*bm.bmWidth+y1]-intImg[(x1)*bm.bmWidth+y2]+intImg[(x1)*bm.bmWidth+(y1)];

			fprintf(fp10,"%d\t",sum);
			int t=85;
			int count=(x2-x1)*(y2-y1);
			if(imagearray[i*bm.bmWidth+j]*count <(int)((sum*t)/100))
			{
				temp3[i*bm.bmWidth+j]=0;
			}
			else
				temp3[i*bm.bmWidth+j]=255;
		}
		fprintf(fp10,"\n");
	}
	cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp3);
	fclose(fp10);
	free(intImg);
	Invalidate();
}

void CTestView::OnButton1()   ///SAD - Correlation -----------
{
	int height,width=0;	

	FILE * fp10=fopen("grayvalue_actual.txt","w+");

	CFileDialog FileDlg1(TRUE, "*", "*.*");
	if( FileDlg1.DoModal ()==IDOK ) //for template image
	{	
		HBITMAP hbmp1=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),FileDlg1.GetPathName(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		if(!hbmp1)
			MessageBox("incorrect image uplooaded");
		else
		{
			if(cmp.DeleteObject())
				cmp.Detach();
			cmp1.Attach(hbmp1);
			cmp1.GetBitmap(&bm1);
			temp4=(PBYTE)LocalAlloc(LPTR,bm1.bmHeight*bm1.bmWidth);//allocating memory
			cmp1.GetBitmapBits(bm1.bmHeight*bm1.bmWidth,temp4);
		}
		cmp1.SetBitmapBits(bm1.bmHeight*bm1.bmWidth,temp4);
	}
	
	height=bm1.bmHeight;
	width=bm1.bmWidth;


	int SAD,isor=0 ,iref=0;
	SAD = 0;
	int sad_max=INT_MAX;
		
	int xcor=0,ycor=0;
	for(int i=0;i<= bm.bmHeight-height;i++)
	{
		for(int j=0;j<= bm.bmWidth-width;j++)
		{
			SAD=0;

			for(int k=0;k<bm1.bmHeight;k++)
			{
				for(int l=0;l<bm1.bmWidth;l++)
				{
					int a=imagearray[(i+k)*bm.bmWidth+(l+j)];
					int b=temp4[k*bm1.bmWidth+l];
					SAD+=abs(a-b);
				}
			}
			if(SAD<sad_max)
			{
				sad_max=SAD;
				xcor=j;
				ycor=i;
			}
		}
	}


	CClientDC dc1(this);
	CDC dcMem1;
	dcMem1.CreateCompatibleDC(&dc1);
	dcMem1.SelectObject(&cmp1);
	dc1.BitBlt(xcor, ycor, bm1.bmWidth, bm1.bmHeight, &dcMem1, 0, 0, SRCCOPY);
	Ellipse(dc1, xcor, ycor, xcor+10, ycor+10);
	char buffer [50];
	sprintf (buffer, "sad value is %d", sad_max);
	dc1.TextOut(bm1.bmWidth+100,bm1.bmHeight+100,buffer);	
}

void CTestView::OnEdge() 
{
	MessageBox("nothing here");	
}

void CTestView::OnTop() 
{
	int sumx=0;
	int sumy=0;
	int avx,avy;
	int c=0;

	for(int i=0;i<bm.bmHeight;i++)
	{
		for(int j=0;j<bm.bmWidth;j++)
		{
			if(temp[i*bm.bmWidth+j]==0)
			{
				sumx+=i;
				sumy+=j;
				c+=1;

			}
			if(c>11)
				break;
		}
		if(c>11)
			break;
			
	}
	avx=int(sumx/c);
	avy=int(sumy/c);
	CClientDC dc(this);
	
	Ellipse(dc, avx, avy, avx+5, avy+5);  //ellipse for locating the centroid

}	


void CTestView::OnLeft() 
{
	int sumx=0;
	int sumy=0;
	int avx,avy;
	int c=0;

	for(int i=0;i<bm.bmHeight;i++)
	{
		for(int j=0;j<bm.bmWidth;j++)
		{
			if(temp[j*bm.bmWidth+i]==0)
			{
				sumx+=i;
				sumy+=j;
				c+=1;

			}
			if(c>11)
				break;
		}
		if(c>11)
			break;
			
	}
	avx=int(sumx/c);
	avy=int(sumy/c);
	CClientDC dc(this);
	
	Ellipse(dc, avx, avy, avx+5, avy+5);  //ellipse for locating the centroid	
}


void CTestView::OnRight() 
{
	int sumx=0;
	int sumy=0;
	int avx,avy;
	int c=0;

	for(int i=bm.bmHeight-1;i>=0;i--)
	{
		for(int j=bm.bmWidth-1;j>=0;j--)
		{
			if(temp[j*bm.bmWidth+i]==0)
			{
				sumx+=i;
				sumy+=j;
				c+=1;

			}
			if(c>11)
				break;
		}
		if(c>11)
			break;
			
	}
	avx=int(sumx/c);
	avy=int(sumy/c);
	CClientDC dc(this);
	
	Ellipse(dc, avx, avy, avx+5, avy+5);  //ellipse for locating the centroid	
}

void CTestView::OnBottom() 
{
	int sumx=0;
	int sumy=0;
	int avx,avy;
	int c=0;

	for(int i=bm.bmHeight-1;i>=0;i--)
	{
		for(int j=bm.bmHeight-1;j>=0;j--)
		{
			if(temp[i*bm.bmWidth+j]==0)
			{
				sumx+=i;
				sumy+=j;
				c+=1;

			}
			if(c>11)
				break;
		}
		if(c>11)
			break;
			
	}
	avx=int(sumx/c);
	avy=int(sumy/c);
	CClientDC dc(this);
	
	Ellipse(dc, avx, avy, avx+5, avy+5);  //ellipse for locating the centroid

	
}

void CTestView::OnSobel() 
{
	temp4=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
	int i=0,j=0;
	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			temp4[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j];
		}
	}
	int gx[3][3] = {  
   {-1,0 ,1 } ,   
   {-2,0 ,2 } ,   
   {-1,0 ,1 }   
	};  //for horizontal

	int gy[3][3] = {  
   {-1,-2 ,-1 } ,   
   {0 , 0 , 0 } ,   
   {1 ,2 ,1 }   
	};//for vertical
	int pix=0,piy=0;
	for( i=1;i<=bm.bmHeight-2;i++)
	{
		for( j=1;j<=bm.bmWidth-2;j++)
		{
			pix=gx[0][0] * imagearray[(i-1)*bm.bmWidth+j-1] + gx[0][1] * imagearray[i*bm.bmWidth+j-1] + gx[0][2] * imagearray[(i+1)*bm.bmWidth+j-1] +
              gx[1][0] * imagearray[(i-1)*bm.bmWidth+j]   + gx[1][1] * imagearray[(i)*bm.bmWidth+j]    + gx[1][2] * imagearray[(i+1)*bm.bmWidth+j]  +
              gx[2][0] * imagearray[(i-1)*bm.bmWidth+j+1] + gx[2][1] * imagearray[i*bm.bmWidth+j+1] + gx[2][2] * imagearray[(i+1)*bm.bmWidth+j+1] ;
			
			piy=gy[0][0] * imagearray[(i-1)*bm.bmWidth+j-1] + gy[0][1] * imagearray[i*bm.bmWidth+j-1] + gy[0][2] * imagearray[(i+1)*bm.bmWidth+j-1] +
              gy[1][0] * imagearray[(i-1)*bm.bmWidth+j]   + gy[1][1] * imagearray[(i)*bm.bmWidth+j]    + gy[1][2] * imagearray[(i+1)*bm.bmWidth+j]  +
              gy[2][0] * imagearray[(i-1)*bm.bmWidth+j+1] + gy[2][1] * imagearray[i*bm.bmWidth+j+1] + gy[2][2] * imagearray[(i+1)*bm.bmWidth+j+1] ;

			int val=(int)sqrt(pix*pix+piy*piy);
			temp4[i*bm.bmWidth+j]=val;
		}
	}
		cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp4);
		Invalidate();
	

}



void CTestView::OnPrewitt() 
{
	temp4=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
	int i=0,j=0;
	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			temp4[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j];
		}
	}
	int gx[3][3] = {  
   {-1,-1 ,-1 } ,   
   { 0, 0 ,0  } ,   
   { 1, 1, 1}   
	};//for horizontal
	int gy[3][3] = {  
   {-1,0 ,1 } ,   
   {-1,0 ,1 } ,   
   {-1,0 ,1 }   
	};  //for vertical

	int pix=0,piy=0;
	for( i=1;i<=bm.bmHeight-2;i++)
	{
		for( j=1;j<=bm.bmWidth-2;j++)
		{
			pix=gx[0][0] * imagearray[(i-1)*bm.bmWidth+j-1] + gx[0][1] * imagearray[i*bm.bmWidth+j-1] + gx[0][2] * imagearray[(i+1)*bm.bmWidth+j-1] +
              gx[1][0] * imagearray[(i-1)*bm.bmWidth+j]   + gx[1][1] * imagearray[(i)*bm.bmWidth+j]    + gx[1][2] * imagearray[(i+1)*bm.bmWidth+j]  +
              gx[2][0] * imagearray[(i-1)*bm.bmWidth+j+1] + gx[2][1] * imagearray[i*bm.bmWidth+j+1] + gx[2][2] * imagearray[(i+1)*bm.bmWidth+j+1] ;
			
			piy=gy[0][0] * imagearray[(i-1)*bm.bmWidth+j-1] + gy[0][1] * imagearray[i*bm.bmWidth+j-1] + gy[0][2] * imagearray[(i+1)*bm.bmWidth+j-1] +
              gy[1][0] * imagearray[(i-1)*bm.bmWidth+j]   + gy[1][1] * imagearray[(i)*bm.bmWidth+j]    + gy[1][2] * imagearray[(i+1)*bm.bmWidth+j]  +
              gy[2][0] * imagearray[(i-1)*bm.bmWidth+j+1] + gy[2][1] * imagearray[i*bm.bmWidth+j+1] + gy[2][2] * imagearray[(i+1)*bm.bmWidth+j+1] ;

			int val=(int)sqrt(pix*pix+piy*piy);
			temp4[i*bm.bmWidth+j]=val;
		}
	}
		cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp4);
		Invalidate();
	
}

void CTestView::OnRobert() 
{
	temp4=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
	int i=0,j=0;
	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			temp4[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j];
		}
	}
	int gx[2][2] = {  
   {1,0} ,   
   { 0, -1}   
	};//for horizontal
	int gy[2][2] = {  
   {0,1} ,   
   {-1,0}};  //for vertical
	int pix=0,piy=0;
	for(i=0;i<=bm.bmHeight-2;i++)
	{
		for(j=0;j<=bm.bmWidth-2;j++)
		{
			pix=abs(imagearray[i*bm.bmWidth+j]-imagearray[(i+1)*bm.bmWidth+(j+1)])+abs(imagearray[i*bm.bmWidth+j+1]-imagearray[(i+1)*bm.bmWidth+j]);
			temp4[i*bm.bmWidth+j]=pix;
			
		}
	}
	cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp4);
	Invalidate();
}

