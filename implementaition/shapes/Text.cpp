#include "Text.h"

std::string Text::getText() {
    return text;
}

void Text::setText(const std::string &txt) {
    text = txt;
}

size_t Text::size()
{
    return text.size();
}

void Text::print(std::ostream &o) const {
    o << "Text: " << text << std::endl;
}
