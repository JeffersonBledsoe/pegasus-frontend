// Pegasus Frontend
// Copyright (C) 2018  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "utils/HashMap.h"
#include "utils/NoCopyNoMove.h"

#include <QString>
#include <QVector>
#include <functional>


enum class KeyEvent : unsigned char {
    ACCEPT,
    CANCEL,
    DETAILS,
    FILTERS,
    NEXT_PAGE,
    PREV_PAGE,
    PAGE_UP,
    PAGE_DOWN,
    MAIN_MENU,
    // internal only:
    LEFT = 64,
    RIGHT,
    UP,
    DOWN,
};

enum GamepadKeyId {
    A = 0x100000,
    B, X, Y,
    L1, L2, L3,
    R1, R2, R3,
    SELECT,
    START,
    GUIDE,
};
enum class ExtProvider : unsigned char {
    ES2,
    STEAM,
    GOG,
};


namespace appsettings {

struct General {
    const QString DEFAULT_LOCALE;
    const QString DEFAULT_THEME;

    bool portable;
    bool silent;
    bool fullscreen;
    QString locale;
    QString theme;

    General();
    NO_COPY_NO_MOVE(General)
};


class Keys {
public:
    Keys();
    NO_COPY_NO_MOVE(Keys)

    void add_key(KeyEvent, int);
    void del_key(KeyEvent, int);
    void clear(KeyEvent);
    void resetAll();

    const QVector<int>& at(KeyEvent) const;
    const QVector<int>& operator[](KeyEvent) const;

private:
    HashMap<KeyEvent, QVector<int>, EnumHash> m_event_keymap;
};


class Providers {
    struct ExtProviderInfo {
        bool enabled;
    };

public:
    Providers();
    NO_COPY_NO_MOVE(Providers)

    ExtProviderInfo& mut(ExtProvider);
    const ExtProviderInfo& at(ExtProvider) const;
    const ExtProviderInfo& operator[](ExtProvider) const;

private:
    HashMap<ExtProvider, ExtProviderInfo, EnumHash> m_providers;
};

} // namespace appsettings


struct AppSettings {
    static appsettings::General general;
    static appsettings::Providers ext_providers;
    static appsettings::Keys keys;

    static void load_config();
    static void save_config();
    static void parse_gamedirs(const std::function<void(const QString&)>&);
};
