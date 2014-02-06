#include "Widgets.hpp"

using namespace gw;

BusWidget::BusWidget(QGraphicsScene *theScene)
  : QGraphicsRectItem(0, 0, 7, 47), m_the_scene{theScene}
{
  setBrush(m_brush);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

  setZValue(10);
}

#include <iostream>
QVariant BusWidget::itemChange(GraphicsItemChange change, const QVariant &value)
{
  //std::cout << "bus changed" << std::endl;
  //std::cout << change << std::endl;
  if(change == ItemPositionHasChanged)
  {
    //std::cout << "bus moved" << std::endl;
    QPointF newPos = value.toPointF();
    for(auto p : m_line_terminals)
    {
      if(p.first == Front)
      {
        p.second->front() = sceneBoundingRect().center();
      }
      else
      {
        p.second->back() = sceneBoundingRect().center();
      }
    }
  }
  m_the_scene->invalidate();

  return QGraphicsItem::itemChange(change, value);
}

LineWidget::LineWidget(QGraphicsScene *parent)
  : QGraphicsPathItem() /*QAbstractGraphicsShapeItem()*/, m_the_scene{parent}
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
  //setFlag(QGraphicsItem::ItemClipsToShape);
  setBoundingRegionGranularity(1);
  setBrush(QBrush(Qt::transparent));
}

QRectF LineWidget::boundingRect() const
{
  return m_polyline.boundingRect();
}

void LineWidget::paint(QPainter *painter, 
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
  QPen pen{};
  pen.setWidth(2);
  pen.setColor(QColor(205, 205, 205));
  painter->setPen(pen);
  painter->drawPolyline(m_polyline);
}

QPainterPath LineWidget::shape() const
{
  QPainterPath path;
  /*
  path.moveTo(m_polyline.first());
  for(auto p = m_polyline.begin()+1; p != m_polyline.end(); ++p)
  {
    path.lineTo(*p);
  }
  */
  path.addPolygon(m_polyline);
  QPainterPathStroker stroker;

  return stroker.createStroke(path);
}
