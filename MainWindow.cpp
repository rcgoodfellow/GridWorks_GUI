#include "MainWindow.hpp"


using namespace gw;


MainWindow::MainWindow()
{
  m_scene = new GridScene(this);
  //m_scene->addText("GridScene");

  setStyleSheet("background: rgba(15, 15, 15, 235);");
  setAttribute(Qt::WA_TranslucentBackground);

  QVBoxLayout *layout = new QVBoxLayout;
  m_scene_view = new QGraphicsView(m_scene);
  m_scene_view->setBackgroundBrush(QColor::fromRgbF(0.17, 0.17, 0.17, 0.1));

  QWidget *widget = new QWidget;
  widget->setLayout(layout);

  setCentralWidget(widget);
  setWindowTitle(tr("GridScene"));
  setUnifiedTitleAndToolBarOnMac(true);

  CreateToolBar();
  m_toolbar->setStyleSheet("background:transparent;");
  m_toolbar->setStyleSheet(
      "QToolButton{ border: 1px solid rgb(255, 255, 255); } "
      "background:transparent; border:1px solid rgb(255, 255, 255);");
  layout->addWidget(m_toolbar);
  layout->addWidget(m_scene_view);

  //m_scene->setSceneRect(m_scene_view->rect());
  m_scene_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void MainWindow::onNewBus()
{
  std::cout << "New Bus Requested" << std::endl;

  //m_scene->addItem(new BusWidget());

  m_scene->click_state = GridScene::ClickState::Insert;
  m_scene->insert_state = GridScene::InsertState::Bus;
}

void MainWindow::onNewLine() {}
void MainWindow::onNewTfrm() {}
void MainWindow::onNewGen() {}
void MainWindow::onNewLoad() {}

void MainWindow::CreateToolBar()
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
