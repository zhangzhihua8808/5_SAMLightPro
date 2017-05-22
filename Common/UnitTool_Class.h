//---------------------------------------------------------------------------

#ifndef UnitTool_ClassH
#define UnitTool_ClassH

//------------------------头文件------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>

#include "UnitTool_Single.h"
//#include "UnitFrameWord.h"

//只做声明
class MError;
class MProgress;
class MTreeNodes_ModeObject;
class MExcelFun;
class MMapElement_ExcelImporter;
class MParaMapElementItems;
class MTreeNodes_DataModule;
class MDataModuleTreeNode;
class MActionList;
class MActionStatuses;
class MActionAttrs;

//------------------extern------------------------------------------------------
extern MError* gError;
extern MProgress* G_Progress;
extern Variant gManual3DEngine;
extern TIniFile* gIniFile;
extern MActionList* gActionList;
extern TMemo * G_PromptLines;

//------------------------MError------------------------------------------------
class MError
{
  private:
    bool fIsLoading;
    bool fBreak;

    bool fIsShow;
    bool fIsMaskShow;
    TMemo*  fMemo;
    TMemo* OldMemo;
    TStatusBar* fStatusBar;
    TStatusPanel*  fStatusPanel;
    bool   fDebug;
    String fHeadTitle;                                                        //Warn1时的标题
    String fWarn1Message;
  protected:
    void  writeMemo(TMemo* aMemo );
    void  writeStatusBar( TStatusBar* aStatusBar );
    void  writeHeadTitle( String aHeadTitle );
  public:
    __property bool IsShow={read=fIsShow,write=fIsShow};
    __property TMemo* Memo={read=fMemo,write=writeMemo};
    __property TStatusBar* StatusBar={read=fStatusBar,write=writeStatusBar};
    __property TStatusPanel* StatusPanel = {read=fStatusPanel,write=fStatusPanel};
    __property bool Debug={read=fDebug,write=fDebug};
    __property String HeadTitle={read=fHeadTitle,write=writeHeadTitle};
    __property bool Break={read=fBreak,write=fBreak};
    __property bool IsMaskShow={read=fIsMaskShow,write=fIsMaskShow};

    __property bool IsLoading={read=fIsLoading,write=fIsLoading};  //20151114

    String WarnMessage;

  public:
    void SetMemo( TMemo* aMemo );
    void RestMemo();


    void SetLoading( TForm* aForm, bool IsLoading, String aHeadTitle );
    void ProcessLoading(TWMKey &Msg);
    void ProcessLoading(WORD &Key, TShiftState Shift);

  public:
    MError();

  public:
    void Error(String aStr);
    void Prompt(String aStr);
    void PromptLine(String aStr);
    void Warn(String aStr);
    void WarnAlways(String aStr);
    void Warn(String aStr,bool IsShowError);
    void WarnAdd(String aStr);

  public:
    void Warn1(String aStr);
    void Warn1_Percent( String aStr, int i, int aCount, int aSp =0 );
    void WarnAdd1(String aStr);
    void WarnAdd1_Percent( String aStr, int i, int aCount, int aSp =0 );
  public:
    String DefaultStr(String aStr);

  public:
    void Duplicate(MError* aSrcError, bool IsCopyKey, bool IsCopyBolbField);     //复制同类对象　//gaoqian
};

//------------------------------------------------------------------------------
class MProgress
{
  public:
    //TStatusBar    *msgBar;
    TControl    *msgBar;
    TProgressBar  *prgBar1;
    TProgressBar  *prgBar2;
    AnsiString  title1, title2, title3, msg1, msg2, msg3;

  public:
    MProgress( TProgressBar *aPrgBar1, TProgressBar *aPrgBar2, TControl* aMsgBar1 );

  public:
    void Prompt( String aPrompt );
  public:
    void BgnShow1( const AnsiString& aTitle, const int& aMin, const int& aMax );
    void BgnShow2( const AnsiString& aTitle, const int& aMin, const int& aMax );
    void BgnShow3( const AnsiString& aTitle, const int& aMin, const int& aMax );
  public:
    void Show1( const AnsiString& aMsg, const int& aPos );
    void Show2( const AnsiString& aMsg, const int& aPos );
    void Show3( const AnsiString& aMsg, const int& aPos );
  public:
    void EndShow1();
    void EndShow2();
    void EndShow3();
};


//---------------- MList_Temp---------------------------------------------------
//功能：集合模板  mod by sxd
//说明：可以完成元素的　Add、Remove、Items[]、Count、Find(String)、Find（T*)操作
//      Find法则可以在继承类中自定义（通过ISEqual()和IsEqualClass()函数）
//例子：class MEntitys : MList_Temp< MEntity >
//------------------------------------------------------------------------------
//zzh: 也就相当于"List",只是对所添加的元素更加灵活而已
template <class T> class MList_Temp : public TList
{
  //----虚函数：this--------------
  protected:
    virtual bool IsEqualByName(String aName,T*,bool IsUppercase)=0;             //必须在继承类中定义
    virtual bool IsEqualByClass(T* t1,T* t2)                                    //缺省为实例相等，可以在继承类中自定义
    {
      return t1 == t2;
    }

  //[------属性------]
  //----DelteObject----    //在Delete List时，是否删除队列中的对象。缺省为删除
  private:
    bool   fDeleteObject;
  protected:
    int readCount() { return TList::Count;  }

    T* ReadItem(int aIndex)
    {
        if ( !IsValidIndex(aIndex) ) return NULL;
        return (T*)TList::Items[aIndex];    }

    void  WriteItem( int aIndex, T* aFeature )
    {
      if ( !IsValidIndex(aIndex) ) return;
      TList::Items[aIndex] = (void*)aFeature;  }

    T*  ReadItemByName(String aName){ return ReadItem(Index(aName));  }
    void  WriteItemByName( String aName, T* aFeature )
                      {  WriteItem(Index(aName),aFeature); }

  public:
    __property bool DeleteObject={read=fDeleteObject,write=fDeleteObject};
    __property int  Count={read=readCount};
    __property  T* Items[int aIndex] =
                       { read = ReadItem, write = WriteItem };
    __property  T* Items_ByName[String aName] =
                       { read = ReadItemByName, write = WriteItemByName };
 public:
 
    //-------Add--------
    void AddVoid( void* Value )                                                 //Product->Object->void->Product时，出现问题
                                                                                //Product->void->Prodct没有问题
    {
      TList::Add( (void*)Value );
    }

    void  Add(T* Value)
    {
      TList::Add( (void*)Value );
    }

    void MoveTo( T* Value, int aNewIndex )
    {
      if( Value==NULL || aNewIndex<0 || aNewIndex>=Count )
        return;

      int aCurIndex = IndexOf( Value );
      if( aCurIndex<0 )
        return;

      if( aCurIndex!=aNewIndex )
        Move( aCurIndex, aNewIndex);
    }

    void MoveToFirst( T* Value )
    {
      MoveTo( Value, 0 );
    }

    void MoveToLast( T* Value )
    {
      MoveTo( Value, Count-1 );
    }

    void AddUnique( T* Value )
    {
      for( int i=0; i<Count; i++ )
        if( Items[i] == Value )
          return;
      Add( Value );
    }

    //-------Remove--------
    void  Remove(T* Value)
    {
      TList::Remove( (void*)Value );
    }

    void  Remove(int aIndex)
    {
       TList::Remove( (void*)Items(aIndex)); //ls
    }

    void Copy( MList_Temp* aSrc )
    {
      for( int i=0; i<aSrc->Count; i++ )
        Add( aSrc->Items[i] );
    }

    int NextIndex(int aIndex)
    {
      int i=aIndex+1;
      if( Count<=0 )
        return -1;

      if( i>=Count )
        i=0;
      return i;
    }

    int PrevIndex(int aIndex)
    {
      int i=aIndex-1;
      if( i<0 )
        i=Count-1;
      return i;
    }

    T* NextItem( T* aNowItem )
    {
      if( Count <= 0 )
        return NULL;

      int i;
      for( i=0; i<Count; i++ )
        if( Items[i]==aNowItem )
          break;

      if( i>=(Count-1) )
        return Items[0];
      else
        return Items[i+1];
    }

    T* PrevItem( T* aNowItem )
    {
      if( Count <= 0 )
        return NULL;

      int i;
      for( i=0; i<Count; i++ )
        if( Items[i]==aNowItem )
          break;

      if( i<=0 )
        return Items[Count-1];
      else
        return Items[i-1];
    }

  //[---函数------]
  public:
    bool  IsValidIndex(int aIndex)
    {
      return ( aIndex>=0 && aIndex<Count );
    }

    int Index(String aName, bool IsUppercase=false)
    {
      for( int i=0; i<Count; i++ )
      {
        if ( IsEqualByName( aName,Items[i],IsUppercase ) )
          return i;
      }
      return -1;
    }

    T* Find(String aName, bool IsUppercase=false)
    {
      int aIndex = Index(aName,IsUppercase);
      if(aIndex<0)
        return NULL;
      return Items[aIndex];
    }

    T* RemoveByName(String aName, bool IsUppercase=false)
    {
      T* aObject = Find(aName,IsUppercase);
      if( aObject!=NULL )
        Remove( aObject );
      return aObject;
    }

    T* Find(T* tFind)
    {
      for( int i=0; i<Count; i++ )
      {
        if ( IsEqualByClass(tFind,Items[i]) )
          return Items[i];
      }
      return NULL;
    }

    T* Find_E(String aName, bool IsUppercase=false)
    {
       T* t = Find( aName, IsUppercase );
       if( t == NULL )
         gError->Error("找不到元素("+aName+")");
       return t;
    }
    T* Find_E(T*aT)
    {
       T* t = Find( aT );
       if( t == NULL )
         gError->Error("找不到元素");
       return aT;
    }

    void DelObject (T* aObject)
    {
       int aIndex = IndexOf(aObject);
       if( IsValidIndex( aIndex ) )
         Delete(aIndex);
    }

  public:
    MList_Temp():TList()
    {
      fSelected=NULL;
      fDeleteObject=true;
    }
  public:
    T* ItemCopy( int aIndex )  //linkang
    {
      T* aSrcObj = Items[aIndex];
      if( aSrcObj==NULL )
        return NULL;

      void* aDestObj = malloc( sizeof(T) );
      memcpy( aDestObj, aSrcObj, sizeof(T) );
      return (T*)aDestObj;
    }

  public:
    virtual void MergeList(MList_Temp * aList, bool IsRmvSame=false )   //by sxd 2008.3.22
    {
      for( int i=0; i<aList->Count; i++ )
      {
        if( IsRmvSame==true &&  Find ( aList->Items[i] )!=NULL  ) 
          continue;

        Add( aList->Items[i] );
      }
    }

    void Duplicate(MList_Temp * aList)   //linkang
    {
      Clear();
      MergeList(aList);
    }

   //----Selected----    //by sxd 2008.3.22
   private:
     T*  fSelected;
   protected:
     void writeSelected(T* aSelected)
     {
       fSelected = aSelected;
     }
     T* readSelected()
     {
       if( Count <= 0 )
         return NULL;
       else
         return fSelected;
     }
   public:
     __property T* Selected={read=readSelected,write=writeSelected};

   public:
     void Select( int aIndex )
     {
       if( aIndex < 0 || !(aIndex<Count) )
         return;
       fSelected = Items[aIndex];
     }
     void SelectLast()
     {
       Select (Count-1);
     }

  public:
    void InsertAfter( T* aInsertObj, T* aIndexObj )
    {
      int aIndex = IndexOf( aIndexObj );
      if( aIndex < 0 )
      {
        Add( aInsertObj );
        return;
      }
      else
        Insert( aIndex+1, aInsertObj );
    }

  public:
    //Clear()并清除ObjectItem
    void Flush()
    {
        for( int i=0; i<Count;  i++ )
        {
          T* aObject =  Items[i];
          SafeDelete( &aObject );
          Items[i]=NULL;
        }
        Clear();
    }

  public:
    __fastcall ~MList_Temp(void)
    {
      if( fDeleteObject )
        Flush();
      else
        Clear();
    }
};


//------------------------------------------------------------------------------
//功能：防止重复关键字元素出现的MList
//说明：在MList基础上，当Add元素时，系统判断该元素的KeyWords是否与集合中元素重复。
//      不是，加入该元素；否则不加入
//      继承类必须自定义　IsEqualByKey( T* t1, T* t2 ) 函数
//------------------------------------------------------------------------------
template <class T> class MListKey_Temp  : public MList_Temp<T>
{
  protected:
    virtual bool IsEqualByKey( T* t1, T* t2 )=0;
    //virtual bool IsEqualByName(String aName,T*);

  public:
    T* FindByKey(T*);

    virtual void Add(T*);
  public:
    MListKey_Temp() : MList_Temp<T>()
    {
    }
   public:
    void Duplicate(MListKey_Temp* alistkey_temp)   //linkang
    {
      if(alistkey_temp==NULL)
        return;

      MList_Temp<T>::Duplicate( (MList_Temp<T>*) alistkey_temp);
    }
};


//------------------------------------------------------------------------------
//名称：MObject  mod by sxd 2008.3.22
//------------------------------------------------------------------------------
class MObject
{
  //[------属性-----]
  private:
    String fEditStatus;
    bool fVisited;
    bool fOldVisited;
    String fType;
    String fName;
  protected:
    virtual String readName();
    virtual String readClassType();
    virtual void  writeName(String aName );
  public:
    __property String EditStatus={read=fEditStatus,write=fEditStatus};          //EditStatus = 状态："New" / "Mod" / "Del"
    __property bool Visited={read=fVisited,write=fVisited};                     //Visited = 遍历标志
    __property bool OldVisited={read=fOldVisited,write=fOldVisited};
    __property String Type={read=fType,write=fType};                            //Type = 同一种Class的分类，区分集合中的不同对象（例如AssemTree）
    __property String Name={read=readName,write=writeName};
    __property String ClassType={read=readClassType};

  //----ObjectControls----   //Object的属性编辑控件，在每个继承对象的构造函数中注册类型, 在SetLinkControls函数中设置具体值
                             //add by sxd 2008.3.22
  public:
    //MObjectControls* ObjectControls();  //add by sxd 2008.3.22

  public:
    MObject();

  //-------虚函数:this---------

  public:
    //void CopyTo(MObject* aNode);
    //virtual void Duplicate(MObject*, bool IsCopyKey, bool IsCopyBolbField );


  //以下虚函数用于在 DB和Form之间传递参数　by sxd 2008.3.22
  public:
    virtual void LoadToSheet(TWinControl* aControls){};                         //LoadToSheet = 将Object的内容装入到aControls界面
    virtual void SaveFromSheet(TWinControl * aControls){};                      //SaveFromSheet = 将aControls的内容存储到Object

  public:
    //virtual void ToListView( TListView* aList, String aTitle );
    virtual String ListViewName( String aTitle )
                      {return "未定义!请继承DisPlayName()";};

    void ObjectToListView( TListView* aList, String aDisplayName, String aSplitter="@@" );
};


//------------------------------------------------------------------------------
//名称：MObjectList
//------------------------------------------------------------------------------
class MObjectList : public MList_Temp<MObject>
{
  //----数据存储------------- 2008.6.11 by sxd

  //----DeledList---- 被删除的元素集合
  //private:
  //  MObjectList*   fDeledList;
  //public:
  //  __property MObjectList* DeledList={read=fDeledList};

  protected:
    //virtual void SaveToDB();    //集合存储的基础模板
    virtual String readClassType() {return "MObjectList";};

  //[-------继承的Virtual函数-----]
  protected:
    virtual bool IsEqualByName(String aName,MObject* aEntity,bool IsUppercase)
    {
      return IsEqualByCase( aName, aEntity->Name, IsUppercase  );
    }

  public:
    __property String ClassType={read=readClassType};

    bool HasMember(MObject* aFeature)
    {
      for( int i=0; i<Count; i++ )
      {
        if ( aFeature==Items[i] )
          return true;
      }
      return false;
    }
    void Add(MObject* aFeature)
    {
       MList_Temp<MObject>::Add( aFeature );
    }
    void Remove(MObject* aFeature)
    {
       MList_Temp<MObject>::Remove( aFeature );
    }

    MObject* NextItem(MObject* aNowItem )
    {
       return MList_Temp<MObject>::NextItem( aNowItem );
    }
    MObject* PrevItem(MObject* aNowItem)
    {
       return MList_Temp<MObject>::PrevItem( aNowItem );
    }

  public:
    MObjectList()
    {
       //fDeledList = new MObjectList();
    }
    __fastcall ~MObjectList();

  public:
    void Merge( MObjectList* aObjectList, bool IsRmvSame );
    void Reverse();
  public:
    MObject* Find(String aName, bool IsUppercase=false);
    MObject* Find(MObject* aEntity);
  public:
    MObject* Find_E(String aName, bool IsUppercase=false);
    MObject* Find_E(MObject* aEntity);
  public:
    void ResetVisited( bool isOn );
    void SaveVisited();
    void RestoreVisited();
    int TheFirstUnVisited();
  public:
    TStrings* Names();
    void GetNames(TStrings* aStrings,bool IsClear);
    String GetNames_Str();
  public:
    void ToListBox( TStrings* aList );

    //virtual void ToListView( TListView* aList );
    void ToListView( TListView* aList,
                     String aListViewTitle, String aListViewSize ) ;
};

//------------------------------------------------------------------------------
template <class T> class MObjectList_Temp : public MObjectList
{
  protected:
    T* ReadItem(int aIndex)
    {
      return (T*)MObjectList::Items[aIndex];
    }
    void WriteItem( int aIndex, T* aFeature )
    {
      MObjectList::Items[aIndex] = (MObject*)aFeature;
    }

    T*  ReadItemByName(String aName)
    {
      return ReadItem(Index(aName));
    }
    void  WriteItemByName( String aName, T* aFeature )
    {
       WriteItem(Index(aName),aFeature);
    }

  public:
    __property  T* Items[int aIndex] = { read = ReadItem, write = WriteItem };
    __property  T* Items_ByName[String aName] = { read = ReadItemByName, write = WriteItemByName };

  public:
     T* FirstItem()
     {
       if( Count < 1 )
         return NULL;
       return Items[0];
     }
     T* LastItem()
     {
       if( Count < 1 )
         return NULL;
       return Items[Count-1];
     }

     T* NextItem( T* aNowItem )
     {
       return (T*)MObjectList::NextItem((MObject*)aNowItem);
     }

     T* PrevItem( T* aNowItem )
     {
       return (T*)MObjectList::PrevItem((MObject*)aNowItem);
     }

  public:
    void MaskAdd(T* aFeature)
    {
      if( Find( aFeature ) != NULL )
        return;
      Add( aFeature );
    }

    void Add(T* aFeature)
    {
        MObjectList::Add( (MObject*)aFeature );
        //((MObject*)aFeature)->Group = this;
    }

    void Remove(T* aFeature)
    {
       MObjectList::Remove( (MObject*)aFeature );
    }

    void Remove(T* aFeature, int aBgnPos)     //去除重复部分
    {
      for( int i=aBgnPos; i<Count; i++ )
      {
        if(  aFeature == Items[i] )
        {
          Delete( i );
          i=i-1;
        }
      }
    }

  public:
    void RemoveSameItem()     //去除重复部分
    {
      for( int i=0; i<Count; i++ )
         Remove( Items[i], i+1 );
    }
  public:
    T* Find(String aName, bool IsUppercase=false)
    {
       return  (T*)MObjectList::Find(aName,IsUppercase);
    }
    T* Find(T* aEntity)
    {
      return (T*)MObjectList::Find(aEntity);
    }
  public:
    T* Find_E(String aName,bool IsUppercase=false)
    {
       return  (T*)MObjectList::Find_E(aName);
    }
    T* Find_E(T* aEntity)
    {
      return (T*)MObjectList::Find_E(aEntity);
    }

  public:
    //Clear()并清除ObjectItem
    void Flush()
    {
      for( int i=0; i<Count;  i++ )
      {
        T* aObject = Items[i];
        SafeDelete (&aObject);
        Items[i]=NULL;
      }
      Clear();
    }

  public:
    //MObjectList_Temp() :  MObjectList() {};

    __fastcall ~MObjectList_Temp()
    {
      if( DeleteObject )
        Flush();
      else
        Clear();
    }

  public:
    void Duplicate( MObjectList_Temp* aEntList )  //linkang
    {
        MObjectList::Duplicate( (MList_Temp<MObject>*) aEntList );
    }

   protected:
     void writeSelected(T* aSelected)
     {
       MObjectList::writeSelected( aSelected );
     }
     T* readSelected()
     {
       return (T*)MObjectList::readSelected();
     }
   public:
     __property T* Selected={read=readSelected,write=writeSelected};
};

//---------------- MListToTreePos ------------------------
class MListToTreePosition : public MObject
{
  //----ParentNodePos----  //父亲节点的位置
  private:
    int fParentNodePos;
    bool fVisited;
  public:
    __property int ParentNodePos={read=fParentNodePos,write=fParentNodePos};
    __property bool Visited={read=fVisited,write=fVisited};

  //----ChildNodesPos----  //孩子节点的位置
  private:
    TStrings*   fChildNodesPos;
  public:
    __property TStrings* ChildNodesPos={read=fChildNodesPos};
    bool Flg;

  public:
    MListToTreePosition();
};

class MListToTreePositions : public MObjectList_Temp<MListToTreePosition>
{
  public:
    void SetVisited( bool aVisited );
};

class MDoubleList :  public MList_Temp<double>
{
  public:
    virtual bool IsEqualByName(String aName,double*,bool IsUppercase) { return true; };
  public:
    int IndexMinimum( int aBgn, int aEnd );
    int IndexMaximum( int aBgn, int aEnd );
};


//------------------------------------------------------------------------------
//功能：MActionList
//------------------------------------------------------------------------------
class MActionControl : public MObject
{
  private:
    TControl* fControl;
  public:
    __property TControl* Control={read=fControl};
  public:
    MActionControl( TControl* fControl );
};

class MActionControls : public MObjectList_Temp<MActionControl>
{
  public:
    void AddControl( TControl* aControl );
};


class MActionStatus : public MObject
{
  private:
    MActionStatuses* fGroup;

  //----EnableActionNames----
  private:
    TStrings*   fEnableActionNames;
  public:
    __property TStrings* EnableActionNames={read=fEnableActionNames};

  //----ReserveActionNames----
  private:
    TStrings*   fReserveActionNames;
  public:
    __property TStrings* ReserveActionNames={read=fReserveActionNames};

  //----ReserveActionNames----
  private:
    TStrings*   fVisibleControlsNames;
  public:
    __property TStrings* VisibleControlsNames={read=fVisibleControlsNames};

  public:
    void LoadFromStr(String aStr);
    void GetLinkStatus();                 //处理@init的语义
  private:
    void GetLinkStatus(String IsWhat);
    bool GetLinkStatus_Item(String aStr, String IsWhat);
    void MergeLinkStatus_Item(TStrings* aList1, TStrings* aList2, String aStr);     

  public:
    MActionStatus( MActionStatuses* aGroup );
    virtual ~MActionStatus();
};

class MActionStatuses : public MObjectList_Temp<MActionStatus>
{
  public:
    void LoadFromStrings(TStrings* aStrings);
    void GetLinkStatus();                 //处理@init的语义    
};

class MActionAttr  : public MObject
{
  private:
    TAction* fAction;
    MActionAttrs* fGroup;
    TNotifyEvent fOldDoOnExcute;
    void __fastcall (__closure *fOldDoOnHint)(AnsiString&,bool&) ;

  //----Name----
  //private:
  //  String   fName;
  //public:
  //  __property String Name={read=fName,write=fName};

  //----StatusAfterClick----   //点击后的状态
  private:
    String   fStatusAfterClick;
  public:
    __property String StatusAfterClick={read=fStatusAfterClick,write=fStatusAfterClick};
  private:
    void __fastcall DoAfterActionClick(TObject *Sender);

  public:
    MActionAttr( TAction* aAction, MActionAttrs* aGroup );
    virtual ~MActionAttr();
  public:
    void LoadFromStr(String aStr);
};

class MActionAttrs : public MObjectList_Temp<MActionAttr>
{
  private:
    MActionList* fActionList;
  public:
    __property MActionList* ActionList={read=fActionList,write=fActionList};
  public:
    void LoadFromStrings(TStrings* aStrings);
  public:
    MActionAttrs( MActionList* aActionList );
};



class MActionList
{
  //----ActionList----
  private:
    TActionList*   fActionList;
  public:
    __property TActionList* ActionList={read=fActionList,write=fActionList};

  //----WinControls----
  private:
    MActionControls* fWinControls;
  public:
    __property MActionControls* WinControls={read=fWinControls};

  //----ActionStatuses----    //注册的状态类型
  private:
    MActionStatuses*   fActionStatuses;
  public:
    __property MActionStatuses* ActionStatuses={read=fActionStatuses};

  //----Status----    //当前状态
  private:
    MActionStatus*   fStatus;
  protected:
    void writeStatus( MActionStatus* aStatus );
  public:
    __property MActionStatus* Status={read=fStatus,write=writeStatus};

  public:
    void SetStatus(String aStatus);
  private:
    void SetEnableActions();
    void SetReserveActions();
    void SetDisableActions();
  private:
    void SetVisibleControls();
    void SetUnVisibleControls();

  //----ActionExcuteStatus----     //Action被点击后的状态注册表
  private:
    MActionAttrs*   fActionExcuteStatus;
  protected:
    void  writeActionExcuteStatus(MActionAttrs* aActionExcuteStatus );
  public:
    __property MActionAttrs* ActionExcuteStatus={read=fActionExcuteStatus,write=writeActionExcuteStatus};

  public:
    MActionList( TActionList* aActionList );
    virtual ~MActionList();

  public:
    TAction* FindActionByName(String aName);

  public:
    void LoadFromFile(String aFileName);        //读入*.Action文件
    void LoadFormStrings(TStrings* aStrings);
};








#endif
