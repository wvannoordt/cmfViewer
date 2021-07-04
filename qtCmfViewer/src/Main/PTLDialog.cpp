#include "PTLDialog.h"
#include "ui_PTLDialog.h"
#include <QFileDialog>

PTLDialog::PTLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PTLDialog)
{
    ui->setupUi(this);
    lastSection = NULL;
}

void PTLDialog::ShowPTLPropertySection(PTL::PropertySection& section)
{
    auto& treeView = ui->dataTree;
    treeView->setColumnCount(1);
    QTreeWidgetItem* item = new QTreeWidgetItem();
    allitems.push_back(item);
    item->setText(0, QString::fromStdString(section.GetSectionName()));
    this->setWindowTitle(QString::fromStdString("PTL Dialog: " + section.GetSectionName()));
    treeView->addTopLevelItem(item);
    sectionMap[item] = &section;
    this->RecurseAddSectionItems(item, section);
    lastSection = &section;
    selectedSection = &section;
}

void PTLDialog::RecurseAddSectionItems(QTreeWidgetItem* currentItem, PTL::PropertySection& section)
{
    int count = 0;
    for (auto& tsec: section)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        allitems.push_back(item);
        item->setText(0, QString::fromStdString(tsec->GetSectionName()));
        currentItem->addChild(item);
        allitems.push_back(item);
        sectionMap[item] = tsec;
        this->RecurseAddSectionItems(item, *tsec);
        if(tsec->HasTemplateVariable()) tsec->SetValue(tsec->GetTemplateVariable()->GetDefaultValueString());
    }
}

PTLDialog::~PTLDialog()
{
    delete ui;
    for (auto& p:allitems)
    {
//        delete p; //revisit this
    }
}

void PTLDialog::on_openFileButton_clicked()
{
    QFileDialog dia;
    QString filename = dia.getOpenFileName();
    if (!filename.isNull() && lastSection != NULL)
    {
        PTL::PropertyTree tree;
        std::string filenameS = filename.toStdString();
        tree.Read(filenameS);
    }
}


void PTLDialog::on_dataTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    selectedSection = sectionMap[current];
    std::string propName = "Property Name: " + sectionMap[current]->GetSectionName();
    ui->propertyNameLabel->setText(QString::fromStdString(propName));

    std::string propDescrip = "Property Description: ";
    if (sectionMap[current]->HasTemplateVariable())
    {
        propDescrip += sectionMap[current]->GetTemplateVariable()->GetDescription();
        std::string defVal = sectionMap[current]->GetSectionValue();
        ui->valueEditBox->setText(QString::fromStdString(defVal));
    }
    else
    {
        std::string notext = "";
        ui->valueEditBox->setText(QString::fromStdString(notext));
    }
    ui->propertyDescriptionLabel->setText(QString::fromStdString(propDescrip));
}

bool PTLDialog::WasClosedWithConfirmation(void)
{
    return wasClosedWithDoneButton;
}

void PTLDialog::on_doneButton_clicked()
{
    wasClosedWithDoneButton = true;
    close();
}


void PTLDialog::on_valueEditBox_textChanged(const QString &arg1)
{
    std::string boxText = arg1.toStdString();
    if (selectedSection->HasTemplateVariable())
    {
        selectedSection->SetValue(boxText);
    }
}

