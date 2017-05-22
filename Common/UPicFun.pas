unit UPicFun;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ExtDlgs, jpeg;

procedure CombinBmp(BmpFilNames: Tstrings; MType: string;
                                var Desbmp: Tbitmap);overload;

procedure CombinBmp(BmpFilNames: Tstrings; HNum: integer;ZNum:integer;
                                var Desbmp: Tbitmap);overload;

FUNCTION LoadGraphicsFile(CONST Filename:  STRING):  TBitmap;

procedure GetLocalPic(FileName:String;EndX,EndY:integer;StX:integer;StY:integer;var Bmp:TBitmap);

procedure Bmp2Jpg(Bmp: TBitmap; Quality: Integer;var Jpg:TJpegImage) ;

function DuFenMiao_To_Miao(  aDuFenMiao:string ): double;
function Miao_To_DuFenMiao(  i_Miao:double;  aDu_Sp:String='-';  aFen_Sp:String='-';  aMiao_Sp:String='' ):string;
procedure bmpSaveasJpg(Tmpbmp:Tbitmap;FilePath:String);
procedure CombinPic(ZNum,HNum:integer;StJd,StWd,DeltJd,DeltWd:string;Filepath,SavePath:String;IsGoOn:Boolean=true);

implementation

uses COMMON_FUNC;
procedure CombinBmp(BmpFilNames: Tstrings; MType: string;
                                var Desbmp: Tbitmap);
var
   i:integer;
   G_Imag : TBitmap;
   Mwidth,Mheight:integer;
   aImgWid,aImgHei:array of integer;
begin
   G_Imag:= TBitmap.Create;
   Mwidth:=0;
   MHeight := 0;
   try
      setlength(aImgWid,BmpFilNames.Count);
      setlength(aImgHei,BmpFilNames.Count);

    for i:=0 to   BmpFilNames.Count-1 do
    begin

      G_Imag:=LoadGraphicsFile(BmpFilNames.Strings[i]);

     aImgWid[i]:=G_Imag.width;
     aImgHei[i]:=G_Imag.height;

     if MType ='横排' then
     begin
        if G_Imag.Height>MHeight then  MHeight := G_Imag.Height;
        Mwidth:=G_Imag.Width+Mwidth;

     end;

     if MType ='竖排' then
     begin
        if G_Imag.Width>Mwidth then  Mwidth := G_Imag.Width;
        MHeight:=G_Imag.Height+MHeight;
     end;
     if MType ='四方' then
     begin
       
     end;

    end;
  
    Desbmp.Width := Mwidth;
    Desbmp.Height:= MHeight;

    for i:=0 to   BmpFilNames.Count-1 do
    begin
      G_Imag:=LoadGraphicsFile(BmpFilNames.Strings[i]);
      if MType ='横排' then
      begin
        if i=0 then
            Desbmp.Canvas.CopyRect(
              Rect(0,0,G_Imag.Width,MHeight),G_Imag.Canvas,
              Rect(0,0,G_Imag.Width,G_Imag.Height))
        else
          Desbmp.Canvas.CopyRect(
            Rect(aImgWid[i-1],0,Mwidth,MHeight),G_Imag.Canvas,
            Rect(0,0,G_Imag.Width,G_Imag.Height));
      end;

     if MType ='竖排' then
     begin
       if i=0 then
            Desbmp.Canvas.CopyRect(
              Rect(0,0,Mwidth,G_Imag.Height),G_Imag.Canvas,
              Rect(0,0,G_Imag.Width,G_Imag.Height))
        else
          Desbmp.Canvas.CopyRect(
            Rect(0,aImgHei[i-1],Mwidth,MHeight),G_Imag.Canvas,
            Rect(0,0,G_Imag.Width,G_Imag.Height));
     end;
   end;
    finally
       G_Imag.Free;
    end;
end;

procedure CombinBmp(BmpFilNames: Tstrings; HNum: integer;ZNum:integer;
                                var Desbmp: Tbitmap);overload;
begin
   
end;
//------------------------------------------------------------------------------
//功能：装入图片文件
//------------------------------------------------------------------------------
FUNCTION LoadGraphicsFile(CONST Filename:  STRING):  TBitmap;
VAR
      Extension:  STRING;
{$IFDEF GIF}
      GIFImage :  TGIFImage;
{$ENDIF}
      Icon     :  TIcon;
      JPEGImage:  TJPEGImage;
      Metafile :  TMetafile;
BEGIN
    RESULT := NIL;  // In case anything goes wrong

    IF   FileExists(Filename)
    THEN BEGIN
      // Extension := UpperCase(ExtractFileExt(Filename));
      Extension := UpperCase( COPY(Filename, LENGTH(Filename)-2, 3) );

     //  Quick and dirty check that file type is OK
      ASSERT( (Extension = 'BMP')  OR
              (Extension = 'EMF')  OR
{$IFDEF GIF}
              (Extension = 'GIF')  OR
{$ENDIF}
              (Extension = 'ICO')  OR
              (Extension = 'JPG')  OR
              (Extension = 'WMF') );

      RESULT := TBitmap.Create;

      // BMP File -- no additional work to get TBitmap
      IF   Extension = 'BMP'
      THEN RESULT.LoadFromFile(Filename);

{$IFDEF GIF}
      // GIF File
      IF   Extension = 'GIF'
      THEN BEGIN
        GIFImage := TGIFImage.Create;
        TRY
          GIFImage.LoadFromFile(Filename);
          RESULT.Height      := GIFImage.Height;
          RESULT.Width       := GIFImage.Width;
          RESULT.PixelFormat := pf24bit;
          RESULT.Canvas.Draw(0,0, GIFImage)
        FINALLY
          GIFImage.Free
        END
      END;
{$ENDIF}

      // ICO File
      IF   Extension = 'ICO'
      THEN BEGIN
        Icon := TIcon.Create;
        TRY
          TRY
            Icon.LoadFromFile(Filename);
            RESULT.Height      := Icon.Height;
            RESULT.Width       := Icon.Width;
            RESULT.PixelFormat := pf24bit;    // avoid palette problems
            RESULT.Canvas.Draw(0,0, Icon)
            EXCEPT
            // Ignore problem icons, e.g., Stream read errors
          END;

        FINALLY
          Icon.Free
        END
      END;

      // JPG File
      IF   Extension = 'JPG'
      THEN BEGIN
        JPEGImage := TJPEGImage.Create;
        TRY
          JPEGImage.LoadFromFile(Filename);
          RESULT.Height      := JPEGImage.Height;
          RESULT.Width       := JPEGImage.Width;
          RESULT.PixelFormat := pf24bit;
          RESULT.Canvas.Draw(0,0, JPEGImage)
        FINALLY
          JPEGImage.Free
        END
      END;

      // Windows Metafiles, WMF or EMF
      IF   (Extension = 'WMF') OR
           (Extension = 'EMF')
      THEN BEGIN
        Metafile := TMetafile.Create;
        TRY
          Metafile.LoadFromFile(Filename);
          RESULT.Height      := Metafile.Height;
          RESULT.Width       := Metafile.Width;
          RESULT.PixelFormat := pf24bit;    // avoid palette problems
          RESULT.Canvas.Draw(0,0, Metafile)
        FINALLY
          Metafile.Free
        END
      END;

    END;

    // If Graphic is missing or invalid, create the "Red X"
    IF   RESULT = NIL
    THEN BEGIN
      RESULT := TBitmap.Create;
      RESULT.Height      := 32;
      RESULT.Width       := 32;
      RESULT.PixelFormat := pf24bit;
      WITH RESULT.Canvas DO BEGIN
        Pen.Color := clRed;
        Pen.Width := 3;
        MoveTo( 2, 2);
        LineTo(29,29);

        MoveTo( 2,29);
        LineTo(29, 2);
      END
    END
END {LoadGraphicFile};

procedure GetLocalPic(FileName:String;EndX,EndY:integer;StX:integer;StY:integer;var Bmp:TBitmap);
Var
  SrPic:Tbitmap;
begin
  try

    if FileName='' then exit;

    bmp.Height      :=EndY-StY;
    bmp.Width       :=EndX-StX;
    SrPic:=Tbitmap.Create;
    try
      SrPic :=LoadGraphicsFile(FileName);
      bmp.Canvas.CopyRect(
                Rect(StX,Sty,EndX,EndY),SrPic.Canvas,
              Rect(StX,Sty,EndX,EndY));
    finally
      SrPic.Free;
    end;
    //Showmessage(IntToStr(result.Width));
  except
    on e:Exception do raise exception.Create('GetLocalPic出错！'+e.Message);
  end;
end;

procedure Bmp2Jpg(Bmp: TBitmap; Quality: Integer;var Jpg:TJpegImage) ;

begin


    if Assigned(Bmp)

    then begin


      Jpg.Assign(Bmp); {Its all folks...}

      Jpg.CompressionQuality := Quality;

      Jpg.JPEGNeeded; {Key method...}

      Jpg.Compress;

    end;


end;


function DuFenMiao_To_Miao(  aDuFenMiao:string ): double;
var
 aDu  : double  ;
 aFen : double ;
 aMiao :double;
begin
  //36-42-49.2
   aDu := StrToFloat( NamedItem( 0, aDuFenMiao, '-' ) )*3600 ;
   aFen :=  StrToFloat( NamedItem( 1, aDuFenMiao, '-' ) )*60;
   aMiao := StrToFloat( NamedItem( 2, aDuFenMiao, '-' ) );
  result:=  aDu+aFen+aMiao ;
end;

function Miao_To_DuFenMiao(  i_Miao:double;  aDu_Sp:String='-';  aFen_Sp:String='-';  aMiao_Sp:String='' ):string;
var
   aMiao_Int,aDu,aFen_Int,aMiao,aFen:integer;
   aRes:double;
   aMiao_Text: String;
begin
   aMiao_Int :=  trunc(i_Miao);
   aRes := i_Miao - aMiao_Int;

   aDu := trunc( aMiao_Int/ 3600 );

   aFen_Int :=  aMiao_Int mod 3600 ;
   aFen := trunc( aFen_Int/60 );

   aMiao :=  aFen_Int mod 60 ;

   aMiao_Text := Format( '%4.2f',[aMiao+aRes] );
  //FloatToStr(double(aMiao)+aRes)

  result:= ( IntToStr(aDu)+aDu_Sp+IntToStr(aFen)+aFen_Sp+ aMiao_Text+aMiao_Sp);

  //36-42-49.2
end;

procedure bmpSaveasJpg(Tmpbmp:Tbitmap;FilePath:String);
var
  JPEGImage : TJPEGImage;
begin
 JPEGImage := TJPEGImage.Create;
 try
    Bmp2Jpg(Tmpbmp,50,JPEGImage);
    if not directoryexists(ExtractFileDir(filePath)) then Mkdir(ExtractFileDir(filePath));
    JPEGImage.SaveToFile(FilePath);
 finally
   JPEGImage.Free;
 end;
end;

procedure CombinPic(ZNum,HNum:integer;StJd,StWd,DeltJd,DeltWd:string;Filepath,SavePath:String;IsGoOn:Boolean=true);
var
  i,j:integer;
  PicFileNames:Tstrings;
  FileName,WdStr,JdStr:String;
  nbmp : TBitmap;
  errorfile:Tstrings;
begin
  PicFileNames:=Tstringlist.Create;
  errorfile:=Tstringlist.Create;
   nbmp:= TBitmap.Create;
  try

    PicFileNames.Clear;
    for i:=0 to HNum-1 do
    begin
      for j:=0 to ZNum-1 do
      begin
        if not IsGoOn then exit;
        application.ProcessMessages;
        if DirectoryExists(Filepath) then
        begin
          JdStr :=Miao_To_DuFenMiao(DuFenMiao_To_Miao(StJd)+j*strtofloat(DeltJd));
          WdStr :=Miao_To_DuFenMiao(DuFenMiao_To_Miao(StWd)+i*strtofloat(DeltWd));

          FileName:=Filepath+'\'+WdStr+'N,'+JdStr+'W.jpg';
          if fileexists(fileName) then
          begin
            PicFileNames.Add(FileName);
          end
          else
            errorfile.Add(filename);
        end;//if DirectoryExists
      end;//for j:=0...
    end;//for i:=0...
   if PicFileNames.Count<=0 then
   begin
     showmessage('无可处理图片！');
     exit;
   end;
    CombinBmp(PicFileNames,HNum,ZNum, nbmp);
    bmpSaveasJpg(nbmp,SavePath+'\'+GetFileName_NoExt(ExtractFileName(PicFileNames.Strings[0]))+IntToStr(HNum)+'&'+IntTOStr(ZNum)+'.jpg');
    if errorfile.Count>0 then
      errorfile.SaveToFile(SavePath+'\'+StJd+'W'+StWd+'N'+'errorfilenames.txt');
  finally
    PicFileNames.Free;
    errorfile.Free;
    nbmp.Free;
  end;
end;
end.
