#include "GridScene.hpp"

using namespace gw;

GridSceneState::GridSceneState(GridScene *gs)
  : scene{gs} {}

GridScene::GridScene(QObject *parent)
  : QGraphicsScene(parent)
{
  m_click_state = new CS_Select{this};
  m_insert_state = new IS_Bus{this};
}

void
CS_Select::init()
{

}

void
CS_Select::handleClick(QGraphicsSceneMouseEvent *e)
{

}

void
CS_Insert::init()
{

}

#include <iostream>
void
CS_Insert::handleClick(QGraphicsSceneMouseEvent *e)
{
  std::cout << "1" << std::endl;
  scene->m_insert_state->handleInsert(e->pos());  
}

void
IS_Bus::init()
{

}

void
IS_Bus::handleInsert(QPointF p)
{
  BusWidget *bp = new BusWidget();
  scene->addItem(bp);
  bp->setPos(p);
  std::cout << "2" << std::endl;
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  /*
  switch(m_click_state)
  {
    case ClickState::Insert : 
      handleInsert(mouseEvent); 
      m_click_state = ClickState::Select;
      break; 
  }
  */
  
  std::cout << "0" << std::endl;
  m_click_state->handleClick(mouseEvent);

  QGraphicsScene::mousePressEvent(mouseEvent);
}

void GridScene::handleInsert(QGraphicsSceneMouseEvent *mouseEvent)
{
  /*
  switch(m_insert_state)
  {
    case InsertState::Bus :
      BusWidget *bw = new BusWidget();
      addItem(bw);
      bw->setPos(mouseEvent->scenePos());
      break;
  }
  */
  m_insert_state->handleInsert(mouseEvent->scenePos());
}

/*
void GridScene::setClickState(ClickState cs) 
{ 
  m_click_state = cs;

}

void GridScene::setInsertState(InsertState is)
{
  m_insert_state = is;
}
*/
