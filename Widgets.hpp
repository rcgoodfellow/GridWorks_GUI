#ifndef GW_WIDGETS
#define GW_WIDGETS

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

namespace gw
{
  class BusWidget : public QGraphicsRectItem
  {
    QBrush m_brush{QColor::fromRgbF(0.47, 0.47, 0.47)};
    public:
      BusWidget(QGraphicsScene*);
      QVariant itemChange(GraphicsItemChange, const QVariant&);

      enum WhichTerminal { Front, Back };
      std::vector<std::pair<WhichTerminal, QPolygonF*>> m_line_terminals;

      QGraphicsScene *m_the_scene;
  };

  class LineWidget : public QAbstractGraphicsShapeItem
  {
    public:
      using QAbstractGraphicsShapeItem::QAbstractGraphicsShapeItem;
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget = nullptr);

      QPolygonF m_polyline;

  };
}

#endif
