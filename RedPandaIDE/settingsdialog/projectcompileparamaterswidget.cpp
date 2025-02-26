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
#include "projectcompileparamaterswidget.h"
#include "ui_projectcompileparamaterswidget.h"
#include "../mainwindow.h"
#include "../project.h"

ProjectCompileParamatersWidget::ProjectCompileParamatersWidget(const QString &name, const QString &group, QWidget *parent) :
    SettingsWidget(name,group,parent),
    ui(new Ui::ProjectCompileParamatersWidget)
{
    ui->setupUi(this);
}

ProjectCompileParamatersWidget::~ProjectCompileParamatersWidget()
{
    delete ui;
}

void ProjectCompileParamatersWidget::doLoad()
{
    ui->txtCCompiler->setPlainText(pMainWindow->project()->options().compilerCmd);
    ui->txtCPPCompiler->setPlainText(pMainWindow->project()->options().cppCompilerCmd);
    ui->txtLinker->setPlainText(pMainWindow->project()->options().linkerCmd);
}

void ProjectCompileParamatersWidget::doSave()
{
    pMainWindow->project()->options().compilerCmd = ui->txtCCompiler->toPlainText();
    pMainWindow->project()->options().cppCompilerCmd = ui->txtCPPCompiler->toPlainText();
    pMainWindow->project()->options().linkerCmd = ui->txtLinker->toPlainText();
    pMainWindow->project()->saveOptions();
}
