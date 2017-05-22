object FormNewProject: TFormNewProject
  Left = 339
  Top = 209
  BorderStyle = bsDialog
  Caption = #26032#24314#24037#31243
  ClientHeight = 350
  ClientWidth = 393
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 393
    Height = 29
    ButtonHeight = 24
    Caption = 'ToolBar1'
    EdgeInner = esNone
    EdgeOuter = esRaised
    TabOrder = 0
    object ToolButton1: TToolButton
      Left = 0
      Top = 2
      Width = 8
      Caption = 'ToolButton1'
      Style = tbsSeparator
    end
    object BitBtn_OK: TBitBtn
      Left = 8
      Top = 2
      Width = 75
      Height = 24
      Caption = #30830#23450
      Default = True
      TabOrder = 0
      OnClick = BitBtn_OKClick
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object BitBtn_Cancel: TBitBtn
      Left = 83
      Top = 2
      Width = 75
      Height = 24
      Caption = #21462#28040
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 29
    Width = 393
    Height = 321
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 7
      Top = 16
      Width = 65
      Height = 24
      Alignment = taCenter
      AutoSize = False
      Caption = #24037#31243#21517#31216
      Layout = tlCenter
    end
    object Label2: TLabel
      Left = 4
      Top = 150
      Width = 65
      Height = 25
      Alignment = taCenter
      AutoSize = False
      Caption = #24037#31243#35828#26126
      Layout = tlCenter
    end
    object Label3: TLabel
      Left = 16
      Top = 47
      Width = 48
      Height = 13
      Caption = #31616#20171#25551#36848
    end
    object EditProjectName: TEdit
      Left = 72
      Top = 17
      Width = 292
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
    end
    object Memo_Des: TMemo
      Left = 72
      Top = 48
      Width = 292
      Height = 96
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object Memo_Say: TMemo
      Left = 71
      Top = 149
      Width = 292
      Height = 156
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
    end
  end
end
