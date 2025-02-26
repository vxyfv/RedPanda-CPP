/*
 * Copyright (C) 2020-2022 Roy Qu (royqh1979@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "../systemconsts.h"
#include "../version.h"


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->lblTitle->setText(ui->lblTitle->text() + tr("Version: ") + DEVCPP_VERSION);

#ifdef  __GNUC__
    ui->lblContent->setText(ui->lblContent->text()
                            .arg(qVersion())
                            .arg(QString("GCC %1.%2")
                                 .arg(__GNUC__)
                                 .arg(__GNUC_MINOR__)
                                 ,__DATE__, __TIME__));
#else
    ui->lblContent->setText(ui->lblContent->text()
                            .arg(qVersion())
                            .arg("Non-GCC Compiler"
                                 ,__DATE__, __TIME__));
#endif
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
