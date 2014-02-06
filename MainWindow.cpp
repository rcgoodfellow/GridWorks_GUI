#include "MainWindow.hpp"

#include <fstream>

using namespace gw;

MainWindow::MainWindow()
{
  initWindow();
  createToolBar();
  createMainViewer();
  setStyle();
}

void MainWindow::initWindow()
{
  m_central_widget = new QWidget;
  m_layout = new QVBoxLayout;
  m_central_widget->setLayout(m_layout);
  setCentralWidget(m_central_widget);
  setWindowTitle(tr("GridScene"));
  setUnifiedTitleAndToolBarOnMac(true);
}

void
MainWindow::createMainViewer()
{
  m_scene = new GridScene(this);
  m_scene_view = new QGraphicsView(m_scene);
  m_scene_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  m_scene_view->setRenderHints(QPainter::Antialiasing);

  m_layout->addWidget(m_scene_view);
}

void MainWindow::setStyle()
{
  setStyleSheet("background: rgba(15, 15, 15, 235);");
  setAttribute(Qt::WA_TranslucentBackground);
  
  m_scene_view->setBackgroundBrush(QColor::fromRgbF(0.17, 0.17, 0.17, 0.1));
  
  m_toolbar->setStyleSheet(
      "QToolButton{ border: 1px solid rgb(255, 255, 255); } "
      "background:transparent; border:1px solid rgb(255, 255, 255);");
}

void MainWindow::onNewBus()
{
  m_scene->transitionClickState<CS_Insert>();
  m_scene->transitionInsertState<IS_Bus>();
}

void MainWindow::onNewLine() 
{
  m_scene->transitionClickState<CS_Insert>();
  m_scene->transitionInsertState<IS_Line>();
}
void MainWindow::onNewTfmr() {}
void MainWindow::onNewGen() {}
void MainWindow::onNewLoad() {}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
  if(e->key() == Qt::Key_Escape) { m_scene->transitionClickState<CS_Select>(); }
}


void MainWindow::createToolBar()
{
  m_button_group = new QButtonGroup(this);
  m_button_group->setExclusive(false);

  m_newBusAct = new QAction(QIcon(":Art/bus_ico.png"), tr("&Bus"), this);
  m_newBusAct->setStatusTip(tr("Create New Bus"));
  connect(m_newBusAct, SIGNAL(triggered()), this, SLOT(onNewBus()));

  m_newLineAct = new QAction(QIcon(":Art/line_ico.png"), tr("&Line"), this);
  m_newLineAct->setStatusTip(tr("Create New Line"));
  connect(m_newLineAct, SIGNAL(triggered()), this, SLOT(onNewLine()));
  
  m_newTfmrAct = new QAction(QIcon(":Art/tfmr_ico.png"), tr("&Transformer"), this);
  m_newTfmrAct->setStatusTip(tr("Create New Transformer"));
  connect(m_newTfmrAct, SIGNAL(triggered()), this, SLOT(onNewTfmr()));

  m_toolbar = new QToolBar(tr("Create")); //addToolBar(tr("Create"));
  m_toolbar->addAction(m_newBusAct);
  m_toolbar->addAction(m_newLineAct);
  m_toolbar->addAction(m_newTfmrAct);
  m_toolbar->setMovable(false);
  
  m_layout->addWidget(m_toolbar);
}

int main(int argc, char **argv)
{
  Q_INIT_RESOURCE(icons);

  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.setGeometry(100,100, 1100, 700);
  mainWindow.show();
  return app.exec();
}
