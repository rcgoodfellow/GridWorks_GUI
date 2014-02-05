#ifndef GW_GRIDSCENE
#define GW_GRIDSCENE

#pragma clang_diagnostic push
#pragma clang_diagnostic ignored "-Wdeprecated"
#include <QGraphicsScene>
#pragma clang_diagnostic pop

#include "Widgets.hpp"

namespace gw
{
  class GridScene : public QGraphicsScene
  {
    Q_OBJECT

    public:
      GridScene(QObject *parent = nullptr);
    
      enum class ClickState { Select, Pan, Insert };
      enum class InsertState { Bus, Line, Transformer };
      ClickState click_state;
      InsertState insert_state;

    protected:
      void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    private:
      QBrush m_brush{QColor::fromRgbF(0.47, 0.47, 0.47)};
      void handleInsert(QGraphicsSceneMouseEvent *mouseEvent);


  };
}

#endif
