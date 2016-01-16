#include <QtPlugin>

#include "../iconeditor/iconeditor.h"
#include "iconeditorplugin.h"

//构造函数
    IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject(parent)
{
}

//那么
//
//name函数返回由该插件提供的这个窗口部件的名字
QString IconEditorPlugin::name() const
{
    return "IconEditor";
}

//includeFile函数返回该插件封装的特定窗口不见的头文件的名称
QString IconEditorPlugin::includeFile() const
{
    return "iconeditor.h";
}

//group函数返回自定义窗口所应属于的窗口不仅工具箱群组的名字
QString IconEditorPlugin::group() const
{
    return tr("Image Manipulation Widgets");
}

//icon函数返回一个图标，可以在Qt设计师窗口部件工具箱中用它来代表自定义窗口部件
QIcon IconEditorPlugin::icon() const
{
    return QIcon(":/images/iconeditor.png");
}

//toolTip函数返回一个工具提示信息，可在鼠标悬停在Qt设计师窗口部件工具箱中的自定义窗口部件上时显示该信息
QString IconEditorPlugin::toolTip() const
{
    return tr("An icon editor widget");
}

//whatsthis函数返回用于Qt设计师“what's this?”中显示的文本
QString IconEditorPlugin::whatsThis() const
{
    return tr("This widget is presented in Chapter 5 of <i>C++ GUI "
              "Programming with Qt 4</i> as an example of a custom Qt "
              "widget.");
}

//判断该窗口部件是否还可以包含其他窗口部件
bool IconEditorPlugin::isContainer() const
{
    return false;
}

//利用给定的父对象创建该窗口部件类的一个实例
QWidget *IconEditorPlugin::createWidget(QWidget *parent)
{
    return new IconEditor(parent);
}

//宏调用，必须有，第一个参数希望给插件的名字，第二个参数是实现该插件类的名字
Q_EXPORT_PLUGIN2(iconeditorplugin, IconEditorPlugin)
