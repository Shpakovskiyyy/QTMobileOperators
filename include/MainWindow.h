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
    ~MainWindow() = default;

private:
    void setupModel();

private:
    std::shared_ptr<Ui::MainWindow> ui;

private:
    std::shared_ptr<QTreeView> treeView;
    std::shared_ptr<QStandardItemModel> model;
    std::shared_ptr<IconDelegate> iconDelegate;

};
#endif // MAINWINDOW_H
