#include <QtGui>

#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);// 告诉布局管理器，理想尺寸是它的最小尺寸，不能对它缩小！  
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);  //窗口部件大小策略

    curColor = Qt::black;
    zoom = 8;// 一个像素将显示成一个8x8的正方形 

    image = QImage(16, 16, QImage::Format_ARGB32);  //初始化为16×16的像素大小和32位的ARGB颜色格式
    image.fill(qRgba(0, 0, 0, 0)); //填充透明颜色，清空image中的数据
}

//设置画笔的当前颜色
void IconEditor::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

//设置图像的缩放因子
void IconEditor::setZoomFactor(int newZoom)
{
    if (newZoom < 1)
        newZoom = 1;

    if (newZoom != zoom) {
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

//设置需要编辑的图像
void IconEditor::setIconImage(const QImage &newImage)
{
    if (newImage != image) {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update(); //使用新的图像强制重绘这个窗口部件
        updateGeometry();
    }
}

//返回一个窗口部件的理想大小
QSize IconEditor::sizeHint() const
{
    //用缩放因子乘以图像的尺寸大小作为这个窗口部件的理想大小
    QSize size = zoom * image.size();
    if (zoom >= 3)
        size += QSize(1, 1);
    return size;
}

//鼠标按下 事件
void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

//鼠标移动 事件
void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

//一个事件处理器
void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (zoom >= 3) {
        painter.setPen(palette().foreground().color());//设置线段的颜色
        for (int i = 0; i <= image.width(); ++i)
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        for (int j = 0; j <= image.height(); ++j)
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
    }

    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            QRect rect = pixelRect(i, j);//返回一个QRect 其中定义了需要重新绘制的区域
            if (!event->region().intersect(rect).isEmpty()) {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255)
                    painter.fillRect(rect, Qt::white);
                painter.fillRect(rect, color);
            }
        }
    }
}

//用来设置或者清空一个像素，pos参数是鼠标在窗口部件中的位置
void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    //把鼠标的位置从窗口不见的坐标转换到图像坐标
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j)) {
        if (opaque) {                    //根据参数opaque判断是设置还是清空图像中的像素
            image.setPixel(i, j, penColor().rgba());
        } else {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom >= 3) {
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    } else {
        return QRect(zoom * i, zoom * j, zoom, zoom);
    }
}
