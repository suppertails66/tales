#include "coloreditorwidget.h"
#include "ui_coloreditorwidget.h"

ColorEditorWidget::ColorEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorEditorWidget)
{
    ui->setupUi(this);

    ui->rSlider->setLabel("Red");
    ui->gSlider->setLabel("Green");
    ui->bSlider->setLabel("Blue");

    QObject::connect(ui->rSlider,
                     SIGNAL(valueChanged(int)),
                     this,
                     SLOT(rSliderChanged(int)));
    QObject::connect(ui->gSlider,
                     SIGNAL(valueChanged(int)),
                     this,
                     SLOT(gSliderChanged(int)));
    QObject::connect(ui->bSlider,
                     SIGNAL(valueChanged(int)),
                     this,
                     SLOT(bSliderChanged(int)));
}

ColorEditorWidget::~ColorEditorWidget()
{
    delete ui;
}

void ColorEditorWidget::setColor(int r__, int g__, int b__) {
    ui->rSlider->setValue(r__);
    ui->gSlider->setValue(g__);
    ui->bSlider->setValue(b__);
}

int ColorEditorWidget::r() {
    return ui->rSlider->value();
}

int ColorEditorWidget::g() {
    return ui->gSlider->value();
}

int ColorEditorWidget::b() {
    return ui->bSlider->value();
}

void ColorEditorWidget::rSliderChanged(int r) {
    emit rChanged(r);
    emit colorChanged(ui->rSlider->value(),
                      ui->gSlider->value(),
                      ui->bSlider->value());
}

void ColorEditorWidget::gSliderChanged(int g) {
    emit gChanged(g);
    emit colorChanged(ui->rSlider->value(),
                      ui->gSlider->value(),
                      ui->bSlider->value());
}

void ColorEditorWidget::bSliderChanged(int b) {
    emit bChanged(b);
    emit colorChanged(ui->rSlider->value(),
                      ui->gSlider->value(),
                      ui->bSlider->value());
}
