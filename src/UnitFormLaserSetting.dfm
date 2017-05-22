object FormLaserSetting: TFormLaserSetting
  Left = 673
  Top = 321
  Width = 583
  Height = 429
  BorderIcons = [biSystemMenu]
  Caption = #24037#33402#21442#25968
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 567
    Height = 35
    ButtonHeight = 28
    Caption = 'ToolBar1'
    Indent = 10
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 10
      Top = 2
      Width = 75
      Height = 28
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
      Height = 28
      Caption = #21462#28040
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 35
    Width = 567
    Height = 356
    Align = alClient
    TabOrder = 1
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 565
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 13
        Width = 113
        Height = 13
        AutoSize = False
        Caption = #28608#20809#26368#22823#21151#29575'(W)    '
      end
      object Edit_LaserMaxPower: TEdit
        Left = 144
        Top = 9
        Width = 193
        Height = 21
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
        Text = '500'
      end
      object Button2: TButton
        Left = 400
        Top = 8
        Width = 75
        Height = 25
        Caption = 'Edit...'
        TabOrder = 1
        OnClick = Button2Click
      end
    end
    object ListView1: TListView
      Left = 1
      Top = 42
      Width = 565
      Height = 313
      Align = alClient
      Columns = <>
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsList
      OnDblClick = ListView1DblClick
    end
  end
end
