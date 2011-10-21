#ifndef ICHCSETTINGSFRAME_H
#define ICHCSETTINGSFRAME_H

#include <QFrame>
#include <QStackedLayout>

class QButtonGroup;

namespace Ui {
    class ICHCSettingsFrame;
}

class ICHCSettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ICHCSettingsFrame(QWidget *parent = 0);
    ~ICHCSettingsFrame();

    enum AxisSelect{None, AxisX, AxisY, AxisZ };

signals:
    void CurrentAxisChanged(QString currentAxisName, int axis);

protected:
    void changeEvent(QEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);

private slots:
    void on_axisZToolButton_clicked();
    void on_axisYToolButton_clicked();
    void on_axisXToolButton_clicked();
    void on_structDefButton_clicked();
    void LevelChanged(int level);
//    void SettingButtonClicked();

private:
    void InitHCSettingPage();
    void InitSignal();

    void ShowAxisSettingPage(QString currentAxisName, int axis);

private:
    Ui::ICHCSettingsFrame *ui;
    QWidget * axisSettingsPage_;
    QWidget * structDefPage_;
    QStackedLayout * centralStackedLayout_;
    QButtonGroup* buttonGroup_;
};

#endif // ICHCSETTINGSFRAME_H
