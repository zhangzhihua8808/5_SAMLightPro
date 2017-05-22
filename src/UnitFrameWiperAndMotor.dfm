object FrameWiperAndMotor: TFrameWiperAndMotor
  Left = 0
  Top = 0
  Width = 421
  Height = 526
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 404
    Height = 153
    Align = alTop
    TabOrder = 0
    object Label2: TLabel
      Left = 10
      Top = 65
      Width = 36
      Height = 13
      Caption = #19978#31881#37327
    end
    object Label3: TLabel
      Left = 11
      Top = 98
      Width = 34
      Height = 13
      Caption = 'Y '#20301#32622
    end
    object Label4: TLabel
      Left = 264
      Top = 98
      Width = 19
      Height = 13
      Caption = 'mm'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 384
      Top = 66
      Width = 10
      Height = 13
      Caption = '%'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label1: TLabel
      Left = 8
      Top = 19
      Width = 51
      Height = 14
      Caption = #21038#26495#25511#21046' '
    end
    object Button4: TButton
      Left = 56
      Top = 122
      Width = 129
      Height = 25
      Caption = #33258#21160#19978#31881
      TabOrder = 0
    end
    object TrackBar1: TTrackBar
      Left = 47
      Top = 60
      Width = 300
      Height = 28
      Max = 100
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
    end
    object Ed_Dose: TEdit
      Left = 348
      Top = 63
      Width = 33
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 2
    end
    object Ed_Y_Pos: TEdit
      Left = 56
      Top = 96
      Width = 201
      Height = 21
      Color = clScrollBar
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 3
    end
    object Button1: TButton
      Left = 75
      Top = 12
      Width = 77
      Height = 25
      Caption = #22238#21040#21407#28857
      TabOrder = 4
    end
    object Button2: TButton
      Left = 179
      Top = 11
      Width = 77
      Height = 25
      Caption = #22238#21040#26368#21069
      TabOrder = 5
    end
    object Button3: TButton
      Left = 280
      Top = 10
      Width = 81
      Height = 25
      Caption = #22238#21040#20013#38388
      TabOrder = 6
    end
    object Edit1: TEdit
      Left = 0
      Top = 42
      Width = 416
      Height = 8
      BevelInner = bvNone
      BevelOuter = bvNone
      Color = clLime
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 7
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 153
    Width = 404
    Height = 375
    Align = alBottom
    TabOrder = 1
    object Label6: TLabel
      Left = 232
      Top = 56
      Width = 58
      Height = 13
      Caption = 'Z '#32477#23545#20301#32622
    end
    object Label7: TLabel
      Left = 384
      Top = 82
      Width = 19
      Height = 13
      Caption = 'mm'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 224
      Top = 136
      Width = 48
      Height = 13
      Caption = #25176#30424#39640#24230
    end
    object Label9: TLabel
      Left = 304
      Top = 162
      Width = 19
      Height = 13
      Caption = 'mm'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 160
      Top = 264
      Width = 24
      Height = 13
      Caption = #23618#21402
    end
    object Label11: TLabel
      Left = 304
      Top = 266
      Width = 17
      Height = 13
      Caption = 'um'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 160
      Top = 296
      Width = 24
      Height = 13
      Caption = #23618#21495
    end
    object Edit2: TEdit
      Left = 176
      Top = 80
      Width = 201
      Height = 21
      Color = clScrollBar
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 0
    end
    object Button5: TButton
      Left = 56
      Top = 122
      Width = 129
      Height = 25
      Caption = 'Go To 40mm'
      TabOrder = 1
    end
    object Button6: TButton
      Left = 56
      Top = 162
      Width = 129
      Height = 25
      Caption = 'Go To 80mm'
      TabOrder = 2
    end
    object Button7: TButton
      Left = 56
      Top = 202
      Width = 129
      Height = 25
      Caption = #35774#32622#22522#20934
      TabOrder = 3
    end
    object Edit3: TEdit
      Left = 200
      Top = 160
      Width = 97
      Height = 21
      Color = clScrollBar
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 4
    end
    object Edit4: TEdit
      Left = 192
      Top = 262
      Width = 97
      Height = 21
      Color = clScrollBar
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 5
    end
    object Edit5: TEdit
      Left = 192
      Top = 294
      Width = 97
      Height = 21
      Color = clScrollBar
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 6
    end
    object UpDown1: TUpDown
      Left = 301
      Top = 289
      Width = 17
      Height = 25
      Min = 0
      Position = 0
      TabOrder = 7
      Wrap = False
    end
  end
end
