/*
  This file is part of Knut.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "document.h"

#include <pugixml.hpp>

namespace Core {

class QtUiDocument;

class QtUiWidget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(bool isRoot READ isRoot CONSTANT)

public:
    QtUiWidget(pugi::xml_node widget, bool isRoot = false, QObject *parent = nullptr);

    QString name() const;

    QString className() const;

    QString id() const;

    bool isRoot() const { return m_isRoot; }

public slots:
    void setName(const QString &newName);
    void setClassName(const QString &newClassName);

signals:
    void nameChanged(const QString &newName);
    void classNameChanged(const QString &newClassName);

private:
    friend QtUiDocument;
    pugi::xml_node m_widget;
    bool m_isRoot = false;
};

class QtUiDocument : public Document
{
    Q_OBJECT
    Q_PROPERTY(QVector<Core::QtUiWidget *> widgets READ widgets NOTIFY fileNameChanged)

public:
    explicit QtUiDocument(QObject *parent = nullptr);

    QVector<Core::QtUiWidget *> widgets() const { return m_widgets; }
    Q_INVOKABLE Core::QtUiWidget *findWidget(const QString &name) const;

public slots:
    void preview() const;

protected:
    bool doSave(const QString &fileName) override;
    bool doLoad(const QString &fileName) override;

private:
    friend QtUiWidget;
    pugi::xml_document m_document;
    QVector<QtUiWidget *> m_widgets;
};

} // namespace Core
