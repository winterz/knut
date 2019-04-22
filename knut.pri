CONFIG += c++17

KNUT_SOURCE_TREE = $$PWD/src
isEmpty(KNUT_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    KNUT_BUILD_TREE = $$clean_path($$OUT_PWD)
    KNUT_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

KNUT_APP_TARGET  = knut

KNUT_APP_PATH    = $$KNUT_BUILD_TREE/bin

INCLUDEPATH += $$KNUT_SOURCE_TREE
