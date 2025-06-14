#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTreeView;
class QStandardItemModel;
class IconDelegate;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupModel();

private:
    Ui::MainWindow *ui;

private:
    QTreeView* treeView;
    QStandardItemModel* model;
    IconDelegate* iconDelegate;

};
#endif // MAINWINDOW_H
