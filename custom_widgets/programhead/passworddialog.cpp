#include "icmessagebox.h"
#include "passworddialog.h"
#include "ui_passworddialog.h"
#include "icparameterssave.h"
#include <QKeyEvent>
#include "mainframe.h"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    buttonGroup_ = new QButtonGroup();
    InitButton();
//    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

}

PasswordDialog::~PasswordDialog()
{
    delete ui;
    delete buttonGroup_;
}

void PasswordDialog::on_buttonBox_accepted()
{
    if(ICParametersSave::Instance()->VerifyPassword(static_cast<ICParametersSave::OperationLevel>(buttonGroup_->checkedId()), ui->pwdEdit->text()))
    {
        emit LevelChanged(buttonGroup_->checkedId());
        ui->pwdEdit->clear();
    }
    else
    {
        ICMessageBox::ICWarning(this, tr("Error"), tr("Password is wrong!"));
    }
}

void PasswordDialog::ShowPwdEdit()
{
    switch(buttonGroup_->checkedId())
    {
    case 0:
        ui->pwdEdit->setEnabled(false);
        break;
    default:
        ui->pwdEdit->setEnabled(true);
    }
}

void PasswordDialog::showEvent(QShowEvent *e)
{
    ui->pwdEdit->clear();
   // PasswordDialog::setStyleSheet ("background-color: #000000;color: #ffffff;");
    QDialog::showEvent(e);
}

void PasswordDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        ui->retranslateUi(this);
    }
        break;
    default:
        break;
    }
}

void PasswordDialog::keyPressEvent(QKeyEvent *e)
{
//    if(e->key() == Qt::Key_F11)
//    {
//        ICKeyboardHandler::Instance()->Keypressed(ICKeyboard::VFB_Run);
//    }
//    else
//    {
    QKeyEvent* ke = new QKeyEvent(*e);
    qApp->postEvent(icMainFrame, ke);
//    this->accept();
//        this->accept();
//    }
}

void PasswordDialog::InitButton()
{
    buttonGroup_->addButton(ui->MachineOperatorPushButton,0);
    buttonGroup_->addButton(ui->MachineAdminPushButton,1);
    buttonGroup_->addButton(ui->AdvanceAdminPushButton,2);

    QList<QAbstractButton*> buttons = buttonGroup_->buttons();
    for(int i = 0; i != buttons.size(); ++i)
    {
        buttons[i]->setCheckable(true);
        connect(buttons.at(i),
                SIGNAL(clicked()),
                this,
                SLOT(ShowPwdEdit()));
    }
    buttonGroup_->setExclusive(true);
    ui->MachineOperatorPushButton->click();
}
