#include "Widgets.hpp"

using namespace gw;

BusWidget::BusWidget()
  : QGraphicsRectItem(0, 0, 7, 47) 
{
  setBrush(m_brush);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsFocusable);
}
