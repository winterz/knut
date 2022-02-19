#pragma once

#include "textrange.h"

#include "lsp/types.h"

#include <QVector>

namespace Core {

struct Symbol
{
    Q_GADGET
    Q_PROPERTY(QString name MEMBER name);
    Q_PROPERTY(QString description MEMBER description);
    Q_PROPERTY(Kind kind MEMBER kind);
    Q_PROPERTY(Core::TextRange range MEMBER range);
    Q_PROPERTY(Core::TextRange selectionRange MEMBER selectionRange);

public:
    enum Kind {
        File = static_cast<int>(Lsp::SymbolKind::File),
        Module = static_cast<int>(Lsp::SymbolKind::Module),
        Namespace = static_cast<int>(Lsp::SymbolKind::Namespace),
        Package = static_cast<int>(Lsp::SymbolKind::Package),
        Class = static_cast<int>(Lsp::SymbolKind::Class),
        Method = static_cast<int>(Lsp::SymbolKind::Method),
        Property = static_cast<int>(Lsp::SymbolKind::Property),
        Field = static_cast<int>(Lsp::SymbolKind::Field),
        Constructor = static_cast<int>(Lsp::SymbolKind::Constructor),
        Enum = static_cast<int>(Lsp::SymbolKind::Enum),
        Interface = static_cast<int>(Lsp::SymbolKind::Interface),
        Function = static_cast<int>(Lsp::SymbolKind::Function),
        Variable = static_cast<int>(Lsp::SymbolKind::Variable),
        Constant = static_cast<int>(Lsp::SymbolKind::Constant),
        String = static_cast<int>(Lsp::SymbolKind::String),
        Number = static_cast<int>(Lsp::SymbolKind::Number),
        Boolean = static_cast<int>(Lsp::SymbolKind::Boolean),
        Array = static_cast<int>(Lsp::SymbolKind::Array),
        Object = static_cast<int>(Lsp::SymbolKind::Object),
        Key = static_cast<int>(Lsp::SymbolKind::Key),
        Null = static_cast<int>(Lsp::SymbolKind::Null),
        EnumMember = static_cast<int>(Lsp::SymbolKind::EnumMember),
        Struct = static_cast<int>(Lsp::SymbolKind::Struct),
        Event = static_cast<int>(Lsp::SymbolKind::Event),
        Operator = static_cast<int>(Lsp::SymbolKind::Operator),
        TypeParameter = static_cast<int>(Lsp::SymbolKind::TypeParameter),
    };
    Q_ENUM(Kind)

    QString name;
    QString description;
    Kind kind;
    TextRange range;
    TextRange selectionRange;
};

} // namespace Core

Q_DECLARE_METATYPE(Core::Symbol)
Q_DECLARE_METATYPE(QVector<Core::Symbol>)