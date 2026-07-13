#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QtWidgets>
#include "mainwindow.h"

#pragma once

struct help_s {
    int arity;
    const char *prim;
    const char *name;
    const char *title;
    const char *desc;
};

extern const help_s help[];
extern int symbolsCount();

class MainWindow;

class HelpWindow : public QMainWindow
{
  Q_OBJECT

public:
  HelpWindow (MainWindow *parent = nullptr);
  ~HelpWindow ();

private:
  MainWindow *mw;
  
protected:
  void closeEvent(QCloseEvent *event) override;
};

#endif // HELPWINDOW_H
