VERSION 5.00
Begin VB.Form frmPrincipal 
   Caption         =   "-_- Gera String"
   ClientHeight    =   3555
   ClientLeft      =   7005
   ClientTop       =   3180
   ClientWidth     =   5610
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   3555
   ScaleWidth      =   5610
   Begin VB.TextBox txtQuantidadeCasas 
      Height          =   285
      Left            =   1110
      TabIndex        =   3
      Text            =   "1"
      Top             =   2370
      Width           =   1215
   End
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   1890
      Top             =   2700
   End
   Begin VB.CommandButton cmdFinalizar 
      Cancel          =   -1  'True
      Caption         =   "Finalizar"
      CausesValidation=   0   'False
      Height          =   375
      Left            =   2490
      TabIndex        =   2
      Top             =   2370
      Width           =   1305
   End
   Begin VB.CommandButton cmdIniciar 
      Caption         =   "Iniciar"
      Default         =   -1  'True
      Height          =   375
      Left            =   3870
      TabIndex        =   1
      Top             =   2370
      Width           =   1305
   End
   Begin VB.ListBox lstvLista 
      Height          =   2205
      Left            =   30
      TabIndex        =   0
      Top             =   90
      Width           =   5175
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Quant. char:"
      Height          =   195
      Left            =   60
      TabIndex        =   4
      Top             =   2400
      Width           =   915
   End
End
Attribute VB_Name = "frmPrincipal"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function InitCommonControls Lib "comctl32.dll" () As Long

Dim str                                         As String
Dim tamanhoMaximo                               As String
Dim stringFinal                                 As String
Dim indexCharMudar                              As Integer
Dim md5                                         As New md5

Private Sub cmdFinalizar_Click()
  Me.Timer.Enabled = False
End Sub

Private Sub cmdIniciar_Click()
  Dim inicializarCasas                          As Integer
  Dim tmp                                       As Integer

  Me.lstvLista.Clear
  tamanhoMaximo = Me.txtQuantidadeCasas.Text
  indexCharMudar = 1
  
  inicializarCasas = InputBox("Com quantas casas deseja inicializar?", "-_-", 1)
  str = ""
  
  While inicializarCasas <> 0
   str = str & "0"
   inicializarCasas = inicializarCasas - 1
  Wend
  
  indexCharMudar = Len(str)
  stringFinal = ""
  
  While tmp < tamanhoMaximo
   stringFinal = stringFinal & "z"
   tmp = tmp + 1
  Wend
  
  Timer.Enabled = True
End Sub

Private Sub Form_Activate()
  Me.txtQuantidadeCasas.SetFocus
  
  'MsgBox "" & mudarProximoCharIndex("100", 3)
End Sub

Private Sub Form_Initialize()
  InitCommonControls
End Sub

Private Sub Form_Resize()
  If Me.WindowState <> vbMinimized Then
   Me.lstvLista.Width = Me.Width - 200
   Me.lstvLista.Height = Me.Height - 900
   
   Me.cmdIniciar.Top = Me.lstvLista.Height + 120
   Me.cmdIniciar.Left = Me.lstvLista.Width - Me.cmdIniciar.Width
   
   Me.cmdFinalizar.Top = Me.cmdIniciar.Top
   Me.cmdFinalizar.Left = Me.cmdIniciar.Left - Me.cmdIniciar.Width - 100
   
   Me.txtQuantidadeCasas.Top = Me.cmdFinalizar.Top + 30
   Me.txtQuantidadeCasas.Left = Me.cmdFinalizar.Left - Me.cmdFinalizar.Width - 100
   
   Me.Label1.Top = Me.txtQuantidadeCasas.Top
   Me.Label1.Left = Me.txtQuantidadeCasas.Left - Me.txtQuantidadeCasas.Width - 10
  End If
End Sub

Private Function proximoChar(str As String) As String
  Dim char                    As Integer
  
  char = Asc(str)
  If (char < 48) Then
   char = 49
  
  ElseIf (char < 65 And char > 57) Then
   char = 65
  
  ElseIf (char < 97 And char > 90) Then
   char = 97
   
  ElseIf (char >= 122) Then
   char = 48
   
  Else
   char = char + 1
  End If
  
  proximoChar = Chr(char)
End Function

'Modifica um char para o proximo char ex: 100 2 = 110
Private Function mudarProximoCharIndex(str As String, index As Integer) As String
  If Len(str) > 1 Then
   If index = 1 Or index = 0 Then
    mudarProximoCharIndex = proximoChar(Mid(str, 1, 1)) & Mid(str, 2, Len(str))
    
   Else
    mudarProximoCharIndex = Mid(str, 1, index - 1) & proximoChar(Mid(str, index, 1)) & Mid(str, index + 1, Len(str))
   End If
   
  Else
   mudarProximoCharIndex = proximoChar(str)
  End If
End Function

Private Sub Timer_Timer()
  Dim tmp                             As Integer

  Me.lstvLista.AddItem str & vbTab & md5.DigestStrToHexStr(str)
  gravarArquivo str & vbTab & vbTab & md5.DigestStrToHexStr(str) & vbNewLine
  
  If Mid(str, Len(str), 1) = "z" Then 'Verifico somente o fim
   If stringFinal = str Then
    Timer.Enabled = False
    Exit Sub
   End If
   
   If tamanhoMaximo > Len(str) And Mid(stringFinal, 1, Len(str)) = str Then
    str = "z" & str
    
    tmp = 1
    While tmp <= Len(str)
     str = mudarProximoCharIndex(str, tmp)
     tmp = tmp + 1
    Wend
    
    indexCharMudar = Len(str)
   Else
    
    tmp = Len(str)
    
    While Mid(str, tmp, 1) = "z"
     str = mudarProximoCharIndex(str, tmp)
     tmp = tmp - 1
    Wend
    
    str = mudarProximoCharIndex(str, tmp)
    
   End If
      
   Exit Sub
  End If
  
  str = mudarProximoCharIndex(str, indexCharMudar)
  Me.Caption = "-_- Gerar String: " & Me.lstvLista.ListCount
End Sub

Private Sub gravarArquivo(str As String)
  Open "StringsMd5.txt" For Binary As 1
   Seek #1, LOF(1) + 1
   Put #1, LOF(1) + 1, str
  Close 1
End Sub
