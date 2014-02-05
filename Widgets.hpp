#ifndef GW_WIDGETS
#define GW_WIDGETS

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

namespace gw
{
  class BusWidget : public QGraphicsRectItem
  {
    QBrush m_brush{QColor::fromRgbF(0.47, 0.47, 0.47)};
    public:
      BusWidget();
  };

}

#endif
