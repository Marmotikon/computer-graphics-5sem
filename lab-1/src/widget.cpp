#include "widget.h"
#include "ui_widget.h"

QColor main_color; // есть цвета - HSV, RGB, CMYK

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{


    ui->setupUi(this);
    grLayout = new QGridLayout(this);
    qApp->installEventFilter(this);
    grLayout->setAlignment(Qt::AlignLeft);
    setMinimumSize(750,500);
    setMaximumSize(750, 500);
    cbUp = new QComboBox();
    cbCenter = new QComboBox();
    cbDown = new QComboBox();
    cbUp->addItems(slUp);
    cbCenter->addItems(slCenter);
    cbDown->addItems(slDown);
    cbUp->setCurrentIndex(-1);
    cbDown->setCurrentIndex(-1);
    cbCenter->setCurrentIndex(-1);

    GradientLabel = new QLabel(this);
    grLayout->addWidget(GradientLabel,0,0,8,6);
    GradientLabel->setMinimumSize(600,300);
    GradientLabel->setMaximumSize(600,300);
    colorRectangle = new QLabel(this);
    grLayout->addWidget(colorRectangle, 9,0);
    colorRectangle->setMinimumSize(600,10);
    colorRectangle->setMaximumSize(600,10);
    colorRectangle->setStyleSheet("QLabel{background-color:rgb(0,0,0);border:0px solid black;}");

    grLayout->addWidget(cbUp,0,6,1,3);
    grLayout->addWidget(cbCenter,5,6,1,3);
    grLayout->addWidget(cbDown,10,6,1,3);

    lbUpFirst = new QLabel("R:");
    lbUpSecond = new QLabel("G:");
    lbUpThird = new QLabel("B:");
    lbUpFourth = new QLabel("");
    leUpFirst = new QLineEdit(this);
    leUpSecond = new QLineEdit(this);
    leUpThird = new QLineEdit(this);
    leUpFourth = new QLineEdit(this);

    grLayout->addWidget(lbUpFirst, 1, 7);
    grLayout->addWidget(leUpFirst, 1,8);
    grLayout->addWidget(lbUpSecond, 2,7);
    grLayout->addWidget(leUpSecond,2,8);
    grLayout->addWidget(lbUpThird,3,7);
    grLayout->addWidget(leUpThird,3,8);
    grLayout->addWidget(lbUpFourth,4,7);
    grLayout->addWidget(leUpFourth,4,8);

    lbCenterFirst = new QLabel("L:");
    lbCenterSecond = new QLabel("A:");
    lbCenterThird = new QLabel("B:");
    lbCenterFourth = new QLabel("");
    leCenterFirst = new QLineEdit(this);
    leCenterSecond = new QLineEdit(this);
    leCenterThird = new QLineEdit(this);
    leCenterFourth = new QLineEdit(this);
    grLayout->addWidget(lbCenterFirst,6,7);
    grLayout->addWidget(leCenterFirst,6,8);
    grLayout->addWidget(lbCenterSecond,7,7);
    grLayout->addWidget(leCenterSecond,7,8);
    grLayout->addWidget(lbCenterThird,8,7);
    grLayout->addWidget(leCenterThird,8,8);
    grLayout->addWidget(lbCenterFourth,9,7);
    grLayout->addWidget(leCenterFourth,9,8);

    lbDownFirst = new QLabel("C:");
    lbDownSecond = new QLabel("M:");
    lbDownThird = new QLabel("Y:");
    lbDownFourth = new QLabel("K:");
    leDownFirst = new QLineEdit(this);
    leDownSecond = new QLineEdit(this);
    leDownThird = new QLineEdit(this);
    leDownFourth = new QLineEdit(this);
    grLayout->addWidget(lbDownFirst,11,7);
    grLayout->addWidget(leDownFirst,11,8);
    grLayout->addWidget(lbDownSecond,12,7);
    grLayout->addWidget(leDownSecond,12,8);
    grLayout->addWidget(lbDownThird,13,7);
    grLayout->addWidget(leDownThird,13,8);
    grLayout->addWidget(lbDownFourth,14,7);
    grLayout->addWidget(leDownFourth,14,8);

    cbUp->setCurrentText("RGB");
    cbCenter->setCurrentText("LAB");
    cbDown->setCurrentText("CMYK");
    Names_For_UpLabels("RGB");
    Names_For_CenterLabels("LAB");
    Names_For_DowntLabels("CMYK");
    setLayout(grLayout);


    sliderUp = new QSlider(this);
    sliderCenter = new QSlider(this);
    sliderDown = new QSlider(this);
    sliderUp->setOrientation(Qt::Vertical);
    sliderDown->setOrientation(Qt::Vertical);
    sliderCenter->setOrientation(Qt::Vertical);
    sliderUp->setRange(0, 255);
    sliderCenter->setRange(0, 255);
    sliderDown->setRange(0, 255);
    grLayout->addWidget(sliderUp,1,6,4,1);
    grLayout->addWidget(sliderCenter,6,6,4,1);
    grLayout->addWidget(sliderDown,11,6,4,1);

    connect(sliderUp, SIGNAL(valueChanged(int)), this, SLOT(red_change()));
    connect(sliderCenter, SIGNAL(valueChanged(int)), this, SLOT(red_change()));
    connect(sliderDown, SIGNAL(valueChanged(int)), this, SLOT(red_change()));

    connect(cbUp,SIGNAL(currentTextChanged(QString)),this,SLOT(Names_For_UpLabels(QString)));
    connect(cbCenter,SIGNAL(currentTextChanged(QString)),this,SLOT(Names_For_CenterLabels(QString)));
    connect(cbDown,SIGNAL(currentTextChanged(QString)),this,SLOT(Names_For_DowntLabels(QString)));

    connect(leUpFirst, SIGNAL(editingFinished()), this, SLOT(changed_UpFirst()));
    connect(leUpSecond, SIGNAL(editingFinished()), this, SLOT(changed_UpSecond()));
    connect(leUpThird, SIGNAL(editingFinished()), this, SLOT(changed_UpThird()));
    connect(leUpFourth, SIGNAL(editingFinished()), this, SLOT(changed_UpFourth()));

    connect(leCenterFirst, SIGNAL(editingFinished()), this, SLOT(changed_CenterFirst()));
    connect(leCenterSecond, SIGNAL(editingFinished()), this, SLOT(changed_CenterSecond()));
    connect(leCenterThird, SIGNAL(editingFinished()), this, SLOT(changed_CenterThird()));
    connect(leCenterFourth, SIGNAL(editingFinished()), this, SLOT(changed_CenterFourth()));

    connect(leDownFirst, SIGNAL(editingFinished()), this, SLOT(changed_DownFirst()));
    connect(leDownSecond, SIGNAL(editingFinished()), this, SLOT(changed_DownSecond()));
    connect(leDownThird, SIGNAL(editingFinished()), this, SLOT(changed_DownThird()));
    connect(leDownFourth, SIGNAL(editingFinished()), this, SLOT(changed_DownFourth()));

    connect(sliderUp, SIGNAL(valueChanged(int)), this, SLOT(slidersChanged()));
    connect(sliderCenter, SIGNAL(valueChanged(int)), this, SLOT(slidersChanged()));
    connect(sliderDown, SIGNAL(valueChanged(int)), this, SLOT(slidersChanged()));
}

Widget::~Widget()
{
    delete ui;
}

double Widget::getY() const
{
    return XYZ_Y;
}

double Widget::getX() const
{
    return XYZ_X;
}

double Widget::getZ() const
{
    return XYZ_Z;
}

void Widget::setX(double x)
{
    XYZ_X = x;
}

void Widget::setY(double x)
{
    XYZ_Y = x;
}

void Widget::setZ(double x)
{
    XYZ_Z = x;
}



void Widget::Names_For_UpLabels(QString text)
{
    leUpFourth->hide();
    if (text == "RGB") {
        lbUpFirst->setText("R:");
        lbUpSecond->setText("G:");
        lbUpThird->setText("B:");
        lbUpFourth->setText("");
    }
    if (text == "HSV") {
        lbUpFirst->setText("H:");
        lbUpSecond->setText("S:");
        lbUpThird->setText("V:");
        lbUpFourth->setText("");
    }
    if (text == "XYZ") {
        lbUpFirst->setText("X:");
        lbUpSecond->setText("Y:");
        lbUpThird->setText("Z:");
        lbUpFourth->setText("");
    }
    if (text == "CMYK") {
        lbUpFirst->setText("C:");
        lbUpSecond->setText("M:");
        lbUpThird->setText("Y:");
        lbUpFourth->setText("K:");
        leUpFourth->show();
    }

    setTexteverywhere();
}

void Widget::Names_For_CenterLabels(QString text)
{
    leCenterFourth->hide();
    if (text == "RGB") {
        lbCenterFirst->setText("R:");
        lbCenterSecond->setText("G:");
        lbCenterThird->setText("B:");
        lbCenterFourth->setText("");
    }
    if (text == "HSV") {
        lbCenterFirst->setText("H:");
        lbCenterSecond->setText("S:");
        lbCenterThird->setText("V:");
        lbCenterFourth->setText("");
    }
    if (text == "XYZ") {
        lbCenterFirst->setText("X:");
        lbCenterSecond->setText("Y:");
        lbCenterThird->setText("Z:");
        lbCenterFourth->setText("");
    }
    if (text == "CMYK") {
        lbCenterFirst->setText("C:");
        lbCenterSecond->setText("M:");
        lbCenterThird->setText("Y:");
        lbCenterFourth->setText("K:");
        leCenterFourth->show();
    }
    if (text == "HLS") {
        lbCenterFirst->setText("H:");
        lbCenterSecond->setText("L:");
        lbCenterThird->setText("S:");
        lbCenterFourth->setText("");
    }
    if (text == "LAB") {
        lbCenterFirst->setText("L:");
        lbCenterSecond->setText("A:");
        lbCenterThird->setText("B:");
        lbCenterFourth->setText("");
    }

    setTexteverywhere();
}

void Widget::Names_For_DowntLabels(QString text)
{
    leDownFourth->hide();
    if (text == "CMYK") {
        lbDownFirst->setText("C:");
        lbDownSecond->setText("M:");
        lbDownThird->setText("Y:");
        lbDownFourth->setText("K:");
        leDownFourth->show();
    }
    if (text == "HLS") {
        lbDownFirst->setText("H:");
        lbDownSecond->setText("L:");
        lbDownThird->setText("S:");
        lbDownFourth->setText("");
    }
    if (text == "LAB") {
        lbDownFirst->setText("L:");
        lbDownSecond->setText("A:");
        lbDownThird->setText("B:");
        lbDownFourth->setText("");
    }
    if (text == "HSV") {
        lbDownFirst->setText("H:");
        lbDownSecond->setText("S:");
        lbDownThird->setText("V:");
        lbDownFourth->setText("");
    }
    if (text == "RGB") {
        lbDownFirst->setText("R:");
        lbDownSecond->setText("G:");
        lbDownThird->setText("B:");
        lbDownFourth->setText("");
    }

    setTexteverywhere();
}

void Widget::changed_UpFirst()
{
    if (cbUp->currentText() == "RGB") {
        main_color.setRed(leUpFirst->text().toInt());
        color_convertation_from_QColor();
    }

    if (lbUpFirst->text() == "C:") {
        main_color.setCmyk(leUpFirst->text().toInt(), main_color.magenta(), main_color.yellow(), main_color.black());
        color_convertation_from_QColor();
    }

    if (lbUpFirst->text() == "H:") {
        main_color.setHsv(leUpFirst->text().toInt(), main_color.saturation(), main_color.value());
        color_convertation_from_QColor();
    }

    if (lbUpFirst->text() == "X:") {
        setX(lbUpFirst->text().toDouble());
        color_convertation_from_XYZ();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_UpSecond()
{
    if (lbUpSecond->text() == "G:") {
        main_color.setGreen(leUpSecond->text().toInt());
        color_convertation_from_QColor();
    }

    if (lbUpSecond->text() == "M:") {
        main_color.setCmyk(main_color.cyan(), leUpSecond->text().toInt(), main_color.yellow(), main_color.black());
        color_convertation_from_QColor();
    }

    if (lbUpSecond->text() == "S:") {
        main_color.setHsv(main_color.hue(), leUpSecond->text().toInt(), main_color.value());
        color_convertation_from_QColor();
    }

    if (cbCenter->currentText() == "XYZ") {
        setY(lbUpSecond->text().toDouble());
        color_convertation_from_XYZ();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_UpThird()
{
    if (lbUpThird->text() == "B:") {
        main_color.setBlue(leUpThird->text().toInt());
        color_convertation_from_QColor();
    }

    if (lbUpThird->text() == "Y:") {
        main_color.setCmyk(main_color.cyan(), main_color.magenta(), leUpThird->text().toInt(), main_color.black());
        color_convertation_from_QColor();
    }

    if (lbUpThird->text() == "V:") {
        main_color.setHsv(main_color.hue(), main_color.saturation(), leUpThird->text().toInt());
        color_convertation_from_QColor();
    }

    if (lbUpThird->text() == "Z:") {
        setZ(lbUpThird->text().toDouble());
        color_convertation_from_XYZ();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_UpFourth()
{
    main_color.setCmyk(main_color.cyan(), main_color.magenta(), main_color.yellow(), leUpFourth->text().toInt());
    color_convertation_from_QColor();
    setSlider();
    setTexteverywhere();
}

void Widget::changed_CenterFirst()
{
    if (cbCenter->currentText() == "LAB") {
        LAB_L = leCenterFirst->text().toDouble();
        color_convertation_from_LAB();
    }

    if (cbCenter->currentText() == "CMYK") {
        main_color.setCmyk(leCenterFirst->text().toInt(), main_color.magenta(), main_color.yellow(), main_color.black());
        color_convertation_from_QColor();
    }

    if (lbCenterFirst->text() == "X:") {
        setX(lbCenterFirst->text().toDouble());
        color_convertation_from_XYZ();
    }

    if (cbCenter->currentText() == "HSV") {
        main_color.setHsv(leCenterFirst->text().toInt(), main_color.saturation(), main_color.value());
        color_convertation_from_QColor();
    }

    if (lbCenterFirst->text() == "R:") {
        XYZ_X = leUpFirst->text().toDouble();
        XYZ_Y = leUpSecond->text().toDouble();
        XYZ_Z = leUpThird->text().toDouble();
        color_convertation_from_XYZ();
    }

    if (cbCenter->currentText() == "HLS") {
        main_color.setHsl(leCenterFirst->text().toDouble(), main_color.lightness(), main_color.hslSaturation());
        color_convertation_from_QColor();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_CenterSecond()
{
    if (cbCenter->currentText() == "LAB") {
        LAB_A = leCenterSecond->text().toDouble();
        color_convertation_from_LAB();
    }

    if (lbCenterSecond->text() == "M:") {
        main_color.setCmyk(main_color.cyan(),leCenterSecond->text().toInt(),  main_color.yellow(), main_color.black());
        color_convertation_from_QColor();
    }

    if (lbCenterSecond->text() == "Y:") {
        setY(lbCenterSecond->text().toDouble());
        color_convertation_from_XYZ();
    }

    if (cbCenter->currentText() == "HSV") {
        main_color.setHsv(main_color.hue(), leCenterSecond->text().toInt(), main_color.value());
        color_convertation_from_QColor();
    }

    if (lbCenterSecond->text() == "G:") {
        main_color.setGreen(leCenterSecond->text().toInt());
        color_convertation_from_QColor();
    }

    if (cbCenter->currentText() == "HLS") {
        main_color.setHsl(main_color.hslHue(), leCenterSecond->text().toDouble(), main_color.hslSaturation());
        color_convertation_from_QColor();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_CenterThird()
{
    if (cbCenter->currentText() == "LAB") {
        LAB_B = leCenterThird->text().toDouble();
        color_convertation_from_LAB();
    }

    if (cbCenter->currentText() == "CMYK") {
        main_color.setCmyk(main_color.cyan(), main_color.magenta(), leCenterThird->text().toInt(), main_color.black());
        color_convertation_from_QColor();
    }

    if (cbCenter->currentText() == "XYZ") {
        setZ(lbCenterThird->text().toDouble());
        color_convertation_from_XYZ();
    }

    if (cbCenter->currentText() == "HSV") {
        main_color.setHsv(main_color.hue(), main_color.saturation(), leCenterThird->text().toInt());
        color_convertation_from_QColor();
    }

    if (cbCenter->currentText() == "RGB") {
        main_color.setBlue(leCenterThird->text().toInt());
        color_convertation_from_QColor();
    }

    if (cbCenter->currentText() == "HLS") { // S
        main_color.setHsl(main_color.hslHue(), main_color.lightness(), leDownThird->text().toDouble());
        color_convertation_from_QColor();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_CenterFourth()
{
    main_color.setCmyk(main_color.cyan(), main_color.magenta(), main_color.yellow(), leCenterFourth->text().toInt());
    color_convertation_from_QColor();
    setSlider();
    setTexteverywhere();
}

void Widget::changed_DownFirst()
{
    if (cbDown->currentText() == "CMYK") {
        main_color.setCmyk(leDownFirst->text().toInt(), main_color.magenta(), main_color.yellow(), main_color.black());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "HLS") { // H
        main_color.setHsl(leDownFirst->text().toDouble(), main_color.saturation(), main_color.lightness());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "LAB") {
        LAB_L = leDownFirst->text().toDouble();
        color_convertation_from_LAB();
    }

    if (cbDown->currentText() == "HSV") {
        main_color.setHsv(leDownFirst->text().toInt(), main_color.saturation(), main_color.value());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "RGB") {
        main_color.setRed(leDownFirst->text().toInt());
        color_convertation_from_QColor();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_DownSecond()
{
    if (cbDown->currentText() == "CMYK") {
        main_color.setCmyk(main_color.cyan(),leDownSecond->text().toInt(),  main_color.yellow(), main_color.black());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "HLS") { // L
        main_color.setHsl(main_color.hslHue(), leDownSecond->text().toDouble(), main_color.hslSaturation());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "LAB") {
        LAB_A = leDownSecond->text().toDouble();
        color_convertation_from_LAB();
    }

    if (cbDown->currentText() == "HSV") {
        main_color.setHsv(main_color.hue(),leDownFirst->text().toInt(),  main_color.value());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "RGB") {
        main_color.setGreen(leDownSecond->text().toInt());
        color_convertation_from_QColor();
    }

    setSlider();
    setTexteverywhere();

}

void Widget::changed_DownThird()
{

    if (cbDown->currentText() == "CMYK") {
        main_color.setCmyk(main_color.cyan(),  main_color.magenta(),leDownThird->text().toInt(), main_color.black());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "HLS") { // это S
        main_color.setHsl(main_color.hslHue(), main_color.lightness(), leDownThird->text().toInt());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "LAB") {
        LAB_B = leDownThird->text().toDouble();
        color_convertation_from_LAB();
    }

    if (cbDown->currentText() == "HSV") {
        main_color.setHsv(main_color.hue(), main_color.saturation(), leDownSecond->text().toDouble());
        color_convertation_from_QColor();
    }

    if (cbDown->currentText() == "RGB") {
        main_color.setBlue(leDownThird->text().toInt());
        color_convertation_from_QColor();
    }

    setSlider();
    setTexteverywhere();
}

void Widget::changed_DownFourth()
{
    main_color.setCmyk(main_color.cyan(), main_color.magenta(), main_color.yellow(), leDownFourth->text().toInt());
    color_convertation_from_QColor();
    setSlider();
    setTexteverywhere();
}

void Widget::setTexteverywhere()
{
    if (cbUp->currentText() == "RGB") {
        leUpFirst->setText(QString::number(main_color.red()));
        leUpSecond->setText(QString::number(main_color.green()));
        leUpThird->setText(QString::number(main_color.blue()));
    }

    if (cbUp->currentText() == "HSV") {
        leUpFirst->setText(QString::number(main_color.hue()));
        leUpSecond->setText(QString::number(main_color.saturation()));
        leUpThird->setText(QString::number(main_color.value()));
    }

    if (cbUp->currentText() == "XYZ") {
        leUpFirst -> setText(QString::number(getX()));
        leUpSecond -> setText(QString::number(getY()));
        leUpThird -> setText(QString::number(getZ()));
    }

    if (cbUp->currentText() == "CMYK") {
        leUpFirst -> setText(QString::number(main_color.cyan()));
        leUpSecond->setText(QString::number(main_color.magenta()));
        leUpThird->setText(QString::number(main_color.yellow()));
        leUpFourth->setText(QString::number(main_color.black()));
    }

    if (cbCenter->currentText() == "LAB") {
        leCenterFirst -> setText(QString::number(LAB_L));
        leCenterSecond->setText(QString::number(LAB_A));
        leCenterThird->setText(QString::number(LAB_B));
    }

    if (cbCenter->currentText() == "CMYK") {
        leCenterFirst -> setText(QString::number(main_color.cyan()));
        leCenterSecond->setText(QString::number(main_color.magenta()));
        leCenterThird->setText(QString::number(main_color.yellow()));
        leCenterFourth->setText(QString::number(main_color.black()));
    }

    if (cbCenter->currentText() == "XYZ") {
        leCenterFirst -> setText(QString::number(getX()));
        leCenterSecond -> setText(QString::number(getY()));
        leCenterThird -> setText(QString::number(getZ()));
    }

    if (cbCenter->currentText() == "HSV") {
        leCenterFirst->setText(QString::number(main_color.hue()));
        leCenterSecond->setText(QString::number(main_color.saturation()));
        leCenterThird->setText(QString::number(main_color.value()));
    }

    if (cbCenter->currentText() == "RGB") {
        leCenterFirst->setText(QString::number(main_color.red()));
        leCenterSecond->setText(QString::number(main_color.green()));
        leCenterThird->setText(QString::number(main_color.blue()));
    }

    if (cbCenter->currentText() == "HLS") {
        leCenterFirst->setText(QString::number(main_color.hslHue()));
        leCenterSecond->setText(QString::number(main_color.lightness()));
        leCenterThird->setText(QString::number(main_color.hslSaturation()));
    }

    if (cbDown->currentText() == "CMYK") {
        leDownFirst->setText(QString::number(main_color.cyan()));
        leDownSecond->setText(QString::number(main_color.magenta()));
        leDownThird->setText(QString::number(main_color.yellow()));
        leDownFourth->setText(QString::number(main_color.black()));
    }

    if (cbDown->currentText() == "HLS") {
        leDownFirst->setText(QString::number(main_color.hslHue()));
        leDownSecond->setText(QString::number(main_color.lightness()));
        leDownThird->setText(QString::number(main_color.hslSaturation()));
    }

    if (cbDown->currentText() == "LAB") {
        leDownFirst -> setText(QString::number(LAB_L));
        leDownSecond->setText(QString::number(LAB_A));
        leDownThird->setText(QString::number(LAB_B));
    }

    if (cbDown->currentText() == "HSV") {
        leDownFirst->setText(QString::number(main_color.hue()));
        leDownSecond->setText(QString::number(main_color.saturation()));
        leDownThird->setText(QString::number(main_color.value()));
    }

    if (cbDown->currentText() == "RGB") {
        leDownFirst->setText(QString::number(main_color.red()));
        leDownSecond->setText(QString::number(main_color.green()));
        leDownThird->setText(QString::number(main_color.blue()));
    }
}

void Widget::red_change()
{
    main_color.setRed(sliderUp->value());
    main_color.setGreen(sliderCenter->value());
    main_color.setBlue(sliderDown->value());
    color_convertation_from_QColor();
    QString r = QString::number(main_color.red());
    QString g = QString::number(main_color.green());
    QString b = QString::number(main_color.blue());
    colorRectangle->setStyleSheet("QLabel{background-color:rgb("+r+
                                  ","+g+","+b+");}");
    setTexteverywhere();
}

void Widget::green_change()
{
    QString r = QString::number(sliderCenter->value());
}

void Widget::blue_change()
{
    QString r = QString::number(sliderCenter->value());
}

void Widget::slidersChanged()
{
}

void Widget::setSlider()
{
    sliderUp->setValue(main_color.red());
    sliderCenter->setValue(main_color.green());
    sliderDown->setValue(main_color.blue());
}

QColor Widget::getPixelAt(int x, int y)
{
    return grab(QRect(x, y, 1, 1)).toImage().pixelColor(0,0);
}

double F_RGB_XYZ(double x) {
    if (x>=0.04045) {
        return pow((x+0.055)/1.055, 2.4);
    }
    return x/12.92;
}

double F_XYZ_LAB(double x) {
    if (x >= 0.008856) {
        return pow(x, 1.0/3.0);
    }
    return 7.787 * x + 16.0 /(double) 116.0;
}

void Widget::color_convertation_from_QColor() {

    double Rn = F_RGB_XYZ(main_color.red() / 255.0);
    double Gn = F_RGB_XYZ(main_color.green() / 255.0);
    double Bn = F_RGB_XYZ(main_color.blue() / 255.0);

    double XYZ_X1 = 0.412453*Rn + 0.357580 * Gn + 0.180423 * Bn;
    double XYZ_Y1 = 0.212671*Rn + 0.715160 * Gn + 0.072169 * Bn;
    double XYZ_Z1 = 0.019334*Rn + 0.119193 * Gn + 0.950227 * Bn;

    XYZ_X1*=100.0;
    XYZ_Y1*=100.0;
    XYZ_Z1*=100.0;

    setX(XYZ_X1);
    setY(XYZ_Y1);
    setZ(XYZ_Z1);

    double X = XYZ_X1 / 95.047;
    double Y = XYZ_Y1 / 100.0;
    double Z = XYZ_Z1 / 108.883;

    LAB_L = 116 * F_XYZ_LAB(Y) - 16;
    LAB_A = 500 * (F_XYZ_LAB(X) - F_XYZ_LAB(Y));
    LAB_B = 200 * (F_XYZ_LAB(Y) - F_XYZ_LAB(Z));
}

double F_XYZ_RGB(double x) {
    if (abs(x)<0.0031308) {
        return 12.92 * x;
    }

    return 1.055 * pow(x, 0.41666) - 0.055;
}

void Widget::color_convertation_from_XYZ() {

    double X = getX();
    double Y = getY();
    double Z = getZ();

    double Rn = 3.2404542 * X - 1.5371385 * Y  - 0.4985314 * Z;
    double Gn = -0.9692660 * X + 1.8760108 * Y  + 0.0415560 * Z;
    double Bn = 0.0556434 * X - 0.2040259 * Y  + 1.0572252 * Z;

    Rn/=100.0;
    Gn/=100.0;
    Bn/=100.0;

    double R = F_XYZ_RGB(Rn);
    double G = F_XYZ_RGB(Gn);
    double B = F_XYZ_RGB(Bn);

    R*=255.0;
    G*=255.0;
    B*=255.0;

    main_color.setRed(round(R));
    main_color.setGreen(round(G));
    main_color.setBlue(round(B));

    LAB_L = 116 * F_XYZ_LAB(X/(double) 100.0)-16;
    LAB_A = 500 * (F_XYZ_LAB(X/95.047)-F_XYZ_LAB(Y/(double) 100.0));
    LAB_B = 200 * (F_XYZ_LAB(Y/(double) 100.0)- F_XYZ_LAB(Z/(double) 108.883));

}

double F_LAB_XYZ(double x) {
    if (pow(x,3)>=0.008856) {
        return pow(x,3);
    }
    return (x-16.0/116.0)/7.878;
}

void Widget::color_convertation_from_LAB() {
    double XYZ_X1 = F_LAB_XYZ(LAB_A/500.0+(LAB_L+16.0)/116.0) * 95.047;
    double XYZ_Y1 = F_LAB_XYZ((LAB_L+16.0)/116.0) * 100.0;
    double XYZ_Z1 = F_LAB_XYZ((LAB_L+16.0)/116.0-LAB_B/200) * 108.883;

    setX(XYZ_X1);
    setY(XYZ_Y1);
    setZ(XYZ_Z1);

    double Rn = 3.2406 * XYZ_X1 / 100 - 1.5372 * XYZ_Y1 / 100 - 0.4986 * XYZ_Z1 / 100;
    double Gn = -0.9689 * XYZ_X1 / 100 + 1.8758 * XYZ_Y1 / 100 + 0.0415 * XYZ_Z1 / 100;
    double Bn = 0.0557 * XYZ_X1 / 100 - 0.2040 * XYZ_Y1 / 100 + 1.0570 * XYZ_Z1 / 100;

    main_color.setRed(round(F_XYZ_RGB(Rn)*255));
    main_color.setGreen(round(F_XYZ_RGB(Gn)*255));
    main_color.setBlue(round(F_XYZ_RGB(Bn)*255));
}

void Widget::paintEvent(QPaintEvent *event) {

    QPixmap pix(GradientLabel->width(),GradientLabel->height());
    QPixmap pix2(GradientLabel->width(),GradientLabel->height());
    QPainter painter(&pix);
    QPainter painter2(&pix2);
    QLinearGradient gradl(0,0,pix.width(),0);
    gradl.setColorAt(0,Qt::red);
    gradl.setColorAt(0.18,Qt::yellow);
    gradl.setColorAt(0.36,Qt::green);
    gradl.setColorAt(0.54,Qt::blue);
    gradl.setColorAt(0.8,Qt::darkBlue);
    gradl.setColorAt(1,Qt::magenta);
    painter.setBrush(gradl);
    painter.drawRect(0,0,GradientLabel->width(),GradientLabel->height());
    GradientLabel->setPixmap(pix);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress && watched == GradientLabel) {
        QMouseEvent* cur = dynamic_cast<QMouseEvent*>(event);
        int x = cur->pos().x() + GradientLabel->x();
        int y = cur->pos().y() + GradientLabel->y();
        main_color = QWidget::grab(QRect(x,y,1,1)).toImage().pixelColor(0,0);
        setTexteverywhere();
        setSlider();
    }

    return false;
}


