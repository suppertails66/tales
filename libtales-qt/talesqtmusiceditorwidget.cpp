#include "talesqtmusiceditorwidget.h"
#include "ui_talesqtmusiceditorwidget.h"
#include "talesqtstatevar.h"
#include "gamedata/SoundID.h"

using namespace Tales;

TalesQtMusicEditorWidget::TalesQtMusicEditorWidget(QWidget *parent) :
    QWidget(parent),
    musicEditor_(appState_.editor().musicEditor()),
    ui(new Ui::TalesQtMusicEditorWidget)
{
    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setLayout(
                new QBoxLayout(QBoxLayout::TopToBottom,
                               ui->scrollAreaWidgetContents));
    ui->scrollAreaWidgetContents_2->setLayout(
                new QBoxLayout(QBoxLayout::TopToBottom,
                               ui->scrollAreaWidgetContents_2));

    for (int i = 0;
         i < musicEditor_.numAreaTracks();
         i++) {
        MusicSelectorWidget* widget = new MusicSelectorWidget(
                    ui->scrollAreaWidgetContents);
        widget->setNumber(i);
        widget->setLabel("Area");
        QObject::connect(widget,
                         SIGNAL(activated(int, int)),
                         this,
                         SLOT(areaMusicActivated(int, int)));
        ui->scrollAreaWidgetContents->layout()->addWidget(widget);
    }

    for (int i = 0;
         i < musicEditor_.numRadioTracks();
         i++) {
        MusicSelectorWidget* widget = new MusicSelectorWidget(
                    ui->scrollAreaWidgetContents_2);
        widget->setNumber(i);
        widget->setLabel("Track");
        QObject::connect(widget,
                         SIGNAL(activated(int, int)),
                         this,
                         SLOT(radioMusicActivated(int, int)));
        ui->scrollAreaWidgetContents_2->layout()->addWidget(widget);
    }

    refreshDisplay();
}

TalesQtMusicEditorWidget::~TalesQtMusicEditorWidget()
{
    delete ui;
}

void TalesQtMusicEditorWidget::refreshDisplay() {
    for (int i = 0;
         i < musicEditor_.numAreaTracks();
         i++) {
        dynamic_cast<MusicSelectorWidget*>(
                    ui->scrollAreaWidgetContents->layout()->itemAt(i)
                        ->widget())
                ->setCurrentTrack(musicEditor_.areaTrack(i));
    }

    for (int i = 0;
         i < musicEditor_.numRadioTracks();
         i++) {
        dynamic_cast<MusicSelectorWidget*>(
                    ui->scrollAreaWidgetContents_2->layout()->itemAt(i)
                        ->widget())
                ->setCurrentTrack(musicEditor_.radioTrack(i));
    }
}

void TalesQtMusicEditorWidget::areaMusicActivated(int trackNum, int value) {
    musicEditor_.setAreaTrack(trackNum, value);
}

void TalesQtMusicEditorWidget::radioMusicActivated(int trackNum, int value) {
    musicEditor_.setRadioTrack(trackNum, value);
}

