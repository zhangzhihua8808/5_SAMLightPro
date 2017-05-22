object FormTestInstance: TFormTestInstance
  Left = 336
  Top = 143
  BorderStyle = bsSingle
  Caption = #27979#35797#20363#31243#21442#25968#21270#35774#35745
  ClientHeight = 629
  ClientWidth = 893
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 260
    Top = 33
    Width = 875
    Height = 616
    Align = alCustom
    Proportional = True
  end
  object Splitter1: TSplitter
    Left = 257
    Top = 33
    Width = 3
    Height = 596
    Cursor = crHSplit
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 893
    Height = 33
    ButtonHeight = 25
    Caption = 'ToolBar1'
    TabOrder = 0
    object BitBtn2: TBitBtn
      Left = 0
      Top = 2
      Width = 75
      Height = 25
      Caption = #20851#38381
      TabOrder = 0
      Kind = bkClose
    end
    object ToolButton1: TToolButton
      Left = 75
      Top = 2
      Width = 8
      Caption = 'ToolButton1'
      Style = tbsSeparator
    end
    object BitBtn1: TBitBtn
      Left = 83
      Top = 2
      Width = 78
      Height = 25
      Caption = #39044#35272
      TabOrder = 1
      OnClick = BitBtn1Click
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555550
        00555555555FFF57775F55555500050BBB0555FFF57775777775500050EEE000
        777057775777777775F709990777777770F0777775FFFFFFF7F7099990000000
        F0F07F5557777777F7F70FFFFFFFFFF0F0F07F5555555557F7F70FFFFFFFFFF0
        F0F07F5555555557F7F70FFFFFFFFFF0F0F07F5FF5FF5F57F7F70F77F77F7FF0
        F0F07F7757757557F7F70FFFFFFFFFF0F0F07F5FF5FFF557F7F70F77F777FFF0
        F0F07F7757775557F7F70FFFFFFFFFF0F0F07FF5F5F5F5F7F7F700F0F0F0F0F0
        F00577F7F7F7F7F7F77F0070707070700005777777777777777F707070707070
        55055757575757575F7555050505050500555575757575757755}
      NumGlyphs = 2
    end
    object BitBtn4: TBitBtn
      Left = 161
      Top = 2
      Width = 118
      Height = 25
      Hint = #29983#25104#36718#24275
      Caption = #36755#20986#20960#20309#36718#24275
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = BitBtn4Click
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00500000000055
        555557777777775F55550FFFFFFFFF0555557F5555555F7FFF5F0FEEEEEE0000
        05007F555555777775770FFFFFF0BFBFB00E7F5F5557FFF557770F0EEEE000FB
        FB0E7F75FF57775555770FF00F0FBFBFBF0E7F57757FFFF555770FE0B00000FB
        FB0E7F575777775555770FFF0FBFBFBFBF0E7F5575FFFFFFF5770FEEE0000000
        FB0E7F555777777755770FFFFF0B00BFB0007F55557577FFF7770FEEEEE0B000
        05557F555557577775550FFFFFFF0B0555557FF5F5F57575F55500F0F0F0F0B0
        555577F7F7F7F7F75F5550707070700B055557F7F7F7F7757FF5507070707050
        9055575757575757775505050505055505557575757575557555}
      NumGlyphs = 2
    end
    object ToolButton2: TToolButton
      Left = 279
      Top = 2
      Width = 8
      Caption = 'ToolButton2'
      ImageIndex = 0
      Style = tbsSeparator
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 33
    Width = 257
    Height = 596
    ActivePage = TabSheet1
    Align = alLeft
    TabIndex = 0
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #35774#35745#21442#25968
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 249
        Height = 568
        Align = alClient
        TabOrder = 0
        object GroupBox2: TGroupBox
          Left = 1
          Top = 1
          Width = 247
          Height = 121
          Align = alTop
          Caption = #35774#35745#23610#23544
          TabOrder = 0
          object Label1: TLabel
            Left = 16
            Top = 32
            Width = 30
            Height = 13
            Caption = #31867#22411'  '
          end
          object Label2: TLabel
            Left = 16
            Top = 64
            Width = 52
            Height = 13
            Caption = #39640#24230'(mm)  '
          end
          object Label3: TLabel
            Left = 16
            Top = 92
            Width = 52
            Height = 13
            Caption = #38271#24230'(mm)  '
          end
          object ComboBox1: TComboBox
            Left = 80
            Top = 27
            Width = 129
            Height = 21
            Style = csDropDownList
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 0
            Text = #30697#24418
            OnChange = ComboBox1Change
            Items.Strings = (
              #30697#24418
              #27491#19977#35282#24418
              #22278#24418
              #24037#20214'I'
              '4X4'#34180#26495
              #28966#24179#38754#23454#39564)
          end
          object EditHeight: TEdit
            Left = 80
            Top = 60
            Width = 129
            Height = 21
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            TabOrder = 1
            Text = '10'
          end
          object EditWidth: TEdit
            Left = 80
            Top = 88
            Width = 129
            Height = 21
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            TabOrder = 2
            Text = '10'
          end
        end
        object GroupBox4: TGroupBox
          Left = 1
          Top = 122
          Width = 247
          Height = 79
          Align = alTop
          Caption = #23618#20449#24687
          TabOrder = 1
          object Label10: TLabel
            Left = 17
            Top = 24
            Width = 52
            Height = 13
            Caption = #23618#21402'(mm)  '
          end
          object Label4: TLabel
            Left = 18
            Top = 48
            Width = 30
            Height = 13
            Caption = #23618#25968'  '
          end
          object Edit_LayerThick: TEdit
            Left = 104
            Top = 20
            Width = 97
            Height = 21
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            TabOrder = 0
            Text = '0.060'
          end
          object Edit1: TEdit
            Left = 104
            Top = 44
            Width = 97
            Height = 21
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            TabOrder = 1
            Text = '80'
          end
        end
        object Panel2: TPanel
          Left = 1
          Top = 201
          Width = 247
          Height = 366
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 2
          object PageControl2: TPageControl
            Left = 0
            Top = 0
            Width = 247
            Height = 366
            ActivePage = TTestFocus
            Align = alClient
            TabIndex = 0
            TabOrder = 0
            object TTestFocus: TTabSheet
              Caption = #28966#24179#38754
              object Label6: TLabel
                Left = 0
                Top = 46
                Width = 82
                Height = 13
                Caption = #30456#37051#39640#24230#24046'(mm)'
              end
              object Label7: TLabel
                Left = 8
                Top = 16
                Width = 76
                Height = 13
                Caption = #31446#32447#38388#36317'(mm)  '
              end
              object Edit3: TEdit
                Left = 104
                Top = 43
                Width = 121
                Height = 21
                ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
                TabOrder = 0
                Text = '1'
              end
              object Edit4: TEdit
                Left = 104
                Top = 12
                Width = 121
                Height = 21
                ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
                TabOrder = 1
                Text = '3'
              end
            end
          end
        end
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 672
  end
end
