#include "GridScene.hpp"

using namespace gw;

GridSceneState::GridSceneState(GridScene *gs)
  : scene{gs} {}

GridScene::GridScene(QMainWindow *parent)
  : QGraphicsScene(parent), m_window{parent}
{
  m_click_state = new CS_Select{this};
  m_insert_state = new IS_Bus{this};
}

void CS_Select::init()
{
  scene->m_window->setCursor(Qt::ArrowCursor);

  selectionRect = new QGraphicsRectItem;
  selectionRect->setVisible(false);
  selectionRect->setBrush(QColor::fromRgbF(1.0, 1.0, 1.0, 0.15));
  selectionRect->setPen(
      QPen(QColor::fromRgbF(1.0, 1.0, 1.0, 0.90),
           1.0, Qt::DotLine)
      );
  selectionRect->setZValue(100);
  
  scene->addItem(selectionRect);
}

void
CS_Select::handleClick(QGraphicsSceneMouseEvent *e) 
{ 
  QTransform id;

  GWidget *w = dynamic_cast<GWidget*>(
      scene->itemAt(e->scenePos(), id)
      );

  if(!w)
  {
    dragging = true;
    s0 = s1 = e->scenePos();
    selectionRect->setRect(QRectF{s0, s1});
    selectionRect->setVisible(true);
    scene->invalidate();
  }
}

void
CS_Select::handleRelease(QGraphicsSceneMouseEvent *e) 
{
  dragging = false;
  s1 = e->scenePos();
  selectionRect->setVisible(false);
  scene->invalidate();

  QTransform ident;
  QPainterPath pth;
  pth.addRect(selectionRect->rect());

  scene->setSelectionArea(pth , ident);
}
   
#include <iostream>
void 
CS_Select::handleMove(QGraphicsSceneMouseEvent *e)
{
  if(dragging)
  {
    s1 = e->scenePos();
    selectionRect->setRect(QRectF{s0, s1});
    scene->invalidate();
  }
}

void CS_Insert::init()
{
  scene->m_window->setCursor(Qt::CrossCursor);
}


void CS_Insert::handleClick(QGraphicsSceneMouseEvent *e)
{
  scene->m_insert_state->handleInsert(e->scenePos());  
}

void
CS_Insert::handleRelease(QGraphicsSceneMouseEvent *e) {};

void IS_Bus::init() { }

void IS_Bus::handleInsert(QPointF p)
{
  BusWidget *bp = new BusWidget(scene);
  scene->addItem(bp);
  bp->setPos(p);

  scene->transitionClickState<CS_Select>();
}

void IS_Line::init() { }

#include <iostream>
void IS_Line::handleInsert(QPointF p)
{

  QGraphicsItem *i{nullptr};
  BusWidget *b{nullptr};
  Waypoint *wp{nullptr};
  QTransform identity;

  if(!theLine)
  {
    i = scene->itemAt(p, identity);
    b = dynamic_cast<BusWidget*>(i);
    
    if(!b) 
    { 
      std::cerr << "Bad line start point" << std::endl; 
      scene->transitionClickState<CS_Select>();
    }

    theLine = new LineWidget{scene};
    theLine->m_Ta = b;
    theLine->m_polyline.append(p);
    scene->addItem(theLine);

    b->m_line_terminals.push_back(
        {BusWidget::WhichTerminal::Front, theLine}
        );

    return;
  }

  theLine->m_polyline.append(p);
  scene->invalidate();

  i = scene->itemAt(p, identity);
  b = dynamic_cast<BusWidget*>(i);
  if(b) { 
    scene->transitionClickState<CS_Select>(); 
    b->m_line_terminals.push_back(
        {BusWidget::WhichTerminal::Back, theLine}
        );
    theLine->m_Tb = b;
    return;
  }
  
  wp = new Waypoint(theLine, theLine->m_polyline.size() - 1);
  wp->setPos(p);
  //We dont need to do this since the waypoints parent is already in the
  //scene the waypoint gets added automagically
  //scene->addItem(wp);
  
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  m_click_state->handleClick(mouseEvent);

  QGraphicsScene::mousePressEvent(mouseEvent);
}

void GridScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  m_click_state->handleRelease(mouseEvent);

  QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  m_click_state->handleMove(mouseEvent);

  QGraphicsScene::mouseMoveEvent(mouseEvent);
}
