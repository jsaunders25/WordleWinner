#include "WordleEdit.h"

WordleEdit::WordleEdit()
{
    setMaximumWidth(30);
    setMaxLength(1);
    QFont font = this->font();
    font.setPointSize(14);
    setFont(font);
    connect(this, &WordleEdit::textEdited, this, &WordleEdit::validateText);
}

void WordleEdit::takeFocus()
{
    setFocus();
    selectAll();
}

void WordleEdit::capitalize(const QString str)
{
    if(!str.isEmpty())
    {
        setText(str.toUpper());
        emit doneSignal();
    }
}

/**
 * @brief WordleEdit::validateText
 * Ensure <str> isn't a number.
 * @param str
 */
void WordleEdit::validateText(const QString str)
{
    bool ok;
    str.toInt(&ok);
    ok ? clear() : capitalize(str);
}
