#include "GridScene.hpp"

using namespace gw;

GridScene::GridScene(QObject *parent)
  : QGraphicsScene(parent)
{
}

void
GridScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  switch(click_state)
  {
    case ClickState::Insert : 
      handleInsert(mouseEvent); 
      click_state = ClickState::Select;
      break; 
  }

  QGraphicsScene::mousePressEvent(mouseEvent);
}

void
GridScene::handleInsert(QGraphicsSceneMouseEvent *mouseEvent)
{
  switch(insert_state)
  {
    case InsertState::Bus :
      BusWidget *bw = new BusWidget();
      addItem(bw);
      bw->setPos(mouseEvent->scenePos());
      break;
  }
}
