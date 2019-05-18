function createMenu(currentMenu) {
    var content = ""

    if (currentMenu.isTopLevel) {
        content += qsTr("void MainWindow::Create%1Menu() {\n").arg(currentMenu.title.replace("&", ""))
        content += qsTr("    QMenu *menu = m_actionManager->CreateMenu(tr(\"%1\"), menuBar());\n").arg(currentMenu.title);
        content += "    QMenu *parentMenu = nullptr;\n"
    }

    for (var i = 0; i < currentMenu.children.length; ++i) {
        var childMenu = currentMenu.children[i]
        if (childMenu.isAction) {
            content += qsTr("    menu->addAction(m_actionManager->GetAction(%1));\n").arg(childMenu.id)
        } else if (childMenu.isSeparator) {
            content += "    menu->addSeparator();\n"
        } else {
            content += "    {\n";
            content += "    parentMenu = menu;\n"
            content += qsTr("    menu = m_actionManager->CreateMenu(tr(\"%1\"), parentMenu);\n\n").arg(childMenu.title);
            content += createMenu(childMenu);
            content += "    menu = parentMenu;\n"
            content += "    }\n";
        }
    }

    if (currentMenu.isTopLevel)
        content += "}\n\n"
    return content;
}

function createActions(currentMenu) {
    var content = ""
    content += qsTr("void MainWindow::Create%1Actions()\n").arg(currentMenu.title.replace("&", ""))
    content += "{\n"
    content += "    QAction *action;\n\n"
    for (var i = 0; i < currentMenu.actions.length; ++i) {
        var action = currentMenu.actions[i]
        content += qsTr("    action = m_actionManager->CreateAction(%1, tr(\"%2\"), this);\n").arg(action.id).arg(action.title)
        if (action.checked) {
            content += "    action->setCheckable(true);\n"
            content += "    action->setChecked(true);\n"
        }
        if (action.toolTip !== "")
            content += qsTr("    action->setToolTip(tr(\"%1\"));\n").arg(action.toolTip)
        if (action.statusTip !== "")
            content += qsTr("    action->setStatusTip(tr(\"%1\"));\n").arg(action.statusTip)
    }
    content += "}\n\n"
    return content
}

function main() {
    for (var i = 0; i < menu.children.length; ++i) {
        var childMenu = menu.children[i]
        var doc = result.createDocument(qsTr("Create%1Menu").arg(childMenu.title.replace("&", "")))
        doc.content += createActions(childMenu)
        doc.content += createMenu(childMenu)
    }
}
