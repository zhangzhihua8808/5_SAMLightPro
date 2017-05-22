//---------------------------------------------------------------------------

#ifndef UnitOfficeFunH
#define UnitOfficeFunH

#include <IniFiles.hpp>
#include <ComCtrls.hpp>

const String DataInfo = "DataInfo";
const String DataValue = "DataValue";
const String PViewClassType = "PVIEW.pviewCtrl.1";
const String MediaClassType = "WMPlayer.OCX.7";

const int PortNumRow = 1;
const int PortNumCol = 2;

//---------------------------------------------------------------------------
String TrimAll(String astr) ;
String ReplaceSymbByDL( String aPName );
const String C_BMLab ="BMPM__" ;

class MOleObj
{
 // [Left As Single], [Top As Single], [Width As Single = -1], [Height As Single = -1], [ClassName As String], [FileName As String], [DisplayAsIcon As MsoTriState], [IconFileName As String], [IconIndex As Long], [IconLabel As String], [Link As MsoTriState])
  public :
    float mLeft;
    float mTop;
    float mWidth;
    float mHeight;
    int mRelDelta;//��Left��top�����ƫ��
    //����
    String mClassName;
    String mName;

    // ����������ֵ���ַ�����
    //eg�� Caption=\"aa\",FontSize=10.5  //ע�⵱����ֵΪ�ַ�����ʽʱ����ȷ���ַ�����˫��������
    String mPropertyStrs;
    int   mLink;
    MOleObj(float aL,float aT,float aW,float aH,String aC,String aName ,int aRelDelta ,String aPropertys = "",int aLink = 0);
    String PosSizeStr(String aSplit = ",");

};
class MOleTitleObj:  public MOleObj
{
   public :
    String mCaption;
    String mFontSize;
    String mPic;
    MOleTitleObj(float aL,float aT,float aW,float aH,String aC,String aN,int aRelDelta,int aLink,String aCaption,String aFontSize = ""):
      MOleObj( aL, aT, aW, aH,aC, aN,aRelDelta,"",aLink )
    {
      mCaption = aCaption;
      mFontSize = aFontSize;
      //mPic = aPic;
    }
};
class MOleFrmBt : public MOleTitleObj
{
  public :

   MOleFrmBt(float aL,float aT,float aW,float aH,int aLink,String aCaption,String aName,int aRelDelta=0,String aFontSize = "")
         :MOleTitleObj(aL,aT,aW,aH,"Forms.CommandButton.1",aName,aRelDelta,aLink,aCaption,aFontSize )
   {
   }
};
class MOleFrmLabel : public MOleTitleObj
{
  public :
   MOleFrmLabel( float aL,float aT,float aW,float aH,int aLink,String aCaption,String aName,int aRelDelta=0,String aFontSize =""):MOleTitleObj(aL,aT,aW,aH,"Forms.Label.1",aName,aRelDelta,aLink,aCaption,aFontSize )
   {
   }
};
class MOleFrmScrollBar:  public MOleObj
{
  public:
    int mValue;
    int mMax;
    MOleFrmScrollBar( float aL,float aT,float aW,float aH,int aLink,String aName ,int aRelDelta=0,int aV=-1,int aMax=-1):MOleObj(aL,aT,aW,aH,"Forms.ScrollBar.1",aName,aRelDelta,"",aLink )
    {
       mValue = aV;
       mMax = aMax;
    }
};
//--------���-------Add Text-20130820-------
class MOleFrmTextBox:  public MOleObj
{
  public:
    String StrNum;                                                         //  , String StrTxtNum = "-1"
    MOleFrmTextBox( float aL,float aT,float aW,float aH,int aLink, String aName,int aRelDelta,String aStrNum ):MOleObj(aL,aT,aW,aH,"Forms.TextBox.1",aName,aRelDelta,aLink)
    {
        StrNum = aStrNum;
    }
};
class MOfficeFun
{
   private:
	  TStrings * fVBS;
   public:       
          bool IsVisible;
          bool IsDebug;
                    
   public:
     __property TStrings * VBS = {read=fVBS,write=fVBS};
     void InitVBS(bool IsOnlyRun = true);
     void EndVBS( bool IsOnlyRun  = true);
     void AddVBS( String aVbs );
     bool ConfirmOpenFile( String aFullFileName );
     MOfficeFun();
     ~MOfficeFun();
};

class MBookMark
{
  private:
	String fPortName;//ӳ��Ķ˿�����
	int fStartPos;  //ӳ����ʼλ��
	int fEndPos;   //ӳ����ֹλ��
        String   fName;
  public:
        __property String Name={read=fName,write=fName};
	__property String  PortName={read=fPortName,write=fPortName};
	__property int  StartPos={read=fStartPos,write=fStartPos};
	__property int  EndPos={read=fEndPos,write=fEndPos};
	MBookMark();
};

TTreeNode * GetTN( TTreeNodes * I_Tree,String aName );
void MapBMToTV( TStrings * aBMInfo,TTreeView * aTV );
TTreeNode *  GetNodeChild( TTreeNode *aPNode ,String aChildName );
Variant GetObjProperty( Variant aObj ,String PropStr);


//extern MWordFun * G_WORD;
//extern MExcelFun * G_EXCEL;
#endif
