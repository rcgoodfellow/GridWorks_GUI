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
}

void
CS_Select::handleClick(QGraphicsSceneMouseEvent *e) { }

void CS_Insert::init()
{
  scene->m_window->setCursor(Qt::CrossCursor);
}

void CS_Insert::handleClick(QGraphicsSceneMouseEvent *e)
{
  scene->m_insert_state->handleInsert(e->scenePos());  
}

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
    theLine->m_polyline.append(p);
    scene->addItem(theLine);

    b->m_line_terminals.push_back(
        {BusWidget::WhichTerminal::Front, &theLine->m_polyline}
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
        {BusWidget::WhichTerminal::Back, &theLine->m_polyline}
        );
  }


  
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  m_click_state->handleClick(mouseEvent);

  QGraphicsScene::mousePressEvent(mouseEvent);
}
