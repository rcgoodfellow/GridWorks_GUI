#ifndef GW_GRIDWINDOW
#define GW_GRIDWINDOW

#include "GridScene.hpp"

#pragma clang_diagnostic push
#pragma clang_diagnostic ignored "-Wdeprecated"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QAction>
#include <QToolBar>
#pragma clang_diagnostic pop

#include <iostream>

namespace gw
{

  class MainWindow : public QMainWindow
  {
    Q_OBJECT

    GridScene *m_scene;
    QGraphicsView *m_scene_view;
    QButtonGroup *m_button_group;
    QToolBar *m_toolbar;
    QAction *m_newBusAct;
    QAction *m_newLineAct;
    QAction *m_newTfmrAct;
    QAction *m_newGenAct;
    QAction *m_newLoadAct;
    QVBoxLayout *m_layout;



    private slots:
      void onNewBus();
      void onNewLine();
      void onNewTfrm();
      void onNewGen();
      void onNewLoad();

    private:
      void CreateToolBar();

    public:
      MainWindow();
  };
}

#endif
