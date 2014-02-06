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
        p.second->pop_front();
        p.second->push_front(sceneBoundingRect().center());
      }
      else
      {
        p.second->pop_back();
        p.second->push_back(sceneBoundingRect().center());
      }
    }
  }
  m_the_scene->invalidate();

  return QGraphicsItem::itemChange(change, value);
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
