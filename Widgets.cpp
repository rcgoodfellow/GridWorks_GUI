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


BusWidget::~BusWidget()
{
  for(auto t : m_line_terminals)
  {
    if(t.second)
    {
      m_the_scene->removeItem(t.second);
      delete(t.second);
    }
  }
  m_line_terminals.clear();
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
        p.second->m_polyline.front() = sceneBoundingRect().center();
      }
      else
      {
        p.second->m_polyline.back() = sceneBoundingRect().center();
      }
    }
    m_the_scene->invalidate();
  }

  return QGraphicsItem::itemChange(change, value);
}

void BusWidget::removeLine(LineWidget* l)
{
  m_line_terminals.erase(
      std::remove_if(
        m_line_terminals.begin(), 
        m_line_terminals.end(),
        [l](const std::pair<WhichTerminal, LineWidget*> &elem)
        { 
          return elem.second == l; 
        }
      )
  );
}

LineWidget::LineWidget(QGraphicsScene *parent)
  : QAbstractGraphicsShapeItem(), m_the_scene{parent}
{
  //setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
  setBoundingRegionGranularity(0.75);
  setBrush(QBrush(Qt::transparent));
}

LineWidget::~LineWidget()
{
  inDestruction = true;
  m_Ta->removeLine(this);
  m_Tb->removeLine(this);
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

void LineWidget::removeWaypoint(size_t pos)
{
  if(inDestruction) { return; }
  m_polyline.erase(m_polyline.begin() + pos);

  for(auto *child : childItems())
  {
    Waypoint *wp = dynamic_cast<Waypoint*>(child);
    if(wp && wp->m_pos > pos) { (wp->m_pos)--; }

  }

  m_the_scene->invalidate();

}

Waypoint::Waypoint(LineWidget *lw, size_t pos)
  : QGraphicsRectItem(-3, -3, 6, 6, lw), m_the_line{lw}, m_pos{pos}
{
  setBrush(m_brush);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

  setZValue(5);
}

Waypoint::~Waypoint()
{
  if(m_the_line)
  {
    m_the_line->removeWaypoint(m_pos);
  }
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
