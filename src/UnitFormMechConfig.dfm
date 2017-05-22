object FormMechConfig: TFormMechConfig
  Left = 605
  Top = 308
  Width = 499
  Height = 271
  BorderIcons = [biSystemMenu]
  Caption = #26426#22120#37197#32622
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 483
    Height = 31
    ButtonHeight = 25
    Caption = 'ToolBar1'
    Indent = 10
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 10
      Top = 2
      Width = 75
      Height = 25
      Caption = #20851#38381
      ModalResult = 1
      TabOrder = 0
      OnClick = BitBtn1Click
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00388888888877
        F7F787F8888888888333333F00004444400888FFF444448888888888F333FF8F
        000033334D5007FFF4333388888888883338888F0000333345D50FFFF4333333
        338F888F3338F33F000033334D5D0FFFF43333333388788F3338F33F00003333
        45D50FEFE4333333338F878F3338F33F000033334D5D0FFFF43333333388788F
        3338F33F0000333345D50FEFE4333333338F878F3338F33F000033334D5D0FFF
        F43333333388788F3338F33F0000333345D50FEFE4333333338F878F3338F33F
        000033334D5D0EFEF43333333388788F3338F33F0000333345D50FEFE4333333
        338F878F3338F33F000033334D5D0EFEF43333333388788F3338F33F00003333
        4444444444333333338F8F8FFFF8F33F00003333333333333333333333888888
        8888333F00003333330000003333333333333FFFFFF3333F00003333330AAAA0
        333333333333888888F3333F00003333330000003333333333338FFFF8F3333F
        0000}
      NumGlyphs = 2
    end
    object BitBtn2: TBitBtn
      Left = 85
      Top = 2
      Width = 75
      Height = 25
      Caption = #21462#28040
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 31
    Width = 483
    Height = 202
    Align = alClient
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 9
      Top = 48
      Width = 216
      Height = 105
      Caption = #24037#20316#21306#22495
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 32
        Width = 55
        Height = 13
        Caption = #38271#24230'(mm)   '
      end
      object Label2: TLabel
        Left = 16
        Top = 72
        Width = 55
        Height = 13
        Caption = #23485#24230'(mm)   '
      end
      object Edit_WorkAreaLength: TEdit
        Left = 86
        Top = 28
        Width = 115
        Height = 21
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
      end
      object Edit_WorkAreaWidth: TEdit
        Left = 87
        Top = 68
        Width = 114
        Height = 21
        Enabled = False
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ReadOnly = True
        TabOrder = 1
      end
    end
    object GroupBox2: TGroupBox
      Left = 232
      Top = 48
      Width = 233
      Height = 129
      Caption = #36735#21410#21442#25968
      TabOrder = 1
      object Label3: TLabel
        Left = 16
        Top = 32
        Width = 67
        Height = 13
        Caption = #22522#20934#38754'(mm)   '
      end
      object Label4: TLabel
        Left = 16
        Top = 64
        Width = 79
        Height = 13
        Caption = #22522#26495#21402#24230'(mm)   '
      end
      object Label5: TLabel
        Left = 8
        Top = 96
        Width = 91
        Height = 13
        Caption = #28966#24179#38754#34917#20607'(mm)   '
      end
      object Edit_ZInitPos: TEdit
        Left = 102
        Top = 28
        Width = 115
        Height = 21
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
      end
      object Edit_BaseBoardThick: TEdit
        Left = 102
        Top = 60
        Width = 115
        Height = 21
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 1
      end
      object Edit1: TEdit
        Left = 102
        Top = 92
        Width = 115
        Height = 21
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 2
      end
    end
    object CBox_WorkArea: TCheckBox
      Left = 16
      Top = 16
      Width = 57
      Height = 17
      Caption = #20351#33021
      TabOrder = 2
      OnClick = CBox_WorkAreaClick
    end
  end
end
