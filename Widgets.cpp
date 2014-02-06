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
  if(change == ItemPositionHasChanged)
  {
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
    m_the_scene->invalidate();
  }

  return QGraphicsItem::itemChange(change, value);
}

LineWidget::LineWidget(QGraphicsScene *parent)
  : QAbstractGraphicsShapeItem(), m_the_scene{parent}
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
  setBoundingRegionGranularity(0.75);
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
  path.addPolygon(m_polyline);
  QPainterPathStroker stroker;

  return stroker.createStroke(path);
}

Waypoint::Waypoint(LineWidget *lw, size_t pos)
  : QGraphicsRectItem(-3, -3, 6, 6), m_the_line{lw}, m_pos{pos}
{
  setBrush(m_brush);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

  setZValue(5);
}

QVariant Waypoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if(change == ItemPositionHasChanged)
  {
    m_the_line->m_polyline[m_pos] = sceneBoundingRect().center();
    m_the_line->m_the_scene->invalidate();
  }

  return QGraphicsItem::itemChange(change, value);
}
