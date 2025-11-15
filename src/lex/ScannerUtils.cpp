//
// Created by cipri on 11/15/2025.
//

#include "ScannerUtils.h"


int indexOf(const StrView &s, char c) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

Str ScannerUtils::getErrorOut(StrView strView) {
    int indexOfEoln = indexOf(strView, '\n');
    if (indexOfEoln != -1) {
        strView = strView.substr(0, indexOfEoln);
    }
    if (strView.length() > 200) {
        strView = strView.substr(0, 200);
    }

    Str result(strView);
    return result;
}
