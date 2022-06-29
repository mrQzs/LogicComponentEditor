#include "qscilexervb.h"

#include <qcolor.h>
#include <qfont.h>

// The ctor.
QsciLexerVB::QsciLexerVB(QObject *parent) : QsciLexerCPP(parent) {}

// The dtor.
QsciLexerVB::~QsciLexerVB() {}

// Returns the language name.
const char *QsciLexerVB::language() const { return "VB"; }

// Returns the foreground colour of the text for a style.
QColor QsciLexerVB::defaultColor(int style) const {
  if (style == VerbatimString) return QColor(0x00, 0x7f, 0x00);

  return QsciLexerCPP::defaultColor(style);
}

// Returns the end-of-line fill for a style.
bool QsciLexerVB::defaultEolFill(int style) const {
  if (style == VerbatimString) return true;

  return QsciLexerCPP::defaultEolFill(style);
}

// Returns the font of the text for a style.
QFont QsciLexerVB::defaultFont(int style) const {
  if (style == VerbatimString)
#if defined(Q_OS_WIN)
    return QFont("Courier New", 10);
#elif defined(Q_OS_MAC)
    return QFont("Courier", 12);
#else
    return QFont("Bitstream Vera Sans Mono", 9);
#endif

  return QsciLexerCPP::defaultFont(style);
}

// Returns the set of keywords.
const char *QsciLexerVB::keywords(int set) const {
  if (set != 1) return 0;

  return "AddHandler AddressOf Alias And AndAlso As Boolean ByRef Byte ByVal "
         "Call"
         "Case Catch CBool CByte CChar CDate CDec CDbl Char CInt"
         "Class CLng CObj Const Continue CSByte CShort CSng CStr CType CUInt"
         "CULng CUShort Date Decimal Declare Default Delegate Dim DirectCast Do"
         "Double Each Else ElseIf EndCase Catch CBool CByte CChar CDate "
         "CDec CDbl Char CInt EndIf Enum Erase Error Event"
         "Exit False Finally For Friend Function Get GetType GetXMLNamespace "
         "Global"
         "GoSub GoTo Handles If Implements Imports Imports In Inherits Integer"
         "Interface Is IsNot Let Lib Like Long Loop Me Mod"
         "Module MustInherit MustOverride MyBase MyClass Namespace Narrowing "
         "New Next Not"
         "Nothing NotInheritable NotOverridable Object Of On Operator Option "
         "Optional Or"
         "OrElse Overloads Overridable Overrides ParamArray Partial Private "
         "Property Protected Public"
         "RaiseEvent ReadOnly ReDim REM RemoveHandler Resume Return SByte "
         "Select Set Shadows"
         "Shared Short Single Static Step Stop String Structure Sub SyncLock"
         "Then Throw To True Try TryCast TypeOf Variant Wend UInteger"
         "ULong UShort Using When While Widening With WithEvents WriteOnly"
         "Xor #Const #Else #ElseIf #End #If = & &= * *= /"
         "/= \ \= ^ ^= + += - -= >> >>= << <<="
         "Aggregate Ansi Assembly Auto Compare Custom Distinct Equals Explicit "
         "From"
         "Group By Join Into IsFalse IsTrue Join Key Mid Off"
         "Order By Preserve Skip Skip While Strict Take Take While Text"
         "Unicode Until Where #ExternalSource #Region";
}

// Returns the user name of a style.
QString QsciLexerVB::description(int style) const {
  if (style == VerbatimString) return tr("Verbatim string");

  return QsciLexerCPP::description(style);
}

// Returns the background colour of the text for a style.
QColor QsciLexerVB::defaultPaper(int style) const {
  if (style == VerbatimString) return QColor(0xe0, 0xff, 0xe0);

  return QsciLexer::defaultPaper(style);
}
