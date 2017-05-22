object FormLoadModel: TFormLoadModel
  Left = 389
  Top = 295
  Width = 444
  Height = 155
  Caption = #27169#22411#20449#24687
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 6
    Top = 57
    Width = 60
    Height = 13
    Caption = #27169#22411#25991#20214'    '
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 428
    Height = 29
    Caption = 'ToolBar1'
    Indent = 5
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 5
      Top = 2
      Width = 75
      Height = 22
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 80
      Top = 2
      Width = 75
      Height = 22
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Edit1: TEdit
    Left = 70
    Top = 55
    Width = 302
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 1
  end
  object Button1: TButton
    Left = 376
    Top = 54
    Width = 33
    Height = 23
    Caption = '...'
    TabOrder = 2
    OnClick = Button1Click
  end
  object OpenDialog1: TOpenDialog
    Left = 384
    Top = 16
  end
end
