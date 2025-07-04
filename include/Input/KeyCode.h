//
// Created by jimmy on 2025/7/4.
//

#pragma once

enum class KeyCode {
    Unknown = 0,

    // 字母鍵
    A, B, C, D, E, F, G,
    H, I, J, K, L, M, N,
    O, P, Q, R, S, T, U,
    V, W, X, Y, Z,

    // 數字鍵（主鍵盤）
    Num0, Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8, Num9,

    // 控制鍵
    Escape,
    Space,
    Enter,
    Tab,
    Backspace,
    LeftShift,
    RightShift,
    LeftCtrl,
    RightCtrl,

    // 方向鍵
    LeftArrow,
    RightArrow,
    UpArrow,
    DownArrow,

    // 功能鍵
    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,
};