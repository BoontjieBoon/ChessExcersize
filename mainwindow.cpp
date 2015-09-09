#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QSize>

#include "game.h"
#include "piece.h"
#include "chessboardwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // setup ui developed in Qt designer
    ui->setupUi(this);

    // instantiate ui elements
    cbw = new ChessBoardWidget(this, QSize(800, 800));
    playerLabel = new QLabel("White's turn");
    stateLabel = new QLabel("Normal");

    // lay out labels horozontally
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(playerLabel);
    labelLayout->addWidget(stateLabel);

    // lay out chess board and labels vertically
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(cbw);
    mainLayout->addLayout(labelLayout);

    // apply layout to central ui widget
    ui->centralWidget->setLayout(mainLayout);

    // set window title and size
    setWindowTitle("Chess Exercise!");
    setFixedSize(sizeHint());

    // hook up chess board signals
    connect(cbw, SIGNAL(squareClicked(int, int)), this, SLOT(boardSquareClicked(int, int)));
    connect(cbw, SIGNAL(stateChanged(GameState)), this, SLOT(gameStateChanged(GameState)));
    connect(cbw, SIGNAL(activePlayerChanged(Player)), this, SLOT(activePlayerChanged(Player)));
}

MainWindow::~MainWindow()
{
    // Qt widgets automatically delete all children
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_action2_Player_triggered()
{
    cbw->reset(HUMAN, HUMAN);
}

void MainWindow::on_actionWhite_vs_PC_triggered()
{
    cbw->reset(HUMAN, COMPUTER);
}

void MainWindow::on_actionBlack_vs_PC_triggered()
{
    cbw->reset(COMPUTER, HUMAN);
}

void MainWindow::activePlayerChanged(Player player)
{
    // display text on UI to indicate current active player
    switch (player.getSide()) {
    case WHITE:
        playerLabel->setText("White's turn");
        break;
    case BLACK:
        playerLabel->setText("Black's turn");
        break;
    default:
        break;
    }
}

void MainWindow::gameStateChanged(GameState state)
{
    // display text on UI to indicate current game state
    switch (state) {
    case NORMAL:
        stateLabel->setText("Normal");
        break;
    case CHECK:
        stateLabel->setText("Check");
        break;
    case CHECKMATE:
        stateLabel->setText("Check Mate");
        break;
    case STALEMATE:
        stateLabel->setText("Stale Mate");
        break;
    default:
        break;
    }
}
