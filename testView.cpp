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
	ON_BN_CLICKED(IDC_Edge, OnEdge)
	ON_BN_CLICKED(IDC_TOP, OnTop)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_BOTTOM, OnBottom)
	ON_BN_CLICKED(IDC_SOBEL, OnSobel)
	ON_BN_CLICKED(IDC_CORELATION, OnCorelation)
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
	temp2=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth); //temp2 for holding the integral sum
	int s=3;
	int i=0,j=0;
	for(i=0;i<bm.bmHeight;i++)
	{
		for(j=0;j<bm.bmWidth;j++)
		{
			if(i==0 && j==0)
			{
				temp2[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j];
				fprintf(fp3,"%d ",temp2[i*bm.bmWidth+j]);
				continue;
			}
			else if(i==0)
			{
				temp2[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j]+temp2[i*bm.bmWidth+(j-1)];
			}
			else if(j==0)
			{
				temp2[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j]+temp2[(i-1)*bm.bmWidth+j];
			}
			else
			{
				temp2[i*bm.bmWidth+j]=imagearray[i*bm.bmWidth+j]+temp2[i*bm.bmWidth+(j-1)]+temp2[(i-1)*bm.bmWidth+j]-temp2[(i-1)*bm.bmWidth+(j-1)];
			}
			fprintf(fp3,"%d ",temp2[i*bm.bmWidth+j]);
		}
		fprintf(fp3,"\n");
	}
	temp3=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth); //temp3 for the output of the adpative threshold
	for(i=1;i<bm.bmHeight-1;i++)
	{
		for(j=1;j<bm.bmWidth-1;j++)
		{
			int sum=0;
			sum=0;
			int x1=i-(1);
			int x2=i+(1);
			int y1=j-1;
			int y2=j+1;
			
			if((x1-1)<0 || y2>=bm.bmWidth)
				sum+=0;
			else
			sum-=temp2[(x1-1)*bm.bmWidth+y2];

			if(x2> bm.bmHeight || (y1-1)<0)
				sum+=0;
			else 
			sum-=temp2[(x2)*bm.bmWidth+(y1-1)];

			if((x1-1)<0 || (y1-1)<0)
				sum+=0;
			else
			sum+=temp2[(x1-1)*bm.bmWidth+(y1-1)];
			sum*=85;

			if(temp2[i*bm.bmWidth+j]*9 <=(int)(sum/100))
			{
				temp3[i*bm.bmWidth+j]=0;
			}
			else
				temp3[i*bm.bmWidth+j]=255;
			//fprintf(fp,"%d ",imagearray[i*bm.bmWidth+j]);
		}
		//fprintf(fp,"\n");
	}
	cmp.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp3);
	Invalidate();
}

void CTestView::OnButton1() 
{
	//FILE * fp4=fopen("hello.txt","w+");
	temp4=(PBYTE)LocalAlloc(LPTR,bm.bmHeight*bm.bmWidth);
	CFileDialog FileDlg(TRUE, "*", "*.*");
	int height,width=0;
	height=bm.bmHeight;
	width=bm.bmWidth;

	CFileDialog FileDlg1(TRUE, "*", "*.*");

	if( FileDlg1.DoModal ()==IDOK ) //for template image
	{
		//An HINSTANCE to the current instance of the application. If called from within a DLL linked with the USRDLL version of MFC, an HINSTANCE to the DLL is returned.
		/* AfxGetInstanceHandle always returns the HINSTANCE of your executable file (.EXE) unless it is called from within a DLL linked with the USRDLL version of MFC. In this case, it returns an HINSTANCE to the DLL.
 */
		HBITMAP hbmp=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),FileDlg1.GetPathName(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		if(!hbmp)
			MessageBox("incorrect image uplooaded");
		else
		{
			if(cmp1.DeleteObject())
				cmp1.Detach();
			cmp1.Attach(hbmp);
			cmp1.GetBitmap(&bm);
			cmp1.GetBitmapBits(bm.bmHeight*bm.bmWidth,temp4);
		}
		/*fprintf(fp4,"%d\t",bm.bmHeight);
		fprintf(fp4,"%d",bm.bmWidth);
		fprintf(fp4,"\n");*/
		/*CClientDC dc(this);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		dcMem.SelectObject(&cmp1);
		dc.StretchBlt(0,0, (bm.bmWidth), (bm.bmHeight), &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);*/
	}
	int i=0,j=0;
	for( i=0;i<bm.bmHeight;i++)	
		{
		  for(j=0;j<bm.bmWidth;j++)
			{
			    int a=temp4[i*bm.bmWidth+j];
				if(a>200)
					temp4[i*bm.bmWidth+j]=0;
				else
					temp4[i*bm.bmWidth+j]=255;
			}
		}
	 cmp1.SetBitmapBits(bm.bmHeight*bm.bmWidth,temp4);
	
	int sad=INT_MAX;
	int xcor=0,ycor=0;
	for(i=0;i<height-bm.bmHeight;i++)
	{
		for(j=0;j<width-bm.bmWidth;j++)
		{
			int c=0;
			for(int k=0;k<bm.bmHeight;k++)
			{
				for(int l=0;l<bm.bmWidth;l++)
				{
					c+=abs(imagearray[(i+k)*width+(l+j)]-temp4[k*bm.bmWidth+l]);// for storing the sad values
					//fprintf(fp4,"%d",c);
				}
				//fprintf(fp4,"\n");
			}
			if(c<sad)
			{
				sad=c;
				xcor=i;
				ycor=j;
			}
		}
	}
	
	//fprintf(fp4,"%d\t",xcor);
	//fprintf(fp4,"%d",ycor);
	CClientDC dc(this);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(&cmp1);
	dc.BitBlt(xcor, ycor, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
	char buffer [50];
	sprintf (buffer, "sad value is %d", sad);
	dc.TextOut(bm.bmWidth+100,bm.bmHeight+100,buffer);
	//Ellipse(dc, xcor, ycor, xcor+10, ycor+10);
}

void CTestView::OnEdge() 
{
	for(int i=0;i<bm.bmHeight;i++)
	{
		for(int j=0;j<bm.bmWidth;j++)
		{
			
		}
	}
		
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

void CTestView::OnCorelation() 
{
	for(int i=0;i<bm.bmHeight;i++)
	{
		for(int j=0;j<bm.bmWidth;j++)
		{
			
		}
	}
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
	// TODO: Add your control notification handler code here
	
}
