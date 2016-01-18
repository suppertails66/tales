#include "musicselectorwidget.h"
#include "ui_musicselectorwidget.h"
#include "gamedata/SoundID.h"
#include "util/StringConversion.h"

using namespace Tales;
using namespace Luncheon;

MusicSelectorWidget::MusicSelectorWidget(QWidget *parent) :
    QWidget(parent),
    number_(0),
    ui(new Ui::MusicSelectorWidget)
{
    ui->setupUi(this);

    for (int i = SoundIDs::musicLowerLimit;
         i < SoundIDs::musicUpperLimit;
         i++) {
        ui->trackComboBox->addItem(
                    (StringConversion::toString(i)
                     + ": "
                     + SoundIDs::nameOfMusicID(
                         static_cast<SoundIDs::SoundID>(i))).c_str(),
                    i);
    }
}

MusicSelectorWidget::~MusicSelectorWidget()
{
    delete ui;
}

void MusicSelectorWidget::on_trackComboBox_activated(int index)
{
    emit activated(number_, index + 0x80);
}

void MusicSelectorWidget::setNumber(int number__) {
    number_ = number__;

    ui->numberLabel->setText(
                (StringConversion::toString(number_)).c_str());
}

void MusicSelectorWidget::setCurrentTrack(int index) {
    ui->trackComboBox->setCurrentIndex(
                index - 0x80);
}

void MusicSelectorWidget::setLabel(const std::string& labelText) {
    ui->label->setText(labelText.c_str());
}
