#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "player.h"
#include "enums.h"

class QLabel;
class Game;
class ChessBoardWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_action2_Player_triggered();
    void on_actionWhite_vs_PC_triggered();
    void on_actionBlack_vs_PC_triggered();

    void activePlayerChanged(Player player);
    void gameStateChanged(GameState state);

private:
    Ui::MainWindow *ui;
    QLabel *playerLabel;
    QLabel *stateLabel;
    ChessBoardWidget *cbw;
};

#endif // MAINWINDOW_H
