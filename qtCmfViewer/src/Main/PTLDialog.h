#ifndef PTLDIALOG_H
#define PTLDIALOG_H

#include <QDialog>
#include "PTL.h"
#include <QTreeWidgetItem>

namespace Ui {
class PTLDialog;
}

class PTLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PTLDialog(QWidget *parent = nullptr);
    ~PTLDialog();
    void ShowPTLPropertySection(PTL::PropertySection& section);
    bool WasClosedWithConfirmation(void);

private slots:
    void on_openFileButton_clicked();

    void on_dataTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_doneButton_clicked();

    void on_valueEditBox_textChanged(const QString &arg1);

private:

    void RecurseAddSectionItems(QTreeWidgetItem* currentItem, PTL::PropertySection& section);

    Ui::PTLDialog *ui;
    std::vector<QTreeWidgetItem*> allitems;
    PTL::PropertySection* lastSection;
    PTL::PropertySection* selectedSection;
    std::map<QTreeWidgetItem*, PTL::PropertySection*> sectionMap;
    bool wasClosedWithDoneButton = false;
};

#endif // PTLDIALOG_H
