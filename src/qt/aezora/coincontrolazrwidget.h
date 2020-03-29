// Copyright (c) 2019 The AEZORA developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLAZRWIDGET_H
#define COINCONTROLAZRWIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlAzrWidget;
}

class CoinControlAzrWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlAzrWidget(QWidget *parent = nullptr);
    ~CoinControlAzrWidget();

private:
    Ui::CoinControlAzrWidget *ui;
};

#endif // COINCONTROLAZRWIDGET_H
