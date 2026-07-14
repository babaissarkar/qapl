#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCommandLineParser>
#include <QFileSystemWatcher>
#include <QLineEdit>
#include <QMainWindow>
#include <QSettings>
#include <QTemporaryDir>
#include <QTextEdit>

#include "history.h"
#include "helpwindow.h"
#include "enums.h"

#define toCString(v)       ((v).toStdString ().c_str ())

#define APPLICATION_ORGANISATION   "qapl"
#define APPLICATION_NAME           "qapl"
#define APPLICATION_VERSION        "1.0"

#define DEFAULT_EDITOR \
   "emacs --geometry=40x20  -background '#ffffcc' -font \"APL385 Unicode-12\""

#define DEFAULT_GVIM_EDITOR \
   "gvim -geometry=40x20  -background '#ffffcc' -font \"APL385 Unicode-12\""

#if 0
#define DEFAULT_SLICK_EDITOR "/opt/slickedit-pro2020/bin/vs -q"
#endif

#define DEFAULT_FONT_FAMILY "APL385 Unicode"
#define DEFAULT_FONT_SIZE   12.0
#define DEFAULT_BG_COLOUR   "#f4f4d3"	// pale yellow
#define DEFAULT_FG_COLOUR   "#000000"	// black
#define DEFAULT_HEIGHT      600
#define DEFAULT_WIDTH       1000

typedef enum {
  SAVE_MODE_NONE,
  SAVE_MODE_SAVE,
  SAVE_MODE_DUMP,
  SAVE_MODE_OUT
} save_mode_e;

class MainWindow;
class HelpWindow;

class InputLineFilter : public QObject
{
    Q_OBJECT

public:
  InputLineFilter (QLineEdit *obj, MainWindow *mw)
  {watched = obj; mainwin = mw;}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
  MainWindow    *mainwin;
  QLineEdit     *watched;
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public slots:
  void inputLineReturn ();

public:
  MainWindow(QCommandLineParser &parser, QWidget *parent = nullptr);
  ~MainWindow();
  void createMenubar ();
  void update_screen (QString &errString, QString &outString);
  void processLine (bool suppressOppressOutput, QString text);
  void readScript (QString pfn, bool &noCONT, bool &noSETUP);
  void readScript (QString pfn);
  QStringList parseCl (QString str);
  void printError (QString emsg, QString estr);
  void printError (QString emsg);
  void closeHW () { HWopen = false; }
  QSettings *getSettings () { return settings; }
  void importChart ();

  QLineEdit *inputLine;
  QTextEdit *outputLog;
  History   *history;

private slots:
  void fileChanged(const QString &path);
  void byebye ();

private:
  void               show_fcn (QString text);
  void               edit_fcn (QString text);
  void               wsLoad ();
  bool               wsSave ();
  bool               wsSaveAs ();
  void               setEditor ();
  void               setFont ();
  void               setBGColour ();
  void               setFGColour ();
  void               setColours ();
  void               symbolsHelp ();
  void               aboutHelp ();
  void               plot2d ();
  void               killTempdir ();
  InputLineFilter   *inputLineFilter;
  QString            editor;
  int                editorIndex;
  QStringList	     extraEditors;
  QTemporaryDir      tempdir;
  QFileSystemWatcher watcher;
  QSettings         *settings;
  QColor             bgColour;
  QColor             fgColour;
  QVector<qint64>    processList;
  QString            libpath;
  save_mode_e        save_mode;
  QString            currentAPLFile;
  bool               HWopen;
  bool               doTrace;
  
protected:
  void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
