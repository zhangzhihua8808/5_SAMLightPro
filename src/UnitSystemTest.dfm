object FormSystemTest: TFormSystemTest
  Left = 304
  Top = 84
  Width = 720
  Height = 534
  BorderIcons = [biSystemMenu]
  Caption = #31995#32479#27979#35797
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
    Width = 704
    Height = 29
    Caption = 'ToolBar1'
    Indent = 10
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 10
      Top = 2
      Width = 75
      Height = 22
      Caption = #20851#38381
      ModalResult = 1
      TabOrder = 0
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
      Height = 22
      Caption = #21462#28040
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 29
    Width = 704
    Height = 467
    ActivePage = TabSheet3
    Align = alClient
    TabIndex = 2
    TabOrder = 1
    TabPosition = tpBottom
    object TabSheet1: TTabSheet
      Caption = #36807#21387#27979#35797
    end
    object TabSheet2: TTabSheet
      Caption = #20445#21387#27979#35797
      ImageIndex = 1
    end
    object TabSheet3: TTabSheet
      Caption = #27668#27969#27979#35797
      ImageIndex = 2
    end
    object TabSheet4: TTabSheet
      Caption = 'TabSheet4'
      ImageIndex = 3
    end
  end
end
