#ifndef GW_GRIDSCENE
#define GW_GRIDSCENE

#pragma clang_diagnostic push
#pragma clang_diagnostic ignored "-Wdeprecated"
#include <QGraphicsScene>
#include <QMainWindow>
#pragma clang_diagnostic pop

#include "Widgets.hpp"

namespace gw
{
  class GridScene;

  struct GridSceneState
  {
    GridScene *scene;
    GridSceneState(GridScene*);

    virtual void init() = 0;
  };

  class ClickState : public GridSceneState
  {
    public:
      using GridSceneState::GridSceneState;

      virtual void handleClick(QGraphicsSceneMouseEvent*) = 0;
  };

  struct CS_Select : public ClickState
  {
    using ClickState::ClickState;
    virtual void init();
    virtual void handleClick(QGraphicsSceneMouseEvent*);
  };

  struct CS_Insert : public ClickState
  {
    using ClickState::ClickState;
    virtual void init();
    virtual void handleClick(QGraphicsSceneMouseEvent*);
  };
      

  class InsertState : public GridSceneState
  {
    public:
      using GridSceneState::GridSceneState;
      virtual void handleInsert(QPointF) = 0;
  };

  struct IS_Bus : public InsertState
  {
    using InsertState::InsertState;
    virtual void init();
    virtual void handleInsert(QPointF);
  };

  struct IS_Line : public InsertState
  {
    using InsertState::InsertState;
    virtual void init();
    virtual void handleInsert(QPointF);
    LineWidget *theLine{nullptr};
  };

  class GridScene : public QGraphicsScene
  {
    Q_OBJECT

    public:

      GridScene(QMainWindow *parent = nullptr);
   
      template <class T>
      void transitionClickState()
      {
        m_click_state = new T{this}; 
        m_click_state->init();
      }

      template <class T>
      void transitionInsertState()
      {
        m_insert_state = new T{this}; 
        m_insert_state->init();
      }
      
      ClickState *m_click_state;
      InsertState *m_insert_state;
      QMainWindow *m_window;

    protected:
      void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    private:

      QBrush m_brush{QColor::fromRgbF(0.47, 0.47, 0.47)};
      //void handleInsert(QGraphicsSceneMouseEvent *mouseEvent);

  };
}

#endif
