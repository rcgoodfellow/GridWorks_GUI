#ifndef GW_GRIDWINDOW
#define GW_GRIDWINDOW

#include "GridScene.hpp"

#pragma clang_diagnostic push
#pragma clang_diagnostic ignored "-Wdeprecated"
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QButtonGroup>
#include <QAction>
#include <QToolBar>
#include <QKeyEvent>
#pragma clang_diagnostic pop

#include <iostream>

namespace gw
{

  class MainWindow : public QMainWindow
  {
    Q_OBJECT

    QVBoxLayout *m_layout;
    QWidget *m_central_widget;

    //Viewer
    QGraphicsView *m_scene_view;
    GridScene *m_scene;

    //Toolbar
    QButtonGroup *m_button_group;
    QToolBar *m_toolbar;
    QAction *m_newBusAct;
    QAction *m_newLineAct;
    QAction *m_newTfmrAct;
    QAction *m_newGenAct;
    QAction *m_newLoadAct;

    std::string m_stylesheet;

    private slots:
      void onNewBus();
      void onNewLine();
      void onNewTfmr();
      void onNewGen();
      void onNewLoad();

    private:
      void initWindow();
      void createToolBar();
      void createMainViewer();
      void setStyle();

    protected:
      void keyPressEvent(QKeyEvent *e);

    public:
      MainWindow();

      void handleDeleteRequest();
  };
}

#endif
