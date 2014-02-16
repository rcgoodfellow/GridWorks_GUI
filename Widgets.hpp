#ifndef GW_WIDGETS
#define GW_WIDGETS

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

namespace gw
{
  class GWidget {};

  class LineWidget;

  class BusWidget : public GWidget, public QGraphicsRectItem
  {
    public:
      BusWidget(QGraphicsScene*);
      virtual ~BusWidget();
      QVariant itemChange(GraphicsItemChange, const QVariant&);

      enum WhichTerminal { Front, Back };
      std::vector<std::pair<WhichTerminal, LineWidget*>> m_line_terminals;
      void removeLine(LineWidget*);

      QGraphicsScene *m_the_scene;
      QBrush m_brush{QColor::fromRgbF(0.47, 0.47, 0.47)};
  };

  class Waypoint;

  class LineWidget : public GWidget, public QAbstractGraphicsShapeItem
  {
    public:
      LineWidget(QGraphicsScene*);
      virtual ~LineWidget();
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget = nullptr);
      QPainterPath shape() const;
      void removeWaypoint(size_t pos);

      QPolygonF m_polyline;
      QGraphicsScene *m_the_scene;
      BusWidget *m_Ta, *m_Tb;
      bool inDestruction{false};

  };
  
  class Waypoint : public GWidget, public QGraphicsRectItem
  {
    public:
      Waypoint(LineWidget*, size_t pos);
      virtual ~Waypoint();
      QVariant itemChange(GraphicsItemChange, const QVariant&);
    
      LineWidget *m_the_line; 
      QBrush m_brush{QColor::fromRgbF(0.47, 0.47, 0.97)};
      size_t m_pos;
  };
}

#endif
