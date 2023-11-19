        #ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QGridLayout *grLayout;
private:

    double XYZ_X = 0;
    double XYZ_Y = 0;
    double XYZ_Z = 0;

    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double);
    void setY(double);
    void setZ(double);

    double LAB_L = 0;
    double LAB_A = 0;
    double LAB_B = 0;

    double getL() const;
    double getA() const;
    double getB() const;
    void setL() const;
    void setA() const;
    void setB() const;

    void paintEvent(QPaintEvent *event);
    void color_convertation_from_QColor();
    void color_convertation_from_XYZ();
    void color_convertation_from_LAB();
    void color_convertation_from_HLS();

    QSlider *sliderUp;
    QSlider *sliderDown;
    QSlider *sliderCenter;
    QLabel *colorRectangle;

    Ui::Widget *ui;
    QComboBox *cbUp;
    QComboBox *cbCenter;
    QComboBox *cbDown;
    QStringList slUp = {"RGB", "CMYK", "HSV", "XYZ"};
    QStringList slCenter = {"LAB", "CMYK", "XYZ", "HSV", "RGB", "HLS"};
    QStringList slDown = {"CMYK", "HLS", "LAB", "HSV", "RGB"};

    QLabel *GradientLabel;

    QLineEdit *leUpFirst;
    QLineEdit *leUpSecond;
    QLineEdit *leUpThird;
    QLineEdit *leUpFourth;
    QLabel *lbUpFirst;
    QLabel *lbUpSecond;
    QLabel *lbUpThird;
    QLabel *lbUpFourth;

    QLineEdit *leCenterFirst;
    QLineEdit *leCenterSecond;
    QLineEdit *leCenterThird;
    QLineEdit *leCenterFourth;
    QLabel *lbCenterFirst;
    QLabel *lbCenterSecond;
    QLabel *lbCenterThird;
    QLabel *lbCenterFourth;

    QLineEdit *leDownFirst;
    QLineEdit *leDownSecond;
    QLineEdit *leDownThird;
    QLineEdit *leDownFourth;
    QLabel *lbDownFirst;
    QLabel *lbDownSecond;
    QLabel *lbDownThird;
    QLabel *lbDownFourth;

public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void Names_For_UpLabels(QString text);
    void Names_For_CenterLabels(QString text);
    void Names_For_DowntLabels(QString text);

    void changed_UpFirst();
    void changed_UpSecond();
    void changed_UpThird();
    void changed_UpFourth();

    void changed_CenterFirst();
    void changed_CenterSecond();
    void changed_CenterThird();
    void changed_CenterFourth();


    void changed_DownFirst();
    void changed_DownSecond();
    void changed_DownThird();
    void changed_DownFourth();

    void setTexteverywhere();
    void red_change();
    void green_change();
    void blue_change();
    void slidersChanged();

    void setSlider();
    QColor getPixelAt(int x, int y);

};
#endif // WIDGET_H
