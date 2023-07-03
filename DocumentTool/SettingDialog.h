/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/04 00:31
*******************************************************************************/


#ifndef _SettingDialog_H_
#define _SettingDialog_H_

#include <QDialog>

namespace Ui{
    class SettingDialog;
}
class SettingDialog : public QDialog {
    Q_OBJECT
private:
    Ui::SettingDialog *ui;
public:
    explicit SettingDialog(QWidget * = nullptr);
    ~SettingDialog() override;

    void SetFount();
    void SetTheme();

    void ClearWindow();
};


#endif  // _SettingDialog_H_
