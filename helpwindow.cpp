#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "mainwindow.h"
#include "helpwindow.h"

#define help_def(ar, prim, name, title, descr) \
  {ar, prim, name, title, descr},

// src/Help.def comes from gnu-apl source tree
const help_s help[] = {
#include "src/Help.def"
};

int symbolsCount() {
  return (int)sizeof(help)/sizeof(help_s);
}

void
HelpWindow::closeEvent(QCloseEvent *event __attribute__((unused)))
{
  mw->closeHW();
  delete this;
}

HelpWindow::HelpWindow(MainWindow *parent)
  : QMainWindow(parent)
{
  this->setWindowTitle("qapl Symbols Help");
  mw = parent;
  QWidget* hw = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout;
  this->setCentralWidget(hw);
  
  const int rowCount = symbolsCount();
  QTableWidget* table = new QTableWidget(rowCount, 2, this);
  table->setShowGrid(false);
  //  QStringList headers = {"Symbol", "Name", "Title", "Description"};
  const QStringList headers = {"Name (Arity)", "Description"};
  table->setHorizontalHeaderLabels(headers);
  
  for (int i = 0; i < rowCount; i++) {
    //  for (int i = 0; i < 10; i++) {
#if 0
    QTableWidgetItem *arityItem
      = new QTableWidgetItem (QString::number (help[i].arity));
    table->setItem (i, 0, arityItem);
#endif

    QTableWidgetItem* primItem
      = new QTableWidgetItem(QString(help[i].prim));
    primItem->setTextAlignment(Qt::AlignCenter);
#if 1
    table->setVerticalHeaderItem(i, primItem);
#else
    table->setItem (i, 0, primItem);
#endif
    
    QTableWidgetItem* nameItem
      = new QTableWidgetItem(QString(help[i].name) + " (" + QString::number(help[i].arity) + ")");
    table->setItem(i, 0, nameItem);
    
    QTableWidgetItem* titleItem
      = new QTableWidgetItem(QString(help[i].title));
    table->setItem(i, 1, titleItem);

#if 0
    QTableWidgetItem *descItem
      = new QTableWidgetItem (QString (help[i].desc));
    table->setItem (i, 3, descItem);
#endif
  }

  table->resizeColumnsToContents();
  table->horizontalHeader()->setSectionResizeMode(
    QHeaderView::ResizeToContents);
  table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
  table->setMinimumHeight(600);
  layout->addWidget(table);

  hw->setLayout(layout);
  this->show();
}

HelpWindow::~HelpWindow()
{
}

