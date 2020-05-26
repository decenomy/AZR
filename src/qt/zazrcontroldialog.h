// Copyright (c) 2017-2019 The AEZORA developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZAZRCONTROLDIALOG_H
#define ZAZRCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zazr/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZAzrControlDialog;
}

class CZAzrControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZAzrControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZAzrControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZAzrControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZAzrControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZAzrControlDialog(QWidget *parent);
    ~ZAzrControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZAzrControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZAzrControlWidgetItem;

private Q_SLOTS:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZAZRCONTROLDIALOG_H
