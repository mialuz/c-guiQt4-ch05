#include <QtGui>

#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    setRange(0, 255);//设置默认范围0～255（0x00-0xFF）
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

//该函数执行从字符串到整数值的逆向转换
int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

//把一个整数值转换成一个字符串
QString HexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}
